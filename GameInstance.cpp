#include "GameInstance.h"
#include "MapLoader.h"
#include "Tank.h"
#include "NPCActor.h"
#include "HealthPack.h"
#include "Shield.h"
#include "WeaponPowerup.h"

cGameInstance::cGameInstance(I3DEngine* engine, string mapName, gameControls controls[5])
{
	mGameEngine = engine;
	mMyCamera = engine->CreateCamera(kManual);

	for (int i = 0; i < 5; i++)
	{
		mControls[i] = controls[i];
	}

	mTankMeshes.push_back(mGameEngine->LoadMesh("HoverTank08.x"));
	mTankMeshes.push_back(mGameEngine->LoadMesh("HoverTank04.x"));

	LoadMap(engine, mModels, mapName);

	mPlayer = new cPlayer();

	mGameEngine->StartMouseCapture();
	
	for (auto it = mModels.begin(); it != mModels.end() - 1; it++)
	{
		if ((*it).mType = NPCBase)
		{
			mEnemySpawnLoc.push_back({ (*it).mModel->GetX(),(*it).mModel->GetY(), (*it).mModel->GetZ() });
		}
		else if ((*it).mType = PlayerBase)
		{
			mPlayerSpawn = { (*it).mModel->GetX(),(*it).mModel->GetY(), (*it).mModel->GetZ() };
		}
	}

	mWaitingMusic = new cMusic("GameWaiting.wav");
	mBattleMusic = new cMusic("GameBattle.wav");

	mPlaying();
}


void cGameInstance::mPlaying()
{
	model_Vector tankChoices;
	actor_Vector npcActors;
	model_Vector spawnLocations;

	IFont* mGameFont = mGameEngine->LoadFont("Font2.bmp");
	
	spawnLocations.push_back(mGameEngine->LoadMesh("dummy.x")->CreateModel(100.0f, 0.0f, 100.0f));
	spawnLocations.push_back(mGameEngine->LoadMesh("dummy.x")->CreateModel(-100.0f, 0.0f, 100.0f));
	spawnLocations.push_back(mGameEngine->LoadMesh("dummy.x")->CreateModel(100.0f, 0.0f, -100.0f));
	spawnLocations.push_back(mGameEngine->LoadMesh("dummy.x")->CreateModel(-100.0f, 0.0f, -100.0f));

	tankChoices.push_back(mGameEngine->LoadMesh("HoverTank08.x")->CreateModel(0.0f, -50.0f, 0.0f));
	tankChoices.push_back(mGameEngine->LoadMesh("HoverTank04.x")->CreateModel(0.0f, -50.0f, 0.0f));
	//IModel* powerupTest = mGameEngine->LoadMesh("Cube.x")->CreateModel(0.0f, -50.0f, 0.0f);
	//powerupTest->SetSkin("testB.png");
	//powerupTest->Scale(0.2f);

	// tmp
	weaponData weapondata;
	weapondata.ammo = 10;
	weapondata.damage = 50.0;
	weapondata.reloadTime = 2;

	// Power ups 1 of each type
	HealthPack *health = new HealthPack(mGameEngine, "Cube.x", 100, 3, 100, "health.png", "HoverTank08 - health.jpg");
	ShieldPowerup *shield = new ShieldPowerup(mGameEngine, "Cube.x", 140, 3, 50, "shield.png", "HoverTank08 - shield.jpg");
	//weaponPowerUp *weapon = new weaponPowerUp(mGameEngine, "Cube.x", 5, 3, -20, "weaponup.png", "HoverTank08 - weapon.jpg", weapondata);

	const int MAXNPCs = 4;
	int numNPC = 0;

	float frameTime;
	float frameRate;

	mWaitingMusic->mStart();
	mBattleMusic->mSetVolume(50.0f);

	while (mGameEngine->IsRunning())
	{
		mGameEngine->DrawScene();

		frameTime = mGameEngine->Timer();
		frameRate = 1 / frameTime;

		mGameFont->Draw(std::to_string(frameRate), 100, 100, kBlack);

		if (!mPlayer->mIsActive())
		{
			// set camera to spawn menu position (looking over the map)
			mMyCamera->SetPosition(200.0f, 300.0f, 200.0f);
			mMyCamera->ResetOrientation();
			mMyCamera->RotateX(90.0f);
			/*powerupTest->SetPosition(-10.0f, 250.0f, -18.0f);
			powerupTest->RotateY(0.05f);*/

			// choosing tank to use
			for (int i = 0; i < tankChoices.size(); i ++)
			{
				tankChoices[i]->SetPosition(i * 10.0f, 250.0f, -18.0f);
				tankChoices[i]->RotateLocalY(5.0f * frameTime);
			}

			if (mGameEngine->KeyHit(Key_Return))
			{
				mPlayer->mSetTank(mTankMeshes[0], mGameEngine, { 200.0f, 0.0f, 150.0f });
				mPlayer->mAttachCamera(mMyCamera);
			}
		}
		else
		{
			if (!mPlayer->mGetTank()->mIsDestroyed())
			{
				mPlayer->mControlTank(mGameEngine, frameTime, mControls, npcActors, mBattleMusic, mWaitingMusic);
			}
			mGameFont->Draw(std::to_string(mPlayer->mGetTank()->mGetHP()), 100, 120, kBlack);

			// health power up
			if (health->CollisionDetection(mPlayer->mGetTank()->mGetModel()) < health->GetCollisionRadius())
			{
				health->Activate(mPlayer->mGetTank(), frameTime);
			}
			if (!health->Active())
			{
				health->AddCounter(1.0f * frameTime);
				health->ApplySkin(mPlayer->mGetTank()->mGetModel(), frameTime);
			}
			if (health->getTimer() >= health->RespawnTimer())
			{
				health->Respawn(mPlayer->mGetTank()->mGetModel());
			}
			health->GetModel()->RotateY(50.0f * frameTime);
			health->GetModel()->RotateX(50.0f * frameTime);

			// shield power up
			if (shield->CollisionDetection(mPlayer->mGetTank()->mGetModel()) < shield->GetCollisionRadius())
			{
				shield->Activate(mPlayer->mGetTank(), frameTime);
			}
			if (!shield->Active())
			{
				shield->AddCounter(1.0f * frameTime);
			}
			if (shield->getTimer() >= shield->RespawnTimer())
			{
				shield->Respawn(mPlayer->mGetTank()->mGetModel());
			}
			shield->GetModel()->RotateY(50.0f * frameTime);
			shield->GetModel()->RotateX(50.0f * frameTime);

			// test spawn locations
			// spawn NPC - TODO:
			// - Timer
			// - Locations
			// - Diff. Models
			// - Teams
			if (numNPC < MAXNPCs)
			{
				cNPCActor* tmpNPC = new cNPCActor();
				npcActors.push_back(tmpNPC);
				npcActors.back()->mSetTank(mTankMeshes[1], spawnLocations[numNPC], mGameEngine);
				npcActors.back()->mSetTarget(mPlayer->mGetTank());
				numNPC++;
			}

			// set NPC behaviour
			for (int i = 0; i < npcActors.size(); i++)
			{
				mGameFont->Draw(std::to_string(npcActors[i]->mGetTank()->mGetHP()), 100, (i * 20) + 140, kBlack);
				if (!npcActors[i]->mGetTank()->mIsDestroyed())
				{
					npcActors[i]->mHunt(frameTime, npcActors);
				}
			}

			for (auto it = mModels.begin(); it != mModels.end() - 1; it++)
			{
				if ((*it).mCollidable)
				{
					mPlayer->mGetTank()->mCollision((*it).mModel);

				}
			}
		}

		if (mGameEngine->KeyHit(Key_Escape))
		{
			return;
		}
	}
}
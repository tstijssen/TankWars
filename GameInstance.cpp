#include "GameInstance.h"
#include "MapLoader.h"
#include "Tank.h"
#include "NPCActor.h"

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

	const int MAXNPCs = 4;
	int numNPC = 0;

	float frameTime;
	float frameRate;

	while (mGameEngine->IsRunning())
	{
		mGameEngine->DrawScene();

		frameTime = mGameEngine->Timer();
		frameRate = 1 / frameTime;

		mGameFont->Draw(std::to_string(frameRate), 100, 100, kBlack);

		if (!mPlayer->mIsActive())
		{
			// set camera to spawn menu position (looking over the map)
			mMyCamera->SetPosition(0.0f, 300.0f, 0.0f);
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
				mPlayer->mSetTank(mTankMeshes[0], mGameEngine);
				mPlayer->mAttachCamera(mMyCamera);
			}
		}
		else
		{
			if (!mPlayer->mGetTank()->mIsDestroyed())
			{
				mPlayer->mControlTank(mGameEngine, frameTime, mControls, npcActors);
			}
			mGameFont->Draw(std::to_string(mPlayer->mGetTank()->mGetHP()), 100, 120, kBlack);

			for (auto it = mModels.begin(); it != mModels.end() - 1; it++)
			{
				mPlayer->mGetTank()->mCollision((*it));
			}


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

		}

		if (mGameEngine->KeyHit(Key_Escape))
		{
			mGameEngine->Stop();
			return;
		}
	}
}
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
	tank_Vector npcTanks;
	actor_Vector npcActors;

	tankChoices.push_back(mGameEngine->LoadMesh("HoverTank08.x")->CreateModel(0.0f, -50.0f, 0.0f));
	tankChoices.push_back(mGameEngine->LoadMesh("HoverTank04.x")->CreateModel(0.0f, -50.0f, 0.0f));
	IModel* powerupTest = mGameEngine->LoadMesh("Cube.x")->CreateModel(0.0f, -50.0f, 0.0f);
	powerupTest->SetSkin("testB.png");
	powerupTest->Scale(0.2f);

	const int MAXNPCs = 1;
	int numNPC = 0;

	float frameTime;
	float frameRate;

	while (mGameEngine->IsRunning())
	{
		mGameEngine->DrawScene();

		frameTime = mGameEngine->Timer();
		frameRate = 1 / frameTime;

		if (!mPlayer->mIsActive())
		{
			// set camera to spawn menu position (looking over the map)
			mMyCamera->SetPosition(0.0f, 300.0f, 0.0f);
			mMyCamera->ResetOrientation();
			mMyCamera->RotateX(90.0f);
			powerupTest->SetPosition(-10.0f, 250.0f, -18.0f);
			powerupTest->RotateY(0.05f);

			// choosing tank to use
			for (int i = 0; i < tankChoices.size(); i ++)
			{
				tankChoices[i]->SetPosition(i * 10.0f, 250.0f, -18.0f);
				tankChoices[i]->RotateLocalY(0.05f);
			}

			if (mGameEngine->KeyHit(Key_Return))
			{
				mPlayer->mSetTank(mTankMeshes[0], mGameEngine);
				mPlayer->mAttachCamera(mMyCamera);
			}
		}
		else
		{
			mPlayer->mControlTank(mGameEngine, frameTime, mControls);
			for (auto it = mModels.begin(); it != mModels.end() - 1; it++)
			{
				mPlayer->mGetTank()->mCollision((*it));
			}

			// spawn NPC - TODO:
			// - Timer
			// - Locations
			// - Diff. Models
			// - Teams
			if (numNPC < MAXNPCs)
			{
				cNPCActor* tmpNPC = new cNPCActor();
				npcActors.push_back(tmpNPC);
				numNPC++;
				npcActors.back()->mSetTank(mTankMeshes[1], mGameEngine);
				npcActors.back()->mSetTarget(mPlayer->mGetTank());
			}

			// set NPC behaviour
			for (int i = 0; i < npcActors.size(); i++)
			{
				npcActors[i]->mHunt(frameTime);

			}

		}

		if (mGameEngine->KeyHit(Key_Escape))
		{
			mGameEngine->Stop();
			return;
		}
	}
}
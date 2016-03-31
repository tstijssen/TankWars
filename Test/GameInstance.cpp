#include "GameInstance.h"
#include "MapLoader.h"
#include "Tank.h"

cGameInstance::cGameInstance(I3DEngine* engine, string mapName)
{
	mGameEngine = engine;
	mMyCamera = engine->CreateCamera(kManual);

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

	tankChoices.push_back(mGameEngine->LoadMesh("HoverTank08.x")->CreateModel(0.0f, -50.0f, 0.0f));
	tankChoices.push_back(mGameEngine->LoadMesh("HoverTank04.x")->CreateModel(0.0f, -50.0f, 0.0f));

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

			mPlayer->mControlTank(mGameEngine, frameTime, mModels);

		}

		if (mGameEngine->KeyHit(Key_Escape))
		{
			mGameEngine->Stop();
			return;
		}
	}
}
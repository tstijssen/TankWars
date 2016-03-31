#include "Player.h"

cPlayer::cPlayer()
{
	mName = "PLAYER";
	mScore = 0;
	mActive = false;
	mTeamNumber = 0;
}

bool cPlayer::mIsActive()
{
	return mActive;
}

void cPlayer::mSetTank(IMesh* newTank, I3DEngine* engine)
{
	if (!mActive)
	{
		mPlayerTank = new cTank(newTank, engine);
		mActive = true;
	}
}

void cPlayer::mSetInactive()
{
	mActive = false;
}

void cPlayer::mControlTank(I3DEngine* engine, float frameTime, model_Vector& mapModels)
{
	float prevX = 0.0f;
	float prevZ = 0.0f;

	mPlayerTank->mRotateTurret(engine->GetMouseMovementX() * 20.0f, engine->GetMouseMovementY() * 20.0f, frameTime);

	if (engine->KeyHit(Mouse_LButton))
	{
		mPlayerTank->mShoot(frameTime);
	}

	for (auto it = mapModels.begin(); it != mapModels.end() - 1; it++)
	{
		mPlayerTank->mCollision((*it));
	}

	prevX = mPlayerTank->mGetModel()->GetX();
	prevZ = mPlayerTank->mGetModel()->GetZ();

	mPlayerTank->mUpdate(frameTime);

	if (engine->KeyHeld(Key_Space))
	{
		mPlayerTank->mBoostMove(frameTime);
	}
	else if (engine->KeyHeld(Key_W) || engine->KeyHeld(Key_S) || engine->KeyHeld(Key_A) || engine->KeyHeld(Key_D))
	{
		if (engine->KeyHeld(Key_W))
		{
			mPlayerTank->mMove(20.0f, 0.0f, frameTime);

		}
		if (engine->KeyHeld(Key_S))
		{
			mPlayerTank->mMove(-20.0f, 0.0f, frameTime);
		}
		if (engine->KeyHeld(Key_A))
		{
			mPlayerTank->mMove(0.0f, -20.0f, frameTime);
		}
		if (engine->KeyHeld(Key_D))
		{
			mPlayerTank->mMove(0.0f, 20.0f, frameTime);
		}
	}
	else
	{
		mPlayerTank->mStopEngine();
	}
}

void cPlayer::mAttachCamera(ICamera* camera)
{
	camera->AttachToParent(mPlayerTank->mGetModel());
	camera->SetLocalPosition(0.0f, 20.0f, -30.0f);
	camera->ResetOrientation();
	camera->RotateX(30.0f);
}
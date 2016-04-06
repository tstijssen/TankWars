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
		mPlayerTank = new cPlayerTank(newTank, engine);
		mActive = true;
	}
}

void cPlayer::mSetInactive()
{
	mActive = false;
}

void cPlayer::mControlTank(I3DEngine* engine, float frameTime, gameControls controls[5])
{
	float prevX = 0.0f;
	float prevZ = 0.0f;

	mPlayerTank->mRotateTurret(engine->GetMouseMovementX() * 20.0f, engine->GetMouseMovementY() * 20.0f, frameTime);

	if (engine->KeyHit(controls[4].keyBind))
	{
		mPlayerTank->mShoot(frameTime);
	}

	prevX = mPlayerTank->mGetModel()->GetX();
	prevZ = mPlayerTank->mGetModel()->GetZ();

	mPlayerTank->mUpdate(frameTime);

	if (engine->KeyHeld(controls[0].keyBind) || engine->KeyHeld(controls[1].keyBind) || engine->KeyHeld(controls[2].keyBind) || engine->KeyHeld(controls[3].keyBind))
	{
		if (engine->KeyHeld(controls[0].keyBind))
		{
			mPlayerTank->mMove(20.0f, 0.0f, frameTime);
		}
		if (engine->KeyHeld(controls[1].keyBind))
		{
			mPlayerTank->mMove(-20.0f, 0.0f, frameTime);
		}
		if (engine->KeyHeld(controls[2].keyBind))
		{
			mPlayerTank->mMove(0.0f, -20.0f, frameTime);
		}
		if (engine->KeyHeld(controls[3].keyBind))
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
	camera->SetLocalPosition(0.0f, 60.0f, -15.0f);
	camera->ResetOrientation();
	camera->RotateX(65.0f);
}

ITank* cPlayer::mGetTank()
{
	return mPlayerTank;
}
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

void cPlayer::mSetTank(IMesh* newTank, I3DEngine* engine, sPosition spawn)
{
	if (!mActive)
	{
		mPlayerTank = new cPlayerTank(newTank, engine, spawn.x, spawn.y, spawn.z);
		mActive = true;
	}
}

void cPlayer::mRespawn(sPosition spawn)
{
	mPlayerTank->mRespawn(spawn);
	mActive = true;
}

void cPlayer::mControlTank(I3DEngine* engine, float frameTime, gameControls controls[5], actor_Vector NPCs, cMusic* battleActivate, cMusic* waitingDeactivate)
{
	float prevX = 0.0f;
	float prevZ = 0.0f;
		//New key press system 
	bool moveForwardKeyPressed = false;
	bool moveBackKeyPressed = false;
	bool moveLeftKeyPressed = false;
	bool moveRightKeyPressed = false;
	bool fireKeyPressed = false;

	moveForwardKeyPressed = (engine->KeyHeld(controls[0].keyBind));
	moveBackKeyPressed = (engine->KeyHeld(controls[1].keyBind));
	moveLeftKeyPressed = (engine->KeyHeld(controls[2].keyBind));
	moveRightKeyPressed = (engine->KeyHeld(controls[3].keyBind));
	fireKeyPressed = (engine->KeyHeld(controls[4].keyBind));

	mPlayerTank->mRotateTurret(engine->GetMouseMovementX() * 20.0f, engine->GetMouseMovementY() * 20.0f, frameTime);

	if (fireKeyPressed)
	{
		mPlayerTank->mShoot(frameTime);
		battleActivate->mStart();
		waitingDeactivate->mStop();
	}

	prevX = mPlayerTank->mGetModel()->GetX();
	prevZ = mPlayerTank->mGetModel()->GetZ();

	mPlayerTank->mUpdate(frameTime, NPCs);

	if (moveForwardKeyPressed || moveBackKeyPressed || moveLeftKeyPressed || moveRightKeyPressed)
	{
		if (moveForwardKeyPressed)
		{
			mPlayerTank->mMove(20.0f, 0.0f, frameTime);
		}
		if (moveBackKeyPressed)
		{
			mPlayerTank->mMove(-20.0f, 0.0f, frameTime);
		}
		if (moveLeftKeyPressed)
		{
			mPlayerTank->mMove(0.0f, -40.0f, frameTime);
		}
		if (moveRightKeyPressed)
		{
			mPlayerTank->mMove(0.0f, 40.0f, frameTime);
		}
	}
	else
	{
		mPlayerTank->mStopEngine();
	}

	if (mPlayerTank->mIsDestroyed())
	{
		mActive = false;
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

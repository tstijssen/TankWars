#include "Tank.h"

	cTank::cTank(IMesh* tankMesh, int teamNumber, ICamera* camera)
	{
		mTankModel = tankMesh->CreateModel(0.0f, 0.5f, 0.0f);
		mTeamNumber = teamNumber;
		mTurret = mTankModel->GetNode(4);
		camera->AttachToParent(mTankModel);
		tankSounds = new cSoundTank;
	}

	void cTank::mMove(float movement, float rotation, float frameTime)
	{
		mTankModel->MoveLocalZ(movement * frameTime);
		mTankModel->RotateY((rotation) * frameTime);
		tankSounds->soundEngine(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	};


	void cTank::mRotateTurret(float rotation, float frameTime)
	{
		mTurret->RotateY(rotation * frameTime);
	}
	void cTank::mStopEngine()
	{
		tankSounds->stopEngine();
	}
	void cTank::mBoostMove(float frameTime)
	{
		mTankModel->MoveLocalZ(50.0f * frameTime);
		tankSounds->soundBoost(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	}
	void mDestroy();
	int mGetTeam();
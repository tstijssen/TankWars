

#include "ScoutTank.h"

cScoutTank::cScoutTank(tle::I3DEngine* engine, float position[3], int team)
{
	mScoutTankMesh = engine->LoadMesh("scoutMesh.x");

	if (mScoutTankMesh)
	{
		mTeamNumber = team;
		mTankModel = mScoutTankMesh->CreateModel(position[0], position[1], position[2]);
		mTurret = mTankModel->GetNode(2);
	}
}
void cScoutTank::mMove(float movement, float rotation, float frameTime)
{
	mTankModel->MoveLocalZ((movement * mSpeed) * frameTime);
	mTankModel->RotateY((rotation * mSpeed) * frameTime);
}

void cScoutTank::mRotateTurret(float rotation, float frameTime)
{
	mTurret->RotateY(rotation * frameTime);
}
void cScoutTank::mBoostMove(float frameTime)
{
	mSpeed *= mSpeed;
	tankSounds->soundBoost(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
}
void cScoutTank::mAttachCamera(tle::ICamera* camera)
{
	camera->AttachToParent(mTankModel);
}
void cScoutTank::mDestroy()
{

}

int cScoutTank::mGetTeam()
{
	return mTeamNumber;
}
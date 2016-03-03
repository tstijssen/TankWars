#include "Tank.h"

	cTank::cTank(IMesh* tankMesh, int teamNumber, ICamera* camera, I3DEngine* engine)
	{
		IMesh* tmp = engine->LoadMesh("Marble.x");

		mDummy = tmp->CreateModel(0.0f, 0.5f, 30.0f);


		// for projectiles
		// have struct of model & bool if fired or not
		// if not fired allow for rotation
		//

		mTankModel = tankMesh->CreateModel(0.0f, 0.5f, 0.0f);
		mTeamNumber = teamNumber;

		mDummy->LookAt(mTankModel);

		mTurret = mTankModel->GetNode(4);
		camera->AttachToParent(mTankModel);
		tankSounds = new cSoundTank;
		mProjectileMesh = engine->LoadMesh("Marble.x");
	}

	void cTank::mMove(float movement, float rotation, float frameTime)
	{
		mTankModel->MoveLocalZ(movement * frameTime);
		mTankModel->RotateY((rotation) * frameTime);
		tankSounds->soundEngine(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	};

	void cTank::mRotateTurret(float Xrotation, float Zrotation, float frameTime)
	{
		mDummy->LookAt(mTankModel);
		mTurret->LookAt(mDummy);

		mDummy->Move(Xrotation * frameTime, 0.0f, -Zrotation * frameTime);
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
	void cTank::mUpdate(float frameTime)
	{
		for (auto it = vProjectiles.begin(); it != vProjectiles.end(); it++)
		{
			(*it)->DetachFromParent();
			(*it)->MoveLocalZ(mSpeed * frameTime);
		}
	}
	void cTank::mShoot(float frameTime)
	{
		IModel* tmp;
		tmp = mProjectileMesh->CreateModel(mTurret->GetX(), mTurret->GetY(), mTurret->GetZ());
		tmp->AttachToParent(mDummy);
		tmp->Scale(0.2f);
		vProjectiles.push_back(tmp);
	}
	void cTank::mCollision(IModel* building)
	{
		float x, z;

		float dist = 0.0f;

		x = mTankModel->GetX() - building->GetX();
		z = mTankModel->GetZ() - building->GetZ();

		dist = sqrt(x*x + z*z);

		if (dist < 5.0f)
		{
			building->SetY(10.0f);
		}

	}

	void mDestroy();
	int mGetTeam();
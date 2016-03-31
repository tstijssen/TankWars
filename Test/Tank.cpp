#include "Tank.h"

	cTank::cTank(IMesh* tankMesh, I3DEngine* engine)
	{
		IMesh* tmp = engine->LoadMesh("Explosion.x");

		mDummy = tmp->CreateModel(0.0f, 0.5f, 30.0f);
		mDummy->SetSkin("crosshair10.png");
		mDummy->Scale(10.0f);

		// for projectiles
		// have struct of model & bool if fired or not
		// if not fired allow for rotation
		//

		tmp = engine->LoadMesh("Dummy.x");

		mTankModel = tankMesh->CreateModel(0.0f, 0.5f, 0.0f);

		mFrontNode = tmp->CreateModel(0.0f, 0.5f, 2.0f);
		mBackNode = tmp->CreateModel(0.0f, 0.5f, -2.0f);
		mFrontNode->AttachToParent(mTankModel);
		mBackNode->AttachToParent(mTankModel);

		mDummy->LookAt(mTankModel);

		mTurret = mTankModel->GetNode(4);
		tankSounds = new cSoundTank;
		mProjectileMesh = engine->LoadMesh("Marble.x");
	}

	void cTank::mMove(float movement, float rotation, float frameTime)
	{
		if (mMovement < 10.0f || mMovement > -10.0f)
		{
			mMovement += movement * frameTime;
		}

		mTankModel->RotateY((rotation) * frameTime);

		mDummy->RotateY((rotation)* frameTime);
		tankSounds->soundEngine(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	};

	void cTank::mRotateTurret(float Xrotation, float Zrotation, float frameTime)
	{
		mTurret->LookAt(mDummy);

		mDummy->MoveLocal(-Xrotation * frameTime, 0.0f, Zrotation * frameTime);
	}

	void cTank::mStopEngine()
	{
		tankSounds->stopEngine();
	}

	void cTank::mBoostMove(float frameTime)
	{
		mTankModel->MoveLocalZ(mMovement * frameTime);
		tankSounds->soundBoost(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	}

	void cTank::mUpdate(float frameTime)
	{
		mPrevX = mTankModel->GetX();
		mPrevZ = mTankModel->GetZ();

		mDummy->MoveLocalZ(-mMovement * frameTime);
		mTankModel->MoveLocalZ(mMovement * frameTime);
		for (auto it = vProjectiles.begin(); it != vProjectiles.end(); it++)
		{
			(*it)->MoveLocalZ(mSpeed * frameTime);
		}
	}
	void cTank::mShoot(float frameTime)
	{
		IModel* tmp;
		tmp = mProjectileMesh->CreateModel(mTurret->GetX(), mTurret->GetY() + 0.5f, mTurret->GetZ());
		tmp->LookAt(mDummy);
		tmp->Scale(0.2f);
		vProjectiles.push_back(tmp);
	}
	void cTank::mCollision(IModel* building)
	{
		float fX, fZ, bX, bZ;
		fX = mFrontNode->GetX() - building->GetX();
		fZ = mFrontNode->GetZ() - building->GetZ();
		bX = mBackNode->GetX() - building->GetX();
		bZ = mBackNode->GetZ() - building->GetZ();

		float frontDist = (fX*fX + fZ*fZ);
		float backDist = (bX*bX + bZ*bZ);

		if (frontDist < 4.0f || backDist < 4.0f)
		{
			mTankModel->SetPosition(mPrevX, 0.0f, mPrevZ);
			mMovement = 0.0f;
		}

		//for (int i = 0; i < vProjectiles.size(); i++)
		//{
		//	x = vProjectiles[i]->GetX() - building->GetX();
		//	z = vProjectiles[i]->GetZ() - building->GetZ();

		//	dist = sqrt(x*x + z*z);

		//	if (dist < 5.0f)
		//	{
		//		building->SetY(10.0f);
		//	}
		//}
	}

	IModel* cTank::mGetModel()
	{
		return mTankModel;
	}

	void mDestroy();
	int mGetTeam();
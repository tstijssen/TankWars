#include "Tank.h"
#include "NPCActor.h"

cNPCTank::cNPCTank(IMesh* tankMesh, IModel* spawnLocation, I3DEngine* engine)
{
	mTankModel = tankMesh->CreateModel(spawnLocation->GetX(), 0.5f, spawnLocation->GetZ());
	mFrontNode = engine->LoadMesh("Dummy.x")->CreateModel(spawnLocation->GetX(), 0.5f, spawnLocation->GetZ() + 2.0f);
	mBackNode = engine->LoadMesh("Dummy.x")->CreateModel(spawnLocation->GetX(), 0.5f, spawnLocation->GetZ() - 2.0f);
	mFrontNode->AttachToParent(mTankModel);
	mBackNode->AttachToParent(mTankModel);

	mTurret = mTankModel->GetNode(4);
	tankSounds = new cSoundTank;
	mProjectileMesh = engine->LoadMesh("Marble.x");


	for (int i = 0; i < 1; i++)
	{
		sProjectiles tmp;
		tmp.mModel = mProjectileMesh->CreateModel(0.0f, -5.0f, 0.0f);
		tmp.mVectorNumber = i;
		vProjectiles.push_back(tmp);
		vProjectiles.back().mModel->Scale(0.2f);
	}
}

void cNPCTank::mMove(float movement, float rotation, float frameTime)
{
	if (mDistanceToTarget > 800.0f)	// tmp movement range
	{
		if (mMovement < 10.0f)
		{
			mMovement += movement * frameTime;
		}
	}
	else
	{
		if (mMovement > 0.0f)
		{
			mMovement -= movement * frameTime;
		}
	}

	mTankModel->RotateY((rotation)* frameTime);

	tankSounds->soundEngine(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
};

void cNPCTank::mRotateTurret(float Xrotation, float Zrotation, float frameTime)
{

}

void cNPCTank::mStopEngine()
{
	tankSounds->stopEngine();
}

void cNPCTank::mSetTarget(ITank* target)
{
	mTarget = target;
}

void cNPCTank::mUpdate(float frameTime, actor_Vector NPCs)
{
	mPrevX = mTankModel->GetX();
	mPrevZ = mTankModel->GetZ();

	float x, z;

	x = mTankModel->GetX() - mTarget->mGetModel()->GetX();
	z = mTankModel->GetZ() - mTarget->mGetModel()->GetZ();

	mDistanceToTarget = (x * x + z * z);
	if (mDistanceToTarget < 3000.0f)	// temporary engagement range
	{
		mShoot(frameTime);
	}

	// collision between NPC's and player

	float distanceToShot = (mPrevX * mPrevX + mPrevZ * mPrevZ);
	mTankModel->MoveLocalZ(mMovement * frameTime);

	for (auto it = vProjectiles.begin(); it != vProjectiles.end(); it++)
	{
		if ((*it).mFired)
		{
			(*it).mModel->MoveLocalZ(mSpeed * frameTime);

			float x = mPrevX - (*it).mModel->GetX();
			float z = mPrevZ - (*it).mModel->GetZ();

			float distanceToShot = (x * x) + (z * z);

			if (distanceToShot > 5000.0f)	// tmp max shot range
			{
				(*it).mFired = false;
			}
			// Collision between shots and tanks
			float fX, bX, fZ, bZ;
			fX = mTarget->mGetFrontDummy()->GetX() - (*it).mModel->GetX();
			bX = mTarget->mGetBackDummy()->GetX() - (*it).mModel->GetX();
			fZ = mTarget->mGetFrontDummy()->GetZ() - (*it).mModel->GetZ();
			bZ = mTarget->mGetBackDummy()->GetZ() - (*it).mModel->GetZ();

			float fDist, bDist;
			fDist = (fX * fX) + (fZ * fZ);
			bDist = (bX * bX) + (bZ * bZ);

			if ((fDist < 5.0f || bDist < 5.0f) && (*it).mModel->GetY() > 0.0f)
			{
				(*it).mModel->SetY(-5.0f);
				mTarget->mDamage();
			}
		}
	}
}

void cNPCTank::mShoot(float frameTime)
{
	float FPS = 1 / frameTime;

	mTimer += 1;

	if (mTimer >= FPS * 2)
	{
		mTimer = 0;
		for (int i = 0; i < 1; i++)
		{
			if (!vProjectiles[i].mFired)
			{
				tankSounds->soundShot(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
				vProjectiles[i].mModel->SetPosition(mTurret->GetX(), mTurret->GetY() + 0.5f, mTurret->GetZ());
				vProjectiles[i].mModel->LookAt(mTarget->mGetModel());
				vProjectiles[i].mModel->Scale(0.2f);
				vProjectiles[i].mFired = true;
				break;
			}
		}
	}
}

void cNPCTank::mCollision(IModel* building)
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

IModel* cNPCTank::mGetModel()
{
	return mTankModel;
}

void cNPCTank::mDestroy()
{
	if (!mDestroyed)
	{
		mTankModel->RotateLocalZ(90.0f);
		mDestroyed = true;
	}
}
int cNPCTank::mGetTeam()
{
	return mTeamNumber;
}

bool cNPCTank::mIsDestroyed()
{
	return mDestroyed;
}


IModel* cNPCTank::mGetFrontDummy()
{
	return mFrontNode;
}
IModel* cNPCTank::mGetBackDummy()
{
	return mBackNode;
}

void cNPCTank::mDamage()
{
	tankSounds->soundImpact(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	if (mHP > 0)
	{
		mHP -= 10;
	}
	
	if(mHP <= 0)
	{
		mDestroy();
	}
}

int cNPCTank::mGetHP()
{
	return mHP;
}

//////// PLAYER TANK \\\\\\\\\

cPlayerTank::cPlayerTank(IMesh* tankMesh, I3DEngine* engine)
{
	IMesh* tmp = engine->LoadMesh("Explosion.x");


	tmp = engine->LoadMesh("Dummy.x");

	mTankModel = tankMesh->CreateModel(0.0f, 0.5f, 0.0f);

	mDummy = tmp->CreateModel(mTankModel->GetX(), mTankModel->GetY() + 0.5f, mTankModel->GetZ() + 10.0f);
//	mDummy->SetSkin("crosshair10.png");
	mDummy->Scale(10.0f);

	mTankModel->SetSkin("TankGreen.jpg");

	mFrontNode = tmp->CreateModel(0.0f, 0.5f, 2.0f);
	mBackNode = tmp->CreateModel(0.0f, 0.5f, -2.0f);
	mFrontNode->AttachToParent(mTankModel);
	mBackNode->AttachToParent(mTankModel);

	mDummy->AttachToParent(mTankModel);

	mTurret = mTankModel->GetNode(4);
	tankSounds = new cSoundTank;
	mProjectileMesh = engine->LoadMesh("Marble.x");

	for (int i = 0; i < 5; i++)
	{
		sProjectiles tmp;
		tmp.mModel = mProjectileMesh->CreateModel(0.0f, -5.0f, 0.0f);
		tmp.mVectorNumber = i;
		vProjectiles.push_back(tmp);
		vProjectiles.back().mModel->Scale(0.2f);
	}
}

void cPlayerTank::mMove(float movement, float rotation, float frameTime)
{
	if (mMovement < 10.0f || mMovement > -10.0f)
	{
		mMovement += movement * frameTime;
	}

	mTankModel->RotateY((rotation) * frameTime);

//	mDummy->RotateY((rotation)* frameTime);
	tankSounds->soundEngine(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
};

void cPlayerTank::mRotateTurret(float Xrotation, float Zrotation, float frameTime)
{
	mTurret->LookAt(mDummy);

	//mDummy->MoveLocal(-Xrotation * frameTime, 0.0f, Zrotation * frameTime);
}

void cPlayerTank::mStopEngine()
{
	tankSounds->stopEngine();
}

void cPlayerTank::mUpdate(float frameTime, actor_Vector NPCs)
{
	mPrevX = mTankModel->GetX();
	mPrevZ = mTankModel->GetZ();

	float distanceToShot = (mPrevX * mPrevX + mPrevZ * mPrevZ);

//	mDummy->MoveLocalZ(-mMovement * frameTime);
	mTankModel->MoveLocalZ(mMovement * frameTime);

	 //collision with other tanks
	for (int i = 0; i < NPCs.size(); i++)
	{
		float fX, bX, fZ, bZ;
		fX = NPCs[i]->mGetTank()->mGetModel()->GetX() - mTankModel->GetX();
//		bX = NPCs[i]->mGetTank()->mGetBackDummy()->GetX() - mBackNode->GetX();
		fZ = NPCs[i]->mGetTank()->mGetModel()->GetZ() - mTankModel->GetZ();
//		bZ = NPCs[i]->mGetTank()->mGetBackDummy()->GetZ() - mBackNode->GetZ();

		float fDist, bDist;
		fDist = (fX * fX) + (fZ * fZ);
//		bDist = (bX * bX) + (bZ * bZ);

		if (fDist < 30.0f)
		{
			mTankModel->SetPosition(mPrevX, 0.0f, mPrevZ);
			mMovement = 0.0f;
		}
	}
	
	for (auto it = vProjectiles.begin(); it != vProjectiles.end(); it++)
	{
		if((*it).mFired)
		{
			(*it).mModel->MoveLocalZ(mSpeed * frameTime);

			float x = mPrevX - (*it).mModel->GetX();
			float z = mPrevZ - (*it).mModel->GetZ();

			float distanceToShot = (x * x) + (z * z);


			if (distanceToShot > 5000.0f)	// tmp max shot range
			{
				(*it).mFired = false;
			}

			// Collision between shots and tanks
			float fX, bX, fZ, bZ;
			float fDist, bDist;
			for (int i = 0; i < NPCs.size(); i++)
			{
				fX = NPCs[i]->mGetTank()->mGetModel()->GetX() - (*it).mModel->GetX();
		//		bX = NPCs[i]->mGetTank()->mGetModel()->GetX() - (*it).mModel->GetX();
				fZ = NPCs[i]->mGetTank()->mGetModel()->GetZ() - (*it).mModel->GetZ();
	//			bZ = NPCs[i]->mGetTank()->mGetModel()->GetZ() - (*it).mModel->GetZ();
				fDist = (fX * fX) + (fZ * fZ);
			//	bDist = (bX * bX) + (bZ * bZ);

				if (fDist < 5.0f && (*it).mModel->GetY() > 0.0f)
				{
					NPCs[i]->mGetTank()->mDamage();
					(*it).mModel->SetY(-5.0f);
				}
			}
		}
	}
}

void cPlayerTank::mShoot(float frameTime)
{
	for (int i = 0; i < 5; i++)
	{
		if (!vProjectiles[i].mFired)
		{
			tankSounds->soundShot(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
			vProjectiles[i].mModel->SetPosition(mTurret->GetX(), mTurret->GetY() + 0.5f, mTurret->GetZ());
			vProjectiles[i].mModel->LookAt(mDummy);
			vProjectiles[i].mModel->Scale(0.2f);
			vProjectiles[i].mFired = true;
			break;
		}
	}
}

void cPlayerTank::mCollision(IModel* building)
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
}

IModel* cPlayerTank::mGetModel()
{
	return mTankModel;
}

void cPlayerTank::mDestroy()
{
	if (!mDestroyed)
	{
		mTankModel->RotateLocalZ(90.0f);
		mDestroyed = true;
	}
}
int cPlayerTank::mGetTeam()
{
	return mTeamNumber;
}

IModel* cPlayerTank::mGetFrontDummy()
{
	return mFrontNode;
}
IModel* cPlayerTank::mGetBackDummy()
{
	return mBackNode;
}

bool cPlayerTank::mIsDestroyed()
{
	return mDestroyed;
}

void cPlayerTank::mDamage()
{
	tankSounds->soundImpact(mTankModel->GetX(), mTankModel->GetY(), mTankModel->GetZ());
	if (mHP > 0)
	{
		mHP -= 10;
	}
	
	if(mHP <= 0)
	{
		mDestroy();
	}
}

int cPlayerTank::mGetHP()
{
	return mHP;
}
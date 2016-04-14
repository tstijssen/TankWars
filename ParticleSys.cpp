#include "ParticleSys.h"

cParticleSystem::cParticleSystem(tle::IMesh* mesh, tle::IModel* parentModel, int size, std::string skin, float scale)
{
	for (int i = 0; i < size; i++)
	{
		tle::IModel* tmp = mesh->CreateModel();
		mModels.push_back(tmp);
		mModels.back()->AttachToParent(parentModel);
		mModels.back()->Scale(scale);
		mModels.back()->SetSkin(skin);
		mLifeTime.push_back(0.0f);
	}
}

void cParticleSystem::mRun(float frameTime)
{
	if (mActive)
	{
		for (int i = 0; i < mModels.size(); i++)
		{

			mModels[i]->MoveLocalX(random(-5.0f, 5.0f) * frameTime);
			mModels[i]->MoveY(random(0.1f, 5.0f) * frameTime);
			mModels[i]->MoveLocalZ(random(-5.0f, 5.0f) * frameTime);
			mLifeTime[i] += random(0.5f, 1.0f) * frameTime;	// each particle has a randomized lifespan to make the thruster look less regular
			if (mLifeTime[i] >= 1.0f)	// once a particle's lifetime has reached below a second, reset it
			{
				mModels[i]->SetLocalPosition(mStartX, mStartY, mStartZ);
				mLifeTime[i] = 0.0f;
			}
		}
	}
}

void cParticleSystem::mGunSmoke(float frameTime, tle::ISceneNode* gunNode)
{
	if (mActive)
	{
		mStartX = gunNode->GetLocalX();
		mStartY = gunNode->GetLocalY();
		mStartZ = gunNode->GetLocalZ();
		for (int i = 0; i < mModels.size(); i++)
		{
			mModels[i]->MoveLocalX(random(-20.0f, 20.0f) * frameTime);
			mModels[i]->MoveY(random(-20.0f, 20.0f) * frameTime);
			mModels[i]->MoveLocalZ(random(50.0f, 80.0f) * frameTime);
			mLifeTime[i] += random(2.5f, 5.0f) * frameTime;	// each particle has a randomized lifespan to make the thruster look less regular
			if (mLifeTime[i] >= 1.0f)	// once a particle's lifetime has reached below a second, reset it
			{
				mModels[i]->SetLocalPosition(mStartX, mStartY, mStartZ);
			}
		}
	}
}

void cParticleSystem::mActivate()
{
	mActive = true;
}

void cParticleSystem::mDeactivate()
{
	mActive = false;
	for (int i = 0; i < mLifeTime.size(); i++)
	{
		mModels[i]->SetLocalPosition(mStartX, mStartY, mStartZ);
		mLifeTime[i] = 0.0f;
	}
}
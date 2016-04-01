#include "NPCActor.h"

int cNPCActor::mNPCCounter = 0;

cNPCActor::cNPCActor()
{
	mNPCCounter++;
	mName = "NPC-" + std::to_string(mNPCCounter);
	mScore = 0;
	mActive = false;
	mTeamNumber = 0;
}

void cNPCActor::mSetTank(IMesh* newTank, I3DEngine* engine)
{
	if (!mActive)
	{
		mTank = new cNPCTank(newTank, engine);
		mActive = true;
	}
}

void cNPCActor::mSetTarget(ITank* target)
{
	mTarget = target;
}

void cNPCActor::mHunt(float frameTime)
{
	if (mTarget != NULL)
	{
		// PATHFINDING HERE

		// just hunt and go forward for now
		mTank->mGetModel()->LookAt(mTarget->mGetModel());
		mTank->mMove(20.0f, 0.0f, frameTime);

	}
}
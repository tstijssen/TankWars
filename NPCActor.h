#ifndef NPC
#define NPC

#include "Player.h"

class cNPCActor
{
	string mName;
	int mScore;
	int mTeamNumber;
	bool mActive;

	cNPCTank* mTank;

	static int mNPCCounter;
	ITank* mTarget;
public:
	cNPCActor();

	void mSetTank(IMesh* newTank, sPosition* spawnLocation, I3DEngine* engine);
	bool mIsActive();
	void mSetInactive();
	void mSetTarget(ITank*, sPosition);
	void mHunt(float, actor_Vector);
	ITank* mGetTank();
};

#endif
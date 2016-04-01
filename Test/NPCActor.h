#ifndef NPC
#define NPC

#include "Player.h"

class cNPCActor
{
	string mName;
	int mScore;
	int mTeamNumber;
	bool mActive;

	ITank* mTank;

	static int mNPCCounter;
	ITank* mTarget;
public:
	cNPCActor();

	void mSetTank(IMesh* newTank, I3DEngine* engine);
	bool mIsActive();
	void mSetInactive();
	void mSetTarget(ITank*);
	void mHunt(float);
};

#endif
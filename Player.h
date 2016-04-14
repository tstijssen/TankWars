#ifndef Player
#define Player

#include <TL-Engine.h>
#include "Tank.h"
#include "TypeDefs.h"

class cPlayer
{
	string mName;
	int mScore;
	int mTeamNumber;
	bool mActive;

	ITank* mPlayerTank;
public:
	cPlayer();
	~cPlayer();

	void mSetTank(IMesh* newTank, I3DEngine* engine, sPosition spawn);
	void mRespawn(sPosition spawn);
	bool mIsActive();
	ITank* mGetTank();
	void mControlTank(I3DEngine* engine, float frameTime, gameControls controls[5], actor_Vector NPCs, cMusic*, cMusic*);
	void mAttachCamera(ICamera* camera);
};

#endif

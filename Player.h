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

	void mSetTank(IMesh* newTank, I3DEngine* engine);
	bool mIsActive();
	void mSetInactive();
	ITank* mGetTank();
	void mControlTank(I3DEngine* engine, float frameTime, gameControls controls[5], actor_Vector NPCs);
	void mAttachCamera(ICamera* camera);
};

#endif

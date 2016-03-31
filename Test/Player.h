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
	cTank* mPlayerTank;

public:

	cPlayer();
	~cPlayer();

	void mSetTank(IMesh* newTank, I3DEngine* engine);
	bool mIsActive();
	void mSetInactive();
	void mControlTank(I3DEngine* engine, float frameTime, model_Vector& mapModels);
	void mAttachCamera(ICamera* camera);
};

#endif

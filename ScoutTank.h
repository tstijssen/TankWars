#ifndef ScoutTank
#define ScoutTank

#include "Tank.h"

class cScoutTank : public ITank
{
	float mSpeed = 40.0f;
	float mPosition[3];
	int mTeamNumber;

	tle::IMesh* mScoutTankMesh;
	tle::IModel* mTankModel;
	tle::ISceneNode* mTurret;
	cSoundTank* tankSounds;
public:
	cScoutTank(tle::I3DEngine* engine, float position[3], int team);
	void mMove(float movement, float rotation, float frameTime);

	void mRotateTurret(float rotation, float frameTime);

	void mBoostMove(float frameTime);

	void mAttachCamera(tle::ICamera* camera);

	void mDestroy();

	int mGetTeam();

};

#endif

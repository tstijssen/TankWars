#ifndef Tanks
#define Tanks

#include "TL-Engine.h"
#include <vector>
#include "Sound.h"
using namespace tle;

enum tmpPowerUps {HP, Scan};

class cTank
{
	IModel* mTankModel;
	ISceneNode* mTurret;
	IModel* mDummy;

	IMesh* mProjectileMesh;

	vector<IModel*> vProjectiles;

	float mRotationValue;
	int mTeamNumber;
	float mSpeed = 20.0f;
	tmpPowerUps powerUps[3];
	// model get matrix
	// set values I want
	// will be reset after lighting
	cSoundTank* tankSounds;
public:

	cTank(IMesh* tankMesh, int teamNumber, ICamera* camera, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mBoostMove(float frameTime);
	void mUpdate(float);
	void mShoot(float);
	void mCollision(IModel*);
	void mDestroy();
	int mGetTeam();
};

class cMBT : public cTank
{
	int mHealth;
	int mSpeed;

public:


};

class cNPC: public cTank
{
public:

private:

};

class cPlayer: public cTank
{
public:

private:

};

#endif
#ifndef Tanks
#define Tanks

#include "TL-Engine.h"
#include "Sound.h"
using namespace tle;

enum tmpPowerUps {HP, Scan};

class cTank
{
	IModel* mTankModel;
	ISceneNode* mTurret;
	int mTeamNumber;
	float mSpeed = 20.0f;
	tmpPowerUps powerUps[3];
	// model get matrix
	// set values I want
	// will be reset after lighting
	cSoundTank* tankSounds;
public:

	cTank(IMesh* tankMesh, int teamNumber, ICamera* camera);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float frameTime);
	void mStopEngine();
	void mBoostMove(float frameTime);
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
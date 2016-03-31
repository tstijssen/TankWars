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

	IModel* mFrontNode;
	IModel* mBackNode;

	IMesh* mProjectileMesh;

	vector<IModel*> vProjectiles;

	float mRotationValue;
	int mTeamNumber;
	float mMovement = 0.0f;
	float mPrevX = 0.0f;
	float mPrevZ = 0.0f;

	float mSpeed = 1000.0f;
	tmpPowerUps powerUps[3];
	cSoundTank* tankSounds;
public:

	cTank(IMesh* tankMesh, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mBoostMove(float frameTime);
	void mUpdate(float);
	void mShoot(float);
	void mCollision(IModel*);
	void mDestroy();
	IModel* mGetModel();
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

#endif
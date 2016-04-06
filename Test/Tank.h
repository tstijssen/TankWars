#ifndef Tanks
#define Tanks

#include "TL-Engine.h"
#include <vector>
#include "Sound.h"
#include "TypeDefs.h"
using namespace tle;

enum tmpPowerUps {HP, Scan};
enum tanktypes {Scout, Arty, MBT, Hover};

struct sProjectiles
{
	IModel* mModel;
	bool mFired = false;
	int mVectorNumber;
};

class ITank
{
public:
	~ITank() {};

	virtual void mMove(float movement, float rotation, float frameTime) = 0;
	virtual void mRotateTurret(float rotation, float, float frameTime) = 0;
	virtual void mStopEngine() = 0;
	virtual void mUpdate(float, actor_Vector) = 0;
	virtual void mShoot(float) = 0;
	virtual void mCollision(IModel*) = 0;
	virtual void mDestroy() = 0;
	virtual IModel* mGetModel() = 0;
	virtual int mGetTeam() = 0;
	virtual IModel* mGetFrontDummy() = 0;
	virtual IModel* mGetBackDummy() = 0;
};


class cPlayerTank : public ITank
{
	IModel* mTankModel;
	ISceneNode* mTurret;
	IModel* mDummy;

	IModel* mFrontNode;
	IModel* mBackNode;

	IMesh* mProjectileMesh;

	vector<sProjectiles> vProjectiles;

	float mRotationValue;
	int mTeamNumber;
	int mNumFired = 0;
	float mMovement = 0.0f;
	float mPrevX = 0.0f;
	float mPrevZ = 0.0f;

	float mSpeed = 1000.0f;
	tmpPowerUps powerUps[3];
	cSoundTank* tankSounds;
public:

	cPlayerTank(IMesh* tankMesh, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mUpdate(float, actor_Vector);
	void mShoot(float);
	void mCollision(IModel*);
	void mDestroy();
	IModel* mGetModel();
	int mGetTeam();
};

class cNPCTank : public ITank
{
	IModel* mTankModel;
	ISceneNode* mTurret;
	IModel* mFrontNode;
	IModel* mBackNode;
	int mTeamNumber;

	const int MSHOTS = 5;
	int mNumFired = 0;

	IMesh* mProjectileMesh;

	vector<sProjectiles> vProjectiles;

	float mSpeed = 1000.0f;
	float mMovement = 0.0f;
	float mPrevX = 0.0f;
	float mPrevZ = 0.0f;
	float mDistanceToTarget = 0.0f;
	float mTimer = 0.0f;

	ITank* mTarget;
	cSoundTank* tankSounds;
public:
	cNPCTank(IMesh* tankMesh, IModel* spawnLocation, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mUpdate(float, actor_Vector);
	void mSetTarget(ITank* target);
	void mShoot(float);
	void mCollision(IModel*);
	void mDestroy();
	IModel* mGetModel();
	int mGetTeam();
};


#endif
#ifndef Tanks
#define Tanks

#include "TL-Engine.h"
#include <vector>
#include "Sound.h"
using namespace tle;

enum tmpPowerUps {HP, Scan};
enum tanktypes {Scout, Arty, MBT, Hover};

class ITank
{
public:
	~ITank() {};

	virtual void mMove(float movement, float rotation, float frameTime) = 0;
	virtual void mRotateTurret(float rotation, float, float frameTime) = 0;
	virtual void mStopEngine() = 0;
	virtual void mUpdate(float) = 0;
	virtual void mShoot(float) = 0;
	virtual void mCollision(IModel*) = 0;
	virtual void mDestroy() = 0;
	virtual IModel* mGetModel() = 0;
	virtual int mGetTeam() = 0;
};


class cPlayerTank : public ITank
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

	cPlayerTank(IMesh* tankMesh, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mUpdate(float);
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

	IMesh* mProjectileMesh;

	vector<IModel*> vProjectiles;

	float mSpeed = 1000.0f;
	float mMovement = 0.0f;
	float mPrevX = 0.0f;
	float mPrevZ = 0.0f;

	ITank* mTarget;
	cSoundTank* tankSounds;
public:
	cNPCTank(IMesh* tankMesh, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mUpdate(float);
	void mShoot(float);
	void mCollision(IModel*);
	void mDestroy();
	IModel* mGetModel();
	int mGetTeam();
};


#endif
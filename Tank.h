#ifndef Tanks
#define Tanks

#include "TL-Engine.h"
#include <vector>
#include "Sound.h"
#include "TypeDefs.h"
#include "ParticleSys.h"
#include "PowerUp.h"

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
	virtual void mCollision(building_vector) = 0;
	virtual void mDestroy() = 0;
	virtual IModel* mGetModel() = 0;
	virtual int mGetTeam() = 0;
	virtual IModel* mGetFrontDummy() = 0;
	virtual IModel* mGetBackDummy() = 0;
	virtual int mGetHP() = 0;
	virtual void mDamage() = 0;
	virtual bool mIsDestroyed() = 0;
	virtual void mSetShield(float) = 0;
	virtual void mSetWeapon(weaponData) = 0;
	virtual void mAddHealth(float) = 0;
	virtual void mRespawn(sPosition) = 0;
};

class cPlayerTank : public ITank
{
	IModel* mTankModel;
	ISceneNode* mTurret;
	IModel* mDummy;

	IModel* mFrontNode;
	IModel* mBackNode;
	IModel* mHealthQuad;


	IMesh* mProjectileMesh;
	cParticleSystem* mDamageParticles[2];
	cParticleSystem* mGunParticles;

	weaponData mWeapon;
	shieldData mShield;

	vector<sProjectiles> vProjectiles;
	bool mDestroyed = false;
	float mHP = 1.0f;
	float mRotationValue;
	int mTeamNumber;
	int mNumFired = 0;
	float mMovement = 0.0f;
	float mPrevX = 0.0f;
	float mPrevZ = 0.0f;

	float mSpeed = 1000.0f;
	cSoundTank* tankSounds;
public:

	cPlayerTank(IMesh* tankMesh, I3DEngine* engine, float x, float y, float z);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mUpdate(float, actor_Vector);
	void mShoot(float);
	void mCollision(building_vector);
	void mDestroy();
	IModel* mGetModel();
	IModel* mGetFrontDummy();
	IModel* mGetBackDummy();
	int mGetTeam();
	int mGetHP();
	void mDamage();
	bool mIsDestroyed();
	void mSetShield(float);
	void mSetWeapon(weaponData);
	void mAddHealth(float);
	void mRespawn(sPosition);
};

class cNPCTank : public ITank
{
	IModel* mTankModel;
	ISceneNode* mTurret;
	IModel* mFrontNode;
	IModel* mBackNode;
	IModel* mHealthQuad;
	int mTeamNumber;

	const int MSHOTS = 5;
	int mNumFired = 0;

	IMesh* mProjectileMesh;
	cParticleSystem* gunParticles;
	vector<sProjectiles> vProjectiles;
	cParticleSystem* mDamageParticles[2];
	cParticleSystem* mGunParticles;


	weaponData mWeapon;
	shieldData mShield;

	bool mDestroyed = false;
	float mHP = 0.4f;
	float mSpeed = 1000.0f;
	float mMovement = 0.0f;
	float mPrevX = 0.0f;
	float mPrevZ = 0.0f;
	float mDistanceToTarget = 0.0f;
	float mTimer = 0.0f;

	ITank* mTarget;
	cSoundTank* tankSounds;
public:
	cNPCTank(IMesh* tankMesh, sPosition* spawnLocation, I3DEngine* engine);
	void mMove(float movement, float rotation, float frameTime);
	void mRotateTurret(float rotation, float, float frameTime);
	void mStopEngine();
	void mUpdate(float, actor_Vector);
	void mSetTarget(ITank* target);
	void mShoot(float);
	void mCollision(building_vector);
	void mDestroy();
	IModel* mGetModel();
	IModel* mGetFrontDummy();
	IModel* mGetBackDummy();
	int mGetTeam();
	int mGetHP();
	void mDamage();
	bool mIsDestroyed();
	void mSetShield(float);
	void mSetWeapon(weaponData);
	void mAddHealth(float);
	void mRespawn(sPosition);
};


#endif
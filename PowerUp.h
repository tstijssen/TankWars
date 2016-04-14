#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "Sound.h"
using namespace tle;

extern struct weaponData
{
	int ammo;
	int damage;
	int reloadTime;
};

extern struct shieldData
{
	bool active = false;
	float duration = 0.0f;
};

class cPowerUps
{
protected:
	float respawnTime = 10.0f;
	float collisionRadius = 5.0f;
	IMesh* mesh;
	std::string mPowerUpSkin;
	std::string mTankSkin;
	IModel* model;
	float xPos;
	float yPos;
	float zPos;
	bool active = true;
	float timer = 0.0f;

	cSoundEffect* mPickupSound;
public:

	cPowerUps(tle::I3DEngine* &myEngine, string modelName, float x, float y, float z, string powerUpSkin, string tankSkin)
	{
		xPos = x;
		yPos = y;
		zPos = z;
		mesh = myEngine->LoadMesh(modelName);
		model = mesh->CreateModel(x, y, z);
		mPowerUpSkin = powerUpSkin;
		model->SetSkin(mPowerUpSkin);
		mTankSkin = tankSkin;
		model->Scale(0.2);
		mPickupSound = new cSoundEffect("Pickup.wav");
	}
	float RespawnTimer();
	float GetCollisionRadius();
	void ResetTimer();
	bool Active();
	float getTimer();
	void PlaySound();
	void AddCounter(float time);
	void Despawn();
	void Respawn(IModel* tank);
	IModel* GetModel();
	float CollisionDetection(IModel* tank);
	virtual void Activate(IModel* tank, float frameTime) {};



};



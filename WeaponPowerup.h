#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "PowerUp.h"
#include "Tank.h"
using namespace tle;

class weaponPowerUp :public cPowerUps
{
private:
	weaponData mWeapon;

public:
	weaponPowerUp(I3DEngine* &myEngine, string modelName, float x, float y, float z, string powerUpSkin, string tankSkin, weaponData weapon) :cPowerUps(myEngine, modelName, x, y, z, powerUpSkin, tankSkin)
	{
		mWeapon = weapon;
	}
	void Activate(ITank* tank, float frameTime)
	{
		tank->mSetWeapon(mWeapon);
		tank->mGetModel()->SetSkin(mTankSkin);
		Despawn();
	}
};
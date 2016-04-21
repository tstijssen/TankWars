#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "PowerUp.h"
#include "Tank.h"
using namespace tle;

class ShieldPowerup :public cPowerUps
{
private:
	const int healthValue = 50.0f;
	float shieldDuration = 15.0f;
public:
	ShieldPowerup(I3DEngine* &myEngine, string modelName, float x, float y, float z, string powerUpSkin, string tankSkin) :cPowerUps(myEngine, modelName, x, y, z, powerUpSkin, tankSkin) {}
	void Activate(ITank* tank, float frameTime)
	{
		tank->mSetShield(shieldDuration);
		tank->mGetModel()->SetSkin(mTankSkin);
		Despawn();
	}
};
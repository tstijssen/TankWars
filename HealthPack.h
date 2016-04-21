#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "PowerUp.h"
#include "Tank.h"
using namespace tle;



class HealthPack :public cPowerUps
{
private:
	const float healthValue = 0.5f;
	bool newSkin = false;
public:
	HealthPack(I3DEngine* &myEngine, string modelName, float x, float y, float z, string powerUpSkin, string tankSkin) :cPowerUps(myEngine, modelName, x, y, z, powerUpSkin, tankSkin) {}
	void Activate(ITank* tank, float frameTime)
	{
		tank->mAddHealth(healthValue);
		newSkin = true;
		PlaySound();
		Despawn();
	}
	void ApplySkin(IModel* tank, float timer)
	{
		AddCounter(timer);
		if (getTimer() > 0.1 && getTimer() < 0.5 && newSkin)
		{
			tank->SetSkin(mTankSkin);
			newSkin = false;
		}
		if (getTimer() > 0.5 && getTimer() < 0.9 && !newSkin)
		{
			tank->SetSkin("HoverTank08.jpg");
			newSkin = true;
		}
	}
};
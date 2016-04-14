#include "PowerUp.h"


float cPowerUps::RespawnTimer()
{
	return respawnTime;
}
float cPowerUps::GetCollisionRadius()
{
	return collisionRadius;
}
void cPowerUps::ResetTimer()
{
	timer = 0;
}

bool cPowerUps::Active()
{
	return active;
}
float cPowerUps::getTimer()
{
	return timer;
}

void cPowerUps::AddCounter(float time)
{
	timer += time;
}

void cPowerUps::PlaySound()
{
	mPickupSound->mPlay();
}

void cPowerUps::Despawn()
{
	model->SetPosition(0, -1000, 0);
	active = false;
}
void cPowerUps::Respawn(IModel* tank)
{
	model->SetPosition(xPos, yPos, zPos);
	active = true;
	ResetTimer();
	tank->SetSkin("HoverTank08.jpg");
}
IModel* cPowerUps::GetModel()
{
	return model;
}
float cPowerUps::CollisionDetection(IModel* tank)
{
	float x;
	float y;
	float z;
	//Calculate the vector between the bullet and the mushrooms.
	x = tank->GetX() - model->GetX();
	y = tank->GetY() - model->GetY();
	z = tank->GetZ() - model->GetZ();
	//Then calculate the length of the vector/distance between the two objects.
	float collisionDist = sqrt(x*x + y*y + z*z);
	return collisionDist;
}

#include "Sound.h"

cSoundTank::cSoundTank()
{
	engine.loadFromFile("floating.wav");
	engineStop.loadFromFile("dead.wav");
	boostBuffer.loadFromFile("boost.wav");
	engineSound.setBuffer(engine);
	engineStopSound.setBuffer(engineStop);
	boostSound.setBuffer(boostBuffer);
	engineSound.setVolume(100.0f);
	sf::Listener::setGlobalVolume(100.0f); // 0 to 100
	engineSound.setLoop(true);
}

void cSoundTank::soundEngine(float x, float y, float z)
{
	engineSound.setPosition(x, y, z);
	if (!engineActive)
	{
		engineSound.play();
		engineActive = true;
	}
	sf::Listener::setPosition(x, y, z);
}

void cSoundTank::stopEngine()
{
	engineSound.stop();
	if (engineActive)
	{
		engineStopSound.setPosition(engineSound.getPosition());
		engineStopSound.play();
		engineActive = false;
	}
	if (boostActive)
	{
		boostActive = false;
	}
}

void cSoundTank::soundBoost(float x, float y, float z)
{
	boostSound.setPosition(x, y, z);
	if (!boostActive)
	{
		boostSound.play();
		boostActive = true;
	}
}

void cSoundTank::soundTurret()
{

}
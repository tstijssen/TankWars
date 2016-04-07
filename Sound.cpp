#include "Sound.h"

cMusic::cMusic(std::string musicFile)
{
	buffer.loadFromFile("Music\\" + musicFile);
	sound.setBuffer(buffer);
	sound.setVolume(100.0f);
	sf::Listener::setGlobalVolume(100.0f); // 0 to 100
	sound.setLoop(true);
}

void cMusic::mStart()
{
	sound.play();
}

void cMusic::mStop()
{
	sound.stop();
}

// sound effect class

cSoundEffect::cSoundEffect(std::string musicFile)
{
	buffer.loadFromFile("Music\\Effects\\" + musicFile);
	sound.setBuffer(buffer);
	sound.setVolume(100.0f);
	sf::Listener::setGlobalVolume(100.0f);
	sound.setLoop(false);
}

void cSoundEffect::mPlay()
{
	if (sound.getStatus() != sound.Playing)
	{
		sound.play();
	}
}

bool cSoundEffect::mGetStatus()
{
	return mSoundStatus;
}

void cSoundEffect::mSetStatus(bool newStatus)
{
	mSoundStatus = newStatus;
}

cSoundTank::cSoundTank()
{
	engine.loadFromFile("Music\\Effects\\EngineHover.wav");
	engineStop.loadFromFile("Music\\Effects\\Crash.wav");
	boostBuffer.loadFromFile("Music\\Effects\\boost.wav");
	impactBuffer.loadFromFile("Music\\Effects\\MetalImpact.wav");
	shootBuffer.loadFromFile("Music\\Effects\\MainGun.wav");

	engineSound.setBuffer(engine);
	shootSound.setBuffer(shootBuffer);
	impactSound.setBuffer(impactBuffer);
	engineStopSound.setBuffer(engineStop);
	boostSound.setBuffer(boostBuffer);

	engineSound.setVolume(100.0f);
	shootSound.setVolume(100.0f);
	impactSound.setVolume(100.0f);
	sf::Listener::setGlobalVolume(100.0f); // 0 to 100
	engineSound.setLoop(true);
}

void cSoundTank::soundEngine(float x, float y, float z)
{
	engineSound.setPosition(x, y, z);
	sf::Listener::setPosition(x, y, z);
	if (!engineActive)
	{
		engineSound.play();
		engineActive = true;
	}

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

void cSoundTank::soundImpact(float x, float y, float z)
{
	impactSound.setPosition(x, y, z);
	impactSound.play();
}

void cSoundTank::soundShot(float x, float y, float z)
{
	shootSound.setPosition(x, y, z);
	sf::Listener::setPosition(x,y,z);
	shootSound.play();
}

void cSoundTank::soundTurret()
{

}
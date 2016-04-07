#ifndef SoundHeader
#define SoundHeader

#include <SFML/Audio.hpp>

using namespace sf;

class cMusic
{
	SoundBuffer buffer;
	Sound sound;
public:
	cMusic(std::string musicFile);
	void mStart();
	void mStop();
};

class cSoundEffect
{
	SoundBuffer buffer;
	Sound sound;
	bool mSoundStatus;
public:
	cSoundEffect(std::string musicFile);
	void mPlay();
	bool mGetStatus();
	void mSetStatus(bool newStatus);
};

class cSoundTank
{
	SoundBuffer engine;
	SoundBuffer engineStop;
	SoundBuffer turretRotate;
	SoundBuffer boostBuffer;
	SoundBuffer impactBuffer;
	SoundBuffer shootBuffer;

	Sound shootSound;
	Sound impactSound;
	Sound engineSound;
	Sound engineStopSound;
	Sound turretRotateSound;
	Sound boostSound;

	bool engineActive = false;
	bool boostActive = false;

public:
	cSoundTank();
	void soundEngine(float x, float y, float z);
	void stopEngine();
	void soundBoost(float x, float y, float z);
	void soundTurret();
	void soundImpact(float x, float y, float z);
	void soundShot(float x, float y, float z);
};


#endif
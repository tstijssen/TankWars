#ifndef SoundHeader
#define SoundHeader

#include <SFML/Audio.hpp>
#include <vector>

using namespace sf;

//class cMusic
//{
//	SoundBuffer buffer;
//	Sound sound;
//public:
//	cMusic(String musicFile);
//	void mStart();
//	void mStop();
//};

class cSoundTank
{
	SoundBuffer engine;
	SoundBuffer engineStop;
	SoundBuffer turretRotate;
	SoundBuffer boostBuffer;

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
};


#endif
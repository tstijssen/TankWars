#ifndef GameInstance
#define GameInstance

#include "TypeDefs.h"
#include "Sound.h"
#include "Player.h"

using namespace tle;

class cGameInstance
{
	I3DEngine* mGameEngine;
	ICamera* mMyCamera;
	mesh_vector mTankMeshes;
	model_Vector mModels;
	gameControls mControls[5];

	cPlayer* mPlayer;
public:
	cGameInstance(I3DEngine* engine, string mapName, gameControls[5]);
	~cGameInstance();

	void mSpawnMenu();
	void mPlaying();

};

#endif
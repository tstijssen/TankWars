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
	position_Vector mEnemySpawnLoc;
	sPosition mPlayerSpawn;
	building_vector mModels;
	gameControls mControls[5];

	cMusic* mWaitingMusic;
	cMusic* mBattleMusic;

	cPlayer* mPlayer;
public:
	cGameInstance(I3DEngine* engine, string mapName, gameControls[5]);
	~cGameInstance();

	void mSpawnMenu();
	void mPlaying();

};

#endif
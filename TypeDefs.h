#ifndef Typedefs
#define Typedefs

#include "TL-Engine.h"
#include <vector>

enum buildingtypes { PlayerBase, NPCBase, Scenery, AirSupport, Upgrades, BreakableScenery };
struct gameControls
{
	string control;
	tle::EKeyCode keyBind;
	int keyBindNumber = 0;//This variable will be used to write to the control file. This number is casted to an EKeyCode to determine what key to use for each control/action.
};

struct sBuilding
{
	tle::IModel* mModel;
	float mBoundingMaxX;
	float mBoundingMinX;

	float mBoundingMaxY;
	float mBoundingMinY;

	float mBoundingMaxZ;
	float mBoundingMinZ;

	bool mCollidable = true;
	buildingtypes mType;
};

struct sPosition
{
	float x, y, z;
};

// range_min <= random number <= range_max
float random(int rangeMin, int rangeMax);


class cNPCActor;

typedef std::vector<sPosition> position_Vector;
typedef std::vector<cNPCActor*> actor_Vector;
typedef std::vector<sBuilding> building_vector;
typedef std::vector<tle::IModel*> model_Vector;
typedef std::vector<tle::IMesh*> mesh_vector;

#endif

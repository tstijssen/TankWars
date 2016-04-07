#ifndef Typedefs
#define Typedefs

#include "TL-Engine.h"
#include <vector>

struct gameControls
{
	string control;
	tle::EKeyCode keyBind;
	int keyBindNumber = 0;//This variable will be used to write to the control file. This number is casted to an EKeyCode to determine what key to use for each control/action.
};


class cNPCActor;

typedef std::vector<cNPCActor*> actor_Vector;
typedef std::vector<tle::IModel*> model_Vector;
typedef std::vector<tle::IMesh*> mesh_vector;

#endif
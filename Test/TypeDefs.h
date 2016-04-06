#ifndef Typedefs
#define Typedefs

#include "TL-Engine.h"
#include <vector>

struct gameControls
{
	string control;
	tle::EKeyCode keyBind; //const EKeyCode KEY_LEFT = tle::Key_Left;
};

class cNPCActor;

typedef std::vector<cNPCActor*> actor_Vector;
typedef std::vector<tle::IModel*> model_Vector;
typedef std::vector<tle::IMesh*> mesh_vector;

#endif
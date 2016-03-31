#ifndef Frontend
#define Frontend

#include "TypeDefs.h"
#include "Sound.h"

#include <TL-Engine.h>// TL-Engine include file and namespace
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace tle;

struct optionMenuText
{
	stringstream text;
	int colour = kRed;
};


struct gameControls
{
	string control;
	EKeyCode keyBind; //const EKeyCode KEY_LEFT = tle::Key_Left;
	int keyBindNumber = 0;//This variable will be used to write to the control file. This number is casted to an EKeyCode to determine what key to use for each control/action.
};


struct textData
{
	//Give default values.
	stringstream text;
	unsigned int textColour = kRed;
	int xPos = 0;
	int yPos = 0;
	bool keyPress = false;
};

class cGameFront
{
	ICamera* mMenuCamera;
	I3DEngine* mFrontEngine;
	IModel* mBackground;
	model_Vector mSceneModels;
//	cMusic* mSceneMusic;

	unordered_map <int, string> keyOutput;
	gameControls gameControl[5];
	ifstream infile;
	ofstream outfile;
	string controlFile = "controls.txt";
	string defaultControls = "defaultcontrols.txt";
	int tempNumber;
	string tempString;
	int controlCounter = 0;


	IFont* mMenuFont;

public:
	cGameFront(I3DEngine* engine);
	~cGameFront();

	void mMenu();
	void mShowMaps();
	void mControls();
	void mTanksView();
};


#endif

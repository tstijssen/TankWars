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

const int NUMCONTROLS = 5;

struct optionMenuText
{
	stringstream text;
	int colour = kRed;
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
	ISprite* mMenuPanel;

	model_Vector mSceneModels;
	cMusic* mSceneMusic;
	cSoundEffect* mButtonPress;
	cSoundEffect* mButtonHover;

	unordered_map <int, string> keyOutput;
	gameControls gameControl[5];
	ifstream infile;
	string controlFile = "controls.txt";
	string defaultControls = "defaultcontrols.txt";
	int tempNumber;
	string tempString;
	int controlCounter = 0;
	textData controlText[NUMCONTROLS];

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
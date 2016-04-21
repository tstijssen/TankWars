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

const int NUMCONTROLS = 7;

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
	ISprite* mOptionsPanel;
	ISprite* mLoadingScreen;
	
	ofstream outfile;
	model_Vector mSceneModels;
	cMusic* mSceneMusic;
	cSoundEffect* mButtonPress;

	unordered_map <int, string> keyOutput;
	gameControls gameControl[5];
	ifstream infile;
	string controlFile = "controls.txt";
	string defaultControls = "defaultcontrols.txt";
	int tempNumber;
	int windowWidth;
	string tempString;
	int controlCounter = 0;
	textData controlText[NUMCONTROLS];

	IFont* mMenuFont;
	IFont* mTitleFont;
public:
	cGameFront(I3DEngine* engine);
	~cGameFront();

	void mMenu();
	void mShowMaps();
	void mControls();
};


#endif

#include "FrontEnd.h"
#include "MapLoader.h"
#include "GameInstance.h"
// prof skills game.cpp: A program using the TL-Engine

using namespace std;

const int MAINMENUTEXTOFFSETX = 2;
const int MAINMENUTEXTOFFSETY = 12;//Every piece of text drawn using this font always has a height of 24 pixels. +- 12 in each y direction. This is the max limit of the text. 
								   //Add 3 more pixels for a wider click range. 
const int OPTIONMENUTEXTOFFSETX = 2;
const int OPTIONMENUTEXTOFFSETY = 10;

// Return a random number in the range between rangeMin and rangeMax inclusive
// range_min <= random number <= range_max
float random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}

//Function used to draw shadows for text. When drawing shadows ensure that the shadow is drawn first then the actual text.
void DrawShadow(textData &text, IFont* font)
{
	font->Draw(text.text.str(), text.xPos + 2, text.yPos + 2, kBlack, kLeft, kVCentre);
}

//Function used to check if the mouse is in the collision region for each button/text display.
bool CheckButtonContact(int mouseXPosition, int mouseYPosition, textData &text, int textWidth, int xOffset, int yOffset)
{
	if (mouseXPosition > text.xPos - xOffset && mouseXPosition < text.xPos + textWidth + xOffset && mouseYPosition > text.yPos - yOffset && mouseYPosition < text.yPos + yOffset)
	{
		return true;
	}
	return false;
}
//Function used to change the key bind assigned to a control.
void ChangeKeyBind(textData &text, bool &changeKeyMenu, I3DEngine* &myEngine, int &tempKeyBindValue, unordered_map<int, string>::iterator it, gameControls &gameControl)
{
	//The iterator that is passed to the function moves through the map of key binds.
	string newKeyChar;
	if (text.keyPress)
	{
		text.textColour = kWhite;
		if (myEngine->KeyHit(static_cast<EKeyCode>(tempKeyBindValue)))//The iterator value is statically cast into an key code enum to detect what key has been hit. 
		{
			gameControl.keyBind = static_cast<EKeyCode>(tempKeyBindValue);//The key bind is changed.
			newKeyChar = it->second;//The string assigned to the enum is then stored so that the new key can be displayed on screen. 
			text.text.str("");
			text.text << gameControl.control + " = ";
			text.text << newKeyChar;
			text.textColour = kWhite;
			text.keyPress = false;
			changeKeyMenu = false;
		}
	}
}

void DisplayControls(int controlCounter, gameControls gameControl[])
{
	for (int i = 0; i < controlCounter; i++)
	{
		cout << "control name = " << gameControl[i].control << endl;
		cout << "keybind= " << gameControl[i].keyBind << endl;
	}
}

void ReadControls(ifstream &infile, string &controlFile, string &defaultControlFile, gameControls gameControl[], textData controlText[], unordered_map <int, string> &keyOutput)
{
	int tempNumber;//This is used to convert the numbers from the file into an int variable. These numbers will be used to determine what key is to be assigned to a control. 
	string tempString;//This will hold the number variable that is read in from the file. 
	int controlCounter = 0;
	bool defaultControls = false;
	infile.open(controlFile);
	if (!infile)
	{
		infile.close();
		defaultControls = true;
	}

	if (defaultControls)
	{
		cout << "Default";
		infile.open("Settings//" + defaultControlFile);
	}
	while (!infile.eof())
	{
		getline(infile, gameControl[controlCounter].control, ' ');
		getline(infile, tempString, '\n');
		tempNumber = std::stoi(tempString);
		gameControl[controlCounter].keyBind = static_cast<EKeyCode>(tempNumber);//Each number in the file is cast into a key code enum value and then assigned to each key bind. 
		controlText[controlCounter].text << gameControl[controlCounter].control << " = " << keyOutput[tempNumber];//This line allows changes to be made to the key code numbers in the control files.
																												  //And still output the correct character on the change button menu rather than assigning them statically. 
		controlCounter++;
	}
	infile.close();
}

void SetKeyCheckMap(unordered_map <int, string> &keyOutput)
{
	keyOutput[0] = "Not in use";
	keyOutput[1] = "Left Mouse Button";
	keyOutput[2] = "Right Mouse Button";
	keyOutput[4] = "Middle Mouse Button";
	keyOutput[8] = "Backspace";
	keyOutput[9] = "Tab";
	keyOutput[12] = "Clear";
	keyOutput[13] = "Enter";
	keyOutput[16] = "Shift";
	keyOutput[17] = "Ctrl";
	keyOutput[18] = "Alt";
	keyOutput[19] = "Pause";
	keyOutput[20] = "Caps Lock";
	keyOutput[27] = "Escape";
	keyOutput[32] = "Spacebar";
	keyOutput[33] = "Page Up";
	keyOutput[34] = "Page Down";
	keyOutput[35] = "End";
	keyOutput[36] = "End";
	keyOutput[37] = "Left";
	keyOutput[38] = "Up";
	keyOutput[39] = "Right";
	keyOutput[40] = "Down";
	keyOutput[41] = "Select";
	keyOutput[42] = "Print";
	keyOutput[44] = "Print Screen";
	keyOutput[45] = "Insert";
	keyOutput[46] = "Delete";
	keyOutput[47] = "Help";
	keyOutput[48] = "0";
	keyOutput[49] = "1";
	keyOutput[50] = "2";
	keyOutput[51] = "3";
	keyOutput[52] = "4";
	keyOutput[53] = "5";
	keyOutput[54] = "6";
	keyOutput[55] = "7";
	keyOutput[56] = "8";
	keyOutput[57] = "9";
	keyOutput[65] = "A";
	keyOutput[66] = "B";
	keyOutput[67] = "C";
	keyOutput[68] = "D";
	keyOutput[69] = "E";
	keyOutput[70] = "F";
	keyOutput[71] = "G";
	keyOutput[72] = "H";
	keyOutput[73] = "I";
	keyOutput[74] = "J";
	keyOutput[75] = "K";
	keyOutput[76] = "L";
	keyOutput[77] = "M";
	keyOutput[78] = "N";
	keyOutput[79] = "O";
	keyOutput[80] = "P";
	keyOutput[81] = "Q";
	keyOutput[82] = "R";
	keyOutput[83] = "S";
	keyOutput[84] = "T";
	keyOutput[85] = "U";
	keyOutput[86] = "V";
	keyOutput[87] = "W";
	keyOutput[88] = "X";
	keyOutput[89] = "Y";
	keyOutput[90] = "Z";
	keyOutput[91] = "Left Windows Key";
	keyOutput[92] = "Right Windows Key";
	keyOutput[93] = "Applications Key";
	keyOutput[96] = "Numpad 0";
	keyOutput[97] = "Numpad 1";
	keyOutput[98] = "Numpad 2";
	keyOutput[99] = "Numpad 3";
	keyOutput[100] = "Numpad 4";
	keyOutput[101] = "Numpad 5";
	keyOutput[102] = "Numpad 6";
	keyOutput[103] = "Numpad 7";
	keyOutput[104] = "Numpad 8";
	keyOutput[105] = "Numpad 9";
	keyOutput[106] = "Numpad *";
	keyOutput[107] = "Numpad +";
	keyOutput[109] = "Numpad -";
	keyOutput[110] = "Numpad .";
	keyOutput[111] = "Numpad /";
	keyOutput[112] = "F1";
	keyOutput[113] = "F2";
	keyOutput[114] = "F3";
	keyOutput[115] = "F4";
	keyOutput[116] = "F5";
	keyOutput[117] = "F6";
	keyOutput[118] = "F7";
	keyOutput[119] = "F8";
	keyOutput[120] = "F9";
	keyOutput[121] = "F10";
	keyOutput[122] = "F11";
	keyOutput[123] = "F12";
	keyOutput[144] = "Num Lock";
	keyOutput[145] = "Scroll Lock";
	keyOutput[160] = "Left Shift";
	keyOutput[161] = "Right Shift";
	keyOutput[162] = "Left Control";
	keyOutput[163] = "Right Control";
	keyOutput[164] = "Left Menu";
	keyOutput[165] = "Right Menu";
	keyOutput[187] = "+";
	keyOutput[188] = ",";
	keyOutput[189] = "-";
	keyOutput[190] = ".";
}

cGameFront::cGameFront(I3DEngine* engine)
{
	//// set up menu music
	//mSceneMusic = new cMusic("menu.wav");
	//mSceneMusic->mStart();

	// set up menu scene
	mFrontEngine = engine;
	//LoadMap(mFrontEngine, mSceneModels, "menuscene.txt");
	SetKeyCheckMap(keyOutput);

	IMesh* skyboxMesh = mFrontEngine->LoadMesh("Skybox.x");
	mBackground = skyboxMesh->CreateModel(0.0f, -960.0f, 0.0f);
	mMenuFont = mFrontEngine->LoadFont("Font2.bmp");

	mMenuCamera = mFrontEngine->CreateCamera(kManual, 0.0f, 50.0f, -180.0f);
	mMenuCamera->RotateX(18.0f);
	mMenu();
}

cGameFront::~cGameFront()
{
	// unallocate pointers and stop music
	delete mMenuCamera;
	mFrontEngine->Delete();
	//mSceneMusic->mStop();
	//delete mSceneMusic;
}

void cGameFront::mMenu()
{
	int windowWidth = mFrontEngine->GetWidth();
	int mouseXPosition;
	int mouseYPosition;
	int textWidth;//Variable used in determining the toggle range of buttons/onscreen text.

	// TEXT VALUES
	textData mainMenuText[3];
	//Play button
	mainMenuText[0].text << "Play";
	mainMenuText[0].xPos = windowWidth / 2;;
	mainMenuText[0].yPos = 100;
	//Option button
	mainMenuText[1].text << "Options";
	mainMenuText[1].xPos = windowWidth / 2;;
	mainMenuText[1].yPos = 200;
	//Quit button
	mainMenuText[2].text << "Quit";
	mainMenuText[2].xPos = windowWidth / 2;;
	mainMenuText[2].yPos = 300;

	while (mFrontEngine->IsRunning())
	{
		mFrontEngine->DrawScene();

		mouseXPosition = mFrontEngine->GetMouseX();
		mouseYPosition = mFrontEngine->GetMouseY();

		//To give text a shadow effect ensure that black text is drawn first.
		for (int i = 0; i < 3; ++i)
		{
			DrawShadow(mainMenuText[i], mMenuFont);
			mMenuFont->Draw(mainMenuText[i].text.str(), mainMenuText[i].xPos, mainMenuText[i].yPos, mainMenuText[i].textColour, kLeft, kVCentre);
		}
		for (int i = 0; i<3; ++i)
		{
			textWidth = mMenuFont->MeasureTextWidth(mainMenuText[i].text.str());
			if (CheckButtonContact(mouseXPosition, mouseYPosition, mainMenuText[i], textWidth, MAINMENUTEXTOFFSETX, MAINMENUTEXTOFFSETY))
			{
				mainMenuText[i].textColour = kWhite;
				if (mFrontEngine->KeyHeld(Mouse_LButton))
				{
					mainMenuText[i].keyPress = true;
				}
			}
			else
			{
				mainMenuText[i].textColour = kRed;
			}
		}
		//Play button
		if (mainMenuText[0].keyPress)
		{
			mainMenuText[0].keyPress = false;
			mShowMaps();
		}
		//Option button
		if (mainMenuText[1].keyPress)
		{
			mainMenuText[1].keyPress = false;
			mControls();
		}
		//Quit button
		if (mainMenuText[2].keyPress)
		{
			mFrontEngine->Stop();
		}
	}
}

void cGameFront::mControls()
{
	int windowWidth = mFrontEngine->GetWidth();
	int mouseXPosition;
	int mouseYPosition;
	int textWidth;//Variable used in determining the toggle range of buttons/onscreen text.
	bool changeKeyMenu = false;

	//Back button
	textData backText;
	backText.text << "Back";
	backText.xPos = windowWidth / 2;
	backText.yPos = 500;

	textData changeKeyText;

	changeKeyText.text << "Please enter a new key bind.";

	changeKeyText.xPos = 600;

	changeKeyText.yPos = 50;

	textData cancelKeyChange;

	cancelKeyChange.text << "Cancel";

	cancelKeyChange.xPos = 1000;

	cancelKeyChange.yPos = 50;


	const int numControls = 5;
	const unsigned int defaultTextcolour = kRed;
	string newKeyChar;
	textData controlText[numControls];

	ReadControls(infile, controlFile, defaultControls, gameControl, controlText, keyOutput);

	//X Positions
	controlText[0].xPos = windowWidth / 2;;
	controlText[1].xPos = windowWidth / 2;;
	controlText[2].xPos = windowWidth / 2;;
	controlText[3].xPos = windowWidth / 2;;
	controlText[4].xPos = windowWidth / 2;;
	//Y Positions
	controlText[0].yPos = 100;
	controlText[1].yPos = 120;
	controlText[2].yPos = 140;
	controlText[3].yPos = 160;
	controlText[4].yPos = 180;

	while (mFrontEngine->IsRunning())
	{
		mFrontEngine->DrawScene();

		mouseXPosition = mFrontEngine->GetMouseX();
		mouseYPosition = mFrontEngine->GetMouseY();

		//For loop used to draw text. Cleaner than multiple Draw statements.
		for (int i = 0; i < numControls; ++i)
		{
			DrawShadow(controlText[i], mMenuFont);
			mMenuFont->Draw(controlText[i].text.str(), controlText[i].xPos, controlText[i].yPos, controlText[i].textColour, kLeft, kVCentre);
		}
		//Draw back button text seperately because its not part of an array.
		DrawShadow(backText, mMenuFont);
		mMenuFont->Draw(backText.text.str(), backText.xPos, backText.yPos, backText.textColour, kLeft, kVCentre);
		//Record the width of the text being drawn so the size of the bounding box to check for button clicks is accurate.
		textWidth = mMenuFont->MeasureTextWidth(backText.text.str());
		if (CheckButtonContact(mouseXPosition, mouseYPosition, backText, textWidth, OPTIONMENUTEXTOFFSETX, OPTIONMENUTEXTOFFSETY))
		{
			backText.textColour = kWhite;
			if (mFrontEngine->KeyHeld(Mouse_LButton))
			{
				changeKeyMenu = false;
				return;
			}
		}
		else
		{
			backText.textColour = defaultTextcolour;
		}
		for (int i = 0; i<numControls; ++i)
		{
			textWidth = mMenuFont->MeasureTextWidth(controlText[i].text.str());
			if (CheckButtonContact(mouseXPosition, mouseYPosition, controlText[i], textWidth, OPTIONMENUTEXTOFFSETX, OPTIONMENUTEXTOFFSETY) && changeKeyMenu == false)
			{
				controlText[i].textColour = kWhite;
				if (mFrontEngine->KeyHeld(Mouse_LButton))
				{
					controlText[i].keyPress = true;
					changeKeyMenu = true;
				}
			}
			else
			{
				controlText[i].textColour = defaultTextcolour;
			}
		}
		//CHANGING KEY BINDS!!
		if (changeKeyMenu)
		{
			DrawShadow(changeKeyText, mMenuFont);
			DrawShadow(cancelKeyChange, mMenuFont);
			mMenuFont->Draw(changeKeyText.text.str(), changeKeyText.xPos, changeKeyText.yPos, changeKeyText.textColour, kLeft, kVCentre);
			mMenuFont->Draw(cancelKeyChange.text.str(), cancelKeyChange.xPos, cancelKeyChange.yPos, cancelKeyChange.textColour, kLeft, kVCentre);//Cancel button.
			textWidth = mMenuFont->MeasureTextWidth(cancelKeyChange.text.str());
			//Checking contact with cancel button if player selects a key that they don't want to change or they change their mind about changing a key. 
			if (CheckButtonContact(mouseXPosition, mouseYPosition, cancelKeyChange, textWidth, OPTIONMENUTEXTOFFSETX, OPTIONMENUTEXTOFFSETY))
			{
				cancelKeyChange.textColour = kWhite;
				if (mFrontEngine->KeyHeld(Mouse_LButton))
				{
					changeKeyMenu = false;
				}
			}
			else
			{
				cancelKeyChange.textColour = defaultTextcolour;
			}

			int tempKeyBindValue;
			for (unordered_map<int, string>::iterator it = keyOutput.begin(); it != keyOutput.end(); ++it)
			{
				tempKeyBindValue = it->first;//The iterator moves through the list and the int value is stored.
				for (int i = 0; i < numControls; ++i)
				{
					if (controlText[i].keyPress)
					{
						ChangeKeyBind(controlText[i], changeKeyMenu, mFrontEngine, tempKeyBindValue, it, gameControl[i]);
					}
				}
			}
		}
	}
}

void cGameFront::mShowMaps()
{
	cGameInstance* newGame = new cGameInstance(mFrontEngine, "Industrial.txt");
}
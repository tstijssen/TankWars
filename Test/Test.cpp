// GameIdea1.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <fstream>		// used to read the game map from a text file
#include <vector>
#include <string>
#include "MapLoader.h"
#include "Tank.h"

using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	
	myEngine->StartWindowed();

	myEngine->SetWindowCaption("TankWars");

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("Media");

	/**** Set up your scene here ****/
	ICamera* myCamera = myEngine->CreateCamera(kManual);
	IMesh* tankMesh = myEngine->LoadMesh("HoverTank08.x");
	IMesh* planetTest = myEngine->LoadMesh("Planet.x");
	IModel* planet = planetTest->CreateModel(10.0f, 0.5f, 2.0f);
	planet->SetSkin("MoonHi.jpg");
	planet->Scale(10);

	


	float matrix[16];

	vector<IModel*> mapModels;

	cTank* player = new cTank(tankMesh, 1, myCamera);

	string industMap = "Industrial.txt";

	LoadMap(myEngine, mapModels, industMap);

	myCamera->Move(0.0f, 20.0f, 10.0f);
	myCamera->RotateX(50.0f);



	float frameTime;

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		frameTime = myEngine->Timer();

		player->mRotateTurret(myEngine->GetMouseMovementX() * 20, frameTime);

		planet->GetMatrix(matrix);
		matrix[3] = myCamera->GetX();
		matrix[7] = myCamera->GetY();
		matrix[11] = myCamera->GetZ();
		planet->SetMatrix(matrix);

		if (myEngine->KeyHeld(Key_Space))
		{
			player->mBoostMove(frameTime);
		}
		else if (myEngine->KeyHeld(Key_W) || myEngine->KeyHeld(Key_S) || myEngine->KeyHeld(Key_A) || myEngine->KeyHeld(Key_D))
		{
			if (myEngine->KeyHeld(Key_W))
			{
				player->mMove(20.0f, 0.0f, frameTime);
			}
			if (myEngine->KeyHeld(Key_S))
			{
				player->mMove(-20.0f, 0.0f, frameTime);
			}
			if (myEngine->KeyHeld(Key_A))
			{
				player->mMove(0.0f, -20.0f, frameTime);
			}
			if (myEngine->KeyHeld(Key_D))
			{
				player->mMove(0.0f, 20.0f, frameTime);
			}
		}
		else
		{
			player->mStopEngine();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

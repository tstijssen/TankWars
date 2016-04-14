// GameIdea1.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <fstream>		// used to read the game map from a text file
#include <vector>
#include <string>
#include "FrontEnd.h"

using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	
	myEngine->StartWindowed(1600, 900);

	myEngine->SetWindowCaption("TankWars");

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("Media");

	cGameFront* cFrontEnd = new cGameFront(myEngine);

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

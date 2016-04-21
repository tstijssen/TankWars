#include <fstream>		// used to read the game map from a text file
#include "MapLoader.h"
#include <sstream>
#include <iterator>

void LoadMap(I3DEngine* myEngine, building_vector& mapModels, string mapName)
{
	ifstream map;	// input file to be opened for the map
	map.open(mapName);	// open this map to read and create the game world
	bool mapSuccess;	// determines if the map was opened successfuly
	if (!map)
	{
		mapSuccess = false;	// only try reading the map if it has opened successfully
	}
	else
	{
		mapSuccess = true;

		int numOfModels;
		string currrentModel;	// contains the current extracted word
		string boundingBox;
		while (!map.eof())
		{
			getline(map, currrentModel);	// get the model name
			if (currrentModel == "")		// make sure the model name is extracted from the map file
			{
				getline(map, currrentModel);
			}
			
			if (currrentModel == "End")
			{
				return;
			}
			getline(map, boundingBox);	// get the bounding box

			std::istringstream buf(boundingBox);
			std::vector<std::string> output{ std::istream_iterator<std::string>(buf),
				std::istream_iterator<std::string>() };



			IMesh* tmp = myEngine->LoadMesh(currrentModel + ".x");	// load the model mesh

			float coordinates[5];	// contains the position, Y rotation and scale of the model
			map >> numOfModels;		// extract the number of models in the map

			char currentItem = ' ';	// holds the last extracted char from the map
			string createdWord;		// holds the current word, defined to finish by comma
			int coordInt = 0;		// counts the number of coordinate items extracted, used to determine if the model can be created
			sBuilding newBuilding;
			newBuilding.mBoundingMinX = std::stof(output[0]);
			newBuilding.mBoundingMinY = std::stof(output[1]);
			newBuilding.mBoundingMinZ = std::stof(output[2]);
			newBuilding.mBoundingMaxX = std::stof(output[3]);
			newBuilding.mBoundingMaxY = std::stof(output[4]);
			newBuilding.mBoundingMaxZ = std::stof(output[5]);
			newBuilding.mCollidable = true;
			newBuilding.mType = Scenery;

			for (int i = 0; i < numOfModels; i++)	// create models
			{
				createdWord.clear();				// clear the last word
				while (createdWord != ";")	// the end of a model's coordinates is defined by the modelName
				{
					map >> currentItem;		// get next item
					if (currentItem == ',')	// check if it marks the end of a word
					{
						if (createdWord == "A")			// air support building
						{
							newBuilding.mType = AirSupport;
						}
						else if (createdWord == "B")	// breakable terrain
						{
							newBuilding.mType = BreakableScenery;
						}
						else if (createdWord == "E")	// enemy base
						{
							newBuilding.mType = NPCBase;
						}
						else if (createdWord == "N")	// non-collidable
						{
							newBuilding.mCollidable = false;
						}
						else if (createdWord == "P")	// player base
						{
							newBuilding.mType = PlayerBase;
						}
						else if (createdWord == "U")	// upgrades building
						{
							newBuilding.mType = Upgrades;
						}
						else if (createdWord != "")
						{
							coordinates[coordInt] = stof(createdWord);	// convert the word to float and store it

						}
						coordInt++;
						createdWord.clear();
					}
					else
					{
						createdWord += currentItem;	// construct the word one by one by item
					}

					if (coordInt == 6)	// if all coordinate items have been stored
					{
						coordInt = 0; // reset
						newBuilding.mModel = tmp->CreateModel(coordinates[0], coordinates[1], coordinates[2]);	// create
						newBuilding.mBoundingMinX += coordinates[0];
						newBuilding.mBoundingMinY += coordinates[1];
						newBuilding.mBoundingMinZ += coordinates[2];
						newBuilding.mBoundingMaxX += coordinates[0];
						newBuilding.mBoundingMaxY += coordinates[1];
						newBuilding.mBoundingMaxZ += coordinates[2];
						newBuilding.mModel->RotateLocalY(coordinates[3]);
						newBuilding.mModel->Scale(coordinates[4]);
						mapModels.push_back(newBuilding);	// add model to world models vector
					}
				}
			}
		}
	}
}
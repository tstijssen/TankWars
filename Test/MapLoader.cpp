#include <fstream>		// used to read the game map from a text file
#include "MapLoader.h"

void LoadMap(I3DEngine* myEngine, vector<IModel*>& mapModels, string mapName)
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

		while (!map.eof())
		{
			getline(map, currrentModel);	// get the model name

			if (currrentModel == "")		// make sure the model name is extracted from the map file
			{
				getline(map, currrentModel);
			}

			IMesh* tmp = myEngine->LoadMesh(currrentModel + ".x");	// load the model mesh

			float coordinates[5];	// contains the position, Y rotation and scale of the model
			map >> numOfModels;		// extract the number of models in the map

			char currentItem = ' ';	// holds the last extracted char from the map
			string createdWord;		// holds the current word, defined to finish by comma
			int coordInt = 0;		// counts the number of coordinate items extracted, used to determine if the model can be created

			for (int i = 0; i < numOfModels; i++)	// create models
			{
				createdWord.clear();				// clear the last word
				while (createdWord != currrentModel)	// the end of a model's coordinates is defined by the modelName
				{
					map >> currentItem;		// get next item
					if (currentItem == ',')	// check if it marks the end of a word
					{
						coordinates[coordInt] = stof(createdWord);	// convert the word to float and store it
						coordInt++;
						createdWord.clear();
					}
					else
					{
						createdWord += currentItem;	// construct the word one by one by item
					}

					if (coordInt == 5)	// if all coordinate items have been stored
					{
						coordInt = 0; // reset
						IModel* newModel = tmp->CreateModel(coordinates[0], coordinates[1], coordinates[2]);	// create
						newModel->RotateLocalY(coordinates[3]);
						newModel->Scale(coordinates[4]);
						mapModels.push_back(newModel);	// add model to world models vector
					}
				}
			}
		}
	}
}
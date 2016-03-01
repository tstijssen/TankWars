#ifndef MapLoader
#define MapLoader
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <vector>
using namespace tle;

void LoadMap(I3DEngine* myEngine, vector<IModel*>& mapModels, string mapName);

#endif
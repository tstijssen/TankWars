#ifndef Scan
#define Scan

#include "PowerUp.h"

class CScan : public IPowerUp
{
	tle::IMesh* mHPMesh;
	tle::IModel* mPowerUpModel;

	float position[3];
	int teamNumber;

public:



};

#endif
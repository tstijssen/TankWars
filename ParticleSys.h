#ifndef ParticleSys
#define ParticleSys

#include "TypeDefs.h"

class cParticleSystem
{
	model_Vector mModels;	// the model used for the particles
					// the starting x,y,z positions, used to reset them after being used
	bool mActive = false;
	float mStartX = 0.0f;
	float mStartY = 0.0f;
	float mStartZ = 0.0f;
	std::vector<float> mLifeTime;	// the amount of time a particle lasts before resetting
public:
	cParticleSystem(tle::IMesh*, tle::IModel*, int, std::string, float);
	void mRun(float);
	void mGunSmoke(float, tle::ISceneNode*);
	void mImpact(float);
	void mActivate();
	void mDeactivate();
};


#endif
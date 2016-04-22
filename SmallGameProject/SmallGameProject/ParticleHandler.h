#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H
#include "Observer.h"
#include "Algorithm.h"
class ParticleHandler :
	public Observer
{
private:

public:
	ParticleHandler();
	virtual ~ParticleHandler();
	void Shutdown();


	virtual void OnNotify(const Entity* entity, Events::ENTITY evnt);
};

#endif
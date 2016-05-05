#ifndef OBSERVER_H
#define OBSERVER_H

#include "EventLib.h"
class Entity;

class Observer {

private:

public:
	Observer();
	virtual ~Observer();
	virtual void onNotify(Entity* entity, Events::ENTITY evnt) = 0;
	virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets) = 0;
	virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, int triggerDelay) = 0;
	virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, int triggerDelay, float arcOnSplit, int projectilesOnSplit) = 0;
	virtual void onNotify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets) = 0;
};

#endif
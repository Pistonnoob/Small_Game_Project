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
    virtual void onNotify(Entity* entity, Events::BOSS evnt, float arc, int nrOfBullets) = 0;
};

#endif
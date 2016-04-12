#ifndef OBSERVER_H
#define OBSERVER_H

#include "Entity.h"
#include "EventLib.h"

class Observer {

private:
	
public:
	Observer();
	virtual ~Observer();
	virtual void onNotify(const Entity& entity, Events::ENTITY evnt) = 0;
};

#endif
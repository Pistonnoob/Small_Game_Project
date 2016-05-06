#ifndef OBSERVER_H
#define OBSERVER_H

#include "EventLib.h"
class Entity;

class Observer {

private:
	
public:
	Observer();
	virtual ~Observer();
	virtual void OnNotify(const Entity* entity, Events::ENTITY evnt) = 0;
};

#endif
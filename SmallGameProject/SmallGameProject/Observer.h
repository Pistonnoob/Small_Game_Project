#ifndef OBSERVER_H
#define OBSERVER_H

#include "Subject.h";
#include "EventLib.h"

class Observer {

private:
	
public:
	Observer();
	virtual ~Observer();
	virtual void onNotify(const Subject& subject, Events::ENTITY evnt) = 0;
};

#endif
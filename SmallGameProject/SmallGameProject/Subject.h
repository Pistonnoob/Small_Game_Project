#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

class Subject {

protected:
	std::set<Observer*> observers;

private:


public:
	Subject();
	virtual ~Subject();
	virtual void addObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
    virtual void notify(Entity* entity, Events::ENTITY evnt) = 0;
};

#endif
#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

class Subject {

private:
	std::set<Observer*> observers;
	virtual void notify(const Entity& entity, Events::ENTITY evnt) = 0;

public:
	Subject();
	virtual ~Subject();
	virtual void addObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
};

#endif
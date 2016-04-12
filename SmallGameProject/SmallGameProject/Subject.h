#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

class Subject {

private:
	std::set<Observer*> observers;
	void notify(const Entity& entity, Events::ENTITY evnt);

public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
};

#endif
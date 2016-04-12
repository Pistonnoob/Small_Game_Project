#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include"Observer.h"

class Subject {

private:
	std::set<Observer*> observers;

public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
};

#endif
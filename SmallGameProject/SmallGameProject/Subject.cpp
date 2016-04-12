#include "Subject.h"

void Subject::notify(const Entity& entity, Events::ENTITY evnt)
{
	//Send the event to all the observers
	std::set<Observer*>::iterator it;										//Create the iterator
	
	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate
		
		Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
		e->onNotify(entity, evnt);											//Notify
	}
}

void Subject::addObserver(Observer* observer)
{
	this->observers.insert(observer);
}

void Subject::removeObserver(Observer* observer)
{
	this->observers.erase(observer);
}

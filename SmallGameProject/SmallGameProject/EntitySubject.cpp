#include "EntitySubject.h"

EntitySubject::EntitySubject()
	:Subject()
{

}

EntitySubject::~EntitySubject()
{
	std::set<Observer*>::iterator it;
	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate
		//delete all observers
		Observer* e = *it;
		delete e;
	}
	this->observers.clear();
}

void EntitySubject::notify(const Entity* entity, Events::ENTITY evnt)
{
	//Send the event to all the observers
	std::set<Observer*>::iterator it;										//Create the iterator

	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate

		Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
		e->onNotify(entity, evnt);											//Notify
	}
}

void EntitySubject::addObserver(Observer* observer)
{
	this->observers.insert(observer);
}

void EntitySubject::removeObserver(Observer* observer)
{
	this->observers.erase(observer);
}

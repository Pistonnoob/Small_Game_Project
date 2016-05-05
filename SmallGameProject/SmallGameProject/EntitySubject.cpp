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
void EntitySubject::ShutDown()
{
    this->observers.clear();
}
void EntitySubject::notify(Entity* entity, Events::ENTITY evnt)
{
	//Send the event to all the observers
	std::set<Observer*>::iterator it;										//Create the iterator

	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate

		Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
		e->onNotify(entity, evnt);											//Notify
	}

}
void EntitySubject::notify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{
    //Send the event to all the observers
    std::set<Observer*>::iterator it;										//Create the iterator

    for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate

        Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
        e->onNotify(entity, evnt, arc, nrOfBullets);						//Notify
    }
}

void EntitySubject::notify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, int triggerDelay)
{
	//Send the event to all the observers
	std::set<Observer*>::iterator it;										//Create the iterator

	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate

		Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
		e->onNotify(entity, evnt, arc, nrOfBullets, triggerDelay);						//Notify
	}
}

void EntitySubject::notify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, int triggerDelay, float arcOnSplit, int projectilesOnSplit)
{
	//Send the event to all the observers
	std::set<Observer*>::iterator it;										//Create the iterator

	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate

		Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
		e->onNotify(entity, evnt, arc, nrOfBullets, triggerDelay, arcOnSplit, projectilesOnSplit);						//Notify
	}
}

void EntitySubject::notify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets)
{
	//Send the event to all the observers
	std::set<Observer*>::iterator it;										//Create the iterator

	for (it = this->observers.begin(); it != this->observers.end(); it++) {	//Iterate

		Observer* e = *it;													//Create a pointer and set it to the object the iterator is pointing to
		e->onNotify(entity, evnt, arc, nrOfBullets);						//Notify
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

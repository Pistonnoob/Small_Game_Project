#ifndef ENTITYSUBJECT_H
#define ENTITYSUBJECT_H

#include "Subject.h"

class EntitySubject : public Subject{

	private:
		std::set<Observer*> observers;

	public:
		EntitySubject();
		virtual ~EntitySubject();
        void ShutDown();
		virtual void addObserver(Observer* observer);
		virtual void removeObserver(Observer* observer);
        void notify(Entity* entity, Events::ENTITY evnt);
        void notify(Entity* entity, Events::BOSS evnt, float arc, int nrOfBullets);

};

#endif
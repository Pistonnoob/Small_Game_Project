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
        void notify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);
		void notify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay);
		void notify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay, float arcOnSplit, int projectilesOnSplit);
		void notify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets);

};

#endif
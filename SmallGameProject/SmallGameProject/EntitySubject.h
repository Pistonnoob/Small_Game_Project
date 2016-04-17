#ifndef ENTITYSUBJECT_H
#define ENTITYSUBJECT_H

#include "Subject.h"

class EntitySubject : public Subject{

	private:
		std::set<Observer*> observers;
		void notify(const Entity* entity, Events::ENTITY evnt);

	public:
		EntitySubject();
		virtual ~EntitySubject();
		virtual void addObserver(Observer* observer);
		virtual void removeObserver(Observer* observer);

};

#endif
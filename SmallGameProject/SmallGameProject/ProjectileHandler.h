#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Observer.h"

class ProjectileHandler : public Observer {

private:


	virtual void OnNotify(const Entity* entity, Events::ENTITY evnt) = 0;
public:

};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#include "BoundingVolume.h"
#include "EntitySubject.h"
#include "Model.h"

class Entity {

private:
	int posX;
	int posY;
	
	Model* entityModel;
	BoundingVolume* entityBV;
	EntitySubject entitySubject;

public:
	Entity(Model* model);
	~Entity();
};

#endif
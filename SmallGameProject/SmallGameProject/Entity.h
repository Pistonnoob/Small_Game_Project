#ifndef ENTITY_H
#define ENTITY_H

#include "SphereBoundingVolume.h"
#include "EntitySubject.h"
#include "Model.h"

class Entity {

protected:
	int posX;
	int posY;
private:
	Model* entityModel;
	BoundingVolume* entityBV;
	EntitySubject entitySubject;

public:
	Entity(Model* model);	//Entitys without BoundingVolume
	Entity(Model* model, bool isSphere);	//Entitus with BoundingVolume, true = sphere, false = OOBB
	virtual~Entity();


};

#endif
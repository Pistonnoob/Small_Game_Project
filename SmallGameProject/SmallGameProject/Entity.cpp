#include "Entity.h"

Entity::Entity(Model* model) {
	this->entityModel = model;
	this->entityBV = nullptr;
	this->entitySubject = EntitySubject();
}

Entity::Entity(Model* model, bool isSphere)
{
	this->entityModel = model;

	if (isSphere) {	//For spheres
		this->entityBV = new SphereBoundingVolume();
		this->entityBV->GenerateBounds(model);
	
	}
	else {			//For OOBBs
		
		this->entityBV = new BoxBoundingVolume();
		this->entityBV->GenerateBounds(model);
	}

	this->entitySubject = EntitySubject();
}


Entity::~Entity()
{
	delete this->entityModel;
	delete this->entityBV;
}
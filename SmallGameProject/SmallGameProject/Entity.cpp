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
		this->entityBV->generateBounds(model);
	
	}
	else {			//For OOBBs
		
		/*this->entityBV = new OOBBBoundingVolume();
		this->entityBV->generateBounds(model);*/
	}

	this->entitySubject = EntitySubject();
}


Entity::~Entity()
{
	delete this->entityModel;
}

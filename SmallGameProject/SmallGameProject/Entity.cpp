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

void Entity::setModel(Model * model)
{
    this->entityModel = model;
}

Model * Entity::getModel()
{
    return this->entityModel;
}

DirectX::XMFLOAT3 Entity::getPosition()
{
    DirectX::XMFLOAT3 pos;
    pos.x = this->posX;
    pos.y = 0;
    pos.z = this->posZ;
    return pos;
}


Entity::~Entity()
{
	//delete this->entityModel;
    this->entityModel = nullptr;
	delete this->entityBV;
}
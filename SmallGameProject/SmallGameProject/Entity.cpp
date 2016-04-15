#include "Entity.h"

Entity::Entity(Model* model)
{
	this->entityModel = model;
	this->entityBV = nullptr;
}


Entity::~Entity()
{
	delete this->entityModel;
}
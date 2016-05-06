#include "Entity.h"

Entity::Entity() {
	this->entityModel = nullptr;
	this->entityBV = nullptr;

	this->posX = 0.0f;
	this->posZ = 0.0f;
}

Entity::~Entity()
{

}

bool Entity::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string objFilename, bool isSphere, EntitySubject* entitySub)
{
	this->entityModel = new Model();
	this->entitySubject = entitySub;
	//If we fail to initialize the model
	if (!this->entityModel->Initialize(device, deviceContext, objFilename))
	{
		return false;
	}
	
	//Generate the Bounding volume
	if (isSphere) {
		this->entityBV = new SphereBoundingVolume();
		this->entityBV->GenerateBounds(this->entityModel);
	}
	else {
		this->entityBV = new BoxBoundingVolume();
		this->entityBV->GenerateBounds(this->entityModel);
	}


	return true;
}

bool Entity::Initialize(Model * model, EntitySubject* entitySubject, bool isSphere)
{
    this->entitySubject = entitySubject;

	this->entityModel = model;

	//Generate the Bounding volume
	if (isSphere) {
		this->entityBV = new SphereBoundingVolume();
		this->entityBV->GenerateBounds(this->entityModel);
	}
	else {
		this->entityBV = new BoxBoundingVolume();
		this->entityBV->GenerateBounds(this->entityModel);
	}


	return true;
}

void Entity::Shutdown(bool isEnemy)
 {
	if (this->entityModel && !isEnemy) 
	{
		this->entityModel->Shutdown();
		delete this->entityModel;
		this->entityModel = nullptr;
	}

	if (this->entityBV) 
	{
		delete this->entityBV;
	}
	this->entityBV = nullptr;
}
void Entity::addObservers(Observer * observer)
{
    this->entitySubject->addObserver(observer);
}

DirectX::XMFLOAT3 Entity::getAimDir()
{
	return DirectX::XMFLOAT3(0, 0, 0);
}

EntitySubject * Entity::getEntitySubject() const
{
	return this->entitySubject;
}

Type Entity::getType()
{
    return this->myType;
}

Model* Entity::getModel()
{
    return this->entityModel;
}

BoundingVolume* Entity::getBV()
{
    return this->entityBV;
}

DirectX::XMFLOAT3 Entity::getPosition()
{
    DirectX::XMFLOAT3 pos;
    pos.x = this->posX;
    pos.y = 0;
    pos.z = this->posZ;
    return pos;
}





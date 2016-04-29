#include "Entity.h"

Entity::Entity() {
	this->entityModel = nullptr;
	this->entityBV = nullptr;
	this->entitySubject = EntitySubject();
}

Entity::~Entity()
{

}

bool Entity::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string objFilename, bool isSphere)
{
	//If we fail to initialize the model
	this->entityModel = new Model();
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

bool Entity::Initialize(Model * model, bool isSphere)
{
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
	if (this->entityModel && !isEnemy) {
		this->entityModel->Shutdown();
		delete this->entityModel;
		this->entityModel = nullptr;
	}

	if (this->entityBV) {
		delete this->entityBV;
	}
	this->entityBV = nullptr;

}

Model* Entity::GetModel()
{
    return this->entityModel;
}



DirectX::XMFLOAT3 Entity::GetPosition()
{
    DirectX::XMFLOAT3 pos;
    pos.x = this->posX;
    pos.y = 0;
    pos.z = this->posZ;
    return pos;
}

const BoundingVolume * Entity::GetBoundingVolume()
{
	return this->entityBV;
}





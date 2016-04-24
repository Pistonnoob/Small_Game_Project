#include "Entity.h"

Entity::Entity() {
	this->entityModel = new Model();
	this->entityBV = nullptr;
	this->entitySubject = EntitySubject();
}

Entity::~Entity()
{

}

bool Entity::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string objFilename, bool isSphere)
{
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

void Entity::Shutdown()
{
	if (this->entityModel) {
		this->entityModel->Shutdown();
		delete this->entityModel;
		this->entityModel = nullptr;
	}

	if (this->entityBV) {
		delete this->entityBV;
		this->entityBV = nullptr;
	}

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





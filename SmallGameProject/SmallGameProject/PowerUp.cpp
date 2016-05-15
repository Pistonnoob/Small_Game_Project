#include "PowerUp.h"

PowerUp::PowerUp(Events::UNIQUE_FIRE type) : Entity()
{
	this->posX = 0;
	this->posZ = 0;

	this->type = type;
}

PowerUp::~PowerUp()
{

}

void PowerUp::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string powerUpModelFilename, bool isSphere, EntitySubject* entitySub)
{
	Entity::Initialize(device, deviceContext, powerUpModelFilename, isSphere, entitySub);
}

float PowerUp::GetTimeLeft() const
{
	return this->timeLeft;
}

void PowerUp::SetTimePowerup(float timeActive)
{
	this->timeLeft = timeActive;
}

Events::UNIQUE_FIRE PowerUp::GetType() const
{
	return this->type;
}

bool PowerUp::Update(float dt)
{
	//Initial offset
	
	//create the new world matrix
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f);
	worldMatrix *= DirectX::XMMatrixTranslation(this->posX, 0, this->posZ);

	//Set the model matrix
	this->entityModel->SetWorldMatrix(worldMatrix);

	//Update the bounding box pos and rotation
	this->entityBV->UpdateBoundingVolume(worldMatrix);

	float convTime = dt / 1000000;
	bool activePow = true;
	//dt är förgången tid per frame
	this->timeLeft -= convTime;
	
	if (this->timeLeft < 0.0f)
	{
		activePow = false;
	}

	return activePow;
}

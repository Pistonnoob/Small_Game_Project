#include "PowerUp.h"

PowerUp::PowerUp() : Entity()
{
	this->posX = 0;
	this->posZ = 0;
}

PowerUp::~PowerUp()
{

}

float PowerUp::getTimeLeft() const
{
	return this->timeLeft;
}

void PowerUp::setTimePowerup(float timeActive)
{
	this->timeLeft = timeActive;
}

bool PowerUp::Update(float dt)
{
	/*
	//this->HandleInput(input, deltaTime);

	DirectX::XMMATRIX playerWorldMatrix;
	this->entityModel->GetWorldMatrix(playerWorldMatrix);

	//Initial offset
	DirectX::XMMATRIX offset = DirectX::XMMatrixTranslation(this->posX, 0, this->posZ);
	//create the new world matrix
	playerWorldMatrix = offset;

	//Set the model matrix
	this->entityModel->SetWorldMatrix(playerWorldMatrix);

	//Update the bounding box pos and rotation
	this->entityModel->GetWorldMatrix(playerWorldMatrix);
	this->entityBV->UpdateBoundingVolume(playerWorldMatrix);

	*/
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

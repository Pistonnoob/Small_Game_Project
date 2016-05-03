#include "PowerUp.h"

PowerUp::PowerUp()
{

}

PowerUp::~PowerUp()
{

}

float PowerUp::getTimeLeft() const
{
	return this->timeLeft;
}

void PowerUp::startPowerup(float timeActive)
{
	this->timeLeft = timeActive;
}

bool PowerUp::Update(float dt)
{
	bool result = false;
	//dt är förgången tid per frame
	this->timeLeft -= dt;
	if (this->timeLeft < 0.0f)
	{
		result = true;
	}
	return result;
}

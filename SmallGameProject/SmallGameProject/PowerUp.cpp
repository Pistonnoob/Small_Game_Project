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

void PowerUp::setTimePowerup(float timeActive)
{
	this->timeLeft = timeActive;
}

bool PowerUp::Update(float dt)
{
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

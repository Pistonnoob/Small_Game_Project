#include "Ability.h"
Ability::Ability()
{
	this->isActivated = false;
	this->counter = 0;
	this->cdCounter = 0;
	this->chargesLeft = 0;
	this->chargesRefresh = 0;
}
Ability::~Ability()
{
}
void Ability::Initialize(float arc, int nrOfProjectiles, int cooldown, int attackDelay, int maxCharges, int triggerDelay)
{
	this->arc = arc;
	this->nrOfProjectiles = nrOfProjectiles;
	this->cooldown = cooldown;
	this->attackDelay = attackDelay;
	this->maxCharges = maxCharges;
	this->triggerDelay = triggerDelay;
	if (this->cooldown < this->triggerDelay)
	{
		this->cooldown = this->triggerDelay + 1;
	}

}
void Ability::update(Enemy * enemy, EntitySubject * entitySubject)
{
	if (this->isActivated == true || this->chargesLeft < this->maxCharges)
	{
		this->cdCounter++;
		this->chargesRefresh++;
	}

	if (this->chargesRefresh > this->cooldown && this->chargesLeft < this->maxCharges)
	{
		this->chargesRefresh = 0;
		this->chargesLeft++;
	}
}

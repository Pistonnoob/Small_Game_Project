#include "Abilities.h"

SplitFire::SplitFire() : Ability()
{
}
SplitFire::~SplitFire()
{
}
void SplitFire::Initialize(float arc, int nrOfProjectiles, int cooldown, int attackDelay, int maxCharges, int triggerDelay, int projectilesOnSplit, float splitArc)
{
	Ability::Initialize(arc, nrOfProjectiles, cooldown, attackDelay, maxCharges, triggerDelay);
	this->projectilesOnSplit = projectilesOnSplit;
	this->splitArc = splitArc;

}
float SplitFire::activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos)
{
	if (this->cdCounter >= this->cooldown || this->chargesLeft > 0)
	{
		this->isActivated = true;
		float x = (playerPos.x - enemy->getPosition().x);
		float z = (playerPos.z - enemy->getPosition().z);

		enemy->setAimDir(DirectX::XMFLOAT3(x, 0, z));

		entitySubject->notify(enemy, Events::UNIQUE_FIRE::SPLITFIRE, this->arc, this->nrOfProjectiles);

		this->cdCounter = 0;
		this->chargesLeft--;

		return this->attackDelay;
	}
	return 0;

}
void SplitFire::update(Enemy* enemy, EntitySubject* entitySubject, float deltaTime)
{
	Ability::update(enemy, entitySubject, deltaTime);
	if (this->isActivated == true)
	{
		this->counter += 5.0f * (deltaTime / 1000000);
	}
	if (this->isActivated == true && this->counter >= this->triggerDelay)
	{
		entitySubject->notify(enemy, Events::ABILITY_TRIGGER::SPLITFIRE_ON_PROJECTILES, this->splitArc, this->projectilesOnSplit);
		this->counter = 0;
		this->isActivated = false;
	}
}
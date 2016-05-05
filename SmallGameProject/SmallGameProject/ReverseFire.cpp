#include "Abilities.h"

ReverseFire::ReverseFire() : Ability()
{
}
ReverseFire::~ReverseFire()
{
}
void ReverseFire::Initialize(float arc, int nrOfProjectiles, float cooldown, int attackDelay, int maxCharges, float triggerDelay)
{
	Ability::Initialize(arc, nrOfProjectiles, cooldown, attackDelay, maxCharges, triggerDelay);

}
float ReverseFire::activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos)
{
	if (this->cdCounter >= this->cooldown || this->chargesLeft > 0)
	{
		this->isActivated = true;
		this->timers.push_back(this->triggerDelay);
		float x = (playerPos.x - enemy->getPosition().x);
		float z = (playerPos.z - enemy->getPosition().z);

		enemy->setAimDir(DirectX::XMFLOAT3(x, 0, z));

		entitySubject->notify(enemy, Events::UNIQUE_FIRE::REVERSERBULLETS, this->arc, this->nrOfProjectiles, this->triggerDelay);

		this->cdCounter = 0;
		this->chargesLeft--;

		return this->attackDelay;
	}
	return -1;
}
void ReverseFire::update(Enemy* enemy, EntitySubject* entitySubject, float deltaTime)
{
	Ability::update(enemy, entitySubject, deltaTime);
	/*for (int i = 0; i < this->timers.size(); i++)
	{
		this->timers.at(i) -= REFRESH_RATE * deltaTime;
		if (this->timers.at(i) <= 0.0f)
		{
			entitySubject->notify(enemy, Events::ABILITY_TRIGGER::REVERSER_PROJECTILES, 0.0f, 0);
			this->timers.erase(this->timers.begin() + i);
		}
	}*/
}
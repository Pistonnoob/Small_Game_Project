#include "Abilities.h"

ReverseFire::ReverseFire() : Ability()
{
}
ReverseFire::~ReverseFire()
{
}
void ReverseFire::Initialize(float arc, int nrOfProjectiles, int cooldown, int attackDelay, int maxCharges, int triggerDelay)
{
	Ability::Initialize(arc, nrOfProjectiles, cooldown, attackDelay, maxCharges, triggerDelay);

}
float ReverseFire::activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos)
{
	if (this->cdCounter >= this->cooldown || this->chargesLeft > 0)
	{
		this->isActivated = true;
		float x = (playerPos.x - enemy->GetPosition().x) * 0.01f;
		float z = (playerPos.z - enemy->GetPosition().z) * 0.01f;

		enemy->SetAimDir(DirectX::XMFLOAT3(x, 0, z));

		entitySubject->Notify(enemy, Events::UNIQUE_FIRE::REVERSERBULLETS, this->arc, this->nrOfProjectiles);

		this->cdCounter = 0;
		this->chargesLeft--;

		return this->attackDelay;
	}
	return 0;
}
void ReverseFire::update(Enemy* enemy, EntitySubject* entitySubject)
{
	Ability::update(enemy, entitySubject);
	if (this->isActivated == true)
	{
		this->counter++;
	}
	if (this->counter >= this->triggerDelay && this->isActivated == true)
	{
		entitySubject->Notify(enemy, Events::ABILITY_TRIGGER::REVERSER_PROJECTILES, 3.14f, 15);
		this->isActivated = false;
		this->counter = 0;
	}
}
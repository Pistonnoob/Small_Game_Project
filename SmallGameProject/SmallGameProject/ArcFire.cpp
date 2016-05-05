#include "Abilities.h"
#include "Algorithm.h"

ArcFire::ArcFire() : Ability()
{
}
ArcFire::~ArcFire()
{
}
void ArcFire::Initialize(float arc, int nrOfProjectiles, float cooldown, int attackDelay, int maxCharges, float triggerDelay)
{
	Ability::Initialize(arc, nrOfProjectiles, cooldown, attackDelay, maxCharges, triggerDelay);

}
float ArcFire::activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos)
{
	if (this->cdCounter >= this->cooldown || this->chargesLeft > 0)
	{
		float x = (playerPos.x - enemy->getPosition().x);
		float z = (playerPos.z - enemy->getPosition().z);

		enemy->setAimDir(DirectX::XMFLOAT3(x, 0, z));

		entitySubject->notify(enemy, Events::UNIQUE_FIRE::ARCFIRE, this->arc, this->nrOfProjectiles);

		this->cdCounter = 0;
		this->chargesLeft--;

		return this->attackDelay;

	}
	return -1;

}
void ArcFire::update(Enemy* enemy, EntitySubject* entitySubject, float deltaTime)
{
	Ability::update(enemy, entitySubject, deltaTime);

}
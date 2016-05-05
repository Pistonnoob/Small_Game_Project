#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
    this->myType = Type::MELEEE;
}

MeleeEnemy::~MeleeEnemy()
{
}

bool MeleeEnemy::Initialize(Model * model, EntitySubject* entitySubject, bool isSphere)
{
    this->aimDir = DirectX::XMFLOAT3(0, 0, 0);
	return Entity::Initialize(model, entitySubject, isSphere);
}

void MeleeEnemy::Shutdown()
{
	Entity::Shutdown(true);
}

void MeleeEnemy::fire(float deltaTime)
{
	if (this->attackCD > M_ATTACK_DELAY)
	{
		this->entitySubject->notify(this, Events::UNIQUE_FIRE::ARCFIRE, 3.14 / 2, 5);
		this->attackCD = 0;
	}
	else
	{
		this->attackCD += deltaTime;
	}
}

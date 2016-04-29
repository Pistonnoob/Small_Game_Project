#include "RangedEnemy.h"

RangedEnemy::RangedEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
    this->myType = Type::RANGED;
}

RangedEnemy::~RangedEnemy()
{
}

bool RangedEnemy::Initialize(Model * model, EntitySubject* entitySubject, bool isSphere)
{
    this->aimDir = DirectX::XMFLOAT3(0, 0, 0);
	return Entity::Initialize(model, entitySubject, isSphere);
}

void RangedEnemy::Shutdown()
{
	Entity::Shutdown(true);
}

void RangedEnemy::fire()
{
    if (this->attackCD > ATTACK_DELAY)
    {
        this->entitySubject->notify(this, Events::ENTITY::Fire);
        this->attackCD = 0;
    }
    else
    {
        this->attackCD++;
    }
}

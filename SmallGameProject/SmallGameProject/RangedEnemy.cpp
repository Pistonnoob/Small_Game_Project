#include "RangedEnemy.h"

RangedEnemy::RangedEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
    this->myType = Type::RANGED;
    this->isAlive = true;
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


void RangedEnemy::Fire(float deltaTime)
{
    if (this->attackCD > R_ATTACK_DELAY)
    {
        this->entitySubject->Notify(this, Events::ENTITY::Fire);
        this->attackCD = 0;
    }
    else
    {
        this->attackCD += deltaTime;
    }
}

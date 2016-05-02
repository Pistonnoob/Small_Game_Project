#include "RangedEnemy.h"

RangedEnemy::RangedEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
}

RangedEnemy::~RangedEnemy()
{
}

bool RangedEnemy::Initialize(Model * model, bool isSphere)
{
	return Entity::Initialize(model, isSphere);
}

void RangedEnemy::Shutdown()
{
	Entity::Shutdown(true);
}

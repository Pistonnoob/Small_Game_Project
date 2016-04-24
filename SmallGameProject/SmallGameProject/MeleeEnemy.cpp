#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
}

MeleeEnemy::~MeleeEnemy()
{
}

bool MeleeEnemy::Initialize(Model * model, bool isSphere)
{
	return Entity::Initialize(model, isSphere);
}

void MeleeEnemy::Shutdown()
{
	Enemy::Shutdown();
}

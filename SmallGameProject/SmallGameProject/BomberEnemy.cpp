#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
}

BomberEnemy::~BomberEnemy()
{
}

bool BomberEnemy::Initialize(Model* model, bool isSphere)
{
	return Entity::Initialize(model, isSphere);
}

void BomberEnemy::Shutdown()
{
	Enemy::Shutdown();
}



#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
    this->myType = Type::RANGED;
}

BomberEnemy::~BomberEnemy()
{
}

bool BomberEnemy::Initialize(Model* model, EntitySubject* entitySubject, bool isSphere)
{
    this->aimDir = DirectX::XMFLOAT3(0, 0, 0);
	return Entity::Initialize(model, entitySubject, isSphere);
}

void BomberEnemy::Shutdown()
{
	Entity::Shutdown(true);
}




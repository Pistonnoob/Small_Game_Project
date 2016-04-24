#include "Enemy.h"

Enemy::Enemy()
: Actor()
{
}

Enemy::~Enemy()
{
}
bool Enemy::Initialize(Model* model, bool isSphere)
{
	if (!Entity::Initialize(model, isSphere)) {
		return false;
	}

	return true;
}
void Enemy::Shutdown()
{
	Entity::Shutdown();
}

void Enemy::moveRight()
{
    this->posX += 0.05f;
}
void Enemy::moveLeft()
{
    this->posX -= 0.05f;
}
void Enemy::moveUp()
{
    this->posZ += 0.05f;
}
void Enemy::moveDown()
{
    this->posZ -= 0.05f;
}
void Enemy::move(DirectX::XMFLOAT3 moveVec)
{
    this->posX += moveVec.x;
    this->posZ += moveVec.z;
}

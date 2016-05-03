#include "Enemy.h"

Enemy::Enemy()
: Actor()
{
}

Enemy::~Enemy()
{
}

void Enemy::moveRight(float deltaTime)
{
    this->posX += 0.05f;
}
void Enemy::moveLeft(float deltaTime)
{
    this->posX -= 0.05f;
}
void Enemy::moveUp(float deltaTime)
{
    this->posZ += 0.05f;
}
void Enemy::moveDown(float deltaTime)
{
    this->posZ -= 0.05f;
}
void Enemy::fire(float deltaTime)
{
    if (this->attackCD > BASE_ATTACK_DELAY)
    {
        this->entitySubject->notify(this, Events::ENTITY::Fire);
        this->attackCD = 0;
    }
    else
    {
        this->attackCD += 1 * (deltaTime / 1000000);
    }
}
void Enemy::move(DirectX::XMFLOAT3 moveVec)
{
    this->posX += moveVec.x;
    this->posZ += moveVec.z;
}

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
    this->posX += MOVEMENT_SPEED * deltaTime;
}
void Enemy::moveLeft(float deltaTime)
{
    this->posX -= MOVEMENT_SPEED * deltaTime;
}
void Enemy::moveUp(float deltaTime)
{
    this->posZ += MOVEMENT_SPEED * deltaTime;
}
void Enemy::moveDown(float deltaTime)
{
	this->posZ -= MOVEMENT_SPEED * deltaTime;
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
        this->attackCD += 1.0f * deltaTime;
    }
}
void Enemy::move(DirectX::XMFLOAT3 moveVec)
{
    this->posX += moveVec.x;
    this->posZ += moveVec.z;
}

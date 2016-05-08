#include "Enemy.h"

Enemy::Enemy()
: Actor()
{
}

Enemy::~Enemy()
{
}

void Enemy::MoveRight()
{
    this->posX += 0.05f;
}
void Enemy::MoveLeft()
{
    this->posX -= 0.05f;
}
void Enemy::MoveUp()
{
    this->posZ += 0.05f;
}
void Enemy::MoveDown()
{
    this->posZ -= 0.05f;
}
void Enemy::Fire()
{
    if (this->attackCD > BASE_ATTACK_DELAY)
    {
        this->entitySubject->Notify(this, Events::ENTITY::Fire);
        this->attackCD = 0;
    }
    else
    {
        this->attackCD++;
    }
}
void Enemy::Move(DirectX::XMFLOAT3 moveVec)
{
    this->posX += moveVec.x;
    this->posZ += moveVec.z;
}

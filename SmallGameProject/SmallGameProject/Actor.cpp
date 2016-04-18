#include "Actor.h"

Actor::Actor() : Entity(nullptr)
{

}

Actor::~Actor()
{
}

void Actor::moveRight()
{
    this->posX += 0.0021f;
}
void Actor::moveLeft()
{
    this->posX -= 0.0021f;
}
void Actor::moveUp()
{
    this->posY += 0.0021f;
}
void Actor::moveDown()
{
    this->posY -= 0.0021f;
}
void Actor::move(DirectX::XMFLOAT3 moveVec)
{
    this->posX += moveVec.x;
    this->posY += moveVec.y;
}
DirectX::XMFLOAT3 Actor::getPosition()
{
    return DirectX::XMFLOAT3(this->posX, this->posY, 10);
}
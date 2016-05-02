#include "Actor.h"

Actor::Actor() : Entity()
{

}

Actor::~Actor()
{
}
void Actor::setAimDir(DirectX::XMFLOAT3 newDir)
{
    this->aimDir = newDir;
}
DirectX::XMFLOAT3 Actor::getAimDir()
{
    return this->aimDir;
}
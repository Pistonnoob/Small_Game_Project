#include "Projectile.h"

Projectile::Projectile() : Entity()
{
    this->posX = 0;
    this->posZ = 0;
    this->origin = DirectX::XMFLOAT3(0, 0, 0);

}
Projectile::~Projectile()
{

}
void Projectile::Initialize(Model* model, float posX, float posZ, DirectX::XMFLOAT3 moveDir)
{
    this->posX = posX;
    this->posZ = posZ;
    this->moveDir = moveDir;
    this->origin = DirectX::XMFLOAT3(posX, 0, posZ);
    //this->setModel(model);
    Entity::Initialize(model, false);
}
void Projectile::Shutdown()
{
    Entity::Shutdown(true);
}
void Projectile::update()
{
    this->posX += this->moveDir.x;
    this->posZ += this->moveDir.z;
}
void Projectile::setMoveDir(DirectX::XMFLOAT3 newMoveDir)
{
    this->moveDir = newMoveDir;
}
DirectX::XMFLOAT3 Projectile::getOrigin()
{
    return this->origin;
}
DirectX::XMFLOAT3 Projectile::getMoveDir()
{
    return this->moveDir;
}
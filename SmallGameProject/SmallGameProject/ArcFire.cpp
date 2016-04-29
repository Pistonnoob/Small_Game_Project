#include "Abilities.h"
#include "Algorithm.h"

ArcFire::ArcFire()
{
    this->isActivated = false;
}
ArcFire::~ArcFire()
{
}
void ArcFire::activate(Actor* actor, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles)
{
    float x = playerPos.x - actor->getPosition().x;
    float z = playerPos.z - actor->getPosition().z;
    Enemy* ptr;
    actor->setAimDir(DirectX::XMFLOAT3(x, 0, z));

    entitySubject->notify(actor, Events::BOSS::ARCFIRE, arc, nrOfProjectiles);
    /*DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationY(-angle / 2);
    DirectX::XMVECTOR dirVec = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
    dirVec = DirectX::XMVector3Transform(dirVec, rotate);

    float x = DirectX::XMVectorGetX(dirVec);
    float y = DirectX::XMVectorGetY(dirVec);
    float z = DirectX::XMVectorGetZ(dirVec);*/

    //shootProjetiles(projectiles, projectileModel, pos, DirectX::XMFLOAT3(x, y, z), angle, nrOfProjectiles);

}
void ArcFire::update(Actor* actor, EntitySubject* entitySubject)
{

}
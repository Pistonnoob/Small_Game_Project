#include "Abilities.h"

SplitFire::SplitFire()
{
    this->isActivated = false;
    this->counter = 0;
}
SplitFire::~SplitFire()
{
}
void SplitFire::activate(Actor* actor, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles)
{
    this->isActivated = true;
    /*DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationY(-angle / 2);
    DirectX::XMVECTOR dirVec = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
    dirVec = DirectX::XMVector3Transform(dirVec, rotate);

    float x = DirectX::XMVectorGetX(dirVec);
    float y = DirectX::XMVectorGetY(dirVec);
    float z = DirectX::XMVectorGetZ(dirVec);*/

    //shootProjetiles(projectiles, projectileModel, pos, DirectX::XMFLOAT3(x, y, z), angle, nrOfProjectiles);

}
void SplitFire::update(Actor* actor, EntitySubject* entitySubject)
{
    if (this->isActivated == true)
    {
        this->counter++;
    }
    if (this->isActivated == true && this->counter >= 30)
    {
        /*DirectX::XMMATRIX rotate;
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 dir;
        DirectX::XMVECTOR dirVec;
        Projectile* projectilePtr;

        int size = projectiles.size();
        for (int i = 0; i < size; i++)
        {
            projectilePtr = projectiles.at(i);
            pos = projectilePtr->getPosition();
            dir = projectilePtr->getMoveDir();
            dirVec = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);

            float angle = 3.14f / 2;
            int nrOfProjectiles = 5;
            rotate = DirectX::XMMatrixRotationY(-angle / 2);
            dirVec = DirectX::XMVector3Transform(dirVec, rotate);

            float x = DirectX::XMVectorGetX(dirVec);
            float y = DirectX::XMVectorGetY(dirVec);
            float z = DirectX::XMVectorGetZ(dirVec);

            //shootProjetiles(projectiles, projectilePtr->getModel(), pos, DirectX::XMFLOAT3(x, y, z), angle, nrOfProjectiles);
        }*/
        this->counter = 0;
        this->isActivated = false;
    }
}
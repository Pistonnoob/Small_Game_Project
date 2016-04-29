#include "Abilities.h"

ReverseFire::ReverseFire()
{
    this->isActivated = false;
    this->counter = 0;
}
ReverseFire::~ReverseFire()
{
}
void ReverseFire::activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles)
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
void ReverseFire::update(Enemy* enemy, EntitySubject* entitySubject)
{
    if (this->isActivated == true)
    {
        this->counter++;
    }
    if (this->counter >= 50 && this->isActivated == true)
    {
        /*int size = projectiles.size();
        for (int i = 0; i < size; i++)
        {
            DirectX::XMFLOAT3 dir = projectiles.at(i)->getMoveDir();
            dir.x *= -1;
            dir.y *= -1;
            dir.z *= -1;
            projectiles.at(i)->setMoveDir(dir);
        }*/
        this->isActivated = false;
        this->counter = 0;
    }
}
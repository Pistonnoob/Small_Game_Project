#include "Abilities.h"

SplitFire::SplitFire()
{
    this->isActivated = false;
    this->counter = 0;
}
SplitFire::~SplitFire()
{
}
void SplitFire::activate(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfProjectiles)
{
    this->isActivated = true;
    DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationY(-angle / 2);
    DirectX::XMVECTOR dirVec = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
    dirVec = DirectX::XMVector3Transform(dirVec, rotate);

    float x = DirectX::XMVectorGetX(dirVec);
    float y = DirectX::XMVectorGetY(dirVec);
    float z = DirectX::XMVectorGetZ(dirVec);

    shootProjetiles(projectiles, projectileModel, pos, DirectX::XMFLOAT3(x, y, z), angle, nrOfProjectiles);

}
void SplitFire::update(std::vector<Projectile*>& projectiles, Model* projectileModel)
{
    if (this->isActivated == true)
    {
        this->counter++;
    }
    if (this->isActivated == true && this->counter >= 30)
    {
        int size = projectiles.size();
        for (int i = 0; i < size; i++)
        {
            DirectX::XMFLOAT3 pos = projectiles.at(i)->getPosition();
            DirectX::XMFLOAT3 dir = projectiles.at(i)->getMoveDir();
            DirectX::XMVECTOR dirVec = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);

            float angle = 3.14f / 2;
            int nrOfProjectiles = 15;
            DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationY(-angle / 2);
            dirVec = DirectX::XMVector3Transform(dirVec, rotate);

            float x = DirectX::XMVectorGetX(dirVec);
            float y = DirectX::XMVectorGetY(dirVec);
            float z = DirectX::XMVectorGetZ(dirVec);

            shootProjetiles(projectiles, projectileModel, pos, DirectX::XMFLOAT3(x, y, z), angle, nrOfProjectiles);
        }
        this->counter = 0;
        this->isActivated = false;
    }
}
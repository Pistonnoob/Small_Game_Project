#include "Abilities.h"

ArcFire::ArcFire()
{
    this->isActivated = false;
}
ArcFire::~ArcFire()
{
}
void ArcFire::activate(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfProjectiles)
{
    DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationY(-angle / 2);
    DirectX::XMVECTOR dirVec = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
    dirVec = DirectX::XMVector3Transform(dirVec, rotate);

    float x = DirectX::XMVectorGetX(dirVec);
    float y = DirectX::XMVectorGetY(dirVec);
    float z = DirectX::XMVectorGetZ(dirVec);

    shootProjetiles(projectiles, projectileModel, pos, DirectX::XMFLOAT3(x, y, z), angle, nrOfProjectiles);
}
void ArcFire::update(std::vector<Projectile*>& projectiles, Model* projectileModel)
{

}
#ifndef ABILITY_H
#define ABILITY_H
#include "Projectile.h"
#include "Model.h"

class Ability
{
private:

protected:
    bool isActivated;


public:
    Ability() { this->isActivated = false; };
    virtual~Ability() {};
    virtual void activate(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfProjectiles) = 0;
    virtual void update(std::vector<Projectile*>& projectiles, Model* projectileModel) = 0;
    void shootProjetiles(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfBullets)
    {
        DirectX::XMMATRIX rotation;
        int nrOfProjectiles = nrOfBullets;
        rotation = DirectX::XMMatrixRotationY(angle / nrOfProjectiles);
        DirectX::XMVECTOR dirr = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
        for (int i = 0; i <= nrOfProjectiles; i++)
        {
            float x = DirectX::XMVectorGetX(dirr);
            float y = DirectX::XMVectorGetY(dirr);
            float z = DirectX::XMVectorGetZ(dirr);
            projectiles.push_back(new Projectile());
            projectiles.at(projectiles.size() - 1)->Initialize(projectileModel, pos.x, pos.z, DirectX::XMFLOAT3(x, y, z));
            //projectiles.at(projectiles.size() - 1).setMoveDir(dirr);
            dirr = DirectX::XMVector3Transform(dirr, rotation);
        }

    }



};
#endif

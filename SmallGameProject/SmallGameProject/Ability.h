#ifndef ABILITY_H
#define ABILITY_H
#include "Projectile.h"
#include "Model.h"
#include "Enemy.h"

class Ability
{
private:

protected:
    bool isActivated;


public:
    Ability() { this->isActivated = false; };
    virtual~Ability() {};
    virtual void activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles) = 0;
    virtual void update(Enemy* enemy, EntitySubject* entitySubject) = 0;
    void shootProjetiles(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfBullets)
    {
        DirectX::XMMATRIX rotation;
        int nrOfProjectiles = nrOfBullets;
        rotation = DirectX::XMMatrixRotationY(angle / nrOfProjectiles);
        DirectX::XMVECTOR dirr = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
        float x;
        float y;
        float z;
        for (int i = 0; i <= nrOfProjectiles; i++)
        {
            x = DirectX::XMVectorGetX(dirr);
            y = DirectX::XMVectorGetY(dirr);
            z = DirectX::XMVectorGetZ(dirr);
            Projectile* temp = new Projectile();
            //temp->Initialize(projectileModel, pos.x, pos.z, DirectX::XMFLOAT3(x, y, z));
            projectiles.push_back(temp);
            //projectiles.at(projectiles.size() - 1)->Initialize(projectileModel, pos.x, pos.z, DirectX::XMFLOAT3(x, y, z));
            dirr = DirectX::XMVector3Transform(dirr, rotation);
        }

    }



};
#endif

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity {

private:

    DirectX::XMFLOAT3 origin;
    DirectX::XMFLOAT3 moveDir;
public:
    Projectile();
    void Initialize(Model* model,EntitySubject* entitySubject, float posX, float posZ, DirectX::XMFLOAT3 moveDir);
    void Shutdown();
    virtual ~Projectile();
    void update();
    void setMoveDir(DirectX::XMFLOAT3 newMoveDir);
    void setPos(DirectX::XMFLOAT3 newPos);
    DirectX::XMFLOAT3 getOrigin();
    DirectX::XMFLOAT3 getMoveDir();
    DirectX::XMFLOAT3 getPos();

};

#endif
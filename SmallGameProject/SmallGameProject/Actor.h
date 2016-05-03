#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"

class Actor : public Entity {

protected:
    DirectX::XMFLOAT3 aimDir;

public:
    Actor();
    virtual~Actor();

    virtual void moveRight(float deltaTime) = 0;
    virtual void moveLeft(float deltaTime) = 0;
    virtual void moveUp(float deltaTime) = 0;
    virtual void moveDown(float deltaTime) = 0;
    virtual void fire() = 0;
    virtual void move(DirectX::XMFLOAT3 moveVec) = 0;
    virtual void setAimDir(DirectX::XMFLOAT3 newDir);
    virtual DirectX::XMFLOAT3 getAimDir();

};

#endif
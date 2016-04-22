#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"

class Actor : public Entity {

private:

public:
    Actor();
    virtual~Actor();
    virtual void moveRight() = 0;
    virtual void moveLeft() = 0;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual void move(DirectX::XMFLOAT3 moveVec) = 0;

};

#endif
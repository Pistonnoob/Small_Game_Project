#ifndef ACTOR_H
#define ACTOR_H

#include "Entity.h"

class Actor : public Entity {

private:

public:
    Actor();
    virtual~Actor();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void move(DirectX::XMFLOAT3 moveVec);
    DirectX::XMFLOAT3 getPosition();

};

#endif
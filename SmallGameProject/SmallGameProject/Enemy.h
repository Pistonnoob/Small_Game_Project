#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"

static int BASE_ATTACK_DELAY = 50;

class Enemy : public Actor {

protected:
    int attackCD;
public:
    Enemy();
    virtual~Enemy();

	virtual bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere) = 0;
	virtual void Shutdown() = 0;
	

    virtual void moveRight();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveDown();
    virtual void fire();
    virtual void move(DirectX::XMFLOAT3 moveVec) ;

};

#endif
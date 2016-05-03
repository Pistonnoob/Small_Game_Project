#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"

static float BASE_ATTACK_DELAY = 0.5f;



class Enemy : public Actor {

protected:
    float attackCD;
public:
    Enemy();
    virtual~Enemy();

	virtual bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere) = 0;
	virtual void Shutdown() = 0;
	

    virtual void moveRight(float deltaTime);
    virtual void moveLeft(float deltaTime);
    virtual void moveUp(float deltaTime);
    virtual void moveDown(float deltaTime);
    virtual void fire(float deltaTime);
    virtual void move(DirectX::XMFLOAT3 moveVec) ;

};

#endif
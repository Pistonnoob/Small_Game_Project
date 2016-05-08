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
	

    virtual void MoveRight();
    virtual void MoveLeft();
    virtual void MoveUp();
    virtual void MoveDown();
    virtual void Fire();
    virtual void Move(DirectX::XMFLOAT3 moveVec) ;

};

#endif
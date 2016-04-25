#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"

class Enemy : public Actor {

private:

public:
    Enemy();
    virtual~Enemy();

	virtual bool Initialize(Model* model, bool isSphere) = 0;
	virtual void Shutdown() = 0;
	

    virtual void moveRight();
    virtual void moveLeft();
    virtual void moveUp();
    virtual void moveDown();
    virtual void move(DirectX::XMFLOAT3 moveVec) ;

};

#endif
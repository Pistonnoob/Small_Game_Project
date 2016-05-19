#ifndef MELEEENEMY_H
#define MELEEENEMY_H

#include "Enemy.h"

static float M_ATTACK_DELAY = 0.75f;
static float M_MOVEMENT_SPEED = 10.0f;

class MeleeEnemy : public Enemy {

private:

public:
    MeleeEnemy(float posX, float posZ);
    virtual~MeleeEnemy();

	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);
	void Shutdown();

	virtual void MoveRight(float deltaTime);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveUp(float deltaTime);
	virtual void MoveDown(float deltaTime);
	virtual void Fire(float deltaTime);
};

#endif
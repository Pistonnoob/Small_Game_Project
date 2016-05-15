#ifndef RANGEDENEMY_H
#define RANGEDENEMY_H

#include "Enemy.h"

static float R_ATTACK_DELAY = 0.5f;
static float R_MOVEMENT_SPEED = 10.0f;


class RangedEnemy : public Enemy {

private:

public:
    RangedEnemy(float posX, float posZ);
    virtual~RangedEnemy();

	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);
	void Shutdown();

	virtual void MoveRight(float deltaTime);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveUp(float deltaTime);
	virtual void MoveDown(float deltaTime);
    virtual void Fire(float deltaTime);
};

#endif
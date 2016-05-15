#ifndef BOMBERENEMY_H
#define BOMBERENEMY_H

#include "Enemy.h"

static float EXPLOSION_DELAY = 5.0f;
static float B_MOVEMENT_SPEED = 20.0f;

class BomberEnemy : public Enemy {

private:

public:
    BomberEnemy(float posX, float posZ);
    virtual~BomberEnemy();

	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);
	void Shutdown();
	virtual bool ChargeExplosion(float deltaTime);

	virtual void MoveRight(float deltaTime);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveUp(float deltaTime);
	virtual void MoveDown(float deltaTime);
	virtual void Fire(float deltaTime);

};

#endif
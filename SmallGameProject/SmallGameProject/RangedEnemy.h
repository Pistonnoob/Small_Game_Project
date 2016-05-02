#ifndef RANGEDENEMY_H
#define RANGEDENEMY_H

#include "Enemy.h"

static int ATTACK_DELAY = 50;

class RangedEnemy : public Enemy {

private:

public:
    RangedEnemy(float posX, float posZ);
    virtual~RangedEnemy();

	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);
	void Shutdown();
    virtual void fire();
};

#endif
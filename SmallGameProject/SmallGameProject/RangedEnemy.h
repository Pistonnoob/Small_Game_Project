#ifndef RANGEDENEMY_H
#define RANGEDENEMY_H

#include "Enemy.h"

class RangedEnemy : public Enemy {

private:

public:
    RangedEnemy(float posX, float posZ);
    virtual~RangedEnemy();

	bool Initialize(Model* model, bool isSphere);
	void Shutdown();
};

#endif
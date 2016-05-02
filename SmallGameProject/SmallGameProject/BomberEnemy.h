#ifndef BOMBERENEMY_H
#define BOMBERENEMY_H

#include "Enemy.h"

class BomberEnemy : public Enemy {

private:

public:
    BomberEnemy(float posX, float posZ);
    virtual~BomberEnemy();

	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);
	void Shutdown();

};

#endif
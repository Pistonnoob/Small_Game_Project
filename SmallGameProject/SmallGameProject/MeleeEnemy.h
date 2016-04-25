#ifndef MELEEENEMY_H
#define MELEEENEMY_H

#include "Enemy.h"

class MeleeEnemy : public Enemy {

private:

public:
    MeleeEnemy(float posX, float posZ);
    virtual~MeleeEnemy();

};

#endif
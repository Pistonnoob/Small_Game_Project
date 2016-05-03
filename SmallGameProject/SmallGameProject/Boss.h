#ifndef BOSS_H
#define BOSS_H


#include "Enemy.h"
#include "Abilities.h"

class Boss : public Enemy {

private:
	std::vector<Ability*> abilities;
	int attackDelay;
public:
	Boss(float posX, float posZ);
	virtual~Boss();

	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere, int nrOfAbilities);
	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere, std::vector<Ability*> abilities);
	void Shutdown();

};

#endif

#ifndef ABILITY_H
#define ABILITY_H
#include "Projectile.h"
#include "Model.h"
#include "Enemy.h"

class Ability
{
private:

protected:
	bool isActivated;

	float arc;
	int nrOfProjectiles;
	int cooldown;
	int attackDelay;
	int maxCharges;
	int triggerDelay;

	float counter;
	float cdCounter;
	int chargesLeft;
	float chargesRefresh;

public:
	Ability();
	virtual~Ability();
	virtual void Initialize(float arc, int nrOfProjectiles, int cooldown, int attackDelay, int maxCharges, int triggerDelay);
	virtual float activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos) = 0;
	virtual void update(Enemy* enemy, EntitySubject* entitySubject, float deltaTime);




};
#endif

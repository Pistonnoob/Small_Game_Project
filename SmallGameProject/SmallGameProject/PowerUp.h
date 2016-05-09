#ifndef POWERUP_H
#define POWERUP_H
#include "Entity.h"

class PowerUp : public Entity
{
private:
	float timeLeft;
	Events::UNIQUE_FIRE type;
public:
	PowerUp(Events::UNIQUE_FIRE type);
	virtual ~PowerUp();

	float GetTimeLeft() const;
	void SetTimePowerup(float timeActive);
	Events::UNIQUE_FIRE GetType() const;


	virtual bool Update(float dt);
};

#endif


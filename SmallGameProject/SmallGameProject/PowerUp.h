#ifndef POWERUP_H
#define POWERUP_H
#include "Entity.h"

class PowerUp : public Entity
{
private:
	float timeLeft;
public:
	PowerUp();
	virtual ~PowerUp();

	float getTimeLeft() const;
	void setTimePowerup(float timeActive);

	virtual bool Update(float dt);
};

#endif


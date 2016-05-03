#ifndef POWERUP_H
#define POWERUP_H

class PowerUp
{
private:
	float timeLeft;
public:
	PowerUp();
	virtual ~PowerUp();

	float getTimeLeft() const;

	void setTimePowerup(float timeActive);
	bool Update(float dt);
};

#endif


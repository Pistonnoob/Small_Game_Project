#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Weapon.h"
#include <fstream>
#include "PowerUp.h"
#include <vector>
#include "Modifiers.h"

class Player : public Actor {

private:
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;
	int playerHighScore;

	std::vector<PowerUp>powerups;

	Weapon* playerWeapon;

public:
	Player();
	~Player();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string playerModelFilename,
		std::string weaponModelFile, bool isSphere, EntitySubject* entitySub);
	void Shutdown();
	Weapon* getPlayerWeapon();
	void PowerPickup(const int &POWER_ENUM);



	virtual void moveRight();
	virtual void moveLeft();
	virtual void moveUp();
	virtual void moveDown();
	virtual void move(DirectX::XMFLOAT3 moveVec);
	virtual void fire(const float &deltaT);
	virtual void fire();
};

#endif
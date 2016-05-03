#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Weapon.h"
#include <fstream>

class Player : public Actor {

private:
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;
	int playerHighScore;

	Weapon* playerWeapon;

public:
	Player();
	~Player();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string playerModelFilename,
		std::string weaponModelFile, bool isSphere, EntitySubject* entitySub);
	void Shutdown();
	Weapon* getPlayerWeapon();


	virtual void moveRight(float deltaTime);
	virtual void moveLeft(float deltaTime);
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void move(DirectX::XMFLOAT3 moveVec);
	virtual void fire(float deltaTime);
};

#endif
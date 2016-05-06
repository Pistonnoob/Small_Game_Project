#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Weapon.h"
#include "GraphicHandler.h"
#include "InputHandler.h"
#include <fstream>

class Player : public Actor {

private:
	DirectX::XMVECTOR forwardDir;
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;
	int playerHighScore;

	Weapon* playerWeapon;

public:
	Player();
	~Player();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string playerModelFilename,
		std::string weaponModelFilename, bool isSphere);
	void Shutdown();
	void Update(InputHandler* input,GraphicHandler* gHandler, CameraHandler* cameraH);

	Weapon* GetWeapon();

	virtual void moveRight();
	virtual void moveLeft();
	virtual void moveUp();
	virtual void moveDown();
	virtual void move(DirectX::XMFLOAT3 moveVec);
	void rotatePlayerTowardsMouse(DirectX::XMFLOAT2 mousePos, GraphicHandler* gHandler, CameraHandler* cameraH);
};

#endif
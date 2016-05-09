#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Weapon.h"
#include "GraphicHandler.h"
#include "InputHandler.h"
#include <fstream>
#include "PowerUp.h"
#include <vector>
#include "Modifiers.h"
#include "GameData.h"

class Player : public Actor {

private:
	DirectX::XMVECTOR forwardDir;

	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;
	int playerHighScore;

	//std::vector<PowerUp>powerups;

	Weapon* playerWeapon;

public:
	Player();
	~Player();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string playerModelFilename,
		std::string weaponModelFile, bool isSphere, EntitySubject* entitySub);
	
	void Shutdown();

	void HandleInput( InputHandler* input, float dTime);
	Weapon* GetPlayerWeapon();
	void PowerPickup(const int &POWER_ENUM);

	//void SetPowerUp(Modifiers::POWERUPS powerUp);
	void Update(InputHandler* input,GraphicHandler* gHandler, CameraHandler* cameraH, float deltaTime);

	Weapon* GetWeapon();

	virtual void MoveRight(float deltaTime);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveUp(float deltaTime);
	virtual void MoveDown(float deltaTime);
	virtual void Move(DirectX::XMFLOAT3 moveVec);

	//virtual void Fire(float deltaT, PowerUp powerUp, Events::UNIQUE_FIRE shootType);
	virtual void Fire(float deltaT);

	void RotatePlayerTowardsMouse(DirectX::XMFLOAT2 mousePos, GraphicHandler* gHandler, CameraHandler* cameraH);
};

#endif
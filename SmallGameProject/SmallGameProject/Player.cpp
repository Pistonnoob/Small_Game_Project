#include "Player.h"

Player::Player() : Actor()
{
	this->playerHealth = 100;
	this->playerMovmentSpeed = 1;
	this->playerDamage = 1;
	this->playerHighScore = 0;

	this->playerWeapon = new Weapon();
}

Player::~Player()
{

}

bool Player::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string playerModelFilename,
	std::string weaponModelFile, bool isSphere, EntitySubject* entitySub)
{
	if (!Entity::Initialize(device, deviceContext, playerModelFilename, isSphere, entitySub)) {
		return false;
	}

	if (!this->playerWeapon->Initialize(device, deviceContext, weaponModelFile)) {
		return false;
	}
	PowerUp spread = PowerUp();
	PowerUp penetration = PowerUp();
	PowerUp weave = PowerUp();


	this->powerups.push_back(spread);
	this->powerups.push_back(penetration);
	this->powerups.push_back(weave);

	return true;
}

void Player::Shutdown()
{
	if (this->playerWeapon) {
		this->playerWeapon->ShutDown();
		delete this->playerWeapon;
		this->playerWeapon = nullptr;
	}
	Entity::Shutdown(false);
}

Weapon * Player::getPlayerWeapon()
{
	return this->playerWeapon;
}

void Player::PowerPickup(const int & POWER_ENUM)
{
}

void Player::setPowerUp(Modifiers::POWERUPS powerUp)
{
	this->powerups.at(powerUp).setTimePowerup(10);
}

void Player::moveRight()
{
	this->posX += (0.05f * this->playerMovmentSpeed);
}

void Player::moveLeft()
{
	this->posX -= (0.05f * this->playerMovmentSpeed);
}

void Player::moveUp()
{
	this->posZ += (0.05f * this->playerMovmentSpeed);
}

void Player::moveDown()
{
	this->posZ -= (0.05f * this->playerMovmentSpeed);
}

void Player::move(DirectX::XMFLOAT3 moveVec)
{
	this->posX += moveVec.x;
	this->posZ += moveVec.z;
}

void Player::fire(const float &deltaT)
{
	this->setAimDir(DirectX::XMFLOAT3(0, 0, 1));

	if (this->powerups.at(0).Update(deltaT) == true)
	{
		playerWeapon->shootWeapon(this);
	}
}

void Player::fire()
{
	//this->setAimDir(DirectX::XMFLOAT3(0, 0, 1));

	//playerWeapon->shootWeapon(this);
}

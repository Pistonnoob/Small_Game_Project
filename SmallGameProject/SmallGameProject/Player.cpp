#include "Player.h"

Player::Player() : Actor()
{
	this->posX = 10;
	this->posZ = 10;
	this->playerHealth = 100;
	this->playerMovmentSpeed = 1;
	this->playerDamage = 1;
	this->playerHighScore = 0;

	this->playerWeapon = nullptr;
}

Player::~Player()
{

}

bool Player::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string playerModelFilename,
	std::string weaponModelFilename, bool isSphere)
{
	if (!Entity::Initialize(device, deviceContext, playerModelFilename, isSphere)) {
		return false;
	}

	this->playerWeapon = new Weapon();
	if (!this->playerWeapon->Initialize(device, deviceContext, weaponModelFilename)) {
		return false;
	}

	//Set the weapon pos to the Player
	//Set the world matrix to a defualt state
	DirectX::XMMATRIX playerWorldMatrix;
	this->entityModel->GetWorldMatrix(playerWorldMatrix);
		
	//Initial offset
	DirectX::XMMATRIX offset = DirectX::XMMatrixTranslation(this->posX, 0, this->posZ);
	//create the new world matrix
	playerWorldMatrix = playerWorldMatrix * offset;

	//weapon matrix
	DirectX::XMMATRIX weaponWorldMatrix = playerWorldMatrix;
	offset = DirectX::XMMatrixTranslation(5, 3, 0);
	//weaponWorldMatrix = weaponWorldMatrix * offset;

	//Rotation matrix
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationY(180);

	//give the player model its new 
	this->entityModel->SetWorldMatrix(rotationMatrix * playerWorldMatrix);
	this->playerWeapon->GetModel()->SetWorldMatrix(rotationMatrix * weaponWorldMatrix);




	return true;
}

void Player::Shutdown()
{
	Entity::Shutdown();

	if (this->playerWeapon) {
		this->playerWeapon->ShutDown();
		delete this->playerWeapon;
		this->playerWeapon = nullptr;
	}
}

Weapon * Player::GetWeapon()
{
	return this->playerWeapon;
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
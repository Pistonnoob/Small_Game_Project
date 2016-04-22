#include "Player.h"

Player::Player() : Actor()
{

}

Player::~Player()
{

}

void Player::moveRight()
{
	this->posX += 0.05f;
}

void Player::moveLeft()
{
	this->posX -= 0.05f;
}

void Player::moveUp()
{
	this->posZ += 0.05f;
}

void Player::moveDown()
{
	this->posZ -= 0.05f;
}

void Player::move(DirectX::XMFLOAT3 moveVec)
{
	this->posX += moveVec.x;
	this->posZ += moveVec.z;
}
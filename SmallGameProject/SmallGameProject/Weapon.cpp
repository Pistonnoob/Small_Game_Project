#include "Weapon.h"

//not so strong weapon
Weapon::Weapon()
{
	this->weaponModel = new Model();

	this->attackDamage = 1.0f;
	this->playerSpeed = 1.0f;
	this->attackSpeed = 1.0f;
}

//if you want to change the base-Stats
Weapon::Weapon(const float &attackDamage, const float &playerSpeed, const float &attackSpeed)
{
	this->weaponModel = new Model();

	this->attackDamage = attackDamage;
	this->playerSpeed = playerSpeed;
	this->attackSpeed = attackSpeed;
}

Weapon::~Weapon()
{
}

bool Weapon::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename)
{
	bool result = true;

	result = this->weaponModel->Initialize(device, deviceContext, objFilename);

	//setting the starting values
	this->attackDamage = 10.0f;
	this->attackSpeed = 10.0f;
	this->playerSpeed = 10.0f;

	return result;
}

void Weapon::ShutDown()
{
	if (this->weaponModel) 
	{
		this->weaponModel->Shutdown();
		delete this->weaponModel;
		this->weaponModel = nullptr;
	}
}

Model * Weapon::GetModel()
{
	return this->weaponModel;
}

float Weapon::getAttackDamageMod() const
{
	return this->attackDamage;
}

float Weapon::getAttackSpeedMod() const
{
	return this->attackSpeed;
}

float Weapon::getPlayerSpeedMod() const
{
	return this->playerSpeed;
}

void Weapon::shootWeapon(Entity * entity)
{
	//player powerups
	entity->getEntitySubject()->notify(entity, Events::UNIQUE_FIRE::ARCFIRE, 3.14, 40);
}

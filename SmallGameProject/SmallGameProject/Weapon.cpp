#include "Weapon.h"

Weapon::Weapon()
{
	this->weaponModel = new Model();
	this->weaponMods = nullptr;
}

Weapon::Weapon(float Hp, float MS, float Dmg)
{
	this->weaponModel = new Model();
	this->weaponMods = nullptr;
}

Weapon::~Weapon()
{
}

bool Weapon::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename)
{
	return this->weaponModel->Initialize(device, deviceContext, objFilename);

	//setting the starting values
	this->attackDamage = 10.0f;
	this->attackSpeed = 10.0f;
	this->playerSpeed = 10.0f;

	this->name = "unknown";

	//this->weaponMods = new bool[this->CAP];


	//set all weapon modifiers off
	//this->setAllToFalse();
	//activates one modifier
	//this->setWeaponModifier(Modifiers::WEAPON::DAMAGE_UPx10);

}

void Weapon::ShutDown()
{
	if (this->weaponModel) 
	{
		this->weaponModel->Shutdown();
		delete this->weaponModel;
		this->weaponModel = nullptr;
	}

	delete[] this->weaponMods;
}

const Model * Weapon::GetModel()
{
	return this->weaponModel;
}

void Weapon::ActivateWeaponMod(const int &weaponEnum)
{
	this->weaponMods[weaponEnum] = true;
}

bool Weapon::setWeaponModifier(int WEAPON_ENUM) throw(...)
{
	bool result = true;
	if (WEAPON_ENUM >= this->CAP)
	{
		throw("out of scope in weaponMod array in weapon.cpp");
		result = false;
	}
	else
	{
		this->weaponMods[WEAPON_ENUM] = true;
	}
	return result;
}

void Weapon::calculateFinalStats()
{
	for (int i = 0; i < this->CAP; i++)
	{
		//get data from the lib
	}
}

void Weapon::setAllToFalse()
{
	for (int i = 0; i < this->CAP; i++)
	{
		this->weaponMods[i] = false;
	}
}

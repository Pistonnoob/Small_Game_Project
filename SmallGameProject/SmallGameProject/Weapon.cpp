#include "Weapon.h"

void Weapon::setAllToFalse()
{
	for (int i = 0; i < this->CAP; i++)
	{
		this->statistics[i] = false;
	}
}

Weapon::Weapon()
{
	this->weaponModel = new Model();
}

Weapon::Weapon(float Hp, float MS, float Dmg)
{
	this->weaponModel = new Model();
}

Weapon::~Weapon()
{
}

bool Weapon::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename)
{
	return this->weaponModel->Initialize(device, deviceContext, objFilename);
	this->setAllToFalse();

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

const Model * Weapon::GetModel()
{
	return this->weaponModel;
}
#include "Weapon.h"

Weapon::Weapon()
{
	this->weapondModel = new Model();

	for (int i = 0; i < this->nrOfModifiers; i++) {
		this->modifyers[i] = 1.f;
	}
}

Weapon::Weapon(float Hp, float MS, float Dmg)
{
	this->weapondModel = new Model();

	// Assign each invidual modifier
	this->modifyers[0] = Hp;
	this->modifyers[1] = MS;
	this->modifyers[2] = Dmg;

}

Weapon::~Weapon()
{

}

bool Weapon::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename)
{
	return this->weapondModel->Initialize(device, deviceContext, objFilename);
}

void Weapon::ShutDown()
{
	if (this->weapondModel) {
		this->weapondModel->Shutdown();
		delete this->weapondModel;
		this->weapondModel = nullptr;
	}
}

const Model * Weapon::GetModel()
{
	return this->weapondModel;
}

const int Weapon::GetNrOFModifiers()
{
	return this->nrOfModifiers;
}

const float * Weapon::GetModifiers()
{
	return this->modifyers;
}

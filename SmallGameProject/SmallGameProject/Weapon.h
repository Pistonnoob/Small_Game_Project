#ifndef WEAPON_H
#define WEAPON_H

#include "Model.h"

class Weapon {

private:
	int const static CAP = 15;

	Model* weaponModel;
	bool statistics[CAP];

	bool setWeaponModifier(int WEAPON_ENUM);
	void calculateModifiers();

	void setAllToFalse();
public:
	Weapon();
	Weapon(float Hp, float MS, float Dmg);
	
	
	~Weapon();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename);
	void ShutDown();

	const Model* GetModel();
	const int GetNrOFModifiers();
	const float* GetModifiers();
};

#endif
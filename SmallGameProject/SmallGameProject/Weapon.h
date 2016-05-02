#ifndef WEAPON_H
#define WEAPON_H

#include "Model.h"

class Weapon {

private:
	Model* weapondModel;

	
	static const int nrOfModifiers = 3;
	//Health, MovmentSpeed, Damage
	float modifyers[nrOfModifiers];

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
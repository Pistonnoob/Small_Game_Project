#ifndef WEAPON_H
#define WEAPON_H

#include "Model.h"
#include "Modifiers.h"

class Weapon {

private:
	int const static CAP = 18;

	float attackDamage;
	float playerSpeed;
	float attackSpeed;

	Model* weaponModel;

	//an array of adresses to the lib
	bool weaponMods[CAP];
public:
	Weapon();
	Weapon(float Hp, float MS, float Dmg);
	
	
	~Weapon();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename);
	void ShutDown();

	const Model* GetModel();
	void ActivateWeaponMod(const int &weaponEnum);

private:
	bool setWeaponModifier(int WEAPON_ENUM) throw(...);
	void calculateFinalStats();
	void StartUp();

	void setAllToFalse();
};

#endif
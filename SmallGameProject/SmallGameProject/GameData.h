#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Observer.h"
#include <string>
#include <fstream>
#include "Modifiers.h"
#include "Weapon.h"


class GameData : public Observer
{
private:
	static bool isInstatiated;	//Check flag
	static GameData* single;

	GameData();					//Only GameData will create itself

	//Data
	//Character
	int playerHighScore;
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;

	//Achivement Related
	int enemiesKilled;

	//weapom related
	int static const CAP = 3;
	Weapon weaponArsenal[CAP];


public:
	virtual ~GameData();
	static GameData* getInstance();
	void onNotify(const Entity* entity, Events::ENTITY evnt);

	bool SavePlayerData(std::string filename);
	bool LoadPlayerData(std::string filename);

	Weapon* getWeapon(int weaponEnum);
};

bool GameData::isInstatiated = false;
GameData* GameData::single = nullptr;

#endif
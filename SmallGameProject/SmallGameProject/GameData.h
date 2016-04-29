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
	Weapon weaponArsenal[Modifiers::nrOfWeapons];
	bool playerUnlockedWeapons[Modifiers::nrOfWeapons];
public:
	virtual ~GameData();
	static GameData* getInstance();

	static void shutdown();

	void onNotify(const Entity* entity, Events::ENTITY evnt);
	void onNotify(const Entity* entity, Events::ACHIEVEMENT achi);

	bool SavePlayerData(std::string filename);
	bool LoadPlayerData(std::string filename);

	Weapon* getWeapon(int weaponEnum);
};

#endif
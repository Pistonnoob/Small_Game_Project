#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Observer.h"
#include <string>
#include <fstream>
#include "Modifiers.h"
#include "Weapon.h"
#include <vector> 

class GameData : public Observer
{
private:
	static bool isInstatiated;	//Check flag
	static GameData* single;

	GameData(GameData const&);

	//GameData();					//Only GameData will create itself

	//Data
	//Character
	int playerHighScore;
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;

	//Achivement Related
	int enemiesKilled;

	//weapom related
	std::vector<Weapon>weaponArsenal;
	bool playerUnlockedWeapons[Modifiers::nrOfWeapons];
public:
	virtual ~GameData();
	static GameData* getInstance();

	void shutdown();

	void onNotify(const Entity* entity, Events::ENTITY evnt);
	void onNotify(const Entity* entity, Events::ACHIEVEMENT achi);

	void onNotify(Entity* entity, Events::ENTITY evnt);
    void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);

	bool SavePlayerData(std::string filename);
	bool LoadPlayerData(std::string filename);

	Weapon* getWeapon(int weaponEnum);
};

#endif
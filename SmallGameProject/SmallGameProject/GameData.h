#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Observer.h"
#include <string>
#include <fstream>

class GameData : public Observer {

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

public:
	
	virtual ~GameData();
	static GameData* getInstance();
	void onNotify(Entity* entity, Events::ENTITY evnt);
    void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);

	bool SavePlayerData(std::string filename);
	bool LoadPlayerData(std::string filename);

};

bool GameData::isInstatiated = false;
GameData* GameData::single = nullptr;

#endif
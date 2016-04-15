#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Observer.h"

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
	void onNotify(const Entity* entity, Events::ENTITY evnt);

};

bool GameData::isInstatiated = false;
GameData* GameData::single = nullptr;

#endif
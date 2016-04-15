#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Observer.h"
#include "Enemy.h"

class GameData : public Observer {

private:
	static bool isInstatiated;	//Check flag
	static GameData* single;

	GameData();					//Only GameData will create itself

	//Data
	static int enemiesKilled;

public:
	
	~GameData();
	static GameData* getInstance();
	virtual void onNotify(const Entity& entity, Events::ENTITY evnt);

};

bool GameData::isInstatiated = false;
GameData* GameData::single = nullptr;

#endif
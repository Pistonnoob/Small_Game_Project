#include "GameData.h"
GameData::GameData()
: Observer()
{
	this->playerHighScore = 0;
	this->playerHealth = 0;
	this->playerMovmentSpeed = 0;
	this->playerDamage = 0;

	this->enemiesKilled = 0;
}

GameData::~GameData()
{
	isInstatiated = false;
	delete this->single;
}

GameData* GameData::getInstance()
{
	if (!isInstatiated) {
		single = new GameData();
		isInstatiated = true;
		return single;
	}
	else {
		return single;
	}
}

void GameData::onNotify(const Entity* entity, Events::ENTITY evnt)
{
	//Need to finish Entity class
	//if (Enemy* enemy = dynamic_cast<Enemy*>(entity) && evnt == Events::DEAD) {
	//	this->enemiesKilled++;
	//}
	return;
}

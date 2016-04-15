#include "GameData.h"
GameData::GameData()
{

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

void GameData::onNotify(const Entity& entity, Events::ENTITY evnt)
{

}

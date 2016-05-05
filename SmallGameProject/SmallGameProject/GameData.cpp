#include "GameData.h"

bool GameData::isInstatiated = false;

GameData* GameData::single = nullptr;

GameData::GameData(GameData const &) : Observer()
{
	playerHighScore = 0;
	playerHealth = 0;
	playerMovmentSpeed = 0;
	playerDamage = 0;

	enemiesKilled = 0;

	//create pistol
	weaponArsenal.push_back(Weapon());
	//shotgun
	weaponArsenal.push_back(Weapon(15, 10, 5));
	//uzi
	weaponArsenal.push_back(Weapon(5, 10, 15));

	for (int i = 0; i < Modifiers::nrOfWeapons; i++)
		playerUnlockedWeapons[i] = false;
}

GameData::~GameData()
{
	//isInstatiated = false;
	//delete this->single;
	for (int i = 0; i < 3; i++)
	{
		weaponArsenal.at(i).ShutDown();
	}
	
}

GameData* GameData::getInstance()
{
	if (!isInstatiated) 
	{
  		single = new GameData(*single);
		isInstatiated = true;
		
	}
	return single;
}

void GameData::shutdown()
{
	
	for (int i = 0; i < Modifiers::nrOfWeapons; i++)
	{
		weaponArsenal.at(i).ShutDown();
	}
	
	isInstatiated = false;
	delete single;
	single = nullptr;
}

void GameData::onNotify(Entity* entity, Events::ENTITY evnt)
{
	//Need to finish Entity class
	//if (Enemy* enemy = dynamic_cast<Enemy*>(entity) && evnt == Events::DEAD) {
	//	this->enemiesKilled++;
	//}

	return;
}

void GameData::onNotify(const Entity * entity, Events::ACHIEVEMENT achi)
{
	if (achi == Events::ACHIEVEMENT::WEAPON_UNLOCK)
	{
		weaponArsenal[Modifiers::WEAPON::SHOTGUN];
	}
}

void GameData::onNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{
}

void GameData::onNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, int triggerDelay)
{
}

void GameData::onNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, int triggerDelay, float arcOnSplit, int projectilesOnSplit)
{
}

void GameData::onNotify(Entity * entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets)
{
}

bool GameData::SavePlayerData(std::string filename)
{
	std::ofstream saveFile;
	std::string path = "..\\SmallGameProject\\Resources\\PlayerSaves\\" + filename + ".txt";
	saveFile.open(path);

	if (!saveFile.is_open()) {
		return false;
	}
	else 
	{
		saveFile << playerHighScore << "\r\n";
		saveFile << playerHealth << "\r\n";
		saveFile << playerMovmentSpeed << "\r\n";
		saveFile << playerDamage << "\r\n";
		saveFile << enemiesKilled << "\r\n";

		saveFile.close();
	}
	return true;
}
bool GameData::LoadPlayerData(std::string filename)
{
	std::ifstream loadFile;
	std::string path = "..\\SmallGameProject\\Resources\\PlayerSaves\\" + filename + ".txt";
	loadFile.open(path);

	if (!loadFile.is_open()) {
		return false;
	}
	else 
	{

		loadFile >> playerHighScore;
		loadFile >> playerHealth;
		loadFile >> playerMovmentSpeed;
		loadFile >> playerDamage;
		loadFile >> enemiesKilled;

		loadFile.close();
	}

	return true;
}

Weapon * GameData::getWeapon(int weaponEnum)
{
	return &weaponArsenal[0];
}

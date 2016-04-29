#include "GameData.h"

bool GameData::isInstatiated = false;

GameData* GameData::single = nullptr;

GameData::GameData(): Observer()
{
	this->playerHighScore = 0;
	this->playerHealth = 0;
	this->playerMovmentSpeed = 0;
	this->playerDamage = 0;

	this->enemiesKilled = 0;
	
	//create pistol
	this->weaponArsenal[Modifiers::WEAPON::PISTOL] = Weapon();
	//shotgun
	this->weaponArsenal[Modifiers::WEAPON::SHOTGUN] = Weapon(15, 10, 5);
	//uzi
	this->weaponArsenal[Modifiers::WEAPON::UZI] = Weapon(5, 10, 15);

	for (int i = 0; i < Modifiers::nrOfWeapons; i++)
		this->playerUnlockedWeapons[i] = false;

}

GameData::~GameData()
{
	//isInstatiated = false;
	//delete this->single;
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

void GameData::shutdown()
{
	isInstatiated = false;
	delete single;
}

void GameData::onNotify(const Entity* entity, Events::ENTITY evnt)
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
		this->weaponArsenal[Modifiers::WEAPON::SHOTGUN];
	}

}

bool GameData::SavePlayerData(std::string filename)
{
	std::ofstream saveFile;
	std::string path = "..\\SmallGameProject\\Resources\\PlayerSaves\\" + filename + ".txt";
	saveFile.open(path);

	if (!saveFile.is_open()) {
		return false;
	}
	else {
		saveFile << this->playerHighScore << "\r\n";
		saveFile << this->playerHealth << "\r\n";
		saveFile << this->playerMovmentSpeed << "\r\n";
		saveFile << this->playerDamage << "\r\n";
		saveFile << this->enemiesKilled << "\r\n";

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
	else {

		loadFile >> this->playerHighScore;
		loadFile >> this->playerHealth;
		loadFile >> this->playerMovmentSpeed;
		loadFile >> this->playerDamage;
		loadFile >> this->enemiesKilled;

		loadFile.close();
	}

	return true;
}

Weapon * GameData::getWeapon(int weaponEnum)
{
	return &this->weaponArsenal[0];
}

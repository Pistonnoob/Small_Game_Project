#include "GameData.h"

bool GameData::isInstatiated = false;

int GameData::nrOfActivePowerups = 0;

std::list<PowerUp*> GameData::powerupArsenal = list<PowerUp*>();

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

	//initialize start powerup, this does in the stageState initialize

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

GameData* GameData::GetInstance()
{
	if (!isInstatiated) 
	{
  		single = new GameData(*single);
		isInstatiated = true;
		
	}
	return single;
}

void GameData::SpawnRandomPowerup()
{
	GameData::powerupArsenal.front()->SetTimePowerup(10);
}

void GameData::Shutdown()
{
	
	for (int i = 0; i < Modifiers::nrOfWeapons; i++)
	{
		weaponArsenal.at(i).ShutDown();
	}
	
	isInstatiated = false;
	delete single;
	single = nullptr;

	std::list<PowerUp*>::iterator iterator;

	for (iterator = GameData::powerupArsenal.begin(); iterator != powerupArsenal.end(); iterator++)
	{
		delete *iterator;
	}
}

void GameData::Update(float deltaTime)
{
	std::list<PowerUp*>::iterator iterator;
	for (iterator = GameData::powerupArsenal.begin(); iterator != powerupArsenal.end(); iterator++)
	{

		(*iterator)->Update(deltaTime);
	}

}

std::list<PowerUp*> GameData::getPowerup()
{
	std::list<PowerUp*>toReturn;
	std::list<PowerUp*>::iterator iterator;

	//iterate throwugh the list
	for (iterator = GameData::powerupArsenal.begin(); iterator != powerupArsenal.end(); iterator++)
	{
		toReturn.push_back((*iterator));
	}
	return toReturn;
}

void GameData::unlockPowerUp(Events::UNIQUE_FIRE newPower)
{
	powerupArsenal.push_back(new PowerUp(Events::UNIQUE_FIRE::ARCFIRE));
}

int GameData::getNrOfActivePowerups()
{
	return nrOfActivePowerups;
}

void GameData::OnNotify(Entity* entity, Events::ENTITY evnt)
{
	//Need to finish Entity class
	//if (Enemy* enemy = dynamic_cast<Enemy*>(entity) && evnt == Events::DEAD) {
	//	this->enemiesKilled++;
	//}

	return;
}

void GameData::OnNotify(const Entity * entity, Events::ACHIEVEMENT achi)
{
	if (achi == Events::ACHIEVEMENT::WEAPON_UNLOCK)
	{
		weaponArsenal[Modifiers::WEAPON::SHOTGUN];
	}
}

void GameData::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{
}

void GameData::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay)
{
}

void GameData::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay, float arcOnSplit, int projectilesOnSplit)
{
}

void GameData::OnNotify(Entity * entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets)
{
}

void GameData::OnNotify(Entity * entity, Events::PICKUP evnt)
{
	
	//this->powerupArsenal.insert()
	this->nrOfActivePowerups++;
	//resulterar till:
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

void GameData::Render(GraphicHandler * gHandler, CameraHandler * camera)
{
	system("pause");
}

Weapon * GameData::GetWeapon(int weaponEnum)
{
	return &weaponArsenal[0];
}

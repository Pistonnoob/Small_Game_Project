#include "GameData.h"
#include <stdlib.h>
#include <time.h>

bool GameData::isInstatiated = false;
bool GameData::isGameStageInit = false;

int GameData::nrOfActivePowerups = 0;

std::list<PowerUp*> GameData::powerupArsenal = std::list<PowerUp*>();

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

void GameData::Shutdown()
{
	
	for (int i = 0; i < Modifiers::nrOfWeapons; i++)
	{
		weaponArsenal.at(i).ShutDown();
	}

	GameData::ShutdownStageStateGD();
	
	isInstatiated = false;
	delete single;
	single = nullptr;
}

void GameData::Update(float deltaTime)
{
	float timeLeft = 0.0f;
	bool expandedPowerup = true;
	std::list<PowerUp*>::iterator iterator;
	for (iterator = GameData::powerupArsenal.begin(); iterator != powerupArsenal.end(); iterator++)
	{
		//only need to update the active powerups
		timeLeft = (*iterator)->GetTimeLeft();
		if (timeLeft > 0.0f)
		{
			expandedPowerup = (*iterator)->Update(deltaTime);
			//if powerup update return false, the powerup has run out
			if (expandedPowerup == false)
			{
				nrOfActivePowerups--;
			}
		}	
	}

}

std::list<PowerUp*> GameData::getPowerup()
{
	std::list<PowerUp*>toReturn;
	std::list<PowerUp*>::iterator iterator;

	//iterate throwugh the list
	for (iterator = GameData::powerupArsenal.begin(); iterator != powerupArsenal.end(); iterator++)
	{
		//if the powerup is active
		if(0.0f < (*iterator)->GetTimeLeft())
			toReturn.push_back((*iterator));
	}
	return toReturn;
}

PowerUp * GameData::GetRandomPowerup()
{
	int randPow = rand() % 3;
	PowerUp* toReturn = nullptr;
	//randPow = 2;

	std::list<PowerUp*>::iterator walker;
	walker = GameData::powerupArsenal.begin();

	for (int i = 0; i < randPow; i++)
	{
		walker++;
	}
	return (*walker);
}

void GameData::unlockPowerUp(Events::UNIQUE_FIRE newPower)
{
	powerupArsenal.push_back(new PowerUp(newPower));
}

int GameData::getNrOfActivePowerups()
{
	return nrOfActivePowerups;
}

void GameData::InitializeStageStateGD(ID3D11Device* device, ID3D11DeviceContext* deviceContext, EntitySubject* playerSubject)
{
	if (GameData::isGameStageInit == false)
	{
		srand((unsigned)time(NULL));

		unlockPowerUp(Events::UNIQUE_FIRE::ARCFIRE);
		unlockPowerUp(Events::UNIQUE_FIRE::SPLITFIRE);
		unlockPowerUp(Events::UNIQUE_FIRE::REVERSERBULLETS);

		std::list<PowerUp*>::iterator walker;
		walker = GameData::powerupArsenal.begin();
		(*walker)->Initialize(device, deviceContext, "ogreFullG", true, playerSubject);
		walker++;
		(*walker)->Initialize(device, deviceContext, "ogreFullG", true, playerSubject);
		walker++;
		(*walker)->Initialize(device, deviceContext, "ogreFullG", true, playerSubject);

		GameData::isGameStageInit = true;
	}
}

void GameData::ShutdownStageStateGD()
{

	std::list<PowerUp*>::iterator walker;
	walker = GameData::powerupArsenal.begin();
	(*walker)->Shutdown();
	delete (*walker);
	walker++;
	(*walker)->Shutdown();
	delete (*walker);
	walker++;
	(*walker)->Shutdown();
	delete (*walker);
    /*
	PowerUp* toRemove = nullptr;

	toRemove = GameData::powerupArsenal.front();

	toRemove->Shutdown();
	delete toRemove;

	GameData::powerupArsenal.pop_front();
	*/
}

void GameData::OnNotify(Entity* entity, Events::ENTITY evnt)
{
	//Need to finish Entity class
	if (evnt == Events::ENTITY::BOMBER_DEAD) {
		this->enemiesKilled++;
		this->playerHighScore += SCORE_VALUE_BOMBER;
	}

	else if (evnt == Events::ENTITY::MELEE_DEAD) {
		this->enemiesKilled++;
		this->playerHighScore += SCORE_VALUE_MELEE;
	}

	else if (evnt == Events::ENTITY::RANGED_DEAD) {
		this->enemiesKilled++;
		this->playerHighScore += SCORE_VALUE_RANGED;
	}
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
	std::list<PowerUp*>::iterator walker;
	walker = GameData::powerupArsenal.begin();

	switch (evnt)
	{
	case Events::PICKUP::PICKUP_SPREAD:
		(*walker)->SetTimePowerup(10.0f);
		break;
	case Events::PICKUP::PICKUP_SPITFIRE:
		walker++;
		(*walker)->SetTimePowerup(10.0f);
		break;
	case Events::PICKUP::PICKUP_REVERSERBULLETS:
		walker++;
		walker++;
		(*walker)->SetTimePowerup(10.0f);
		break;
	default:
		break;
	}

	//flashy particles here
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

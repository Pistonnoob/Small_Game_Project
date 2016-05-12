#include "GameData.h"

bool GameData::isInstatiated = false;

GameData* GameData::single = nullptr;

GameData::GameData(GameData const &) : Observer()
{
	this->playerHighScore = 0;
	this->playerHealth = 0;
	this->playerMovmentSpeed = 0;
	this->playerDamage = 0;

	this->enemiesKilled = 0;
	this->enemiesKilledStage = 0;
	this->playerScoreStage = 0;

	//create pistol
	this->weaponArsenal.push_back(Weapon());
	//shotgun
	this->weaponArsenal.push_back(Weapon(15, 10, 5));
	//uzi
	this->weaponArsenal.push_back(Weapon(5, 10, 15));

	for (int i = 0; i < Modifiers::nrOfWeapons; i++)
		this->playerUnlockedWeapons[i] = false;
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
	
	isInstatiated = false;
	delete single;
	single = nullptr;
}

void GameData::Update(float deltaTime)
{

}

void GameData::NewStage()
{
	this->enemiesKilledStage = 0;
	this->playerScoreStage = 0;
}

void GameData::EndStage(bool winner)
{
	if (winner) {
		if (this->playerScoreStage > this->playerHighScore) {
			this->playerHighScore = this->playerScoreStage;
		}
		
		this->experience += (this->playerScoreStage * EXP_PER_SCORE);
		while (this->experience > EXP_PER_POINT) {
			this->experience -= EXP_PER_POINT;
			this->points++;
		}
	}
	
}

int GameData::SpendPointOn(int stat) //0: dmg, 1: hp, 2: speed
{
	if (this->points == 0) {
		return 1;
	}

	switch (stat) {
	case 0:
		this->playerDamage += INC_PER_POINT;
		break;
	case 1:
		this->playerHealth += INC_PER_POINT;
		break;
	case 2:
		this->playerMovmentSpeed += INC_PER_POINT;
		break;
	default:
		return -1;
		break;
	}
	this->points--;

	return 0;
}

void GameData::OnNotify(Entity* entity, Events::ENTITY evnt)
{
	//Need to finish Entity class
	if (evnt == Events::ENTITY::BOMBER_DEAD) {
		this->enemiesKilled++;
		this->enemiesKilledStage++;
		this->playerScoreStage += SCORE_VALUE_BOMBER;
	}

	else if (evnt == Events::ENTITY::MELEE_DEAD) {
		this->enemiesKilled++;
		this->enemiesKilledStage++;
		this->playerScoreStage += SCORE_VALUE_MELEE;
	}

	else if (evnt == Events::ENTITY::RANGED_DEAD) {
		this->enemiesKilled++;
		this->enemiesKilledStage++;
		this->playerScoreStage += SCORE_VALUE_RANGED;
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
	Player* ptr = nullptr;

	ptr = dynamic_cast<Player*>(entity);

	//här behöver avgöras vad som tas upp upp


	//resulterar till:

	ptr->SetPowerUp(Modifiers::POWERUPS::SPREAD);
}

bool GameData::SavePlayerData(std::string filename)
{
	std::ofstream saveFile;
	std::string path = "..\\SmallGameProject\\Resources\\Data\\" + filename + ".txt";
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
	std::string path = "..\\SmallGameProject\\Resources\\Data\\" + filename + ".txt";
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

int GameData::GetEnemiesKilledInStage()
{
	return this->enemiesKilledStage;
}

int GameData::GetScoreInStage()
{
	return this->playerScoreStage;
}

int GameData::GetHighScore()
{
	return this->playerHighScore;
}

int GameData::GetPlayerDamage()
{
	return this->playerDamage;
}

int GameData::GetPlayerHealth()
{
	return this->playerHealth;
}

int GameData::GetPlayerMoveSpeed()
{
	return this->playerMovmentSpeed;
}

int GameData::GetPoints()
{
	return this->points;
}

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Observer.h"
#include <string>
#include <fstream>
#include "Modifiers.h"
#include "Weapon.h"
#include <vector> 
#include "Player.h"
#include "GameState.h"
#include "EntitySubject.h"
#include "ProjectileHandler.h"
#include <list>

const int SCORE_VALUE_BOMBER = 50;
const int SCORE_VALUE_MELEE = 100;
const int SCORE_VALUE_RANGED = 150;

const int EXP_PER_POINT = 100;
const float EXP_PER_SCORE = 0.1f;
const int DMG_INC_PER_POINT = 5;
const int HEALTH_INC_PER_POINT = 20;
const int SPEED_INC_PER_POINT = 2;
const float GOAL_TIME = 20.0f;

class GameData : public Observer
{
private:
	static bool isInstatiated;	//Check flag
	static bool isGameStageInit; //check for powerup list
	static int nrOfUnlockedPowers;
	Modifiers::WEAPON equipedWeapon;

	static GameData* single;
	static int nrOfActivePowerups;

	GameData(GameData const&);
	int playerHighScore;

	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;

	int experience;
	int points;

	//Stage stuff
	int enemiesKilledStage;
	int playerScoreStage;

	//Achivement Related
	int enemiesKilled;

	//weapon related
	std::vector<Weapon*>weaponArsenal;
	static std::list<PowerUp*>powerupArsenal;

	bool playerUnlockedWeapons[Modifiers::nrOfWeapons];
public:
	virtual ~GameData();

	static GameData* GetInstance();

	void Shutdown();
	static void Update(float deltaTime);
	static PowerUp* getPowerup();
	static PowerUp* GetRandomPowerup();

	static void unlockPowerUp(Events::UNIQUE_FIRE newPower);

	int static getNrOfActivePowerups();

	static void InitializeStageStateGD(ID3D11Device* device, ID3D11DeviceContext* deviceContext, EntitySubject* playerSubject);
	static void ShutdownStageStateGD();

	void NewStage();
	void CheckPoint(float time);
	void EndStage(bool winner, float time);
	int SpendPointOn(int stat);

	void OnNotify(Entity* entity, Events::ENTITY evnt);
	void OnNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);
	void OnNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay);
	void OnNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay, float arcOnSplit, int projectilesOnSplit);
	void OnNotify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets);
	void OnNotify(Entity* entity, Events::PICKUP evnt);

	void OnNotify(const Entity* entity, Events::ACHIEVEMENT achi);

	bool SavePlayerData(std::string filename);
	bool LoadPlayerData(std::string filename);

	void Render(GraphicHandler * gHandler, CameraHandler* camera);

	Weapon* GetWeapon();
	int GetEnemiesKilledInStage();
	int GetScoreInStage();
	int GetHighScore();
	int GetPlayerDamage();
	int GetPlayerHealth();
	int GetPlayerMoveSpeed();
	int GetPoints();
	int GetUnlockedPowerups() const;
	
	float GetWeaponAttackMod() const;
	float GetWeaponHealthMod() const;
	float GetWeaponMovementSpeed() const;


	void equipWeapon(Modifiers::WEAPON);
};

#endif
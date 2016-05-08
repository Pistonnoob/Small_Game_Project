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

class GameData : public Observer
{
private:
	static bool isInstatiated;	//Check flag
	static GameData* single;

	GameData(GameData const&);
	int playerHighScore;
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;

	//Achivement Related
	int enemiesKilled;

	//weapom related
	std::vector<Weapon>weaponArsenal;
	bool playerUnlockedWeapons[Modifiers::nrOfWeapons];
public:
	virtual ~GameData();

	static GameData* GetInstance();

	void Shutdown();
	void Update(float deltaTime);

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

	Weapon* GetWeapon(int weaponEnum);
};

#endif
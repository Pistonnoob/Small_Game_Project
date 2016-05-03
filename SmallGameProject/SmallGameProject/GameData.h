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
			//Only GameData will create itself

								//Data
								//Character
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

	static GameData* getInstance();

	void shutdown();
	void Update(float deltaTime);

	void onNotify(const Entity* entity, Events::ENTITY evnt);
	void onNotify(const Entity* entity, Events::ACHIEVEMENT achi);

	void onNotify(Entity* entity, Events::ENTITY evnt);
	void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);
	void onNotify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets);

	void onNotify(Entity* entity, Events::PICKUP evnt);

	bool SavePlayerData(std::string filename);
	bool LoadPlayerData(std::string filename);

	void render(GraphicHandler * gHandler, CameraHandler* camera);

	Weapon* getWeapon(int weaponEnum);
};

#endif
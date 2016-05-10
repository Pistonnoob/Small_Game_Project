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

class GameData : public Observer
{
private:
	static bool isInstatiated;	//Check flag
	static GameData* single;
	static int nrOfActivePowerups;

	GameData(GameData const&);
	int playerHighScore;
	int playerHealth;
	int playerMovmentSpeed;
	int playerDamage;

	//Achivement Related
	int enemiesKilled;

	//weapom related
	std::vector<Weapon>weaponArsenal;
	static std::list<PowerUp*>powerupArsenal;

	bool playerUnlockedWeapons[Modifiers::nrOfWeapons];
public:
	virtual ~GameData();

	static GameData* GetInstance();

	void Shutdown();
	static void Update(float deltaTime);
	static std::list<PowerUp*> getPowerup();
	static PowerUp* GetRandomPowerup();

	static void unlockPowerUp(Events::UNIQUE_FIRE newPower);

	int static getNrOfActivePowerups();

	static void InitializeStageStateGD(ID3D11Device* device, ID3D11DeviceContext* deviceContext, EntitySubject* playerSubject);
	static void ShutdownStageStateGD();

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
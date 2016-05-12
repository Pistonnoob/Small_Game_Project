#ifndef STAGESTATE_H
#define STAGESTATE_H
#include "GameState.h"
#include "ParticleHandler.h"
#include "Ai.h"
#include "Player.h"
#include "Projectile.h"
#include "Abilities.h"
#include "Algorithm.h"
#include "EntitySubject.h"
#include "ProjectileHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Boss.h"
#include "GameData.h"
#include "PowerUp.h"


struct ToSpawn
{
    int spawnIndex;
	Type type;
};
struct Wave
{
	int time;
	std::vector<ToSpawn> toSpawn;
};
struct Level
{
    std::vector<Wave> wave;
};
class StageState :
	public GameState
{
private:	//Variables
	CameraHandler myCamera;
    ProjectileHandler enemyPjHandler;

	PowerUp spreadPower;
	EntitySubject powerUpSubject; 

	Model m_car;
    Model m_ball;
	Model m_ground;

    EntitySubject enemySubject;

	//player variables
	
	EntitySubject playerSubject;
	ProjectileHandler playerProjectile;
	Player player;
	
	Ai m_AI;
	std::vector<Enemy*> enemies;

	float timeToNextWave;
	int currentLevel;
	int currentWave;
	std::vector<Level> levels;
	std::vector<DirectX::XMFLOAT3> spawnPoints;

	
	ParticleHandler myParticleHandler;

	UIHandler uiHandler;

    float t;
	bool exitStage;

	bool renderUI;
public:
	StageState();
	virtual ~StageState();
	virtual void Shutdown();

	int Initialize(GraphicHandler* gHandler, GameStateHandler* GSH);
	int LoadMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int stageNr);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);
    virtual void ReadFile(std::string fileName);
    virtual void HandleWaveSpawning(float deltaTime);
    virtual void SpawnWave(int levelIndex, int waveIndex);
	virtual void SpawnEnemy(Type type, int pointIndex);
    virtual void RemoveDeadEnemies();
	virtual Type ConvertToEnemyType(std::string type);

private:	//Functions

};

#endif
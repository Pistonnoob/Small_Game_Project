#ifndef STAGESTATE_H
#define STAGESTATE_H
#include "GameState.h"
#include "ParticleHandler.h"
#include "Ai.h"
#include "Player.h"
#include "Projectile.h"
#include "Abilities.h"
#include "Algorithm.h"
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
	vector<ToSpawn> toSpawn;
};
struct Level
{
    vector<Wave> wave;
};
class StageState :
	public GameState
{
private:	//Variables
	CameraHandler myCamera;
    ProjectileHandler enemyPjHandler;

	EntitySubject powerUpSubject; 

	Model m_car;
    Model m_ball;
	Model m_ground;

    EntitySubject enemySubject;
	int latestSpawnPoint;

	std::vector<DirectX::XMFLOAT2>spawnPos;

	//player variables
	Player player;

	EntitySubject* playerSubject = nullptr;
	ProjectileHandler* playerProjectile = nullptr;

	PowerUp* powerUpPointer;

	Ai m_AI;
	vector<Enemy*> enemies;

	float timeToNextWave;
	int currentLevel;
	int currentWave;
    vector<Level> levels;

	vector<DirectX::XMFLOAT3> spawnPoints;
	vector<DirectX::XMFLOAT3> spawnPointsPowerUp;


	
	ParticleHandler myParticleHandler;

	float timeElapsed;
    float t;
	bool exitStage;

	float camPosX;
	float camPosZ;
	bool inc;
public:
	StageState();
	virtual ~StageState();
	virtual void Shutdown();

	int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);
    virtual void ReadFile(string fileName);
    virtual void HandleWaveSpawning(float deltaTime);
    virtual void SpawnWave(int levelIndex, int waveIndex);
	virtual void SpawnEnemy(Type type, int pointIndex);
    virtual void RemoveDeadEnemies();
	virtual Type ConvertToEnemyType(string type);

private:	//Functions

};

#endif
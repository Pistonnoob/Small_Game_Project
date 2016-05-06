#ifndef STAGESTATE_H
#define STAGESTATE_H
#include "GameState.h"
#include "Ai.h"
#include "Projectile.h"
#include "Abilities.h"
#include "Algorithm.h"
#include "EntitySubject.h"
#include "ProjectileHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Boss.h"


struct ToSpawn
{
	Type type;
	int amount;
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

	
	Model m_car;
    Model m_ball;
	Model m_ground;

    EntitySubject enemySubject;

	//player variables
	EntitySubject* playerSubject;
	ProjectileHandler playerPjHandler;
	Player* hero;
	
	Ai m_AI;
	vector<Enemy*> enemies;

	float timeToNextWave;
	int currentLevel;
	int currentWave;
    vector<Level> levels;
	vector<DirectX::XMFLOAT3> spawnPoints;

	bool exitStage;

public:
	StageState();
	virtual ~StageState();
	virtual void Shutdown();

	int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime);
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
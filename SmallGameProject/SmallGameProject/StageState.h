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
#include "GameData.h"
#include "PowerUp.h"


struct Wave
{
    string type;
    int amount;
};
struct Level
{
    int time;
    vector<Wave> toSpawn;
};
class StageState :
	public GameState
{
private:	//Variables
	CameraHandler myCamera;
    ProjectileHandler enemyPjHandler;
	DirectX::XMFLOAT3 playerPos;

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
	vector<Enemy*> enemies;
    //vector<toSpawn> wave;
    vector<Level> waves;

	
	ParticleHandler myParticleHandler;
	//vector<Projectile*> projectiles;

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
    virtual void ReadFile();
    virtual void SpawnWave();
};

#endif
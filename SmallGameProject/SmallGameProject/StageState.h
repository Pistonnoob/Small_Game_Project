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

	Ai m_AI;
	vector<Enemy*> enemies;

    Ability* ability1;
    Ability* ability2;
    Ability* ability3;

	Weapon testWeap;

	bool exitStage;

public:
	StageState();
	virtual ~StageState();
	void Shutdown();

	int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);

private:	//Functions

};

#endif
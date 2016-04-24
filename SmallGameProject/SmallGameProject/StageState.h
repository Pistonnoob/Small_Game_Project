#ifndef STAGESTATE_H
#define STAGESTATE_H
#include "GameState.h"
#include "Ai.h"

class StageState :
	public GameState
{
private:	//Variables
	Model m_model;
	CameraHandler myCamera;
	
	Model* testModel;
	Model* testModelGround;

	Ai* AI;
	vector<Enemy*> enemies;

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
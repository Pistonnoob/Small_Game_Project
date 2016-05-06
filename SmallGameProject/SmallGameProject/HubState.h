#ifndef HUBSTATE_H
#define HUBSTATE_H
#include "GameState.h"
#include "ParticleHandler.h"
#include "Player.h"
#include "Algorithm.h"

class HubState :
	public GameState
{
private:	//Variables
	CameraHandler myCamera;

	Model m_ground;

	Player player;
	ParticleHandler myParticleHandler;

	float t;

	DirectX::XMFLOAT3 playerPos;

	bool exitStage;

public:
	HubState();
	virtual ~HubState();
	void Shutdown();

	int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);

};

#endif
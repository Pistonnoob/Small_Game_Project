#ifndef STAGESTATE_H
#define STAGESTATE_H
#include "GameState.h"
class StageState :
	public GameState
{
private:	//Variables
	Model m_model;

	CameraHandler myCamera;
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
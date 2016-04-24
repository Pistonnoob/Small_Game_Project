#include "StageState.h"



StageState::StageState()
{
	this->m_model = Model();
	this->myCamera = CameraHandler();
}


StageState::~StageState()
{
	GameState::Shutdown();
	this->m_model.Shutdown();
}

void StageState::Shutdown()
{
}

int StageState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	return 0;
}

int StageState::HandleInput(InputHandler * input)
{
	return 0;
}

int StageState::Update(float deltaTime)
{
	return 0;
}

int StageState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	return 0;
}

#include "MenuState.h"



MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

int MenuState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	return 0;
}

int MenuState::HandleInput(InputHandler * input)
{
	return 0;
}

int MenuState::Update(float deltaTime)
{
	return 0;
}

int MenuState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	return 0;
}

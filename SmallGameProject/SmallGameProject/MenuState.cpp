#include "MenuState.h"



MenuState::MenuState()
{
	int selected = 0;
}


MenuState::~MenuState()
{
}

void MenuState::Shutdown()
{
}

int MenuState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	int result = 0;
	//Initialize the base class GameState
	result = this->InitializeBase(GSH);
	if (result)
	{
		//Proceed to initialize thyself
		this->selected = 0;
	}
	return result;
}

int MenuState::HandleInput(InputHandler * input)
{
	int result = 0;
	return result;
}

int MenuState::Update(float deltaTime)
{
	int result = 0;
	return result;
}

int MenuState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
	return result;
}

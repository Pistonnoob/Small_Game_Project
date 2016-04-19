#include "StartState.h"



StartState::StartState()
{
	this->startGame = false;
}

StartState::StartState(GameStateHandler * GSH)
{
	this->m_GSH = GSH;
}

StartState::~StartState()
{
}

int StartState::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH)
{
	int result = 0;
	
	//Initialize the base class GameState
	result = this->InitializeBase(GSH);
	if (result)
	{
		//Proceed to initialize thyself

	}

	return result;
}

int StartState::HandleInput(InputHandler * input)
{
	int result = 0;
	
	return result;
}

int StartState::Update(float deltaTime)
{
	int result = 0;
	return result;
}

int StartState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;

	//this->spriteBatch->Begin();

	////Draw sprites

	//this->spriteBatch->End();

	return result;
}

#include "GameStateHandler.h"

GameStateHandler::GameStateHandler()
{
	m_gameStates.reserve(5);
	this->m_device = nullptr;
	this->m_deviceContext = nullptr;
}

GameStateHandler::~GameStateHandler()
{
}

void GameStateHandler::Shutdown()
{
	while (m_gameStates.size())
	{
		GameState* state = m_gameStates.back();
		state->Shutdown();
		delete state;
		state = NULL;
		m_gameStates.pop_back();
	}
}

bool GameStateHandler::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	int result = 1;
	StartState* startState = new StartState();
	this->m_device = device;
	this->m_deviceContext = deviceContext;
	startState->Initialize(device, deviceContext, this);
	this->m_gameStates.push_back(startState);
	return result;
}

int GameStateHandler::HandleInput(InputHandler * input)
{
	int result = 0;
	if (this->m_gameStates.size())
	{
		result = m_gameStates.back()->HandleInput(input);
	}
	return result;
}

int GameStateHandler::Update(float deltaTime)
{
	int result = 0;
	if (this->m_gameStates.size())
	{
		result = m_gameStates.back()->Update(deltaTime);
	}
	return result;
}


int GameStateHandler::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
	if (m_gameStates.size())
	{
		result = m_gameStates.back()->Render(gHandler, hwnd);
	}
	return result;
}

void GameStateHandler::PushState(GameState * gameState)
{
	m_gameStates.push_back(gameState);
}

GameState * GameStateHandler::PopState()
{
	GameState* gameState = nullptr;
	if (m_gameStates.size())
	{
		gameState = m_gameStates.back();
		m_gameStates.pop_back();
	}
	return gameState;
}

#include "GameState.h"

GameState::GameState()
{
	m_GSH = NULL;
}

GameState::~GameState()
{
}

void GameState::Shutdown()
{
	this->m_GSH = NULL;
}

int GameState::InitializeBase(GameStateHandler * GSH)
{
	int result = 1;
	this->m_GSH = GSH;
	return result;
}

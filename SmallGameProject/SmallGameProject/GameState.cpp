#include "GameState.h"

GameState::GameState()
{
	m_GSH = NULL;
}

GameState::GameState(GameStateHandler * GSH)
{
	m_GSH = GSH;
}

GameState::~GameState()
{
}

void GameState::Shutdown()
{
	this->m_GSH = NULL;
}

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

void GameState::Initialize(GameStateHandler* GSH)
{
	this->m_GSH = GSH;
}

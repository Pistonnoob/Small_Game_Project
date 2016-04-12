#include "StartState.h"



StartState::StartState()
{
}

StartState::StartState(GameStateHandler * GSH)
{
	this->m_GSH = GSH;
}

StartState::~StartState()
{
}

void StartState::Initialize()
{

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
	return result;
}

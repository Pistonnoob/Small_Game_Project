#include "StartState.h"
#include "GameStateHandler.h"


StartState::StartState()
{
	this->startGame = false;
	this->manualClearing = false;
	this->startModel = Model();
	this->nextState = nullptr;
}

StartState::StartState(GameStateHandler * GSH)
{
	this->m_GSH = GSH;
}

StartState::~StartState()
{
}

void StartState::Shutdown()
{
	GameState::Shutdown();
	
	this->startModel.Shutdown();
}

int StartState::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH)
{
	int result = 0;
	this->startModel = Model();
	this->manualClearing = false;
	this->nextState = nullptr;
	//Initialize the base class GameState
	result = this->InitializeBase(GSH, device, deviceContext);
	if (result)
	{
		//Proceed to initialize thyself
		result = this->startModel.Initialize(device, deviceContext, "StartGame");
	}

	return result;
}

GameState * StartState::GetPush()
{
	return this->nextState;
}

int StartState::HandleInput(InputHandler * input)
{
	int result = 0;
	if (input->isKeyPressed(VK_SPACE))
	{
		this->startGame = true;
	}
	return result;
}

int StartState::Update(float deltaTime)
{
	int result = 0;
	if (this->startGame)
	{
		this->startGame = false;
		//Create the menu and push it
		MenuState* menu = new MenuState();
		menu->Initialize(this->m_device, this->m_deviceContext, this->m_GSH);
		menu->SetManualClearing(false);
		this->m_GSH->PushState(menu);
	}
	return result;
}

int StartState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;

	this->startModel.Render(gHandler->GetDeviceContext());

	return result;
}

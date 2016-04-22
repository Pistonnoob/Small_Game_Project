#include "MenuState.h"



MenuState::MenuState()
{
	int selected = 0;
	this->m_model = Model();
}


MenuState::~MenuState()
{
}

void MenuState::Shutdown()
{
	GameState::Shutdown();

	this->m_model.Shutdown();
}

int MenuState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	int result = 0;
	this->selected = 0;
	this->m_model = Model();
	//Initialize the base class GameState
	result = this->InitializeBase(GSH, device, deviceContext);
	if (result)
	{
		//Proceed to initialize thyself
		bool modelResult = m_model.Initialize(device, deviceContext, "Menu");
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixScaling(0.02f, 0.02f, 0.02f);
		worldMatrix *= DirectX::XMMatrixTranslation(0, -4, 0);
		modelResult = this->camera.Initialize();
		this->m_model.SetWorldMatrix(worldMatrix);
	}
	return result;
}

int MenuState::HandleInput(InputHandler * input)
{
	int result = 1;
	int oldSelected = this->selected;
	if (input->isKeyPressed(VK_DOWN))
	{
		this->selected--;
	}
	if (input->isKeyPressed(VK_UP))
	{
		this->selected++;
	}
	if (this->selected < 0)
		this->selected = OPTION_COUNT;
	this->selected = this->selected % OPTION_COUNT;


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
	gHandler->DeferredRender(&this->m_model, &this->camera);
	return result;
}

#include "MenuState.h"



MenuState::MenuState()
{
	this->first = true;
	this->doOption = false;
	this->selected = 0;
	this->m_model = Model();
	this->myTextures = Texture();
	this->myCamera = CameraHandler();
}


MenuState::~MenuState()
{
}

void MenuState::Shutdown()
{
	GameState::Shutdown();
	this->myTextures.Shutdown();
	this->m_model.Shutdown();
}

int MenuState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	int result = 0;
	this->first = true;
	this->doOption = false;
	this->selected = 0;
	this->m_model = Model();
	//Initialize the base class GameState
	result = this->InitializeBase(GSH, device, deviceContext);
	if (result)
	{
		//Proceed to initialize thyself
		//Firstly thy must initialize thy mighty sword of obj!
		bool victory = m_model.Initialize(device, deviceContext, "Menu");
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixScaling(0.02f, 0.02f, 0.02f);
		worldMatrix *= DirectX::XMMatrixTranslation(0, -4, 0);
		victory = this->myCamera.Initialize();
		this->m_model.SetWorldMatrix(worldMatrix);

		//Now initialize thy shields (texture views of changing nature!)
		this->myTextures = Texture();
		std::string skinOfMyFallenEnemies = "MenuSelected.mtl";
		victory = this->myTextures.Initialize(device, deviceContext, skinOfMyFallenEnemies);
	}
	return result;
}

int MenuState::HandleInput(InputHandler * input)
{
	int result = 1;
	int oldSelected = this->selected;

	if (input->isKeyPressed(DIK_DOWNARROW))
	{
		this->selected++;
	}
	if (input->isKeyPressed(DIK_UPARROW))
	{
		this->selected--;
	}
	if (this->selected < 0)
		this->selected = OPTION_COUNT - 1;
	this->selected = this->selected % OPTION_COUNT;
	//If the selection changed
	if (oldSelected != this->selected)
	{
		//Switch the textures
		ID3D11ShaderResourceView* oscarHasFallen = this->m_model.SwapTextureView(this->myTextures.GetTexture(this->selected), this->selected);
		this->myTextures.SwapTextureView(oscarHasFallen, this->selected);
		ID3D11ShaderResourceView* axelHasFallen = this->m_model.SwapTextureView(this->myTextures.GetTexture(oldSelected), oldSelected);
		this->myTextures.SwapTextureView(axelHasFallen, oldSelected);
	}
	else if (this->first)
	{
		this->first = false;
 		ID3D11ShaderResourceView* oscarHasFallen = this->m_model.SwapTextureView(this->myTextures.GetTexture(this->selected), this->selected);
		this->myTextures.SwapTextureView(oscarHasFallen, this->selected);
	}

	return result;
}

int MenuState::Update(float deltaTime)
{
	int result = 0;

	if (doOption)
	{
		switch (this->selected)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
	}

	return result;
}

int MenuState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
	gHandler->DeferredRender(&this->m_model, &this->myCamera);
	return result;
}

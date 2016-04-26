#include "MenuState.h"
#include "GameStateHandler.h"



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
		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 0.0f, -19.0f));
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
	if (input->isKeyPressed(DIK_SPACE) || input->isKeyPressed(DIK_RETURN))
	{
		this->doOption = true;
	}
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

	if (input->isKeyPressed(DIK_ESCAPE))
	{
		//Ask Loki to cheat and lie to the system that we have used the option END_GAME
		this->doOption = true;
		this->selected = MenuOption::END_GAME;
	}

	return result;
}

int MenuState::Update(float deltaTime)
{
	int result = 1;

	if (doOption)
	{
		this->doOption = false;
		switch (this->selected)
		{
		case MenuOption::START_GAME:
		{
			//Create a stage state and push it to the stack
			StageState* newStage = new StageState();
			newStage->Initialize(this->m_device, this->m_deviceContext, this->m_GSH);
			newStage->SetManualClearing(false);
			this->m_GSH->PushState(newStage);
		}
		break;
		case MenuOption::OPTIONS:
			break;
		case MenuOption::END_GAME:
		{
			result = 0;
			break;
		}
		default:
			break;
		}
	}

	return result;
}

int MenuState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;

	gHandler->SetDeferredRTVs();

	gHandler->DeferredRender(&this->m_model, &this->myCamera);

	LightShaderParameters* lightShaderParams = new LightShaderParameters;

	gHandler->SetLightRTV();

	lightShaderParams->camPos = this->myCamera.GetCameraPos();
	lightShaderParams->lightPos = DirectX::XMFLOAT4(0.0f, 0.0f, -20.0f, 0.0f);

	DirectX::XMMATRIX viewMatrix;
	this->myCamera.GetBaseViewMatrix(viewMatrix);

	lightShaderParams->viewMatrix = viewMatrix;

	gHandler->LightRender(lightShaderParams);

	delete lightShaderParams;

	return result;
}

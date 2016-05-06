#include "HubState.h"
#include "GameStateHandler.h"
#include "MyMathLib.h"



HubState::HubState()
{
	this->myCamera = CameraHandler();
	this->myParticleHandler = ParticleHandler();

	this->m_ground = Model();
	this->player = Player();

	this->playerPos = DirectX::XMFLOAT3(0, 0, 0);

	this->exitStage = false;
}


HubState::~HubState()
{
}

void HubState::Shutdown()
{
	//Release the models
	this->m_ground.Shutdown();

	this->myParticleHandler.Shutdown();

	this->player.Shutdown();

	GameState::Shutdown();
}

int HubState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	int result = 0;
	this->exitStage = false;

	//Arm thy father
	result = this->InitializeBase(GSH, device, deviceContext);
	if (result)
	{
		//Open thy eyes!
		bool cameraResult = this->myCamera.Initialize();
		float zoomIn = 1.0f / 6.0f;

		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 20.0f / zoomIn, -7.0f / zoomIn));

		this->myCamera.SetLookAt(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
		this->myCamera.UpdateCamera();
		if (cameraResult)
			result = 1;

		//Pull down the visor of epic particle effects
		//A visor is the moving part of a helmet, namely the part that protects the eyes
		this->myParticleHandler.Initialize(device, deviceContext);

		//Place the ground beneeth your feet and thank the gods for their
		//sanctuary from the oblivion below!
		this->m_ground = Model();

		result = this->m_ground.Initialize(device, deviceContext, "testMap");
		if (!result) {
			return false;
		}

		PointLight light;
		light.Diffuse = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		light.Ambient = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		light.Specular = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		light.Position = DirectX::XMFLOAT4(0.0f, 1.0f, -4.0f, 1.0f);
		light.Attenuation = DirectX::XMFLOAT4(50.0f, 1.0f, 0.18f, 0.032f);
		this->pointLights.push_back(light);

		light.Diffuse = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		light.Ambient = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		light.Specular = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		light.Position = DirectX::XMFLOAT4(-5.0f, 1.0f, 2.0f, 1.0f);
		this->pointLights.push_back(light);

		light.Diffuse = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		light.Ambient = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		light.Specular = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		light.Position = DirectX::XMFLOAT4(5.0f, 1.0f, 2.0f, 1.0f);
		this->pointLights.push_back(light);

		result = this->player.Initialize(device, deviceContext, "sphere1", "carSLS3", true);
		if (!result) {
			return false;
		}

		DirectX::XMFLOAT3 a = this->player.GetPosition();
		int i = 0;
	}


	return result;
}

int HubState::HandleInput(InputHandler * input)
{
	int result = 1;

	if (input->isKeyDown(DIK_ESCAPE))
		this->exitStage = true;

	if (input->isKeyDown(DIK_W)) {
		this->player.moveUp();
	}
	if (input->isKeyDown(DIK_S)) {
		this->player.moveDown();
	}
	if (input->isKeyDown(DIK_D)) {
		this->player.moveRight();
	}
	if (input->isKeyDown(DIK_A)) {
		this->player.moveLeft();
	}

	return result;
}

int HubState::Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler)
{
	int result = 1;

	this->player.Update(input, gHandler, &this->myCamera);

	XMFLOAT3 playerPos = this->player.GetPosition();
	
	this->myParticleHandler.Update(deltaTime / 1000, this->m_deviceContext);

	if (this->exitStage)
	{
		this->exitStage = false;
		//Pop ourself
		GameState* state = this->m_GSH->PopState();
		//We do not care about the returned state but check if return
		if (state)
		{
			//The state wasn't a nullptr, meaning it didn't have automatic clearing on
			//Something went somewhat wrong here eh?
		}
	}

	this->myParticleHandler.Update(deltaTime, this->m_deviceContext);
	this->pointLights.at(0).Position = XMFLOAT4(playerPos.x, 1.0f, playerPos.z, 1.0f);

	return result;
}

int HubState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
	//Render models

	//Player and weapon render
	gHandler->DeferredRender(this->player.GetModel(), &this->myCamera);
	gHandler->DeferredRender(this->player.GetWeapon()->GetModel(), &this->myCamera);

	gHandler->DeferredRender(&this->m_ground, &this->myCamera);

	//shadowMap

	gHandler->ShadowRender(this->player.GetModel(), &this->myCamera);
	gHandler->ShadowRender(this->player.GetWeapon()->GetModel(), &this->myCamera);

	gHandler->LightRender(this->myCamera.GetCameraPos(), this->pointLights);

	this->myParticleHandler.Render(gHandler, &this->myCamera);

	return result;
}

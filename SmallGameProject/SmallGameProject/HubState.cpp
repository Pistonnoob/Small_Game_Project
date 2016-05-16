#include "HubState.h"
#include "GameStateHandler.h"
#include "MyMathLib.h"



HubState::HubState()
{
	this->myCamera = CameraHandler();
	this->myParticleHandler = ParticleHandler();
	this->m_ground = Model();
	this->portals = std::vector<Model>();
	this->hubStatistics = UIHandler();

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

	for (std::vector<Model>::iterator portal = this->portals.begin(); portal != this->portals.end(); portal++) {
		(*portal).Shutdown();
	}

	this->hubStatistics.Shutdown();

	this->myParticleHandler.Shutdown();

	this->player.Shutdown();
	this->playerSubject.ShutDown();

	GameState::Shutdown();
}

int HubState::Initialize(GraphicHandler* gHandler, GameStateHandler * GSH)
{
	int result = 0;
	this->exitStage = false;

	ID3D11Device* device = gHandler->GetDevice();
	ID3D11DeviceContext* deviceContext = gHandler->GetDeviceContext();

	GameData::InitializeStageStateGD(device, deviceContext, &this->playerSubject);

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

		//hubInterface
		this->hubStatistics.Initialize(gHandler);

		//add the background
		this->hubStatistics.CreateTextHolder(32); // Powerups
		this->hubStatistics.CreateTextHolder(32); // spread
		this->hubStatistics.CreateTextHolder(32); // spitfire
		this->hubStatistics.CreateTextHolder(32); // reverse bullets
		int powerUps = GameData::GetInstance()->GetUnlockedPowerups();
		std::string titleText = "Power-ups status:";
		std::string arcfireText = "Arcfire unlocked";
		std::string spitfireText = "Splitfire locked";
		std::string reverseText = "Reversefire locked";
		if (powerUps == 2)
		{
			spitfireText = "Splitfire unlocked";
		}

		else if (powerUps == 3)
		{
			spitfireText = "Splitfire unlocked";
			reverseText = "Reversefire unlocked";
		}

		//400, 500
		this->hubStatistics.UpdateTextHolder(0, titleText, 10, 175, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);
		this->hubStatistics.UpdateTextHolder(1, arcfireText, 10, 200, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.0f);
		this->hubStatistics.UpdateTextHolder(2, spitfireText, 10, 220, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.0f);
		this->hubStatistics.UpdateTextHolder(3, reverseText, 10, 240, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.0f);

		//Pull down the visor of epic particle effects
		//A visor is the moving part of a helmet, namely the part that protects the eyes
		this->myParticleHandler.Initialize(device, deviceContext);

		//Place the ground beneeth your feet and thank the gods for their
		//sanctuary from the oblivion below!
		result = this->m_ground.Initialize(device, deviceContext, "HubWorld");
		if (!result) {
			return false;
		}

		for (int i = 0; i < NR_OF_MAPS; i++){
			Model portal = Model();
			result = portal.Initialize(device, deviceContext, "portal");
			if (!result) {
				return false;
			}
			this->portals.push_back(portal);
		}

		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(-30.0f, 0.0f, 30.0f);
		this->portals.at(0).SetWorldMatrix(worldMatrix); 
		worldMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 30.0f);
		this->portals.at(1).SetWorldMatrix(worldMatrix);

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
		light.Position = DirectX::XMFLOAT4(-30.0f, 1.0f, 30.0f, 1.0f);
		this->pointLights.push_back(light);

		light.Diffuse = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		light.Ambient = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		light.Specular = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		light.Position = DirectX::XMFLOAT4(0.0f, 1.0f, 30.0f, 1.0f);
		this->pointLights.push_back(light);
		
		this->playerSubject = EntitySubject();
		this->playerSubject.AddObserver(GameData::GetInstance());
		this->playerSubject.AddObserver(&this->myParticleHandler);

		result = this->player.Initialize(gHandler, "sphere1", "projectile", true, &this->playerSubject);

		GameData::GetInstance()->LoadPlayerData("PlayerSave");

		if (!result) {
			return false;
		}
	}

	return result;
}

int HubState::HandleInput(InputHandler * input)
{
	int result = 1;

	if (input->isKeyPressed(DIK_ESCAPE))
		this->exitStage = true;
	if (input->isKeyPressed(DIK_1))
	{
		GameData::GetInstance()->equipWeapon(Modifiers::WEAPON::PISTOL);
		this->player.setWeapon(GameData::GetInstance()->GetWeapon());
	}

	if (input->isKeyPressed(DIK_2))
	{
		GameData::GetInstance()->equipWeapon(Modifiers::WEAPON::SHOTGUN);
		this->player.setWeapon(GameData::GetInstance()->GetWeapon());
	}

	if (input->isKeyPressed(DIK_3))
	{
		GameData::GetInstance()->equipWeapon(Modifiers::WEAPON::UZI);
		this->player.setWeapon(GameData::GetInstance()->GetWeapon());
	}
	


	return result;
}

int HubState::Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler)
{
	int result = 1;
	
	this->player.Update(input, gHandler, &this->myCamera,deltaTime);

	DirectX::XMFLOAT3 playerPos = this->player.GetPosition();

	if ((playerPos.x < -28.5f && playerPos.x > -31.5f) && (playerPos.z < 31.5f && playerPos.z > 28.5f)) {
		this->player.SetPosition(0.0f, 0.0f);
		this->player.Update(input, gHandler, &this->myCamera, deltaTime);
		StageState* newStage = new StageState();
		newStage->Initialize(gHandler, this->m_GSH);
		newStage->LoadMap(gHandler->GetDevice(), gHandler->GetDeviceContext(), 1);
		newStage->SetManualClearing(false);
		this->m_GSH->PushState(newStage);
	}
	if ((playerPos.x < 1.5f && playerPos.x > -1.5f) && (playerPos.z < 31.5f && playerPos.z > 28.5f)) {
		this->player.SetPosition(0.0f, 0.0f);
		this->player.Update(input, gHandler, &this->myCamera, deltaTime);
		StageState* newStage = new StageState();
		newStage->Initialize(gHandler, this->m_GSH);
		newStage->LoadMap(gHandler->GetDevice(), gHandler->GetDeviceContext(), 2);
		newStage->SetManualClearing(false);
		this->m_GSH->PushState(newStage);
	}
	
	if (this->exitStage)
	{
		GameData::GetInstance()->SavePlayerData("PlayerSave");
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
	this->pointLights.at(0).Position = DirectX::XMFLOAT4(playerPos.x, 1.0f, playerPos.z, 1.0f);

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

	for (std::vector<Model>::iterator portal = this->portals.begin(); portal != this->portals.end(); portal++) {
		gHandler->DeferredRender(&(*portal), &this->myCamera);
	}
	//shadowMap

	gHandler->ShadowRender(this->player.GetModel(), &this->myCamera);
	gHandler->ShadowRender(this->player.GetWeapon()->GetModel(), &this->myCamera);
	//gHandler->ShadowRender(&this->m_ground, &this->myCamera);

	gHandler->LightRender(this->myCamera.GetCameraPos(), this->pointLights);

	this->myParticleHandler.Render(gHandler, &this->myCamera);

	gHandler->UIRender(this->player.GetUIHandler());
	gHandler->UIRender(&this->hubStatistics);

	return result;
}

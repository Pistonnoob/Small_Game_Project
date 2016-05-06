#include "StageState.h"
#include "GameStateHandler.h"
#include "MyMathLib.h"



StageState::StageState()
{
	this->myCamera = CameraHandler();
	this->myParticleHandler = ParticleHandler();

	this->m_car = Model();
	this->m_ball = Model();
	this->m_ground = Model();
	this->m_AI = Ai();
	this->player = Player();

    this->playerPos = DirectX::XMFLOAT3(0, 0, 0);

	this->playerPos = DirectX::XMFLOAT3(0, 0, 0);

	this->exitStage = false;

	this->camPosX = -30.0f;
	this->camPosZ = 0.0f;
	this->inc = true;
}


StageState::~StageState()
{
}

void StageState::Shutdown()
{
	//Release the models
	this->m_car.Shutdown();
	this->m_ball.Shutdown();
	this->m_ground.Shutdown();

	//Release the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* enemyTemp = this->enemies.at(i);
		enemyTemp->Shutdown();
		delete enemyTemp;
	}
	this->enemies.clear();
	for (int i = 0; i < this->projectiles.size(); i++)
	{
		Projectile* temp = this->projectiles.at(i);
		temp->Shutdown();
		delete temp;
	}
	this->projectiles.clear();

	if (this->ability1)
		delete this->ability1;
	if (this->ability2)
		delete this->ability2;
	if (this->ability3)
		delete this->ability3;

	this->myParticleHandler.Shutdown();

	this->player.Shutdown();

	GameState::Shutdown();
}

int StageState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
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

		/*this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 10.0f / zoomIn, -7.0f / zoomIn));
		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 0.0f, -20.0f));*/
		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 20.0f / zoomIn, -7.0f / zoomIn));
		//this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 6.0f, -50.0f));

		this->myCamera.SetLookAt(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
		this->myCamera.UpdateCamera();
		if (cameraResult)
			result = 1;

		//Pull down the visor of epic particle effects
		//A visor is the moving part of a helmet, namely the part that protects the eyes
		this->myParticleHandler.Initialize(device, deviceContext);

		//Arm thy mind with the knowledge that will lead thy armies to battle!
		this->m_AI = Ai();


		//Form thy armies from the clay!
		this->m_car = Model();
		this->m_ball = Model();
		bool modelResult = this->m_car.Initialize(device, this->m_deviceContext, "projectile");
		if (!modelResult) {
			return false;
		}
		modelResult = this->m_ball.Initialize(device, this->m_deviceContext, "sphere1");
		if (!modelResult) {
			return false;
		}

		//Colour thy armies in the name of the racist overlord Axel!
		this->m_car.SetColor(DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f));
		this->m_ball.SetColor(DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f));

		//Arm thy armies!
		//creates the enemies must call setModel function to give enemies models
		this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		//this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		//this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);
		// 
		//this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		//this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
		//      this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		this->ability1 = new ArcFire();
		this->ability2 = new SplitFire();
		this->ability3 = new ReverseFire();

		//Place the ground beneeth your feet and thank the gods for their
		//sanctuary from the oblivion below!
		this->m_ground = Model();

		result = this->m_ground.Initialize(device, deviceContext, "testMap");
		if (!result) {
			return false;
		}
		//this->m_ground.SetColor(DirectX::XMFLOAT3(0.2f, 0.2f, 0.2f));

		DirectX::XMMATRIX worldMatrix;
		/*worldMatrix = DirectX::XMMatrixTranslation(0.0f, -5.0f, 0.0f);
		this->m_ground.SetWorldMatrix(worldMatrix);*/
		worldMatrix = DirectX::XMMatrixScaling(3.0f, 3.0f, 3.0f);
		worldMatrix *= DirectX::XMMatrixTranslation(0.0f, -3.5f, 2.0f);
		this->m_car.SetWorldMatrix(worldMatrix);

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

int StageState::HandleInput(InputHandler * input)
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

int StageState::Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler)
{
	int result = 1;

	this->player.Update(input, gHandler, &this->myCamera);

	XMFLOAT3 playerPos = this->player.GetPosition();
	//sends the enemies vector to the m_AI for updating cameraPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, playerPos);
	XMFLOAT3 enemyPos = this->enemies.at(0)->GetPosition();
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
	this->pointLights.at(2).Position = XMFLOAT4(enemyPos.x, 1.0f, enemyPos.z, 1.0f);

	/*this->camPosX += deltaTime / 100000;

	if (this->camPosX > 30) {
	this->camPosX = -30.0f;
	this->camPosZ = 0.0f;
	this->inc = true;
	}
	if (this->camPosX > 0) {
	this->inc = false;
	}
	if (this->inc && this->camPosZ > -30.0f) {
	this->camPosZ -= deltaTime / 100000;
	}
	else if(!this->inc && this->camPosZ < 0.0f) {
	this->camPosZ += deltaTime / 100000;

	}

	this->myCamera.SetCameraPos(DirectX::XMFLOAT3(this->camPosX, 4.0f, this->camPosZ));
	this->myCamera.UpdateCamera();*/

	return result;
}

int StageState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
	//Render models

	//Player and weapon render
	gHandler->DeferredRender(this->player.GetModel(), &this->myCamera);
	gHandler->DeferredRender(this->player.GetWeapon()->GetModel(), &this->myCamera);

	//renders all the actors in the enemies vector
	for (int i = 0; i < this->enemies.size(); i++)
	{
		XMFLOAT3 pos = this->enemies.at(i)->GetPosition();
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		this->m_car.SetWorldMatrix(worldMatrix);

		gHandler->DeferredRender(this->enemies.at(i)->GetModel(), &this->myCamera);

	}
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        XMFLOAT3 pos = this->projectiles.at(i)->GetPosition();
        DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
        this->m_ball.SetWorldMatrix(worldMatrix);

        gHandler->DeferredRender(this->projectiles.at(i)->GetModel(), &this->myCamera);
    }

	//this->graphicH->DeferredRender(this->m_car, this->cameraH);

	//Set deferred render targets

	for (int i = 0; i < this->projectiles.size(); i++)
	{
		XMFLOAT3 pos = this->projectiles.at(i)->GetPosition();
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		this->m_ball.SetWorldMatrix(worldMatrix);

		gHandler->DeferredRender(this->projectiles.at(i)->GetModel(), &this->myCamera);
	}
	XMFLOAT3 pos;
	DirectX::XMMATRIX worldMatrix;
	/*pos = this->test->getPosition();
	worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	this->m_ball.SetWorldMatrix(worldMatrix);
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        XMFLOAT3 pos = this->projectiles.at(i)->GetPosition();
        DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
        this->m_ball.SetWorldMatrix(worldMatrix);

        gHandler->DeferredRender(this->projectiles.at(i)->GetModel(), &this->myCamera);
    }
    XMFLOAT3 pos;
    DirectX::XMMATRIX worldMatrix;
    /*pos = this->test->getPosition();
    worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
    this->m_ball.SetWorldMatrix(worldMatrix);

	gHandler->DeferredRender(this->test->getModel(), &this->myCamera);*/

	//this->graphicH->DeferredRender(this->m_car, this->cameraH);

	gHandler->DeferredRender(&this->m_ground, &this->myCamera);

	//shadowMap
	for (int i = 0; i < this->enemies.size(); i++)
	{
		gHandler->ShadowRender(this->enemies[i]->GetModel(), &this->myCamera);
	}

	gHandler->LightRender(this->myCamera.GetCameraPos(), this->pointLights);

	//this->myParticleHandler.Render(gHandler, &this->myCamera);

	return result;
}

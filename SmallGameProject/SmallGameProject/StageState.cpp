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

    this->playerPos = DirectX::XMFLOAT3(0, 0, 0);

	this->exitStage = false;
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

	if(this->ability1)
	    delete this->ability1;
	if(this->ability2)
	    delete this->ability2;
	if(this->ability3)
		delete this->ability3;

	this->myParticleHandler.Shutdown();

	//Release your m_AI

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
		float zoomIn = 1.0f / 4.0f;

		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 10.0f / zoomIn, -7.0f / zoomIn));
		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0.0f, 8.0f, -50.0f));

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
		bool modelResult = this->m_car.Initialize(device, this->m_deviceContext, "carSLS3");
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

		this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);
		 
		this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
        this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

        this->ability1 = new ArcFire();
        this->ability2 = new SplitFire();
        this->ability3 = new ReverseFire();


		//Place the ground beneeth your feet and thank the gods for their
		//sanctuary from the oblivion below!
		this->m_ground = Model();

		result = this->m_ground.Initialize(device, deviceContext, "ground");
		if (!result) {
			return false;
		}
		this->m_ground.SetColor(DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f));

		DirectX::XMMATRIX worldMatrix;
		worldMatrix = DirectX::XMMatrixTranslation(0.0f, -5.0f, 0.0f);
		this->m_ground.SetWorldMatrix(worldMatrix);


	}


	return result;
}

int StageState::HandleInput(InputHandler * input)
{
	int result = 1;

	if (input->isKeyPressed(DIK_ESCAPE))
		this->exitStage = true;


	return result;
}

int StageState::Update(float deltaTime)
{
	int result = 1;

	//sends the enemies vector to the m_AI for updating cameraPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, DirectX::XMFLOAT3(0, 0.0f, -20.0f));

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


	return result;
}

int StageState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;

	//Render models
	//renders all the actors in the enemies vector
	for (int i = 0; i < this->enemies.size(); i++)
	{
		XMFLOAT3 pos = this->enemies.at(i)->getPosition();
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		this->m_car.SetWorldMatrix(worldMatrix);

		gHandler->DeferredRender(this->enemies.at(i)->getModel(), &this->myCamera);
	}
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        XMFLOAT3 pos = this->projectiles.at(i)->getPosition();
        DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
        this->m_ball.SetWorldMatrix(worldMatrix);

        gHandler->DeferredRender(this->projectiles.at(i)->getModel(), &this->myCamera);
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
		gHandler->ShadowRender(this->enemies[i]->getModel(), &this->myCamera);
	}

	gHandler->LightRender();
	
	this->myParticleHandler.Render(gHandler, &this->myCamera);
	return result;
}

#include "StageState.h"
#include "GameStateHandler.h"
#include "MyMathLib.h"
#include "Weapon.h"



StageState::StageState()
{
	this->myCamera = CameraHandler();

	this->m_car = Model();
    this->m_ball = Model();
	this->m_ground = Model();
	this->m_AI = Ai();

    this->enemyPjHandler = ProjectileHandler();

    this->enemySubject = EntitySubject();
    this->enemySubject.addObserver(&this->enemyPjHandler);

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

    this->enemyPjHandler.ShutDown();
    this->enemySubject.ShutDown();
	//Release the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* enemyTemp = this->enemies.at(i);
		enemyTemp->Shutdown();
		delete enemyTemp;
	}
	this->enemies.clear();

    delete this->ability1;
    delete this->ability2;
    delete this->ability3;

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
		this->myCamera.SetLookAt(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
		this->myCamera.UpdateCamera();
		if (cameraResult)
			result = 1;




		//Army thy mind with the knowledge that will lead thy armies to battle!
		this->m_AI = Ai();

        this->enemyPjHandler.Initialize(device, this->m_deviceContext);
		
		this->testWeap.Initialize(device, deviceContext, "string");


		//Form thy armies from the clay!
		this->m_car = Model();
        this->m_ball = Model();
		bool modelResult = this->m_car.Initialize(device, this->m_deviceContext, "sphere1");
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
		//this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		//this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		//this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);
		 
		this->enemies.push_back(new RangedEnemy(0.0f, 20.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		//this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
        //this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		ArcFire* temp1 = new ArcFire();
		temp1->Initialize(3.14f / 2, 1, 500, 50, 1, 400);
		this->ability1 = temp1;

		SplitFire* temp2 = new SplitFire();
		temp2->Initialize(3.14f, 3, 500, 50, 1, 400, 5, 3.14f / 2);
		this->ability2 = temp2;

		ReverseFire* temp3 = new ReverseFire();
		temp3->Initialize(3.14f / 2, 15, 500, 50, 1, 400);
		this->ability3 = temp3;

		//Place the ground beneeth your feet and thank the gods for their
		//sanctuary from the oblivion below!
		this->m_ground = Model();

		result = this->m_ground.Initialize(device, deviceContext, "ground");
		if (!result) {
			return false;
		}
		this->m_ground.SetColor(DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f));

		DirectX::XMMATRIX worldMatrix;
		worldMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		this->m_ground.SetWorldMatrix(worldMatrix);

	}


	return result;
}

int StageState::HandleInput(InputHandler * input)
{
	int result = 1;

	if (input->isKeyPressed(DIK_ESCAPE))
		this->exitStage = true;

	if (input->isKeyPressed(DIK_1))
	{
		this->ability1->activate(this->enemies.at(0), &this->enemySubject, DirectX::XMFLOAT3(0, 0, 0));
	}
	this->ability1->update(this->enemies.at(0), &this->enemySubject);

	if (input->isKeyPressed(DIK_2))
	{
		this->ability2->activate(this->enemies.at(0), &this->enemySubject, DirectX::XMFLOAT3(0, 0, 0));
	}
	this->ability2->update(this->enemies.at(0), &this->enemySubject);

	if (input->isKeyPressed(DIK_3))
	{
		this->ability3->activate(this->enemies.at(0), &this->enemySubject, DirectX::XMFLOAT3(0, 0, 0));
	}
	this->ability3->update(this->enemies.at(0), &this->enemySubject);

	return result;
}

int StageState::Update(float deltaTime)
{
	int result = 1;

	this->enemies.at(0)->setAimDir(DirectX::XMFLOAT3(0, 0, 1));

	this->testWeap.shootWeapon(this->enemies.at(0));
	//sends the enemies vector to the m_AI for updating playerPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, DirectX::XMFLOAT3(0,0,0));
    this->enemyPjHandler.update(deltaTime);

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
    XMFLOAT3 pos;
    DirectX::XMMATRIX worldMatrix;

	//Render models
	//renders all the actors in the enemies vector
	for (int i = 0; i < this->enemies.size(); i++)
	{
		pos = this->enemies.at(i)->getPosition();
		worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		this->m_car.SetWorldMatrix(worldMatrix);

		gHandler->DeferredRender(this->enemies.at(i)->getModel(), &this->myCamera);
	}
    this->enemyPjHandler.render(gHandler, &this->myCamera);

	gHandler->DeferredRender(&this->m_ground, &this->myCamera);

	//shadowMap
	gHandler->SetShadowRTV(); //här är läckan
	for (int i = 0; i < this->enemies.size(); i++)
	{
		gHandler->ShadowRender(this->enemies[i]->getModel(), &this->myCamera);
	}

	return result;
}

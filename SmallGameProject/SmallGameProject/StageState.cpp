#include "StageState.h"
#include "GameStateHandler.h"
#include "MyMathLib.h"



StageState::StageState()
{
	this->myCamera = CameraHandler();

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
		this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);
		 
		this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, true);

		this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
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

	return result;
}

int StageState::Update(float deltaTime)
{
	int result = 1;

    //0x57 = W
    if (GetAsyncKeyState(0x57))
    {
        this->playerPos.z += 0.5f;
    }
    //0x53 = S
    if (GetAsyncKeyState(0x53))
    {
        this->playerPos.z -= 0.5f;
    }
    //0x44 = D
    if (GetAsyncKeyState(0x44))
    {
        this->playerPos.x += 0.5f;
    }
    //0x41 = A
    if (GetAsyncKeyState(0x41))
    {
        this->playerPos.x -= 0.5f;
    }
    //0x43 = C
    if (GetAsyncKeyState(0x43))
    {
        for (int i = 0; i < this->projectiles.size(); i++)
        {
            Projectile* temp = this->projectiles.at(i);
            temp->Shutdown();
            delete temp;
        }
        this->projectiles.clear();
    }
    //0x31 = 1
    if (GetAsyncKeyState(0x31))
    {
        for (int i = 0; i < this->projectiles.size(); i++)
        {
            Projectile* temp = this->projectiles.at(i);
            temp->Shutdown();
            delete temp;
        }
        this->projectiles.clear();
        this->ability1->activate(this->projectiles, &this->m_ball, DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, 1), 3.14 / 3, 15);
    }
    //0x32 = 2
    if (GetAsyncKeyState(0x32))
    {
        for (int i = 0; i < this->projectiles.size(); i++)
        {
            Projectile* temp = this->projectiles.at(i);
            temp->Shutdown();
            delete temp;
        }
        this->projectiles.clear();
        this->ability2->activate(this->projectiles, &this->m_ball, DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, 1), 3.14 / 2, 4);
    }
    this->ability2->update(this->projectiles, &this->m_ball);
    //0x33 = 3
    if (GetAsyncKeyState(0x33))
    {
        for (int i = 0; i < this->projectiles.size(); i++)
        {
            Projectile* temp = this->projectiles.at(i);
            temp->Shutdown();
            delete temp;
        }
        this->projectiles.clear();
        this->ability3->activate(this->projectiles, &this->m_ball, DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, 1), 3.14 * 2, 30);
    }
    this->ability3->update(this->projectiles, &this->m_ball);


	//sends the enemies vector to the m_AI for updating playerPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, this->playerPos);
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        this->projectiles.at(i)->update();
    }
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

    XMFLOAT3 pos = this->playerPos;
    DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
    this->m_car.SetWorldMatrix(worldMatrix);

    gHandler->DeferredRender(&this->m_car, &this->myCamera);


	//this->graphicH->DeferredRender(this->m_car, this->cameraH);
	gHandler->DeferredRender(&this->m_ground, &this->myCamera);


	return result;
}

#include "StageState.h"
#include "GameStateHandler.h"
#include "MyMathLib.h"
#include "Weapon.h"



StageState::StageState()
{
	this->myCamera = CameraHandler();
	this->myParticleHandler = ParticleHandler();

	this->m_car = Model();
	this->m_ball = Model();
	this->m_ground = Model();
	this->m_AI = Ai();
	this->player = Player();

	this->enemySubject = EntitySubject();
    this->enemyPjHandler = ProjectileHandler();
	this->enemySubject.AddObserver(&this->enemyPjHandler);

	this->playerSubject = EntitySubject();
	this->playerProjectile = ProjectileHandler();

	this->playerSubject.AddObserver(&this->playerProjectile);
	this->playerSubject.AddObserver(GameData::GetInstance());
	
	this->exitStage = false;

	this->spreadPower = PowerUp();
	this->powerUpSubject = EntitySubject();

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

    this->enemyPjHandler.ShutDown();
    this->enemySubject.ShutDown();

	this->playerSubject.ShutDown();
	this->playerProjectile.ShutDown();
	
	this->player.Shutdown();

	//Release the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* enemyTemp = this->enemies.at(i);
		enemyTemp->Shutdown();
		delete enemyTemp;
	}
	this->enemies.clear();

	this->myParticleHandler.Shutdown();
	this->powerUpSubject.ShutDown();
	this->spreadPower.Shutdown();

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

        this->enemyPjHandler.Initialize(device, this->m_deviceContext);
		

		//the player will rise
 		this->player.Initialize(device, deviceContext, "sphere1","ogreFullG", false, &this->playerSubject);
		this->playerProjectile.Initialize(device, this->m_deviceContext);
		
		//Form thy armies from the clay!
		this->m_car = Model();
		this->m_ball = Model();

		bool modelResult = this->m_ball.Initialize(device, this->m_deviceContext, "projectile");
		if (!modelResult) {
			return false;
		}
		modelResult = this->m_car.Initialize(device, this->m_deviceContext, "sphere1");
		if (!modelResult) {
			return false;
		}

		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		//this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);
		 
		this->enemies.push_back(new RangedEnemy(0.0f, 20.0f));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		//this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
        //this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);

		//ze powerups
		this->spreadPower.Initialize(device, deviceContext, "sphere1", true, &this->powerUpSubject);
		this->spreadPower.GetModel()->SetColor(XMFLOAT3(0, 0, 255));

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

		if (!result) {
			return false;
		}

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
	    //how do I update this shiet
		Entity* ptr = &this->player;
		this->player.GetEntitySubject()->Notify(ptr, Events::PICKUP::POWERUP_PICKUP);
	}

	return result;
}

int StageState::Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler)
{
	int result = 1;
	//sends the enemies vector to the m_AI for updating playerPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, DirectX::XMFLOAT3(0,0,0));
    this->enemyPjHandler.Update(deltaTime);
	
	this->playerProjectile.Update(deltaTime);
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


	for (int i = 0; i < this->enemies.size(); i++) {

		if (this->player.GetBV()->Intersect(this->enemies.at(i)->GetBV())) {
			int j = 0;
		}
	}

	this->pointLights.at(0).Position = XMFLOAT4(playerPos.x, 1.0f, playerPos.z, 1.0f);
	this->pointLights.at(2).Position = XMFLOAT4(enemyPos.x, 1.0f, enemyPos.z, 1.0f);

	return result;
}

int StageState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
    XMFLOAT3 pos;
    DirectX::XMMATRIX worldMatrix;

	//Render models

	//Player and weapon render
	gHandler->DeferredRender(this->player.GetModel(), &this->myCamera);
	gHandler->DeferredRender(this->player.GetWeapon()->GetModel(), &this->myCamera);

	//renders all the actors in the enemies vector
	for (int i = 0; i < this->enemies.size(); i++)
	{
		pos = this->enemies.at(i)->GetPosition();
		
		worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		this->m_car.SetWorldMatrix(worldMatrix);

		gHandler->DeferredRender(this->enemies.at(i)->GetModel(), &this->myCamera);

	}

	//render shots
	this->playerProjectile.Render(gHandler, &this->myCamera);

    this->enemyPjHandler.Render(gHandler, &this->myCamera);

	gHandler->DeferredRender(&this->m_ground, &this->myCamera);


	//renderPowerups
 	pos = this->spreadPower.GetPosition();

	pos.x += 15;
	pos.z += 15;

	worldMatrix = DirectX::XMMatrixTranslation(pos.x, 0.f, pos.z);
	this->spreadPower.GetModel()->SetWorldMatrix(worldMatrix);

	//render that shiet
	gHandler->DeferredRender(this->spreadPower.GetModel(), &this->myCamera);

	for (int i = 0; i < this->enemies.size(); i++)
	{
		gHandler->ShadowRender(this->enemies[i]->GetModel(), &this->myCamera);
	}

	gHandler->ShadowRender(this->player.GetModel(), &this->myCamera);
	gHandler->ShadowRender(this->player.GetWeapon()->GetModel(), &this->myCamera);

	gHandler->LightRender(this->myCamera.GetCameraPos(), this->pointLights);

	this->myParticleHandler.Render(gHandler, &this->myCamera);

	return result;
}

void StageState::ReadFile()
{
    string line;
    ifstream myFile("Stage Spawn Pattern.txt");

    if (myFile.is_open())
    {
        getline(myFile, line);
        while (line.at(0) != ' ')
        {
            Level waveTemp;
            //getline(myFile, line);
            string waveLenght = "";
            string enemyType = "";
            string nrOfEnemies = "";


            if (line.at(0) == 't')
            {
                size_t start = 1;
                size_t end = line.find("}");
                waveLenght = line.substr(start, end - 1);
            }
            std::stringstream ss(waveLenght);
            ss >> waveTemp.time;
            this->waves.push_back(waveTemp);

            getline(myFile, line);
            for (int i = 0; i < 4; i++)
            {
                Wave temp;
                if (line.at(1) == '}')
                {
                    enemyType = "";
                    nrOfEnemies = "00";
                }
                else if (line.at(0) == '{')
                {
                    size_t start = 1;
                    size_t end = line.find("*");
                    enemyType = line.substr(start, end - 1);

                    size_t start2 = end + 1;
                    size_t end2 = line.find("}");
                    nrOfEnemies = line.substr(start2, end2 - 1);
                }


                temp.type = enemyType;

                nrOfEnemies.pop_back();
                std::stringstream ss2(nrOfEnemies);
                ss2 >> temp.amount;
                getline(myFile, line);

                //this->wave.push_back(temp);
                this->waves.at(this->waves.size() - 1).toSpawn.push_back(temp);
            }

        }

    }
}

void StageState::SpawnWave()
{

}
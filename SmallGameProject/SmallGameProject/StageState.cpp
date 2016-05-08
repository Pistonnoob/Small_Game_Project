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

	for (int i = 0; i < this->levels.size(); i++)
	{
		for (int a = 0; a < this->levels.at(i).wave.size(); a++)
		{
			this->levels.at(i).wave.at(a).toSpawn.clear();
		}
		this->levels.at(i).wave.clear();
	}
	this->levels.clear();

	//Releas eyour m_AI
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
 		this->player.Initialize(device, deviceContext, "sphere1","projectile", true, &this->playerSubject);
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

		//Colour thy armies in the name of the racist overlord Axel!
		this->m_car.SetColor(DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f));
        this->m_ball.SetColor(DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f));

//>>>>>>> beforeMemLeak

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

		//DirectX::XMFLOAT3 a = this->player.GetPosition();
		int i = 0;


        ReadFile("Stage1.txt");

		this->currentLevel = 0;
		this->currentWave = 0;
		this->timeToNextWave = this->levels.at(currentLevel).wave.at(currentWave).time;

		//Arm thy armies!
        SpawnWave(this->currentLevel, this->currentWave);
	}


	return result;
}

int StageState::HandleInput(InputHandler * input)
{
	int result = 1;

	if (input->isKeyPressed(DIK_ESCAPE))
		this->exitStage = true;

	if (input->isKeyPressed(DIK_C))
	{
	    //how do I update this shiet
		Entity* ptr = &this->player;
		this->player.GetEntitySubject()->Notify(ptr, Events::PICKUP::POWERUP_PICKUP);
	}
	if (input->isKeyDown(DIK_W)) {
		this->player.MoveUp(0.01f);
	}
	if (input->isKeyDown(DIK_S)) {
		this->player.MoveDown(0.01f);
	}
	if (input->isKeyDown(DIK_D)) {
		this->player.MoveRight(0.01f);
	}
	if (input->isKeyDown(DIK_A)) {
		this->player.MoveLeft(0.01f);

	}
	if (input->isKeyDown(DIK_F))
	{
		this->player.Fire(0.0);
	}

	return result;
}

int StageState::Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler)
{
	int result = 1;

	float newDT = deltaTime / 1000000;
	
/*<<<<<<< HEAD
	this->playerProjectile.Update(deltaTime);
	this->player.Update(input, gHandler, &this->myCamera, deltaTime);

	XMFLOAT3 playerPos = this->player.GetPosition();
	//sends the enemies vector to the m_AI for updating cameraPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, playerPos);
	XMFLOAT3 enemyPos = this->enemies.at(0)->GetPosition();
=======*/
    HandleWaveSpawning(newDT);

    RemoveDeadEnemies();
 
	this->m_AI.updateActors(this->enemies, this->player.GetPosition(), newDT);
    this->enemyPjHandler.Update(newDT);

	this->playerProjectile.Update(newDT);
	this->player.Update(input, gHandler, &this->myCamera, newDT);

//>>>>>>> beforeMemLeak
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


	if (this->enemyPjHandler.IntersectionTest(&this->player)) {
		int j = 0;
		this->exitStage = true;
	}

	for (auto enemy : this->enemies) {

		if (this->player.GetBV()->Intersect(enemy->GetBV())) {
 			int j = 0;
		}
	}

	XMFLOAT3 playerPos = this->player.GetPosition();
	XMFLOAT3 enemyPos = this->enemies.at(0)->GetPosition();
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


void StageState::ReadFile(string fileName)
{
    string line;
    ifstream myFile(fileName);

    if (myFile.is_open())
    {
		int nrOfSpawnPoints = 0;
        getline(myFile, line);

		string xStr;
		string zStr;
		while(line.at(0) == 'p')
		{
			std::stringstream ss;
			DirectX::XMFLOAT3 point;
			point.y = 0;
			size_t start = 1;
			size_t end = line.find(",");
			xStr = line.substr(start, end - 1);
			ss << xStr;
			ss >> point.x;
			ss.clear();

			start = end + 1;
			end = line.find("}");
			zStr = line.substr(start, end - 1);
			zStr.pop_back();
			ss << zStr;
			ss >> point.z;
			ss.clear();

			nrOfSpawnPoints++;
			this->spawnPoints.push_back(point);
			getline(myFile, line);
		}
		while (line == "new Level")
		{
			getline(myFile, line);
			Level temp;
			this->levels.push_back(temp);
			while (line != "new Level" && line != "end")
			{
				Wave waveTemp;
				ToSpawn spawnTemp;
				string waveLenght = "";
				string enemyType = "";
				string nrOfEnemies = "";

				//get wave lenght
				size_t start = 1;
				size_t end = line.find("}");
				waveLenght = line.substr(start, end - 1);

				std::stringstream ss(waveLenght);
				ss >> waveTemp.time;
				ss.clear();

				getline(myFile, line);
				for (int i = 0; i < nrOfSpawnPoints; i++)
				{
                    spawnTemp.spawnIndex = 0;
					spawnTemp.type = Type::NONE;
					if (line.at(1) == '}')
					{
					}
					else if (line.at(0) == '{')
					{
                        for (int a = 1; a < line.size(); a++)
                        {
                            if (line.at(a) != ' ' && line.at(a) != '}')
                            {
                                string bossCheck = line.substr(a, a + 3);
                                if (bossCheck.at(bossCheck.size() - 1) == '}')
                                {
                                    bossCheck.pop_back();
                                }
                                if (bossCheck == "BOSS")
                                {
                                    spawnTemp.spawnIndex = i;
                                    spawnTemp.type = ConvertToEnemyType(bossCheck);
                                    waveTemp.toSpawn.push_back(spawnTemp);
                                    a += 3;
                                }
                                else
                                {
                                    spawnTemp.spawnIndex = i;
                                    enemyType = line.at(a);
                                    spawnTemp.type = ConvertToEnemyType(enemyType);
                                    waveTemp.toSpawn.push_back(spawnTemp);
                                }

                            }
                        }
					}


					getline(myFile, line);
				}
				this->levels.at(this->levels.size() - 1).wave.push_back(waveTemp);
			}

		}


    }
}

void StageState::HandleWaveSpawning(float deltaTime)
{
    this->timeToNextWave -= deltaTime;
    if (this->timeToNextWave <= 0)
    {
        if (this->currentLevel < this->levels.size())
        {
            this->currentWave++;
            if (this->currentWave >= this->levels.at(this->currentLevel).wave.size())
            {
                this->currentWave = 0;
                this->currentLevel++;
            }
            if (this->currentLevel < this->levels.size())
            {
                this->timeToNextWave = this->levels.at(this->currentLevel).wave.at(this->currentWave).time;
                SpawnWave(this->currentLevel, this->currentWave);
            }
        }
    }
}


void StageState::SpawnWave(int levelIndex, int waveIndex)
{
	//level
	// |->wave
	//      |->time
	//      |->toSpawn
	//           |->type
	//			 |->amnount

    int size = this->levels.at(levelIndex).wave.at(waveIndex).toSpawn.size();
    for (int i = 0; i < size; i++)
    {
        Type type = this->levels.at(levelIndex).wave.at(waveIndex).toSpawn.at(i).type;
        int point = this->levels.at(levelIndex).wave.at(waveIndex).toSpawn.at(i).spawnIndex;
        SpawnEnemy(type, point);
    }
}
void StageState::SpawnEnemy(Type type, int pointIndex)
{
	int x = this->spawnPoints.at(pointIndex).x;
	int z = this->spawnPoints.at(pointIndex).z;
	switch (type)
	{
	case(Type::BOMBER) :
		this->enemies.push_back(new BomberEnemy(x, z));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &this->enemySubject, true);
		break;
	case(Type::RANGED) :
		this->enemies.push_back(new RangedEnemy(x, z));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &this->enemySubject, true);
		break;
	case(Type::MELEEE) :
		this->enemies.push_back(new MeleeEnemy(x, z));
		this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &this->enemySubject, true);
		break;
	case(Type::BOSS) :
		Boss* boss = new Boss(x, z);
		boss->Initialize(&this->m_car, &this->enemySubject, true, 1);
		this->enemies.push_back(boss);
		break;
	}
}
void StageState::RemoveDeadEnemies()
{
    for (int i = 0; i < this->enemies.size(); i++)
    {
        if (!this->enemies.at(i)->GetIsAlive())
        {
            this->enemies.at(i)->Shutdown();
            delete this->enemies.at(i);
            this->enemies.erase(this->enemies.begin() + i);
            i--;

        }
    }
}
Type StageState::ConvertToEnemyType(string type)
{
	if (type == "B")
	{
		return Type::BOMBER;
	}
	else if (type == "R")
	{
		return Type::RANGED;
	}
	else if (type == "M")
	{
		return Type::MELEEE;
	}
	else if(type == "BOSS")
	{
		return Type::BOSS;
	}
	else
	{
		return Type::NONE;
	}
}

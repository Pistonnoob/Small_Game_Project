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

	this->enemySubject = EntitySubject();
    this->enemyPjHandler = ProjectileHandler();
	this->enemySubject.addObserver(&this->enemyPjHandler);
	

	this->playerSubject = new EntitySubject();
	this->playerPjHandler = ProjectileHandler();
	this->playerSubject->addObserver(&this->playerPjHandler);
	
	this->hero = new Player();

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

	this->playerPjHandler.ShutDown();
	this->playerSubject->ShutDown();
	delete this->playerSubject;
	this->playerSubject = nullptr;
	
	this->hero->Shutdown();
	delete this->hero;
	this->hero = nullptr;

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

		//the hero will rise
 		this->hero->Initialize(device, deviceContext, "sphere1","ogreFullG", false, this->playerSubject);
		this->playerPjHandler.Initialize(device, deviceContext);

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
        for (int i = 0; i < this->enemies.size(); i++)
        {
            this->enemies.at(i)->setIsAlive(false);
        }
	}

	return result;
}

int StageState::Update(float deltaTime)
{
	int result = 1;
	float newDT = deltaTime / 1000000;
	
    HandleWaveSpawning(newDT);

    RemoveDeadEnemies();
 
	this->m_AI.updateActors(this->enemies, DirectX::XMFLOAT3(0,0,0), newDT);

    this->enemyPjHandler.update(newDT);

	this->playerPjHandler.update(newDT);

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

	//calculate player position and mathemagics
	pos = this->hero->getPosition();
	worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	this->m_car.SetWorldMatrix(worldMatrix);

	//render
	gHandler->DeferredRender(this->hero->getModel(), &this->myCamera);

	//calculate THE PLAYER WEAPON position and mathemagics
	pos.x += 15;
	pos.z += 15;
	worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	this->m_car.SetWorldMatrix(worldMatrix);

	//render PLAYER WEAPON
	gHandler->DeferredRender(this->hero->getPlayerWeapon()->GetModel(), &this->myCamera);
	
	//render shots
	playerPjHandler.render(gHandler, &this->myCamera);

    this->enemyPjHandler.render(gHandler, &this->myCamera);

	gHandler->DeferredRender(&this->m_ground, &this->myCamera);

	//shadowMap
	gHandler->SetShadowRTV();
	for (int i = 0; i < this->enemies.size(); i++)
	{
		gHandler->ShadowRender(this->enemies[i]->getModel(), &this->myCamera);
	}

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
        if (!this->enemies.at(i)->getIsAlive())
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
	else
	{
		return Type::BOSS;
	}
}

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
		temp2->Initialize(3.14f, 3, 100, 50, 1, 50, 5, 3.14f / 2);
		this->ability2 = temp2;

		ReverseFire* temp3 = new ReverseFire();
		temp3->Initialize(3.14f / 2, 15, 100, 50, 1, 50);
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

        readFile("Stage1.txt");
        spawnWave(0);
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
		//this->ability1->activate(this->enemies.at(0), &this->enemySubject, DirectX::XMFLOAT3(0, 0, 0));
		this->hero->fire(); //how do I update this shiet
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
 
	//sends the enemies vector to the m_AI for updating playerPos is the temporary pos that the enemies will go to
	this->m_AI.updateActors(this->enemies, DirectX::XMFLOAT3(0,0,0));
    this->enemyPjHandler.update(deltaTime);

	this->playerPjHandler.update(deltaTime);

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

void StageState::readFile(string fileName)
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
					spawnTemp.amount = 0;
					spawnTemp.type = Type::NONE;
					if (line.at(1) == '}')
					{
					}
					else if (line.at(0) == '{')
					{
						//get enemy type
						size_t start = 1;
						size_t end = line.find("*");
						enemyType = line.substr(start, end - 1);
						spawnTemp.type = convertToEnemyType(enemyType);

						//get nr of enemies to spawn
						size_t start2 = end + 1;
						size_t end2 = line.find("}");
						nrOfEnemies = line.substr(start2, end2 - 1);
						nrOfEnemies.pop_back();
						std::stringstream ss2(nrOfEnemies);
						ss2 >> spawnTemp.amount;

					}
					waveTemp.toSpawn.push_back(spawnTemp);


					getline(myFile, line);
				}
				this->levels.at(this->levels.size() - 1).wave.push_back(waveTemp);
			}

		}


    }
}

void StageState::spawnWave(int index)
{
	//level
	// |->wave
	//      |->time
	//      |->toSpawn
	//           |->type
	//			 |->amnount
	for (int i = 0; i < this->spawnPoints.size(); i++)
	{
		Type type = this->levels.at(0).wave.at(index).toSpawn.at(i).type;
		int amount = this->levels.at(0).wave.at(index).toSpawn.at(i).amount;
		for (int t = 0; t < amount; t++)
		{
			spawnEnemy(type, i);
		}

	}
}
void StageState::spawnEnemy(Type type, int pointIndex)
{
	//this->enemies.push_back(new RangedEnemy(0.0f, 20.0f));
	//this->enemies.at(this->enemies.size() - 1)->Initialize(&this->m_car, &enemySubject, true);
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

		break;
	}
}
Type StageState::convertToEnemyType(string type)
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

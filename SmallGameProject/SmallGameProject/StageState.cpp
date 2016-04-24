#include "StageState.h"



StageState::StageState()
{
	this->m_model = Model();
	this->myCamera = CameraHandler();

	this->testModel = nullptr;
	this->AI = nullptr;
}


StageState::~StageState()
{
}

void StageState::Shutdown()
{
	//Release the models
	if (this->testModel) {
		this->testModel->Shutdown();
		delete this->testModel;
		this->testModel = nullptr;
	}
	if (this->testModelGround) {
		this->testModelGround->Shutdown();
		delete this->testModelGround;
		this->testModelGround = nullptr;
	}

	//Release the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* enemyTemp = this->enemies.at(i);
		delete enemyTemp;
	}
	this->enemies.clear();
	//Release your AI
	if (this->AI != nullptr)
	{
		delete this->AI;
	}

	GameState::Shutdown();
	this->m_model.Shutdown();
}

int StageState::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, GameStateHandler * GSH)
{
	int result = 0;

	//Arm thy father
	result = this->InitializeBase(GSH, device, deviceContext);
	if (result)
	{
		//Open thy eyes!
		this->myCamera.SetCameraPos(DirectX::XMFLOAT3(0, 0, -20));
		bool cameraResult = this->myCamera.Initialize();
		if (cameraResult)
			result = 1;


		//Army thy mind with the knowledge that will lead thy armies to battle!
		this->AI = new Ai();


		//Form thy armies from the clay!
		this->testModel = new Model;
		result = this->testModel->Initialize(device, this->m_deviceContext, "carSLS3");
		if (!result) {
			return false;
		}
		//Colour thy armies in the name of the racist overlord Axel!
		this->testModel->SetColor(DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f));

		//Arm thy armies!
		//creates the enemies must call setModel function to give enemies models
		this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->setModel(this->testModel);

		this->enemies.push_back(new BomberEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->setModel(this->testModel);

		this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->setModel(this->testModel);

		this->enemies.push_back(new RangedEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->setModel(this->testModel);

		this->enemies.push_back(new MeleeEnemy(0.0f, 0.0f));
		this->enemies.at(this->enemies.size() - 1)->setModel(this->testModel);
		

		//Place the ground beneeth your feet and thank the gods for their
		//sanctuary from the oblivion below!
		this->testModelGround = new Model;

		result = this->testModelGround->Initialize(device, deviceContext, "ground");
		if (!result) {
			return false;
		}
		this->testModelGround->SetColor(DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f));

		DirectX::XMMATRIX worldMatrix;
		worldMatrix = DirectX::XMMatrixTranslation(0.0f, -5.0f, 0.0f);
		this->testModelGround->SetWorldMatrix(worldMatrix);


	}


	return result;
}

int StageState::HandleInput(InputHandler * input)
{
	int result = 0;
	return result;
}

int StageState::Update(float deltaTime)
{
	int result = 0;

	//sends the enemies vector to the AI for updating cameraPos is the temporary pos that the enemies will go to
	this->AI->updateActors(this->enemies, DirectX::XMFLOAT3(0, 0, -20));



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
		this->testModel->SetWorldMatrix(worldMatrix);

		gHandler->DeferredRender(this->enemies.at(i)->getModel(), &this->myCamera);
	}
	//this->graphicH->DeferredRender(this->testModel, this->cameraH);
	gHandler->DeferredRender(this->testModelGround, &this->myCamera);


	return result;
}

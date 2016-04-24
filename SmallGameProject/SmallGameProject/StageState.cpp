#include "StageState.h"



StageState::StageState()
{
	this->m_model = Model();
	this->myCamera = CameraHandler();

	this->testModel = nullptr;
	this->entity = nullptr;
	this->AI = nullptr;
}


StageState::~StageState()
{
	GameState::Shutdown();
	this->m_model.Shutdown();
}

void StageState::Shutdown()
{
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


		this->testModel = new Model;

		result = this->testModel->Initialize(device, this->m_deviceContext, "carSLS3");
		if (!result) {
			return false;
		}
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
		//

		this->testModelGround = new Model;

		result = this->testModelGround->Initialize(this->graphicH->GetDevice(), this->graphicH->GetDeviceContext(), "ground");
		if (!result) {
			return false;
		}
		this->testModelGround->SetColor(DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f));


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
	return result;
}

int StageState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;
	return result;
}

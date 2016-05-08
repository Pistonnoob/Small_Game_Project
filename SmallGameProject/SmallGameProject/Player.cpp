#include "Player.h"

Player::Player() : Actor()
{
	this->posX = 20.f;
	this->posZ = 20.f;
	this->playerHealth = 100;
	this->playerMovmentSpeed = 10;
	this->playerDamage = 1;
	this->playerHighScore = 0;
	
	//Initiliaze the forward vecktor as 0,0,1
	this->forwardDir = DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(0, 0, 1));
	this->playerWeapon = nullptr;
}

Player::~Player()
{

}

bool Player::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string playerModelFilename,
	std::string weaponModelFile, bool isSphere, EntitySubject* entitySub)
{
	if (!Entity::Initialize(device, deviceContext, playerModelFilename, isSphere, entitySub)) {
		return false;
	}
	this->playerWeapon = new Weapon();
	if (!this->playerWeapon->Initialize(device, deviceContext, weaponModelFile)) {
		return false;
	}


	PowerUp spread = PowerUp();
	PowerUp penetration = PowerUp();
	PowerUp weave = PowerUp();


	this->powerups.push_back(spread);
	this->powerups.push_back(penetration);
	this->powerups.push_back(weave);

	//Rotation matrix
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationY(0);

	//Set the weapon pos to the Player
	//Set the world matrix to a defualt state
	DirectX::XMMATRIX playerWorldMatrix;
	this->entityModel->GetWorldMatrix(playerWorldMatrix);
	
		
	//Initial offset
	DirectX::XMMATRIX offset = DirectX::XMMatrixTranslation(this->posX, 0, this->posZ);
	//create the new world matrix
	playerWorldMatrix = playerWorldMatrix * offset;

	//Set the model matrix
	this->entityModel->SetWorldMatrix(playerWorldMatrix);

	//weapon matrix
	DirectX::XMMATRIX weaponWorldMatrix = playerWorldMatrix;
	offset = DirectX::XMMatrixTranslation(5, 4, 0);
	weaponWorldMatrix = weaponWorldMatrix * offset;

	//give the player model its new 
	this->playerWeapon->GetModel()->SetWorldMatrix(weaponWorldMatrix);

	return true;
}

void Player::Shutdown()
{
	if (this->playerWeapon) {
		this->playerWeapon->ShutDown();
		delete this->playerWeapon;
		this->playerWeapon = nullptr;
	}
	for (int i = 0; i < this->powerups.size(); i++)
	{
		this->powerups.at(i).Shutdown();
	} 
	Entity::Shutdown(false);
}

Weapon * Player::GetPlayerWeapon()
{
	return this->playerWeapon;
}

void Player::PowerPickup(const int & POWER_ENUM)
{
}

void Player::SetPowerUp(Modifiers::POWERUPS powerUp)
{
	this->powerups.at(powerUp).setTimePowerup(10);
}

void Player::HandleInput(InputHandler * input)
{
	if (input->isKeyDown(DIK_W)) {
		this->MoveUp(0.00001f);
	}
	if (input->isKeyDown(DIK_S)) {
		this->MoveDown(0.00001f);
	}
	if (input->isKeyDown(DIK_D)) {
		this->MoveRight(0.00001f);
	}
	if (input->isKeyDown(DIK_A)) {
		this->MoveLeft(0.00001f);
	}

}

void Player::Update(InputHandler* input, GraphicHandler* gHandler, CameraHandler* cameraH, float deltaTime)
{

	this->HandleInput(input);

	DirectX::XMMATRIX playerWorldMatrix;
	this->entityModel->GetWorldMatrix(playerWorldMatrix);

	//Initial offset
	DirectX::XMMATRIX offset = DirectX::XMMatrixTranslation(this->posX, 0, this->posZ);
	//create the new world matrix
	playerWorldMatrix = offset;

	//Set the model matrix
	this->entityModel->SetWorldMatrix(playerWorldMatrix);

	this->RotatePlayerTowardsMouse(input->getMousePos(), gHandler, cameraH);

	//Update the bounding box pos and rotation
	this->entityModel->GetWorldMatrix(playerWorldMatrix);
	this->entityBV->UpdateBoundingVolume(playerWorldMatrix);

	//weapon matrix
	this->entityModel->GetWorldMatrix(playerWorldMatrix);
	DirectX::XMMATRIX weaponWorldMatrix = playerWorldMatrix;
	offset = DirectX::XMMatrixTranslation(5, 4, 0);
	weaponWorldMatrix = offset * weaponWorldMatrix;

	this->playerWeapon->GetModel()->SetWorldMatrix(weaponWorldMatrix);

	//update powerups
	for (auto Powerups = this->powerups.begin(); Powerups != this->powerups.end(); Powerups++)
	{
		(Powerups)->Update(deltaTime);
	}	
}

Weapon * Player::GetWeapon()
{
	return this->playerWeapon;
}


void Player::MoveRight(float deltaTime)
{
	if (this->posX < 42.0f) {
		this->posX += (0.05f * this->playerMovmentSpeed);
	}
}


void Player::MoveLeft(float deltaTime)
{
	if (this->posX > -42.0f) {
		this->posX -= (0.05f * this->playerMovmentSpeed);
	}
}


void Player::MoveUp(float deltaTime)
{
	if (this->posZ < 42.0f) {
		this->posZ += (0.05f * this->playerMovmentSpeed);
	}
}


void Player::MoveDown(float deltaTime)
{
	if (this->posZ > -42.0f) {
		this->posZ -= (0.05f * this->playerMovmentSpeed);
	}
}

void Player::Move(DirectX::XMFLOAT3 moveVec)
{
	this->posX += moveVec.x;
	this->posZ += moveVec.z;
}

void Player::Fire(float deltaT)
{
	/*
	this->SetAimDir(DirectX::XMFLOAT3(0, 0, 1));

	if (this->powerups.at(0).Update(deltaT) == true)
	{
		playerWeapon->ShootWeapon(this);
	}
	*/

	PowerUp* powerUpPtr = nullptr;
	int size = this->powerups.size();

	DirectX::XMStoreFloat3(&this->aimDir, this->forwardDir);
	this->aimDir.y = 0.0f;

	for (int i = 0; i < size; i++)
	{
		powerUpPtr = &this->powerups.at(i);
		if (powerUpPtr->getTimeLeft() > 0.0f)
		{
			playerWeapon->ShootWeapon(this);
		}
	}
}

void Player::Fire()
{
	/*
	PowerUp* powerUpPtr = nullptr;
	int size = this->powerups.size();
	
	DirectX::XMStoreFloat3(&this->aimDir,this->forwardDir);
	
	for (int i = 0; i < size; i++)
	{
		powerUpPtr = &this->powerups.at(i);
		if (powerUpPtr->getTimeLeft() > 0.0f)
		{
			playerWeapon->ShootWeapon(this);
		}
	}
	*/
}

void Player::RotatePlayerTowardsMouse(DirectX::XMFLOAT2 mousePos, GraphicHandler* gHandler, CameraHandler* cameraH)
{
	// The angle is calculated in Normal Device Space

	DirectX::XMVECTOR playerPos = XMVectorSet(this->posX, 0, this->posZ, 1);
	DirectX::XMMATRIX modelWorld;
	DirectX::XMMATRIX cameraView;
	DirectX::XMMATRIX projection;
	int screenWidth = gHandler->GetScreenWidth();
	int screenHeight = gHandler->GetScreenHeight();

	this->entityModel->GetWorldMatrix(modelWorld);
	cameraH->GetViewMatrix(cameraView);
	projection = gHandler->GetPerspectiveMatrix();
	
	//DirectX::XMMATRIX clipMatrix = modelWorld * cameraView * projection;

	//playerPos = DirectX::XMVector3TransformCoord(playerPos, modelWorld);
	playerPos = DirectX::XMVector4Transform(playerPos, cameraView);
	playerPos = DirectX::XMVector4Transform(playerPos, projection);

	//Move player pos to a float4 to be able to devide each value with w
	XMFLOAT4 v;
	XMStoreFloat4(&v, playerPos);

	v.x = v.x / v.w;
	v.y = v.y / v.w;
	v.z = v.z / v.w;

	// Re-save it
	playerPos = XMLoadFloat4(&v);

	DirectX::XMFLOAT4X4 tempProj;
	DirectX::XMStoreFloat4x4(&tempProj, projection);

	//Move the cords to the window
	float mouseX = mousePos.x - (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
	float mouseY = mousePos.y - (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

	// Get the mouse pos in -1, 1
	mouseX = (((2 * mouseX) / screenWidth) - 1);
	mouseY = (((-2 * mouseY) / screenHeight) + 1);

	//Move the pos to a vector
	DirectX::XMVECTOR mousePosV = DirectX::XMVectorSet( mouseX, mouseY , 1, 1);
	
	//Direction vector
	XMVECTOR dirVec = XMVector2Normalize(mousePosV - playerPos);
	this->forwardDir = dirVec;
	float angle = atan2(XMVectorGetY(dirVec), XMVectorGetX(dirVec));

	//Create the rotation matrix
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationY(-angle);

	//Apply rotation
	DirectX::XMMATRIX weaponModelMatrix;
	DirectX::XMMATRIX playermodelMatrix;
	this->playerWeapon->GetModel()->GetWorldMatrix(weaponModelMatrix);
	this->entityModel->GetWorldMatrix(playermodelMatrix);

	//this->playerWeapon->GetModel()->SetWorldMatrix(rotationMatrix * weaponModelMatrix);
	this->entityModel->SetWorldMatrix(rotationMatrix * playermodelMatrix);

}

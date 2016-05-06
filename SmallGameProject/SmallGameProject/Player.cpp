#include "Player.h"

Player::Player() : Actor()
{
	this->posX = 0.f;
	this->posZ = 0.f;
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
	std::string weaponModelFilename, bool isSphere)
{
	if (!Entity::Initialize(device, deviceContext, playerModelFilename, isSphere)) {
		return false;
	}

	this->playerWeapon = new Weapon();
	if (!this->playerWeapon->Initialize(device, deviceContext, weaponModelFilename)) {
		return false;
	}

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
	Entity::Shutdown();

	if (this->playerWeapon) {
		this->playerWeapon->ShutDown();
		delete this->playerWeapon;
		this->playerWeapon = nullptr;
	}
}

void Player::Update(InputHandler* input, GraphicHandler* gHandler, CameraHandler* cameraH)
{
	DirectX::XMMATRIX playerWorldMatrix;
	this->entityModel->GetWorldMatrix(playerWorldMatrix);

	//Initial offset
	DirectX::XMMATRIX offset = DirectX::XMMatrixTranslation(this->posX, 0, this->posZ);
	//create the new world matrix
	playerWorldMatrix = offset;

	//Set the model matrix
	this->entityModel->SetWorldMatrix(playerWorldMatrix);


	//give the player model its new 
	

	this->rotatePlayerTowardsMouse(input->getMousePos(), gHandler, cameraH);

	//weapon matrix
	this->entityModel->GetWorldMatrix(playerWorldMatrix);
	DirectX::XMMATRIX weaponWorldMatrix = playerWorldMatrix;
	offset = DirectX::XMMatrixTranslation(5, 4, 0);
	weaponWorldMatrix = offset * weaponWorldMatrix;

	this->playerWeapon->GetModel()->SetWorldMatrix(weaponWorldMatrix);
}

Weapon * Player::GetWeapon()
{
	return this->playerWeapon;
}

void Player::moveRight()
{
	this->posX += (0.05f * this->playerMovmentSpeed);
}

void Player::moveLeft()
{
	this->posX -= (0.05f * this->playerMovmentSpeed);
}

void Player::moveUp()
{
	this->posZ += (0.05f * this->playerMovmentSpeed);
}

void Player::moveDown()
{
	this->posZ -= (0.05f * this->playerMovmentSpeed);
}

void Player::move(DirectX::XMFLOAT3 moveVec)
{
	this->posX += moveVec.x;
	this->posZ += moveVec.z;
}

void Player::rotatePlayerTowardsMouse(DirectX::XMFLOAT2 mousePos, GraphicHandler* gHandler, CameraHandler* cameraH)
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

#include "Player.h"

Player::Player() : Actor()
{
	this->posX = 10;
	this->posZ = 10;
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

	//weapon matrix
	DirectX::XMMATRIX weaponWorldMatrix = playerWorldMatrix;
	offset = DirectX::XMMatrixTranslation(5, 4, 0);
	weaponWorldMatrix = weaponWorldMatrix * offset;

	//give the player model its new 

	this->playerWeapon->GetModel()->SetWorldMatrix(weaponWorldMatrix);
	this->rotatePlayerTowardsMouse(input->getMousePos(), gHandler, cameraH);
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


	XMFLOAT4 v;
	XMStoreFloat4(&v, playerPos);

	v.x = v.x / v.w;
	v.y = v.y / v.w;
	v.z = v.z / v.w;
	v.w = 1;

	playerPos = XMLoadFloat4(&v);
	DirectX::XMVECTOR mousePosV = DirectX::XMVectorSet(((2 * mousePos.x) / screenWidth) - 1, ((-2 * mousePos.y) / screenHeight) + 1, 1, 1);
	
	if (DirectX::XMVectorGetX(mousePosV) < 0 && DirectX::XMVectorGetY(mousePosV) < 0) {
		float i = DirectX::XMVectorGetX(mousePosV);
		float j = DirectX::XMVectorGetY(mousePosV);
		int tk = 0;
	}



	DirectX::XMVECTOR dot = DirectX::XMVector2Dot(playerPos, mousePosV);

	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationY(DirectX::XMVectorGetX(dot) * 52);

	DirectX::XMMATRIX modelMatrix;
	this->playerWeapon->GetModel()->GetWorldMatrix(modelMatrix);
	this->playerWeapon->GetModel()->SetWorldMatrix(rotationMatrix * modelMatrix);

}

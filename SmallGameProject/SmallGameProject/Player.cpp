#include "Player.h"

Player::Player() : Actor()
{
	this->posX = 0.f;
	this->posZ = 0.f;
	this->playerMovmentSpeed = 100;
	this->shootCounter = 0;
	this->health = 100;	
	this->damage = 100;

	//Initiliaze the forward vecktor as 0,0,1
	this->forwardDir = DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(0, 0, 1));
	this->playerWeapon = nullptr;

	this->uiHandler = UIHandler();
}

Player::~Player()
{

}

bool Player::Initialize(GraphicHandler* graphicsH, std::string playerModelFilename,
	std::string weaponModelFile, bool isSphere, EntitySubject* entitySub)
{
	ID3D11Device* device = graphicsH->GetDevice();
	ID3D11DeviceContext* deviceContext = graphicsH->GetDeviceContext();

	if (!Entity::Initialize(device, deviceContext, playerModelFilename, isSphere, entitySub)) {
		return false;
	}
	this->entitySubject->Notify(this, Events::ENTITY::PLAYER_CREATED);
	//this->playerWeapon = new Weapon();
	//if (!this->playerWeapon->Initialize(device, deviceContext, weaponModelFile)) {
	//	return false;
	//}
	this->playerWeapon = GameData::GetInstance()->GetWeapon();

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

	this->uiHandler.Initialize(graphicsH);
	this->uiHandler.CreateTextHolder(32);
	this->uiHandler.CreateTextHolder(32);
	this->uiHandler.CreateTextHolder(32);
	this->uiHandler.CreateTextHolder(32);
	this->uiHandler.CreateTextHolder(32);
	this->uiHandler.CreateTextHolder(32);

	return true;
}

void Player::Shutdown()
{
	//if (this->playerWeapon) {
		//this->playerWeapon->ShutDown();
		//delete this->playerWeapon;
		//this->playerWeapon = nullptr;
	//}

	this->uiHandler.Shutdown();

	Entity::Shutdown(false);
}

Weapon * Player::GetPlayerWeapon()
{
	return this->playerWeapon;
}

void Player::PowerPickup(const int & POWER_ENUM)
{
}

void Player::HandleInput(InputHandler * input, float dTime)
{
	this->shootCounter -= (dTime / 1000000);
	if (input->isKeyPressed(DIK_1))
	{
		this->entitySubject->Notify(this, Events::ENTITY::BOMBER_DEAD);
	}
	if (input->isKeyPressed(DIK_2))
	{
		this->entitySubject->Notify(this, Events::ENTITY::PLAYER_HIT);
	}
	if (input->isKeyPressed(DIK_3))
	{
		this->entitySubject->Notify(this, Events::ENTITY::RANGED_CREATED);
	}
	if (input->isKeyPressed(DIK_4))
	{
		this->entitySubject->Notify(this, Events::ENTITY::RANGED_DEAD);
	}
	if (input->isKeyDown(DIK_W)) {
		this->MoveUp(dTime);
	}
	if (input->isKeyDown(DIK_S)) {
		this->MoveDown(dTime);
	}
	if (input->isKeyDown(DIK_D)) {
		this->MoveRight(dTime);
	}
	if (input->isKeyDown(DIK_A)) {
		this->MoveLeft(dTime);
	}

	if (input->isKeyPressed(DIK_C))
	{
		//how do I update this shiet
		//this->entitySubject->Notify(this, Events::PICKUP::POWERUP_PICKUP);
	}

	if (input->isMouseKeyDown(0) && this->shootCounter <= 0)//0 = left, 1 = right, 2 = scroll click, 3 = "Down button" on mouse
	{
		this->shootCounter = SHOOT_DELAY;
		this->Fire(0.0);
	}

}

void Player::Update(InputHandler* input, GraphicHandler* gHandler, CameraHandler* cameraH, float deltaTime)
{

	this->HandleInput(input, deltaTime);

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

	DirectX::XMMATRIX weaponRot = DirectX::XMMatrixRotationY(1.5) * weaponWorldMatrix;
	weaponWorldMatrix = DirectX::XMMatrixScaling(0.75f, 0.75f, 0.75f) * weaponRot;

	offset = DirectX::XMMatrixTranslation(2.5f, 1.0f, 0.0f);
	weaponWorldMatrix = offset * weaponWorldMatrix;

	this->playerWeapon->GetModel()->SetWorldMatrix(weaponWorldMatrix);

	std::string text = "Damage: " + std::to_string(this->GetDamage());
	this->uiHandler.UpdateTextHolder(0, text, 150, 20, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);
	text = "Health: " + std::to_string((this->health + GameData::GetInstance()->GetPlayerHealth()) - this->damageTaken);
	this->uiHandler.UpdateTextHolder(1, text, 270, 20, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);
	text = "Speed: " + std::to_string((this->playerMovmentSpeed + GameData::GetInstance()->GetPlayerMoveSpeed()) * GameData::GetInstance()->GetWeaponMovementSpeed());
	this->uiHandler.UpdateTextHolder(2, text, 390, 20, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);
	if (GameData::GetInstance()->getPowerup()) {
		text = "PowerUp Timer: " + std::to_string(int(GameData::GetInstance()->getPowerup()->GetTimeLeft()));
	}
	else {
		text = "";
	}
	this->uiHandler.UpdateTextHolder(3, text, 510, 20, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);


	GameData::Update(deltaTime);
}

Weapon * Player::GetWeapon()
{
	return this->playerWeapon;
}

void Player::setWeapon(Weapon* weap)
{
	this->playerWeapon = weap;
}


void Player::MoveRight(float deltaTime)
{
	if (this->posX < 42.0f) {
		this->posX += (0.0000005f * deltaTime * (this->playerMovmentSpeed + GameData::GetInstance()->GetPlayerMoveSpeed()));
	}
}


void Player::MoveLeft(float deltaTime)
{
	if (this->posX > -42.0f) {
		this->posX -= (0.0000005f * deltaTime * (this->playerMovmentSpeed + GameData::GetInstance()->GetPlayerMoveSpeed()));
	}
}


void Player::MoveUp(float deltaTime)
{
	if (this->posZ < 42.0f) {
		this->posZ += (0.0000005f * deltaTime * (this->playerMovmentSpeed + GameData::GetInstance()->GetPlayerMoveSpeed()));
	}
}


void Player::MoveDown(float deltaTime)
{
	if (this->posZ > -42.0f) {
		this->posZ -= (0.0000005f * deltaTime  * (this->playerMovmentSpeed + GameData::GetInstance()->GetPlayerMoveSpeed()));
	}
}

void Player::Move(DirectX::XMFLOAT3 moveVec)
{
	this->posX += moveVec.x;
	this->posZ += moveVec.z;
}

void Player::Fire(float deltaT)
{
	DirectX::XMStoreFloat3(&this->aimDir, this->forwardDir);

	this->aimDir.x = DirectX::XMVectorGetX(this->forwardDir);
	this->aimDir.z = DirectX::XMVectorGetZ(this->forwardDir);
	this->aimDir.y = 0.0f;

	PowerUp* activePows = GameData::getPowerup();
	if (activePows)
	{
		this->playerWeapon->ShootWeapon(this, activePows->GetType());
	}
	
	else
	{
		this->playerWeapon->ShootWeapon(this);
	}
	
}

void Player::RotatePlayerTowardsMouse(DirectX::XMFLOAT2 mousePos, GraphicHandler* gHandler, CameraHandler* cameraH)
{
	// The angle is calculated in Normal Device Space

	DirectX::XMVECTOR playerPos = DirectX::XMVectorSet(this->posX, 0.0f, this->posZ, 1);
	DirectX::XMVECTOR dirVec;
	DirectX::XMMATRIX cameraView;
	DirectX::XMMATRIX cameraViewInverse;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX projectionInverse;
	DirectX::XMFLOAT4X4 projectionFloat;
	int screenWidth = gHandler->GetScreenWidth();
	int screenHeight = gHandler->GetScreenHeight();

	cameraH->GetViewMatrix(cameraView);
	cameraViewInverse = DirectX::XMMatrixInverse(NULL, cameraView);
	projection = gHandler->GetPerspectiveMatrix();
	projectionInverse = DirectX::XMMatrixInverse(NULL, projection);
	DirectX::XMStoreFloat4x4(&projectionFloat, projection);
	

	//Move the cords to the window
	float mouseX = mousePos.x - (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
	float mouseY = mousePos.y - (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

	// Get the mouse pos in -1, 1
	mouseX = (((2 * mouseX) / screenWidth) - 1);
	mouseY = ((-(2 * mouseY) / screenHeight) + 1);

	mouseX /= projectionFloat._11;
	mouseY /= projectionFloat._22;

	DirectX::XMFLOAT4 cameraPos = cameraH->GetCameraPos();

	DirectX::XMVECTOR rayO = DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f));
	DirectX::XMVECTOR rayD = DirectX::XMLoadFloat3(&DirectX::XMFLOAT3(mouseX, mouseY, 1.0f));

	rayO = DirectX::XMVector3TransformCoord(rayO, cameraViewInverse);
	rayD = DirectX::XMVector3TransformNormal(rayD, cameraViewInverse);

	float t = 0.0f;
	XMVECTOR planeNormal = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR dDot = DirectX::XMVector3Dot(planeNormal, playerPos);
	float d = DirectX::XMVectorGetX(dDot);
	float topRight = (DirectX::XMVectorGetX(planeNormal) * DirectX::XMVectorGetX(rayO) + DirectX::XMVectorGetY(planeNormal) * DirectX::XMVectorGetY(rayO) + DirectX::XMVectorGetZ(planeNormal) * DirectX::XMVectorGetZ(rayO));
	float altTopRight = DirectX::XMVectorGetX(DirectX::XMVector3Dot(planeNormal, rayO));
	float bottom = (DirectX::XMVectorGetX(planeNormal) * DirectX::XMVectorGetX(rayD) + DirectX::XMVectorGetY(planeNormal) * DirectX::XMVectorGetY(rayD) + DirectX::XMVectorGetZ(planeNormal) * DirectX::XMVectorGetZ(rayD));
	float altBottom = DirectX::XMVectorGetX(DirectX::XMVector3Dot(planeNormal, rayD));
	t = (-d -altTopRight)/altBottom;

	DirectX::XMVECTOR intersectionPoint = rayO + rayD * t;
	DirectX::XMVECTOR playerToInter = intersectionPoint - playerPos;
	dirVec = DirectX::XMVector3Normalize(playerToInter);

	//Calculate the float angle between intersectionPoint and player pos
	float angle = 0.0f;
	angle = atan2(DirectX::XMVectorGetZ(playerToInter), DirectX::XMVectorGetX(playerToInter));
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationY(-angle);


	this->forwardDir = dirVec;

	
	//Apply rotation
	DirectX::XMMATRIX weaponModelMatrix;
	DirectX::XMMATRIX playermodelMatrix;
	this->playerWeapon->GetModel()->GetWorldMatrix(weaponModelMatrix);
	this->entityModel->GetWorldMatrix(playermodelMatrix);

	this->playerWeapon->GetModel()->SetWorldMatrix(rotationMatrix * weaponModelMatrix);
	this->entityModel->SetWorldMatrix(rotationMatrix * playermodelMatrix);

}

unsigned int Player::GetDamage()
{
	GameData* ptr = nullptr;
	ptr = GameData::GetInstance();

	return (this->damage + ptr->GetPlayerDamage()) * ptr->GetWeaponAttackMod();
}

bool Player::IsAlive()
{
	if (((this->health + GameData::GetInstance()->GetPlayerHealth()) * GameData::GetInstance()->GetWeaponHealthMod()) - this->damageTaken <= 0) {
		return false;
	}

	return true;
}

UIHandler * Player::GetUIHandler()
{
	return &this->uiHandler;
}

void Player::SetLevel(int level)
{
	std::string text = "Level: " + std::to_string(level);
	this->uiHandler.UpdateTextHolder(4, text, 710, 20, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);
}

void Player::SetWave(int wave)
{
	std::string text = "Wave: " + std::to_string(wave);
	this->uiHandler.UpdateTextHolder(5, text, 710, 40, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), 1.5f);
}

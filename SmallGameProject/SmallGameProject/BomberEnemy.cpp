#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(float posX, float posZ)
{
    this->posX = posX;
    this->posZ = posZ;
    this->myType = Type::BOMBER;
    this->isAlive = true;
}

BomberEnemy::~BomberEnemy()
{
}

bool BomberEnemy::Initialize(Model* model, EntitySubject* entitySubject, bool isSphere)
{
    this->aimDir = DirectX::XMFLOAT3(0, 0, 0);
	bool result = Entity::Initialize(model, entitySubject, isSphere);
	this->entitySubject->Notify(this, Events::ENTITY::BOMBER_CREATED);
	return result;
}

void BomberEnemy::Shutdown()
{
	Entity::Shutdown(true);
}

bool BomberEnemy::ChargeExplosion(float deltaTime)
{
	bool canExplode = false;
	if (this->attackCD > -1)
	{
		this->attackCD += deltaTime;
	}
	if (this->attackCD > EXPLOSION_DELAY)
	{
		canExplode = true;
	}
	return canExplode;
}

void BomberEnemy::Fire(float deltaTime)
{
	if (this->attackCD > EXPLOSION_DELAY)
	{
		//this->entitySubject->Notify(this, Events::UNIQUE_FIRE::ARCFIRE, 3.14f * 2, 20);
		this->entitySubject->Notify(this, Events::ENTITY::BOMBER_DEAD);
        this->isAlive = false;
		this->attackCD = -1;
	}
	else if(this->attackCD > -1)
	{
		this->attackCD += deltaTime;
	}
}




#include "Boss.h"

Boss::Boss(float posX, float posZ)
{
	this->posX = posX;
	this->posZ = posZ;
	this->abilityUsed = 0;
}
Boss::~Boss()
{

}

bool Boss::Initialize(Model * model, EntitySubject * entitySubject, bool isSphere)
{
	this->aimDir = DirectX::XMFLOAT3(0, 0, 0);
	return Entity::Initialize(model, entitySubject, isSphere);
}

bool Boss::Initialize(Model* model, EntitySubject* entitySubject, bool isSphere, int nrOfAbilities)
{
	this->aimDir = DirectX::XMFLOAT3(0, 0, 0);

	ArcFire* temp1 = new ArcFire();
	temp1->Initialize(0.0f, 1, 0.5f, 0.5f, 1, 1);
	this->abilities.push_back(temp1);

	SplitFire* temp2 = new SplitFire();
	temp2->Initialize(3.14f * 2, 5, 4, 1, 1, 0.5f, 5, 3.14f / 2);
	this->abilities.push_back(temp2);

	ReverseFire* temp3 = new ReverseFire();
	temp3->Initialize(3.14f * 2, 15, 8, 3, 1, 3);
	this->abilities.push_back(temp3);

	return Entity::Initialize(model, entitySubject, isSphere);
}
bool Boss::Initialize(Model* model, EntitySubject* entitySubject, bool isSphere, std::vector<Ability*> abilities)
{
	this->aimDir = DirectX::XMFLOAT3(0, 0, 0);

	for (int i = 0; i < abilities.size(); i++)
	{
		this->abilities.push_back(abilities.at(i));
	}

	return Entity::Initialize(model, entitySubject, isSphere);

}
void Boss::Shutdown()
{
	for (int i = 0; i < this->abilities.size(); i++)
	{
		delete this->abilities.at(i);
	}
	this->abilities.clear();
	Entity::Shutdown(true);
}

void Boss::update(DirectX::XMFLOAT3 playerPos, float deltaTime)
{
	for (int i = 0; i < this->abilities.size(); i++)
	{
		this->abilities.at(i)->update(this, this->getEntitySubject(), deltaTime);

	}
	this->attackDelay -= deltaTime;
	int counter = 0;
	while (counter < this->abilities.size() && this->attackDelay <= 0)
	{
		float result = this->abilities.at(this->abilityUsed)->activate(this, this->getEntitySubject(), playerPos);
		this->abilityUsed++;
		if (result == -1)
		{
			counter++;
		}
		else
		{
			this->attackDelay = result;
		}
		if (this->abilityUsed >= this->abilities.size())
		{
			this->abilityUsed = 0;
		}
	}

}

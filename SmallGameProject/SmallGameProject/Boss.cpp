#include "Boss.h"

Boss::Boss(float posX, float posZ)
{
	this->posX = posX;
	this->posZ = posZ;
}
Boss::~Boss()
{

}

bool Boss::Initialize(Model* model, EntitySubject* entitySubject, bool isSphere, int nrOfAbilities)
{
	this->aimDir = DirectX::XMFLOAT3(0, 0, 0);

	ArcFire* temp1 = new ArcFire();
	temp1->Initialize(3.14f / 2, 1, 500, 50, 1, 400);
	this->abilities.push_back(temp1);

	SplitFire* temp2 = new SplitFire();
	temp2->Initialize(3.14f, 3, 500, 50, 1, 400, 5, 3.14f / 2);
	this->abilities.push_back(temp2);

	ReverseFire* temp3 = new ReverseFire();
	temp3->Initialize(3.14f / 2, 15, 500, 50, 1, 400);
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
}
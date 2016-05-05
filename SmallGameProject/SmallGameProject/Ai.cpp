#include "Ai.h"

#include <ctime>
#include <cstdlib>
Ai::Ai()
{
    srand(unsigned(time(0)));

}
Ai::~Ai()
{

}
void Ai::updateActors(std::vector<Enemy*>& actors, DirectX::XMFLOAT3 playerPos, float deltaTime)
{
    for (int i = 0; i < actors.size(); i++)
    {
        updateActor(actors.at(i), playerPos, deltaTime);
    }
    separateActors(actors);
}
void Ai::updateActor(Enemy* actor, DirectX::XMFLOAT3 playerPos, float deltaTime)
{
	if (actor->getType() == Type::BOMBER)
	{
		BomberEnemy* bPtr = (BomberEnemy*)actor;
		updateBomber(bPtr, playerPos, deltaTime);
	}
	else if (actor->getType() == Type::RANGED)
	{
		RangedEnemy* bPtr = (RangedEnemy*)actor;
		updateRange(bPtr, playerPos, deltaTime);
	}
	else if(actor->getType() == Type::MELEEE)
	{
		MeleeEnemy* bPtr = (MeleeEnemy*)actor;
		updateMelee(bPtr, playerPos, deltaTime);
	}
	else
	{
		Boss* bossPtr = (Boss*)actor;
		updateBoss(bossPtr, playerPos, deltaTime);
	}

    if (commands.size() != 0)
    {
        int action = rand() % commands.size();

        this->commands.at(action)->execute(*actor, deltaTime);
        /*for (int i = 0; i < commands.size(); i++)
        {
            this->commands.at(i)->execute(*actor, deltaTime);
        }*/
        delete this->commands.at(action);
        this->commands.at(action) = nullptr;

    }
    //moveToPlayer(actor, playerPos);

    for (int i = 0; i < commands.size(); i++)
    {
        if (this->commands.at(i) != nullptr)
            delete this->commands.at(i);
    }
    this->commands.clear();
}
void Ai::updateBomber(BomberEnemy* actor, DirectX::XMFLOAT3 playerPos, float deltaTime)
{
	float distance = distanceBetween(actor->getPosition(), playerPos);
    if (distance > 7.5f)
    {
        moveToPlayer(actor, playerPos);
    }
	if (distance < 10.0f)
	{
		bool canExlpode = actor->chargeExplosion(deltaTime);
		if (canExlpode == true)
		{
			float x = (playerPos.x - actor->getPosition().x);
			float z = (playerPos.z - actor->getPosition().z);
			actor->setAimDir(DirectX::XMFLOAT3(x, 0, z));
			this->commands.push_back(new FireCommand());
		}
	}

}
void Ai::updateRange(RangedEnemy* actor, DirectX::XMFLOAT3 playerPos, float deltaTime)
{
    float distance = distanceBetween(actor->getPosition(), playerPos);
    if (distance > RANGED_MAX_DESIRED_DISTANCE)
    {
        moveToPlayer(actor, playerPos);
    }
    else if (distance < RANGED_MIN_DESIRED_DISTANCE)
    {
        moveAwayFromPlayer(actor, playerPos);
    }
    if(distance < RANGED_MAX_DESIRED_DISTANCE)
    {
        float x = (playerPos.x - actor->getPosition().x);
        float z = (playerPos.z - actor->getPosition().z);
		actor->setAimDir(DirectX::XMFLOAT3(x, 0, z));
        this->commands.push_back(new FireCommand());
    }
}
void Ai::updateMelee(MeleeEnemy* actor, DirectX::XMFLOAT3 playerPos, float deltaTime)
{
	float distance = distanceBetween(actor->getPosition(), playerPos);
    if (distance > MELEE_MAX_DESIRED_DISTANCE)
    {
        moveToPlayer(actor, playerPos);
    }
    else if (distance < MELEE_MIN_DESIRED_DISTANCE)
    {
        moveAwayFromPlayer(actor, playerPos);
    }
	else
	{
		float x = (playerPos.x - actor->getPosition().x);
		float z = (playerPos.z - actor->getPosition().z);
		actor->setAimDir(DirectX::XMFLOAT3(x, 0, z));
		this->commands.push_back(new FireCommand());
	}
}
void Ai::updateBoss(Boss* actor, DirectX::XMFLOAT3 playerPos, float deltaTime)
{
	actor->update(playerPos, deltaTime);
	float distance = distanceBetween(actor->getPosition(), playerPos);
	if (distance > 20.0f)
	{
		this->moveToPlayer(actor, playerPos);
	}
	if (distance < 10.0f)
	{
		this->moveAwayFromPlayer(actor, playerPos);
	}
}

//private functions
void Ai::moveToPlayer(Enemy* actor, DirectX::XMFLOAT3 playerPos)
{
    DirectX::XMFLOAT3 pos = playerPos;
    if (actor->getPosition().x < playerPos.x )
    {
        this->commands.push_back(new MoveRightCommand());
    }
    else if (actor->getPosition().x > playerPos.x )
    {
        this->commands.push_back(new MoveLeftCommand());
    }
    if (actor->getPosition().z < playerPos.z )
    {
        this->commands.push_back(new MoveUpCommand());
    }
    else if (actor->getPosition().z > playerPos.z)
    {
        this->commands.push_back(new MoveDownCommand());
    }
}
void Ai::moveAwayFromPlayer(Enemy* actor, DirectX::XMFLOAT3 playerPos)
{
    if (actor->getPosition().x < playerPos.x)
    {
        this->commands.push_back(new MoveLeftCommand());
    }
    else if (actor->getPosition().x > playerPos.x )
    {
        this->commands.push_back(new MoveRightCommand());
    }
    if (actor->getPosition().z < playerPos.z )
    {
        this->commands.push_back(new MoveDownCommand());
    }
    else if (actor->getPosition().z > playerPos.z)
    {
        this->commands.push_back(new MoveUpCommand());
    }
}
void Ai::separateActors(std::vector<Enemy*>& actors)
{
    for (int i = 0; i < actors.size(); i++)
    {
        for (int a = 1; a < actors.size() && a != i; a++)
        {
            DirectX::XMFLOAT3 pos1 = actors.at(i)->getPosition();
            DirectX::XMFLOAT3 pos2 = actors.at(a)->getPosition();

            float d = distanceBetween(pos1, pos2);
            if (d <= 0.001f)
            {
                DirectX::XMFLOAT3 temp;
                temp.x = (rand() % 10);
                temp.y = 0.0f;
                temp.z = (rand() % 10);

                seperate(actors.at(i), actors.at(a), 0.05f, temp);
            }
            if (d < 5)
            {
                DirectX::XMFLOAT3 temp;
                temp.x = pos1.x - pos2.x;
                temp.y = 0.0f;
                temp.z = pos1.z - pos2.z;

                seperate(actors.at(i), actors.at(a), 0.05f, temp);
            }
            if (d < 7 && actors.at(i)->getType() != actors.at(a)->getType())
            {
                DirectX::XMFLOAT3 temp;
                temp.x = pos1.x - pos2.x;
                temp.y = 0.0f;
                temp.z = pos1.z - pos2.z;

                seperate(actors.at(i), actors.at(a), 0.01f, temp);
            }
        }
    }
}

float Ai::distanceBetween(DirectX::XMFLOAT3 positon1, DirectX::XMFLOAT3 positon2)
{

    float xDiff = abs(positon1.x - positon2.x);
    float yDiff = abs(positon1.y - positon2.y);
    float zDiff = abs(positon1.z - positon2.z);

    return pow(xDiff + yDiff + zDiff,2);
}    
void Ai::seperate(Enemy* actor1, Enemy* actor2, float amplitude, DirectX::XMFLOAT3 dir)
{
    dir.x *= amplitude;
    dir.z *= amplitude;
    actor1->move(dir);

    dir.x *= -1.0f;
    dir.z *= -1.0f;
    actor2->move(dir);
}

int Ai::getNrOfActions() const
{
    return this->nrOfActions;
}
void Ai::setNrOfActions(int nrOfActions)
{
    this->nrOfActions = nrOfActions;
}
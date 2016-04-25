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
void Ai::updateActors(std::vector<Enemy*>& actors, DirectX::XMFLOAT3 playerPos)
{
    for (int i = 0; i < actors.size(); i++)
    {
        updateActor(actors.at(i), playerPos);
    }
    separateActors(actors);
}
void Ai::updateActor(Enemy* actor, DirectX::XMFLOAT3 playerPos)
{
    BomberEnemy* ptr = nullptr;
    ptr = dynamic_cast<BomberEnemy*>(actor);
    if (ptr != nullptr)
    {
        updateBomber(ptr, playerPos);
    }
    else
    {
        MeleeEnemy* ptr = nullptr;
        ptr = dynamic_cast<MeleeEnemy*>(actor);
        if (ptr != nullptr)
        {
            updateMelee(ptr, playerPos);
        }
        else
        {
            RangedEnemy* ptr = nullptr;
            ptr = dynamic_cast<RangedEnemy*>(actor);

            if (ptr != nullptr)
            {
                updateRange(ptr, playerPos);
            }
        }

    }
    if (commands.size() != 0)
    {
        //int action = rand() % commands.size();

        //this->commands.at(action)->execute(*actor);
        for (int i = 0; i < commands.size(); i++)
        {
            this->commands.at(i)->execute(*actor);
        }
        //delete this->commands.at(action);
        //this->commands.at(action) = nullptr;

    }
    //moveToPlayer(actor, playerPos);

    for (int i = 0; i < commands.size(); i++)
    {
        if (this->commands.at(i) != nullptr)
            delete this->commands.at(i);
    }
    this->commands.clear();
}
void Ai::updateBomber(BomberEnemy* actor, DirectX::XMFLOAT3 playerPos)
{
    moveToPlayer(actor, playerPos);
}
void Ai::updateRange(RangedEnemy* actor, DirectX::XMFLOAT3 playerPos)
{

    if (distanceBetween(actor->GetPosition(), playerPos) > RANGED_MAX_DESIRED_DISTANCE)
    {
        moveToPlayer(actor, playerPos);
    }
    else if (distanceBetween(actor->GetPosition(), playerPos) < RANGED_MIN_DESIRED_DISTANCE)
    {
        moveAwayFromPlayer(actor, playerPos);
    }
}
void Ai::updateMelee(MeleeEnemy* actor, DirectX::XMFLOAT3 playerPos)
{
    if (distanceBetween(actor->GetPosition(), playerPos) > MELEE_MAX_DESIRED_DISTANCE)
    {
        moveToPlayer(actor, playerPos);
    }
    else if (distanceBetween(actor->GetPosition(), playerPos) < MELEE_MIN_DESIRED_DISTANCE)
    {
        moveAwayFromPlayer(actor, playerPos);
    }
}
void Ai::updateBoss(Enemy* actor, DirectX::XMFLOAT3 playerPos)
{

}

//private functions
void Ai::moveToPlayer(Enemy* actor, DirectX::XMFLOAT3 playerPos)
{
    DirectX::XMFLOAT3 pos = playerPos;
    if (actor->GetPosition().x < playerPos.x )
    {
        this->commands.push_back(new MoveRightCommand());
    }
    else if (actor->GetPosition().x > playerPos.x )
    {
        this->commands.push_back(new MoveLeftCommand());
    }
    if (actor->GetPosition().z < playerPos.z )
    {
        this->commands.push_back(new MoveUpCommand());
    }
    else if (actor->GetPosition().z > playerPos.z)
    {
        this->commands.push_back(new MoveDownCommand());
    }
}
void Ai::moveAwayFromPlayer(Enemy* actor, DirectX::XMFLOAT3 playerPos)
{
    if (actor->GetPosition().x < playerPos.x)
    {
        this->commands.push_back(new MoveLeftCommand());
    }
    else if (actor->GetPosition().x > playerPos.x )
    {
        this->commands.push_back(new MoveRightCommand());
    }
    if (actor->GetPosition().z < playerPos.z )
    {
        this->commands.push_back(new MoveDownCommand());
    }
    else if (actor->GetPosition().z > playerPos.z)
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
            DirectX::XMFLOAT3 pos1 = actors.at(i)->GetPosition();
            DirectX::XMFLOAT3 pos2 = actors.at(a)->GetPosition();

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
            if (d < 7)
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
#include "Ai.h"

Ai::Ai()
{


}
Ai::~Ai()
{

}
void Ai::updateActors(std::vector<Actor>& actors, DirectX::XMFLOAT3 playerPos)
{
    for (int i = 0; i < actors.size(); i++)
    {
        updateActor(actors.at(i), playerPos);
    }
    separateActors(actors);
}
void Ai::updateActor (Actor& actor, DirectX::XMFLOAT3 playerPos)
{
    if (commands.size() != 0)
    {
        int action = rand() % commands.size();

        this->commands.at(action)->execute(actor);
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
void Ai::updateBomber(BomberEnemy& actor, DirectX::XMFLOAT3 playerPos)
{
    moveToPlayer(actor, playerPos);
}
void Ai::updateRange (RangedEnemy& actor, DirectX::XMFLOAT3 playerPos)
{
    
    if (distanceBetween(actor.getPosition(), DirectX::XMFLOAT3(playerPos.x, playerPos.y, 10)) > 70)
    {
        moveToPlayer(actor, playerPos);
    }
    else if (distanceBetween(actor.getPosition(), DirectX::XMFLOAT3(playerPos.x, playerPos.y, 10)) < 40)
    {
        moveAwayFromPlayer(actor, playerPos);
    }
}
void Ai::updateMelee (MeleeEnemy& actor, DirectX::XMFLOAT3 playerPos)
{
    if (distanceBetween(actor.getPosition(), DirectX::XMFLOAT3(playerPos.x, playerPos.y, 10)) > 5)
    {
        moveToPlayer(actor, playerPos);
    }
    else if (distanceBetween(actor.getPosition(), DirectX::XMFLOAT3(playerPos.x, playerPos.y, 10)) < 2)
    {
        moveAwayFromPlayer(actor, playerPos);
    }
}
void Ai::updateBoss  (Actor& actor, DirectX::XMFLOAT3 playerPos)
{

}

//private functions
void Ai::moveToPlayer(Actor& actor, DirectX::XMFLOAT3 playerPos)
{
    if (actor.getPosition().x < playerPos.x && actor.getPosition().x < 64)
    {
        this->commands.push_back(new MoveRightCommand());
    }
    else if (actor.getPosition().x > playerPos.x && actor.getPosition().x > 0)
    {
        this->commands.push_back(new MoveLeftCommand());
    }
    if (actor.getPosition().y < playerPos.y && actor.getPosition().y < 64)
    {
        this->commands.push_back(new MoveUpCommand());
    }
    else if (actor.getPosition().y > playerPos.y && actor.getPosition().y > 0)
    {
        this->commands.push_back(new MoveDownCommand());
    }
}
void Ai::moveAwayFromPlayer(Actor& actor, DirectX::XMFLOAT3 playerPos)
{
    if (actor.getPosition().x < playerPos.x && actor.getPosition().x > 0)
    {
        this->commands.push_back(new MoveLeftCommand());
    }
    else if (actor.getPosition().x > playerPos.x && actor.getPosition().x < 64)
    {
        this->commands.push_back(new MoveRightCommand());
    }
    if (actor.getPosition().y < playerPos.y && actor.getPosition().y > 0)
    {
        this->commands.push_back(new MoveDownCommand());
    }
    else if (actor.getPosition().y > playerPos.y && actor.getPosition().y < 64)
    {
        this->commands.push_back(new MoveUpCommand());
    }
}
void Ai::separateActors(std::vector<Actor>& actors)
{
    for (int i = 0; i < actors.size(); i++)
    {
        for (int a = 1; a < actors.size(); a++)
        {
            DirectX::XMFLOAT3 pos1 = actors.at(i).getPosition();
            DirectX::XMFLOAT3 pos2 = actors.at(a).getPosition();

            if (distanceBetween(pos1, pos2) < 2)
            {
                DirectX::XMFLOAT3 temp;
                temp.x = pos1.x - pos2.x;
                temp.y = pos1.y - pos2.y;
                //a.Normalize();
                actors.at(i).move(temp);
                actors.at(a).move(temp);
            }
        }
    }
}

float Ai::distanceBetween(DirectX::XMFLOAT3 positon1, DirectX::XMFLOAT3 positon2)
{
    DirectX::XMFLOAT3 diffVec;

    float xDiff = abs(positon1.x - positon2.x);
    float yDiff = abs(positon1.x - positon2.x);

    return yDiff + xDiff;
}

int Ai::getNrOfActions() const
{
    return this->nrOfActions;
}
void Ai::setNrOfActions(int nrOfActions)
{
    this->nrOfActions = nrOfActions;
}
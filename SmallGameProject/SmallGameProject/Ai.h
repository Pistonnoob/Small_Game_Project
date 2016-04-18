#ifndef AI_H
#define AI_H
#include "Command.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveDownCommand.h"
#include "MoveUpCommand.h"
#include "BomberEnemy.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include "Enemy.h"
#include <vector>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>


class Ai{

private:
    std::vector<Command*> commands;
    int nrOfActions;
    DirectX::XMFLOAT3 playerPos;

    void moveToPlayer(Enemy* actor, DirectX::XMFLOAT3 playerPos);
    void moveAwayFromPlayer(Enemy* actor, DirectX::XMFLOAT3 playerPos);
    float distanceBetween(DirectX::XMFLOAT3 positon1, DirectX::XMFLOAT3 positon2);
public:
    Ai();
    ~Ai();
    
    void updateActors(std::vector<Enemy>& actors, DirectX::XMFLOAT3 playerPos);
    void updateActor(Enemy* actor, DirectX::XMFLOAT3 playerPos);
    void updateBomber(BomberEnemy* actor, DirectX::XMFLOAT3 playerPos);
    void updateRange(RangedEnemy* actor, DirectX::XMFLOAT3 playerPos);
    void updateMelee(MeleeEnemy* actor, DirectX::XMFLOAT3 playerPos);
    void updateBoss(Enemy* actor, DirectX::XMFLOAT3 playerPos);
    void separateActors(std::vector<Enemy>& actors);

    int getNrOfActions() const;
    void setNrOfActions(int nrOfActions);

};

#endif
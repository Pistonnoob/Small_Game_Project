#include "FireCommand.h"

FireCommand::FireCommand(DirectX::XMFLOAT3 dir)
{
    this->dir = dir;
}

void FireCommand::execute(Actor& actor)
{
    actor.SetAimDir(this->dir);
    actor.Fire();
}
#include"MoveUpCommand.h"

void MoveUpCommand::execute(Actor& actor, float deltaTime)
{
    actor.moveUp(deltaTime);
}
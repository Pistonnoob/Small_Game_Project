#include "MoveRightCommand.h"


void MoveRightCommand::execute(Actor& actor)
{
    actor.moveRight();
}
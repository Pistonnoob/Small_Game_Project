#include "MoveLeftCommand.h"

void MoveLeftCommand::execute(Actor& actor)
{
    actor.moveLeft();
}
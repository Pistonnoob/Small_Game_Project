#ifndef COMMAND_H
#define COMMAND_H
#include "Actor.h"

class Command {

private:

public:
    virtual ~Command() {}
    virtual void execute(Actor& actor) = 0;

};

#endif
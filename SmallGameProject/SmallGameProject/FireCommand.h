#ifndef FIRECOMMAND_H
#define FIRECOMMAND_H

#include "Command.h"

class FireCommand : public Command {

private:
    DirectX::XMFLOAT3 dir;
public:
    FireCommand(DirectX::XMFLOAT3 dir);
    virtual void execute(Actor& actor);

};

#endif

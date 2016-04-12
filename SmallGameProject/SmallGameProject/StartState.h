#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "GameState.h"

class StartState :
	public GameState
{
public:
	StartState();
	virtual ~StartState();
};

#endif
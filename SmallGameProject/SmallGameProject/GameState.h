#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateHandler.h"
class GameState {

protected:
	GameStateHandler* m_GSH;
public:
	virtual int HandleInput(InputHandler* input) = 0;
	virtual int Update(float deltaTime) = 0;
};

#endif
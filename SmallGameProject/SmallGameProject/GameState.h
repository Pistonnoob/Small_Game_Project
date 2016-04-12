
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "InputHandler.h"
#include <Windows.h>
#include "GraphicHandler.h"
#include "GameStateHandler.h"
class GameState {

protected:
	GameStateHandler* m_GSH;
public:

	GameState();	//This will initialize the GSH pointer to NULL
	GameState(GameStateHandler* GSH);	//USE THIS CONSTRUCTOR
	virtual ~GameState();

	virtual int HandleInput(InputHandler* input) = 0;
	virtual int Update(float deltaTime) = 0;
	virtual int Render(GraphicHandler* gHandler, HWND hwnd) = 0;
	
};

#endif
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "InputHandler.h"
#include <Windows.h>
#include "GraphicHandler.h"
class GameStateHandler;
class GameState {

protected:
	GameStateHandler* m_GSH;
public:

	GameState();	//This will initialize the GSH pointer to NULL
	GameState(GameStateHandler* GSH);
	virtual ~GameState();

	virtual void Shutdown();

	virtual int HandleInput(InputHandler* input) = 0;
	virtual int Update(float deltaTime) = 0;
	virtual int Render(GraphicHandler* gHandler, HWND hwnd) = 0;
	
};

#endif
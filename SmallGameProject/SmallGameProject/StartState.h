#ifndef STARTSTATE_H
#define STARTSTATE_H
#include "GameState.h"
class StartState :
	public GameState
{
public:
	StartState();
	StartState(GameStateHandler* GSH);
	virtual ~StartState();

	void Initialize();
	
	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);
};

#endif
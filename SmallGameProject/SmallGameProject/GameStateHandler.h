#ifndef _GAMESTATEHANDLER_H_
#define _GAMESTATEHANDLER_H_
#include "InputHandler.h"
#include "GraphicHandler.h"
#include "StartState.h"
#include <d3d11.h>
#include <vector>
#include <Windows.h>

class GameStateHandler {

private:
	std::vector<GameState*> m_gameStates;
public:
	GameStateHandler();
	~GameStateHandler();

	void Shutdown();

	bool Initialize();

	int HandleInput(InputHandler* input);
	int Update(float deltaTime);
	int Render(GraphicHandler* gHandler, HWND hwnd);

	void PushState(GameState* gameState);
	GameState* PopState();
};


#endif

#ifndef GAMESTATEHANDLER_H
#define GAMESTATEHANDLER_H
#include "InputHandler.h"
#include "GraphicHandler.h"
#include <d3d11.h>
#include <vector>
#include <Windows.h>

#include "StartState.h"
class GameStateHandler {

private:
	std::vector<GameState*> m_gameStates;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
public:
	GameStateHandler();
	~GameStateHandler();

	void Shutdown();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	int HandleInput(InputHandler* input);
	int Update(float deltaTime);
	int Render(GraphicHandler* gHandler, HWND hwnd);

	void PushState(GameState* gameState);
	GameState* PopState();
};


#endif

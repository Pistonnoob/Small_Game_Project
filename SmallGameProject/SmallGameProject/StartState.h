#ifndef STARTSTATE_H
#define STARTSTATE_H
#include "GameState.h"
class StartState :
	public GameState
{
private:
	bool startGame = false;
public:
	StartState();
	StartState(GameStateHandler* GSH);
	virtual ~StartState();

	int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);

private:
};

#endif
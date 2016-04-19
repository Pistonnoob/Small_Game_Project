#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "InputHandler.h"
#include <Windows.h>
#include "GraphicHandler.h"
#include <d3d11.h>
#include <vector>
class GameStateHandler;
class GameState {

protected:
	GameStateHandler* m_GSH;
	bool manualClearing;
	static ID3D11Device* m_device;
	static ID3D11DeviceContext* m_deviceContext;
public:

	GameState();	//This will initialize the GSH pointer to NULL
	virtual ~GameState();

	virtual void Shutdown();

	int InitializeBase(GameStateHandler * GSH, ID3D11Device * device, ID3D11DeviceContext * deviceContext);

	virtual int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH) = 0;
	
	bool GetManualClearing();
	void SetManualClearing(bool myCase);

	virtual GameState* GetPush();

	virtual int HandleInput(InputHandler* input) = 0;
	virtual int Update(float deltaTime) = 0;
	virtual int Render(GraphicHandler* gHandler, HWND hwnd) = 0;
	
};

#endif
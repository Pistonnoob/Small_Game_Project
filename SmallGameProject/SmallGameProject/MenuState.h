#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"
#include "Model.h"
class MenuState :
	public GameState
{
private:
	int selected;
	Model m_model;
	Texture myTextures;
public:
	MenuState();
	~MenuState();

	void Shutdown();

	int Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, GameStateHandler* GSH);

	virtual int HandleInput(InputHandler* input);
	virtual int Update(float deltaTime);
	virtual int Render(GraphicHandler* gHandler, HWND hwnd);
};

#endif
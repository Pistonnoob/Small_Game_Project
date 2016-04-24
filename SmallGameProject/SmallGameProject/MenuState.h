#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"
#include "Model.h"
#include "StageState.h"

enum MenuOption {
	START_GAME,
	OPTIONS,
	END_GAME
};

static const int OPTION_COUNT = 3;
class MenuState :
	public GameState
{
private:
	bool first;
	bool doOption;
	int selected;
	Model m_model;
	Texture myTextures;

	CameraHandler myCamera;

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
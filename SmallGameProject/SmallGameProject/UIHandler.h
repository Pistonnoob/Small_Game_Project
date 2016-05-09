#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <vector>

#include "UIElement.h"
#include "InputHandler.h"

class UIHandler
{
private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	int screenWidth;
	int screenHeight;

	std::vector<UIElement> elements;
public:
	UIHandler();
	~UIHandler();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int screenWidth, int screenHeight);
	void HandleInput(InputHandler* inputH);
	void Render();
	void Shutdown();

	int AddElement(int width, int height, int posX, int posY, std::string& textureMtl, int nrOfTextures, bool isButton = false);
	int UpdateElement(int elementIndex, int posX = -1, int posY = -1, int textureIndex = -1);
	int RemoveElement(int elementIndex);

	bool WasButtonPressed(int buttonID);
};

#endif
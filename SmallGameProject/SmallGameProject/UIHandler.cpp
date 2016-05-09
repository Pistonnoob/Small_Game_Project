#include "UIHandler.h"

UIHandler::UIHandler()
{
	this->elements = std::vector<UIElement>();
}

UIHandler::~UIHandler()
{
}

bool UIHandler::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, int screenWidth, int screenHeight)
{
	this->device = device;
	this->deviceContext = deviceContext;

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	return true;
}

void UIHandler::HandleInput(InputHandler * inputH)
{
	for (auto button : this->elements) {
		button.UpdateClicked(inputH->getMousePos(), this->screenWidth, this->screenHeight);
	}
}

bool UIHandler::WasButtonPressed(int buttonID)
{
	if (buttonID < this->elements.size()) {
		return this->elements.at(buttonID).WasClicked();
	}

	return false;
}

void UIHandler::Render()
{
}

void UIHandler::Shutdown()
{
	for (auto element : this->elements) {
		element.Shutdown();
	}
}

int UIHandler::AddElement(int width, int height, int posX, int posY, std::string & textureMtl, int nrOfTextures, bool isButton)
{
	UIElement temp = UIElement();
	bool result = temp.Initialize(this->device, this->deviceContext, width, height, posX, posY, textureMtl, nrOfTextures, isButton);
	if (!result) {
		return -1;
	}
	this->elements.push_back(temp);
	
	return this->elements.size() - 1;
}

int UIHandler::UpdateElement(int elementIndex, int posX, int posY, int textureIndex)
{
	if (elementIndex >= this->elements.size()) {
		return -1;
	}

	this->elements.at(elementIndex).SetPosition(posX, posY);
	this->elements.at(elementIndex).ChangeTexture(textureIndex);

	return 1;
}

int UIHandler::RemoveElement(int elementIndex)
{
	if (elementIndex >= this->elements.size()) {
		return -1;
	}

	this->elements.erase(this->elements.begin() + elementIndex);
}

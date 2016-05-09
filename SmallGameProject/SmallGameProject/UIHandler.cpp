#include "UIHandler.h"

UIHandler::UIHandler()
{
	this->elements = std::vector<UIElement>();
	this->UIShaderH = UIShaderHandler();
}

UIHandler::~UIHandler()
{
}

bool UIHandler::Initialize(GraphicHandler* graphicsH)
{
	this->device = graphicsH->GetDevice();
	this->deviceContext = graphicsH->GetDeviceContext();

	this->screenWidth = graphicsH->GetScreenWidth();
	this->screenHeight = graphicsH->GetScreenHeight();

	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f);
	DirectX::XMVECTOR camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	this->viewMatrix = DirectX::XMMatrixLookAtLH(camPos, lookAt, camUp);

	this->projectionMatrix = graphicsH->GetOrthograpicMatrix();

	if (!this->UIShaderH.Initialize(this->device)) {
		return false;
	}

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
	for (auto element : this->elements) {
		element.Render(this->deviceContext);

		this->UIShaderH.Render(this->deviceContext, 6, element.GetWorldMatrix(), this->viewMatrix, this->projectionMatrix, element.GetTexture());
	}
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

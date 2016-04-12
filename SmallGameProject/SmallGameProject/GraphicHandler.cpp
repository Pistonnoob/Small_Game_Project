#include "GraphicHandler.h"

GraphicHandler::GraphicHandler()
{
	this->engine = nullptr;
}

GraphicHandler::~GraphicHandler()
{
}

bool GraphicHandler::initialize(HWND* hwnd, int screenWidth, int screenHeight)
{
	std::string errorMessage;
	bool result;

	this->engine = new D3DHandler;
	if (!this->engine) {
		return false;
	}
	try
	{
		this->engine->initialize();
	}

	catch (char* e)
	{
		errorMessage = e;
	}

	this->deferredShaderH = new DeferredShaderHandler;
	if (!this->deferredShaderH) {
		return false;
	}
	result = this->deferredShaderH->Initialize(this->engine->GetDevice(), hwnd, screenWidth, screenHeight);
	if (!result) {
		return false;
	}

	this->lightShaderH = new LightShaderHandler;
	if (!this->lightShaderH) {
		return false;
	}
	result = this->lightShaderH->Initialize(this->engine->GetDevice(), hwnd);
	if (!result) {
		return false;
	}

	this->screenQuad = new ScreenQuad;
	if (!this->screenQuad) {
		return false;
	}
	result = this->screenQuad->Initialize(this->engine->GetDevice(), this->engine->GetDeviceContext(), screenWidth, screenHeight);
	if (!result) {
		return false;
	}
	
	return true;
}

void GraphicHandler::DeferredRender(ID3D11DeviceContext* deviceContext, int indexCount, int indexStart, DeferredShaderParameters shaderParams)
{


	return;
}

void GraphicHandler::LightRender(ID3D11DeviceContext* deviceContext, int indexCount, LightShaderParameters shaderParams)
{


	return;
}

void GraphicHandler::Shutdown()
{
	//Delete the D3DHandler object
	if (this->engine) {
		this->engine->Shutdown();
		delete this->engine;
		this->engine = nullptr;
	}
	//Delete the DeferredShaderHandler object
	if (this->deferredShaderH) {
		this->deferredShaderH->Shutdown();
		delete this->deferredShaderH;
		this->deferredShaderH = nullptr;
	}
	//Delete the LightShaderHandler object
	if (this->lightShaderH) {
		this->lightShaderH->Shutdown();
		delete this->lightShaderH;
		this->lightShaderH = nullptr;
	}

	return;
}
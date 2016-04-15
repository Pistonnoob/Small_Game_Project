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

	//Create the Direct3D handler
	this->engine = new D3DHandler;
	if (!this->engine) {
		return false;
	}
	try
	{
		this->engine->Initialize(hwnd, screenWidth, screenHeight);
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

	//Setup projection matrix
	//fieldOfView = 3.141592654f / 4.0f;
	float fieldOfView = (float)DirectX::XM_PI / 4.0f;
	float screenAspect = (float)screenWidth / (float)screenHeight;

	this->perspectiveMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);

	//Create an orthographic projection matrix for 2D rendering
	this->orthographicMatrix = DirectX::XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	
	return true;
}

void GraphicHandler::DeferredRender(int indexCount, int indexStart, DeferredShaderParameters* shaderParams)
{
	shaderParams->projectionMatrix = this->perspectiveMatrix;

	this->deferredShaderH->Render(this->engine->GetDeviceContext(), indexCount, indexStart, shaderParams);

	return;
}

void GraphicHandler::LightRender(LightShaderParameters* shaderParams)
{
	
	shaderParams->worldMatrix = DirectX::XMMatrixIdentity();
	shaderParams->projectionMatrix = this->orthographicMatrix;
	shaderParams->lightViewMatrix = DirectX::XMMatrixIdentity();
	shaderParams->lightProjectionMatrix = DirectX::XMMatrixIdentity();
	shaderParams->deferredTextures = this->deferredShaderH->GetShaderResourceViews();

	this->screenQuad->Render(this->engine->GetDeviceContext());
	this->lightShaderH->Render(this->engine->GetDeviceContext(), 3, shaderParams);

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

ID3D11Device* GraphicHandler::GetDevice()
{
	return this->engine->GetDevice();
}

ID3D11DeviceContext* GraphicHandler::GetDeviceContext()
{
	return this->engine->GetDeviceContext();
}

void GraphicHandler::ClearRTVs()
{
	this->deferredShaderH->ClearRenderTargets(this->engine->GetDeviceContext());
	this->engine->ClearDepthAndRTVViews();
}

void GraphicHandler::SetDeferredRTVs()
{
	this->deferredShaderH->SetDeferredRenderTargets(this->engine->GetDeviceContext());
	this->engine->SetDepth(true);
}

void GraphicHandler::SetLightRTV()
{
	this->engine->SetRenderTargetView();
	this->engine->SetDepth(false);
}

void GraphicHandler::PresentScene()
{
	this->engine->PresentScene();
}

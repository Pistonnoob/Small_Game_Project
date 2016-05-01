#include "GraphicHandler.h"

GraphicHandler::GraphicHandler()
{
	this->engine = nullptr;
	this->deferredShaderH = nullptr;
	this->lightShaderH = nullptr;
	this->particleShaderH = nullptr;
	this->screenQuad = nullptr;
	this->textH = nullptr;
}

GraphicHandler::~GraphicHandler()
{
}

bool GraphicHandler::initialize(HWND* hwnd, int screenWidth, int screenHeight, DirectX::XMMATRIX baseViewMatrix)
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
	result = this->lightShaderH->Initialize(this->engine->GetDevice(), hwnd, this->deferredShaderH->GetBufferCount());
	if (!result) {
		return false;
	}

	this->particleShaderH = new ParticleShaderHandler;
	if (!this->particleShaderH) {
		return false;
	}
	result = this->particleShaderH->Initialize(this->engine->GetDevice(), hwnd);
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

	this->textH = new TextHandler;
	if (!this->textH) {
		return false;
	}
	result = this->textH->Initialize(this->engine->GetDevice(), this->engine->GetDeviceContext(), baseViewMatrix, screenWidth, screenHeight);
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
	

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));
	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ONE;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	this->engine->GetDevice()->CreateBlendState(&blendDesc, &this->transparencyBlendState);

	rtbd.BlendEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	this->engine->GetDevice()->CreateBlendState(&blendDesc, &this->disableTransparencyBlendState);

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0] = rtbd;

	this->engine->GetDevice()->CreateBlendState(&blendDesc, &this->textTransparencyBlendState);

	return true;
}

void GraphicHandler::DeferredRender(Model* model, CameraHandler* camera)
{
	DeferredShaderParameters* params = new DeferredShaderParameters;

	params->camPos = camera->GetCameraPos();

	DirectX::XMMATRIX viewMatrix;
	camera->GetViewMatrix(viewMatrix);
	params->viewMatrix = viewMatrix;

	params->projectionMatrix = this->perspectiveMatrix;

	int indexCount;
	int indexStart;
	model->Render(this->engine->GetDeviceContext());
	int nrOfSubsets = model->GetNrOfSubsets();
	for (int i = 0; i < nrOfSubsets; i++) {
		model->GetDeferredShaderParameters(params, i, indexCount, indexStart);

		this->deferredShaderH->Render(this->engine->GetDeviceContext(), indexCount, indexStart, params);
		delete params;
		params = new DeferredShaderParameters;
		params->camPos = camera->GetCameraPos();

		params->viewMatrix = viewMatrix;

		params->projectionMatrix = this->perspectiveMatrix;
	}

	delete params;

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
	this->lightShaderH->Render(this->engine->GetDeviceContext(), 6, shaderParams);

	this->lightShaderH->ResetPSShaderResources(this->engine->GetDeviceContext());

	return;
}

void GraphicHandler::ParticleRender(ParticleShaderParameters * shaderParams, CameraHandler* camera)
{
	DirectX::XMMATRIX viewMatrix;
	camera->GetViewMatrix(viewMatrix);

	shaderParams->viewMatrix = viewMatrix;
	shaderParams->camPos = camera->GetCameraPos();
	shaderParams->projectionMatrix = this->perspectiveMatrix;

	this->particleShaderH->Render(this->engine->GetDeviceContext(), 5, 0, shaderParams);
}

void GraphicHandler::TextRender()
{
	this->engine->GetDeviceContext()->OMSetBlendState(this->textTransparencyBlendState, NULL, 0xffffffff);
	this->textH->Render(this->engine->GetDeviceContext(), this->orthographicMatrix);
}

void GraphicHandler::Shutdown()
{
	//Delete the quad
	if (this->screenQuad) {
		this->screenQuad->Shutdown();
		delete this->screenQuad;
		this->screenQuad = nullptr;
	}

	//Release tranparencystate
	if (this->transparencyBlendState) {
		this->transparencyBlendState->Release();
		this->transparencyBlendState = nullptr;
	}

	//Delete the textHandler
	if (this->textH) {
		this->textH->Shutdown();
		delete this->textH;
		this->textH = nullptr;
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

	//Delete the ParticleShaderHandler object
	if (this->particleShaderH) {
		this->particleShaderH->Shutdown();
		delete this->particleShaderH;
		this->particleShaderH = nullptr;
	}

	//Delete the D3DHandler object
	if (this->engine) {
		this->engine->Shutdown();
		delete this->engine;
		this->engine = nullptr;
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

int GraphicHandler::CreateTextHolder(int maxLength)
{
	return this->textH->CreateSentence(this->engine->GetDevice(), maxLength);
}

bool GraphicHandler::UpdateTextHolder(int id, const std::string & text, int posX, int posY, const DirectX::XMFLOAT3 & color)
{
	return this->textH->UpdateSentence(this->engine->GetDeviceContext(), id, text, posX, posY, color);
}

void GraphicHandler::ClearRTVs()
{
	this->deferredShaderH->ClearRenderTargets(this->engine->GetDeviceContext());
	this->engine->ClearDepthAndRTVViews();
}

void GraphicHandler::SetDeferredRTVs()
{
	this->engine->GetDeviceContext()->OMSetBlendState(this->disableTransparencyBlendState, NULL, 0xffffffff);
	this->deferredShaderH->SetDeferredRenderTargets(this->engine->GetDeviceContext());
	this->engine->SetDepth(1);
}

void GraphicHandler::SetLightRTV()
{
	this->engine->GetDeviceContext()->OMSetBlendState(this->disableTransparencyBlendState, NULL, 0xffffffff);
	this->engine->SetRenderTargetView();
	this->engine->SetDepth(2);
}

void GraphicHandler::SetParticleRTV()
{
	this->engine->GetDeviceContext()->OMSetBlendState(this->transparencyBlendState, NULL, 0xffffffff);
	this->engine->SetRenderTargetView(this->deferredShaderH->GetDepthView());
	this->engine->SetDepth(3);
}

void GraphicHandler::PresentScene()
{
	this->engine->PresentScene();
}

#include "ShadowShaderHandler.h"

ShadowShaderHandler::ShadowShaderHandler()
{
	this->startUp();
}

ShadowShaderHandler::~ShadowShaderHandler()
{
	this->Shutdown();
}

bool ShadowShaderHandler::Initialize(ID3D11Device * device, HWND * hwnd, int nrOfResources)
{
	return false;
}

void ShadowShaderHandler::Shutdown()
{
}

void ShadowShaderHandler::ResetPSShaderResources(ID3D11DeviceContext * deviceContext)
{
}

bool ShadowShaderHandler::Render(ID3D11DeviceContext * deviceContext, int indexCount, LightShaderParameters * params)
{
	return false;
}

void ShadowShaderHandler::startUp()
{
	this->vertexShader	= nullptr;
	this->layout		= nullptr;
	this->matrixBuffer	= nullptr;
	this->samplerState	= nullptr;
	this->nullResource	= nullptr;
}

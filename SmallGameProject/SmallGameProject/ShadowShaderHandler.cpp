#include "ShadowShaderHandler.h"

ShadowShaderHandler::ShadowShaderHandler()
{
	this->startUp();
}

ShadowShaderHandler::~ShadowShaderHandler()
{
	this->Shutdown();
}

bool ShadowShaderHandler::Initialize(ID3D11Device * gDevice, HWND * hwnd, int nrOfResources, int screenWidth, int screenHeight) throw(...)
{
	try
	{
		this->setViewPort(gDevice, screenWidth, screenHeight);
		this->create2DTexture(gDevice, screenWidth, screenHeight);
	}
	catch (LPCTSTR e)
	{
		MessageBox(*hwnd, e, L"Error", MB_OK);
	}

	return true;
}

void ShadowShaderHandler::Shutdown()
{
	delete this->viewPort;

	if (this->depthMap != nullptr)
	{
		this->depthMap->Release();
		this->depthMap = nullptr;
	}
	
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
	this->viewPort		= nullptr;
	this->mDepthMapSRV	= nullptr;
	this->mDepthMapDSV	= nullptr;
	this->depthMap		= nullptr;
}

void ShadowShaderHandler::setViewPort(ID3D11Device * gDevice, int clientWidth, int clientHeight)
{
	this->viewPort = new D3D11_VIEWPORT;
	float width = 0.0f;
	float height = 0.0f;

	width = static_cast<float>(clientWidth);
	height = static_cast<float>(clientHeight);

	this->viewPort->TopLeftX	= 0.0f;
	this->viewPort->TopLeftY	= 0.0f;
	this->viewPort->Width		= width;
	this->viewPort->Height		= height;
	this->viewPort->MinDepth	= 0.0f;
	this->viewPort->MaxDepth	= 1.0f;
}

void ShadowShaderHandler::create2DTexture(ID3D11Device * gDevice, int screenWidth, int screenHeight) throw(...)
{
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));

	HRESULT resultHelper;

	UINT width = static_cast<UINT>(screenWidth);
	UINT height = static_cast<UINT>(screenHeight);

	texDesc.Width = width;
	texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;


	ID3D11Texture2D* depthMap = nullptr;
	resultHelper = gDevice->CreateTexture2D(&texDesc, 0, &depthMap);

	if (FAILED(resultHelper))
	{
		throw("failed to create depthMap 2Dtexture, in ShadowShaderHandler.cpp");
	}
}

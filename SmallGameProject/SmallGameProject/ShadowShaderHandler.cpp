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

		this->createDepthStencilView(gDevice);
		this->createShaderResourceView(gDevice);


	}
	catch (char* e)
	{
		//hover at e to see error
		system("pause");
	}
	return true;
}

void ShadowShaderHandler::Shutdown()
{
	if (this->depthMap != nullptr)
	{
		this->depthMap->Release();
		this->depthMap = nullptr;
	}

	if (this->mDepthMapDSV != nullptr)
	{
		this->mDepthMapDSV->Release();
		this->mDepthMapDSV = nullptr;
	}

	if (this->mDepthMapSRV != nullptr)
	{
		this->mDepthMapSRV->Release();
		this->mDepthMapSRV = nullptr;
	}

	//delete this->viewPort; Cannot free the memory here
}

void ShadowShaderHandler::BindAndSetNullRenderTargets(ID3D11DeviceContext * gDeviceContext)
{
	gDeviceContext->RSSetViewports(1, this->viewPort);
	/*
	Set null render target because we are only going to draw to depth buffer. 
	Setting a null render target will disable color writes
	*/
	ID3D11RenderTargetView* nullTarget[1] = { nullptr };

	gDeviceContext->OMSetRenderTargets(1, nullTarget, this->mDepthMapDSV);
	this->clearShadowMapRDW(gDeviceContext);
}

bool ShadowShaderHandler::Render(ID3D11DeviceContext * deviceContext, int indexCount, LightShaderParameters * params)
{
	this->BindAndSetNullRenderTargets(deviceContext);
	return false;
}

void ShadowShaderHandler::clearShadowMapRDW(ID3D11DeviceContext* gDeviceContext)
{
	gDeviceContext->ClearDepthStencilView(this->mDepthMapDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
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

	resultHelper = gDevice->CreateTexture2D(&texDesc, 0, &this->depthMap);

	if (FAILED(resultHelper))
	{
		throw("failed to create depthMap 2Dtexture, in ShadowShaderHandler.cpp");
	}
}

void ShadowShaderHandler::createDepthStencilView(ID3D11Device * gDevice) throw(...)
{
	HRESULT resultHelper;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));

	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	resultHelper = gDevice->CreateDepthStencilView(this->depthMap, &dsvDesc, &this->mDepthMapDSV);
	
	if (FAILED(resultHelper))
	{
		throw("Failed creating the DepthStencilView");
	}
}

void ShadowShaderHandler::createShaderResourceView(ID3D11Device * gDevice) throw(...)
{
	HRESULT resultHelper;
	
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	resultHelper = gDevice->CreateShaderResourceView(depthMap, &srvDesc, &mDepthMapSRV);

	if (FAILED(resultHelper))
	{
		throw("Failed creating the shaderResourceView");
	}
}

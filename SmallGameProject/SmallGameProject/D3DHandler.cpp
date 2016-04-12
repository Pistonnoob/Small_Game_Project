#include "D3DHandler.h"
#include <iostream>
#include <assert.h> 

D3DHandler::D3DHandler()
{

	this->clientDriverType = D3D_DRIVER_TYPE_HARDWARE;
	this->featureSupport = D3D_FEATURE_LEVEL_11_0;

	try
	{
		createDeviceAndContext();
		check4xMsaaQualitySupp();
	}
	catch (char* errorMessage)
	{
		cout << errorMessage << endl;
	}

}

D3DHandler::~D3DHandler()
{
}

void D3DHandler::createDeviceAndContext() throw(...)
{
	HRESULT resultHelper;
	bool result = true;
	D3D_FEATURE_LEVEL featureLevel;
	string errorMessage;


	resultHelper = D3D11CreateDevice(
		0,							// default adapter
		this->clientDriverType,		// D3D_DRIVER_TYPE_HARDWARE, created in the default constructor
		0,							// no software device
		D3D11_CREATE_DEVICE_DEBUG,	// flag
		0, 
		0,						// default feature level array
		D3D11_SDK_VERSION,
		&this->gDevice,
		&featureLevel,
		&this->gDeviceContext);

	if (FAILED(resultHelper))
	{
		errorMessage = "D3D11CreateDevice Failed.";
		result = false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		errorMessage = "Direct3D Feature Level 11 unsupported. I messed up featurelevel somehow";
		result = false;
	}
	if (result == false)
	{
		throw(errorMessage);
	}
}

void D3DHandler::check4xMsaaQualitySupp() throw(...)
{
	string errorMessage = "Check4XMSAA quality support function error";
	UINT sampleCount = 4;
	HRESULT resultHelper;

	resultHelper = this->gDevice->CheckMultisampleQualityLevels
		(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			sampleCount,
			&this->m4xMsaaQuality
		);

	if(FAILED(resultHelper))
	{
		throw(errorMessage);
	}
	assert(m4xMsaaQuality > 0);
}

void D3DHandler::setWindowToEngine(HWND &setWindow) throw(...)
{
	this->activeWindow = &setWindow;
	if (this->activeWindow == nullptr)
	{
		throw("error in setWindowToEngine");
	}
}

void D3DHandler::describeSwapChain() throw(...)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc.Width = this->clientWidth;
	swapChainDesc.BufferDesc.Height = this->clientHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;	//pc master-race
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//are we using MSAA?
	if (this->msaa4xEnabled)
	{
		swapChainDesc.SampleDesc.Count = 4;
		swapChainDesc.SampleDesc.Quality = this->m4xMsaaQuality - 1;
	}
	//if no MSAA
	else
	{
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}
	
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow;  //window goes here
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	
}


#include "D3DHandler.h"
#include <iostream>
#include <assert.h> 

D3DHandler::D3DHandler()
{
	this->startUpValues();

	this->clientDriverType = D3D_DRIVER_TYPE_HARDWARE;
	this->featureSupport = D3D_FEATURE_LEVEL_11_0;
	this->activeWindow = nullptr;
}

D3DHandler::D3DHandler(HWND & window)
{
	this->startUpValues();

	this->clientDriverType = D3D_DRIVER_TYPE_HARDWARE;
	this->featureSupport = D3D_FEATURE_LEVEL_11_0;
	this->activeWindow = &window;
}

D3DHandler::~D3DHandler()
{
	this->shutdown();
}

void D3DHandler::SetWindowToEngine(HWND &setWindow) throw(...)
{
	this->activeWindow = &setWindow;
	if (this->activeWindow == nullptr)
	{
		throw("error in setWindowToEngine");
	}
}

bool D3DHandler::Initialize() throw(...)
{
	std::string errorMessage;
	bool result = true;

	if (this->activeWindow == nullptr)
	{
		errorMessage = "Can not initialize the D3DHandler, no active window is set";
		result = false;
	}

	try
	{
		this->createDeviceAndContext();
		this->check4xMsaaQualitySupp();
		
		DXGI_SWAP_CHAIN_DESC scDesc;
		scDesc = this->describeSwapChain();

		this->createSwapChain(&scDesc);
		this->createRenderTargetViewDS();
	}
	catch (char* errorMessage)
	{
		std::cout << errorMessage << std::endl;
	}

	return result;
}

void D3DHandler::CreateDeviceAndContext() throw(...)
{
	HRESULT resultHelper;
	bool result = true;
	D3D_FEATURE_LEVEL featureLevel;
	std::string errorMessage;


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

void D3DHandler::Check4xMsaaQualitySupp() throw(...)
{
	std::string errorMessage = "Check4XMSAA quality support function error";
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

DXGI_SWAP_CHAIN_DESC D3DHandler::DescribeSwapChain() throw(...)
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
	swapChainDesc.OutputWindow = *this->activeWindow;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	return swapChainDesc;
}

bool D3DHandler::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc) throw(...)
{
	HRESULT resultHelper;
	bool result = true;
	std::string errorMessage = "";

	IDXGIDevice* dxgiDevice = nullptr;
	resultHelper = this->gDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	
	if (FAILED(resultHelper))
	{
		errorMessage = "DxGiDevice error";
		result = false;
	}

	IDXGIAdapter* dxgiAdapter = nullptr;
	resultHelper = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	if (FAILED(resultHelper))
	{
		errorMessage = "DxGiDevice error";
		result = false;
	}

	//get the IDXGIFactory interface
	IDXGIFactory* dxgiFactory = nullptr;
	resultHelper = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	if (FAILED(resultHelper))
	{
		errorMessage = "DxGiDevice error";
		result = false;
	}

	//create the swapchain
	resultHelper = dxgiFactory->CreateSwapChain(this->gDevice, desc, &this->gSwapChain);

	if (FAILED(resultHelper))
	{
		errorMessage = "error creating the swapchain";
		result = false;
	}

	return result;
}

void D3DHandler::CreateRenderTargetViewDS() throw(...)
{
	HRESULT resultHandler;
	ID3D11Texture2D* backBuffer;
	this->gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

	resultHandler = this->gDevice->CreateRenderTargetView(backBuffer, 0, &this->mDepthStencilRTV);

	if (FAILED(resultHandler))
	{
		throw("Failed to create the render target view for the depth buffer");
	}

	//realease the com object
	backBuffer->Release();
}

void D3DHandler::CreateDepthBufferAndView() throw(...)
{

}

void D3DHandler::StartUpValues()
{
	this->gDevice			= nullptr;
	this->gDeviceContext	= nullptr;
	this->activeWindow		= nullptr;
	this->gSwapChain		= nullptr;

	this->mDepthStencilBuffer	= nullptr;
	this->mDepthStencilRTV		= nullptr;
	this->mDepthStencilView		= nullptr;
}

void D3DHandler::Shutdown()
{
	this->gSwapChain->Release();
	this->gDeviceContext->Release();
	this->gDevice->Release();
}
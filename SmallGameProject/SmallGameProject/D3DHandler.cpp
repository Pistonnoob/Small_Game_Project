#include "D3DHandler.h"

D3DHandler::D3DHandler()
{
	this->clientDriverType = D3D_DRIVER_TYPE_HARDWARE;
	this->featureSupport = D3D_FEATURE_LEVEL_11_0;
}

D3DHandler::~D3DHandler()
{
}

bool D3DHandler::createDeviceAndContext()
{
	HRESULT result;
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,							// default adapter
		this->clientDriverType,		// D3D_DRIVER_TYPE_HARDWARE, created in the default constructor
		0,							// no software device
		D3D11_CREATE_DEVICE_DEBUG,	// flag
		0, 
		0,						// default feature level array
		D3D11_SDK_VERSION,
		&md3dDevice,
		&featureLevel,
		&md3dImmediateContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}



	result = D3D11CreateDevice();
}


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


#ifndef D3DHANDLER_H
#define D3DHANDLER_H

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <D3D11.h>
#include <windows.h>
#include <string>

using namespace std;


class D3DHandler 
{
public:
	D3DHandler();
	virtual ~D3DHandler();

protected:
	bool InitDirect3D();
	void createDeviceAndContext() throw(...);
	void check4xMsaaQualitySupp() throw(...);
	void D3DHandler::describeSwapChain() throw(...);


	void CalculateFrameStats();
protected:
	ID3D11Device* gDevice;
	ID3D11DeviceContext* gDeviceContext;
	IDXGISwapChain* gSwapChain;

	//data to depthStencil
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mDepthStencilRTV;
	ID3D11DepthStencilView* mDepthStencilView;

	D3D11_VIEWPORT gameViewport;

	D3D_DRIVER_TYPE clientDriverType;
	D3D_FEATURE_LEVEL featureSupport;
	
	int clientWidth;
	int clientHeight;

	UINT m4xMsaaQuality;
	bool msaa4xEnabled;
};

#endif
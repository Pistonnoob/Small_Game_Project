#ifndef D3DHANDLER_H
#define D3DHANDLER_H

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <D3D11.h>
#include <windows.h>
#include <string>

class D3DHandler 
{
public:
	D3DHandler();
	D3DHandler(HWND &window);
	virtual ~D3DHandler();

	void setWindowToEngine(HWND &setWindow) throw(...);
	bool initialize() throw(...);

protected:
	bool InitDirect3D();
	void createDeviceAndContext() throw(...);
	// checks the quality level support for 4x MSAA
	void check4xMsaaQualitySupp() throw(...);
	
	//swapChain
	DXGI_SWAP_CHAIN_DESC describeSwapChain() throw(...);
	bool createSwapChain(DXGI_SWAP_CHAIN_DESC* desc) throw(...);

	//setAllVariablestToNullPtr
	void startUpValues();
	void CalculateFrameStats();

	void shutdown();
protected:
	ID3D11Device* gDevice;
	ID3D11DeviceContext* gDeviceContext;
	HWND* activeWindow;
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
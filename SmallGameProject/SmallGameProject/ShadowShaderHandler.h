#ifndef ShadowShaderHandler_H
#define ShadowShaderHandler_H

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include <string>

#include "ShaderStructLibrary.h"

class ShadowShaderHandler {
private:
	struct ShadowConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	ID3D11VertexShader* vertexShader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* samplerState;
	ID3D11ShaderResourceView** nullResource;
	
	D3D11_VIEWPORT* viewPort;

	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;
	ID3D11Texture2D* depthMap;

	ID3D10Blob* vertexShaderBuffer;

	static int const nrOfShaderResources = 1;
public:
	ShadowShaderHandler();
	virtual ~ShadowShaderHandler();

	bool Initialize(ID3D11Device* gDevice, HWND* hwnd, int nrOfResources, int screenWidth, int screenHeight) throw(...);
	void Shutdown();

	void BindAndSetNullRenderTargets(ID3D11DeviceContext* gDeviceContext);

	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, ShadowShaderParameters* params);
	void clearShadowMapRDW(ID3D11DeviceContext* gDeviceContext);


private:
	void StartUp();
	void SetViewPort(ID3D11Device* gDevice, int clientWidth, int clientHeight);

	void Create2DTexture(ID3D11Device* gDevice, int screenWidth, int screenHeight) throw(...);
	void CreateDepthStencilView(ID3D11Device* gDevice) throw(...);
	void CreateShaderResourceView(ID3D11Device* gDevice) throw(...);

	/*
	vertex shader help functions
	*/
	void LoadVertexShaderFromFile() throw(...);
	void CreateVertexLayout(ID3D11Device* gDevice) throw(...);
	void ReleaseVertexBuffer();

	void CreateConstantBuffer(ID3D11Device* gDevice) throw(...);

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND* hwnd, WCHAR* shaderFilename);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, ShadowShaderParameters* params) throw(...);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

	LPCWSTR stringToLPCSTR(std::string toConvert) const;
};


#endif
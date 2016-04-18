#ifndef ShadowShaderHandler_H
#define ShadowShaderHandler_H

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>

#include "ShaderStructLibrary.h"

class ShadowShaderHandler {
private:
	struct LightConstantBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX lightView;
		DirectX::XMMATRIX lightProjection;

		DirectX::XMFLOAT4 camPos;
		DirectX::XMFLOAT4 lightPos;
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

	static int const nrOfShaderResources = 1;
public:
	ShadowShaderHandler();
	virtual ~ShadowShaderHandler();

	bool Initialize(ID3D11Device* gDevice, HWND* hwnd, int nrOfResources, int screenWidth, int screenHeight) throw(...);
	void Shutdown();
	void ResetPSShaderResources(ID3D11DeviceContext* deviceContext);

	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, LightShaderParameters* params);


private:
	void startUp();
	void setViewPort(ID3D11Device * gDevice, int clientWidth, int clientHeight);

	void create2DTexture(ID3D11Device * gDevice, int screenWidth, int screenHeight) throw(...);
	void createDepthStencilView(ID3D11Device * gDevice) throw(...);
	void createShaderResourceView(ID3D11Device * gDevice) throw(...);

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND* hwnd, WCHAR* shaderFilename);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, LightShaderParameters* params);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
};


#endif
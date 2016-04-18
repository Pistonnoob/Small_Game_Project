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

	static int const nrOfShaderResources = 1;

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND* hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, LightShaderParameters* params);

	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

public:
	ShadowShaderHandler();
	virtual ~ShadowShaderHandler();

	bool Initialize(ID3D11Device* device, HWND* hwnd, int nrOfResources);
	void Shutdown();
	void ResetPSShaderResources(ID3D11DeviceContext* deviceContext);

	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, LightShaderParameters* params);


private:
	void startUp();
};


#endif
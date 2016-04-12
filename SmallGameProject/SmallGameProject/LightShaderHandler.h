#ifndef LIGHTSHADERHANDLER_H
#define LIGHTSHADERHANDLER_H

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>

class LightShaderHandler {
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
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* samplerState;

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix,
		DirectX::XMMATRIX projectionMatrix, DirectX::XMMATRIX lightViewMatrix, DirectX::XMMATRIX lightProjectionMatrix, 
		ID3D11ShaderResourceView** deferredTextures, DirectX::XMFLOAT4 lightPos, DirectX::XMFLOAT4 camPos); 

	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

public:
	LightShaderHandler();
	~LightShaderHandler();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();

	bool Render(ID3D11DeviceContext* deviceContext, int, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix,
		DirectX::XMMATRIX projectionMatrix, DirectX::XMMATRIX lightViewMatrix, DirectX::XMMATRIX lightProjectionMatrix,
		ID3D11ShaderResourceView** deferredTextures, DirectX::XMFLOAT4 lightPos, DirectX::XMFLOAT4 camPos);
};

#endif
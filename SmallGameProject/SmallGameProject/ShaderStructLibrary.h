#ifndef SHADERSTRUCTLIBRARY_H
#define SHADERSTRUCTLIBRARY_H

#include <d3d11.h>
#include <directxmath.h>

struct DeferredShaderParameters {
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;

	ID3D11ShaderResourceView* diffTexture;

	DirectX::XMFLOAT4 diffColor;
	DirectX::XMFLOAT4 ambientColor;
	DirectX::XMFLOAT4 specColor;
	DirectX::XMFLOAT4 camPos;
};

struct LightShaderParameters {
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
	DirectX::XMMATRIX lightViewMatrix;
	DirectX::XMMATRIX lightProjectionMatrix;

	ID3D11ShaderResourceView** deferredTextures;

	DirectX::XMFLOAT4 lightPos;
	DirectX::XMFLOAT4 camPos;
};

struct ShadowShaderParameters {
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
};

#endif
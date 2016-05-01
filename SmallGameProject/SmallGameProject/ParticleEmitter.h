#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include <d3d11.h>
#include <directxmath.h>
#include "GraphicHandler.h"
class ParticleEmitter
{
protected:	//Variables
	struct VertexType {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
	};

	DirectX::XMMATRIX world;
	float accumulatedTime;

	int currentParticleCnt;
	int maxParticles;

	int vertexCount, indexCount;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11ShaderResourceView* texture;

	VertexType* vertices;
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();
	virtual void Shutdown();
	virtual void ShutdownSpecific() = 0;

	virtual bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture);

	bool Update(float dT, ID3D11DeviceContext* deviceContext);
	virtual bool UpdateSpecific(float dT, ID3D11DeviceContext* deviceContext) = 0;
	virtual void Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters& emitterParameters, int& amountOfParticles) = 0;

protected:	//Functions
	virtual bool InitializeBuffers(ID3D11Device* device);

	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);
};

#endif
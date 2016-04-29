#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include <d3d11.h>
#include <directxmath.h>
#include "GraphicHandler.h"
class ParticleEmitter
{
private:

	struct Particle {
		float x, y, z, scale;
		float r, g, b, rotation;
		float velocity;
		bool active;
	};

	struct VertexType {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
	};

	float particleDeviationX, particleDeviationY, particleDeviationZ, particleVelocityVariation;
	float particleVelocity;
	float particleSize, particlesPerSecond;

	int currentParticleCnt;
	int maxParticles;
	float accumulatedTime;

	int vertexCount, indexCount;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11ShaderResourceView* texture;

	DirectX::XMMATRIX world;

	Particle* rootParticle;
	Particle* particles;
	VertexType* vertices;

public:
	ParticleEmitter();
	virtual ~ParticleEmitter();
	void Shutdown();

	bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture);
	bool Update(float dT, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters& emitterParameters);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

private:
	bool InitializeEmitter();
	bool InitializeBuffers(ID3D11Device* device);

	void EmitParticles(float dT);
	void UpdateParticles(float dT);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);

};

#endif
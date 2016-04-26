#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include <d3d11.h>
#include <directxmath.h>
class ParticleEmitter
{
private:

	struct Particle {
		float x, y, z, scale;
		float r, g, b, rotation;
		Particle* next;
		bool active;
	};

	struct VertexType {
		DirectX::XMVECTOR position;
		DirectX::XMVECTOR color;
	};

	float particleDeviationX, particleDeviationY, particleDeviationZ;
	float particleVelocity;
	float particleSize, particlesPerSecond;

	int currentParticleCnt;
	int maxParticles;
	float accumulatedTime;

	int vertexCount, indexCount;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11ShaderResourceView* texture;

	Particle* rootParticle;
	Particle* particles;
	VertexType* vertices;

public:
	ParticleEmitter();
	virtual ~ParticleEmitter();
	void Shutdown();

	bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture);
	bool Update(float dT, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext* deviceContext);

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
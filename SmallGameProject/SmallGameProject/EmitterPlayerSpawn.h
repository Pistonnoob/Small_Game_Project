#ifndef EMITTERPLAYERSPAWN
#define EMITTERPLAYERSPAWN
#include "ParticleEmitter.h"
#include "Particle.h"
#include <algorithm>
class EmitterPlayerSpawn :
	public ParticleEmitter
{
private:
	struct by_cameraPos {
		bool operator()(const Particle &left, const Particle &right) {
			return left.cameraDistance > right.cameraDistance;
		}
	};

	float particleVelocity;
	float particleSize, particlesPerSecond;

	Particle* particles;
public:
	EmitterPlayerSpawn();
	virtual ~EmitterPlayerSpawn();

	void ShutdownSpecific();

	bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture);
	bool UpdateSpecific(float dT, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters& emitterParameters, int& amountOfParticles);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

	bool SortParticles();

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
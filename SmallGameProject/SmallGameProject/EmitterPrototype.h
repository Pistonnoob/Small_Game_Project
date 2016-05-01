#ifndef EMITTERPTROTOTYPE_H
#define EMITTERPROTOTYPE_H
#include "ParticleEmitter.h"
class EmitterPrototype :
	public ParticleEmitter
{
private:

	struct Particle {
		float x, y, z, scale;
		float r, g, b, rotation;
		float velocity;
		bool active;
	};


	float particleDeviationX, particleDeviationY, particleDeviationZ, particleVelocityVariation;
	float particleVelocity;
	float particleSize, particlesPerSecond;

	Particle* particles;

public:
	EmitterPrototype();
	virtual ~EmitterPrototype();
	void ShutdownSpecific();

	bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture);
	bool UpdateSpecific(float dT, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters& emitterParameters, int& amountOfParticles);

	ID3D11ShaderResourceView* GetTexture();
	int GetInstanceCount();

private:
	bool InitializeEmitter();
	bool InitializeBuffers(ID3D11Device* device);

	void EmitParticles(float dT);
	void UpdateParticles(float dT);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);

};

#endif
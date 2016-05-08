#ifndef EMITTEREXPLOSION_H
#define EMITTEREXPLOSION_H
#include "ParticleEmitter.h"
class EmitterExplosion :
	public ParticleEmitter
{
private:
	struct Particle {
		//Variables
		float x, y, z, scale;
		float r, g, b, uCoord;
		float velocity;
		//Not the true distance but close enough
		float timeCap;
		float time;
		bool active;

		bool operator<(const Particle& that)const {
			//Sort in reverse order distance from camera > being optimal
			return this->y < that.y;
		}
	};

	struct Particle_Update {
		Particle_Update(float deltaTime) : dT{ deltaTime } { }
		float dT;
		Particle operator()(Particle node) {
			float x = 0, y = 0;
			node.time += dT;
			Algorithm::GetEllipse(x, y, node.time * node.velocity, node.time / 2, node.time / 2);
			node.x = x;
			node.z = y;
			return node;
		};
		//void operator()(Particle& element) { element.time += dT; Algorithm::GetEllipse(element.x, element.y, element.time * element.velocity, element.time, element.time); };
	};

	float particleTimeLimit;
	float particleVelocity;
	float particleSize;
	
	std::vector<Particle> root;
public:
	EmitterExplosion();
	virtual ~EmitterExplosion();

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

	void EmittParticles(float dT);
	void UpdateParticles(float dT);
	void KillParticles();


	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);
};

#endif
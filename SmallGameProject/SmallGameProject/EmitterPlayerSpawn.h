#ifndef EMITTERPLAYERSPAWN
#define EMITTERPLAYERSPAWN
#include "ParticleEmitter.h"
#include "Particle.h"
#include <vector>
#include <algorithm>
class EmitterPlayerSpawn :
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


	struct sort_by_Y {
		bool operator()(const Particle &left, const Particle &right)const {
			return left.y < right.y;
		}
	};

	

	float particleVelocity;
	float particleSize, particlesPerSecond;
	std::vector<Particle> root;
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

	void EmittParticles(float dT);
	void UpdateParticles(float dT);
	void KillParticles();


	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);
};

#endif
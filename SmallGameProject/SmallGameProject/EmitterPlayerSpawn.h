#ifndef EMITTERPLAYERSPAWN
#define EMITTERPLAYERSPAWN
#include "ParticleEmitter.h"
//#include "Particle.h"
#include <vector>
#include <algorithm>
#include <ppl.h>
using namespace concurrency;
class EmitterPlayerSpawn :
	public ParticleEmitter
{
private:
	struct Particle {
		//Variables
		float x, y, z, scale;
		float r, g, b, a, uCoord;
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
		Particle_Update(float deltaTime) : dT{deltaTime} { }
		float dT;
		Particle operator()(Particle node) {
			float x = 0, y = 0;
			node.time += dT;
			Algorithm::GetEllipse(x, y, node.time * node.velocity, node.time, node.time);
			node.x = x;
			node.z = y;
			return node;
		};
		//void operator()(Particle& element) { element.time += dT; Algorithm::GetEllipse(element.x, element.y, element.time * element.velocity, element.time, element.time); };
	};

	/*void Particle_Update(Particle& element)
	{
		float x = 0.0f, y = 0.0f;
		float t = element.time;
		float size = t;
		t *= element.velocity;
		Algorithm::GetEllipse(element.x, element.y, t, size, size);
	}*/

	struct sort_by_Y {
		bool operator()(const Particle &left, const Particle &right)const {
			return left.y < right.y;
		}
	};

	bool my_predicate(const Particle item){
		return item.active != true;
	}

	float particleTimeLimit;
	float particleVelocity;
	float particleSize, particlesPerSecond;
	std::vector<Particle> root;
public:
	EmitterPlayerSpawn();
	virtual ~EmitterPlayerSpawn();

	void ShutdownSpecific();

	bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture, float timeLimit = 4.0f);
	bool UpdateSpecific(float dT, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters* emitterParameters, int& amountOfParticles);

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
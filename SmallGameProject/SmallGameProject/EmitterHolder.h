#ifndef EMITTERHOLDER_H
#define EMITTERHOLDER_H
#include "ParticleEmitter.h"
#include <algorithm>
class EmitterHolder :
	public ParticleEmitter
{
private:
	struct Particle {
		//Variables
		float x, y, z, scale;
		float originX, originZ;
		float minScale, maxScale;
		float dX, dZ;
		float r, g, b, a, uCoord;
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
			float x = 0.0f, y = 0.0f;
			node.time += dT;
			//Let it scale from max to min through its lifetime
			float existedFor = node.time / node.timeCap;
			float newScale = node.maxScale * existedFor + node.minScale;
			node.scale = newScale;
			node.x = node.originX + node.dX * node.time;
			node.z = node.originZ + node.dZ * node.time;
			node.a = 0.3f;
			node.active = node.time < node.timeCap;
			return node;
		};
		//void operator()(Particle& element) { element.time += dT; Algorithm::GetEllipse(element.x, element.y, element.time * element.velocity, element.time, element.time); };
	};

	struct sort_by_Y {
		bool operator()(const Particle &left, const Particle &right)const {
			return left.y < right.y;
		}
	};

	float height;
	std::vector<Particle> particles;
public:
	EmitterHolder();
	virtual ~EmitterHolder();
	void ShutdownSpecific();

	bool AddParticle(float x, float y, float z, float minSize, float maxSize, float r, float g, float b, float textureIndex, float time, float movingX, float movingZ);

	bool Initialize(ID3D11Device* device, ID3D11ShaderResourceView* texture, float timeLimit = 1.0f);
	bool UpdateSpecific(float dT, ID3D11DeviceContext* deviceContext);
	void Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters* emitterParameters, int& amountOfParticles);

	int GetIndexCount();
	bool SortParticles();

	virtual bool IsCompleted();
private:
	bool InitializeEmitter();
	bool InitializeBuffers(ID3D11Device* device);

	void UpdateParticles(float dT);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext* deviceContext);

	void RenderBuffers(ID3D11DeviceContext* deviceContext);
};

#endif
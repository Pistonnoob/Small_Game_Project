#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H
#include "Observer.h"
#include "Algorithm.h"
#include "Texture.h"
#include "ParticleEmitter.h"
#include "GraphicHandler.h"
#include "CameraHandler.h"

class ParticleHandler :
	public Observer
{
private:
	std::vector<ParticleEmitter> emitters;
	struct Particle {
		float x, y, z, scale;
		float r, g, b, rotation;
	};
	struct VertexType {
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
	};
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	ID3D11ShaderResourceView* texture;
	Texture myTextures;

	Particle particles[5];
	VertexType vertices[5];

	DirectX::XMMATRIX world;
public:
	ParticleHandler();
	virtual ~ParticleHandler();
	void Shutdown();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	virtual void OnNotify(const Entity* entity, Events::ENTITY evnt);

	int Render(GraphicHandler* gHandler, CameraHandler* camera);

	int CreateEmitterParabola(ID3D11ShaderResourceView* texture);
	int CreateEmitterCircle(ID3D11ShaderResourceView* texture);
	int CreateEmitterEllipse(ID3D11ShaderResourceView* texture, int widthConstant, int heightConstant);
	int CreateEmitterLissajous(ID3D11ShaderResourceView* texture, int widthConstant, int heightConstant, int xLobes, int yLobes);
	int CreateEmitterHypotrochoid(ID3D11ShaderResourceView* texture, int circleRadius, int containedCircleRadius, int pointOffset);
};

#endif
#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H
#include "Observer.h"
#include "Algorithm.h"
#include "Texture.h"
#include "EmitterPrototype.h"
#include "EmitterPlayerSpawn.h"
#include "GraphicHandler.h"
#include "CameraHandler.h"

class ParticleHandler :
	public Observer
{
private:
	std::vector<ParticleEmitter*> emitters;

	Texture myTextures;
	ID3D11Device* device;
public:
	ParticleHandler();
	virtual ~ParticleHandler();
	void Shutdown();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	virtual void OnNotify(Entity* entity, Events::ENTITY evnt);
	virtual void OnNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);
	virtual void OnNotify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets);
	virtual void OnNotify(Entity* entity, Events::PICKUP evnt);

	int Update(float dT, ID3D11DeviceContext* deviceContext);

	int Render(GraphicHandler* gHandler, CameraHandler* camera);

	int CreateEmitterParabola(ID3D11ShaderResourceView* texture);
	int CreateEmitterCircle(ID3D11ShaderResourceView* texture);
	int CreateEmitterEllipse(ID3D11ShaderResourceView* texture, int widthConstant, int heightConstant);
	int CreateEmitterLissajous(ID3D11ShaderResourceView* texture, int widthConstant, int heightConstant, int xLobes, int yLobes);
	int CreateEmitterHypotrochoid(ID3D11ShaderResourceView* texture, int circleRadius, int containedCircleRadius, int pointOffset);
private:	//Functions
};

#endif
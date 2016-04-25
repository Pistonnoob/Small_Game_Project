#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H
#include "Observer.h"
#include "Algorithm.h"
#include "Texture.h"
#include "ParticleEmitter.h"
class ParticleHandler :
	public Observer
{
private:
	std::vector<ParticleEmitter> emitters;
public:
	ParticleHandler();
	virtual ~ParticleHandler();
	void Shutdown();


	virtual void OnNotify(const Entity* entity, Events::ENTITY evnt);

	int CreateEmitterParabola(ID3D11ShaderResourceView* texture);
	int CreateEmitterCircle(ID3D11ShaderResourceView* texture);
	int CreateEmitterEllipse(ID3D11ShaderResourceView* texture, int widthConstant, int heightConstant);
	int CreateEmitterLissajous(ID3D11ShaderResourceView* texture, int widthConstant, int heightConstant, int xLobes, int yLobes);
	int CreateEmitterHypotrochoid(ID3D11ShaderResourceView* texture, int circleRadius, int containedCircleRadius, int pointOffset);
};

#endif
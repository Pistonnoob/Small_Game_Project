#include "ParticleHandler.h"



ParticleHandler::ParticleHandler()
{
}


ParticleHandler::~ParticleHandler()
{
}

void ParticleHandler::Shutdown()
{
}

void ParticleHandler::OnNotify(const Entity * entity, Events::ENTITY evnt)
{
	switch (evnt)
	{
	case Events::CREATED:
		break;
	case Events::IDLE:
		break;
	case Events::MOVING:
		break;
	case Events::DEAD:
		break;
	default:
		break;
	}
}

int ParticleHandler::CreateEmitterParabola(ID3D11ShaderResourceView * texture)
{
	return 0;
}

int ParticleHandler::CreateEmitterCircle(ID3D11ShaderResourceView * texture)
{
	return 0;
}

int ParticleHandler::CreateEmitterEllipse(ID3D11ShaderResourceView * texture, int widthConstant, int heightConstant)
{
	return 0;
}

int ParticleHandler::CreateEmitterLissajous(ID3D11ShaderResourceView * texture, int widthConstant, int heightConstant, int xLobes, int yLobes)
{
	return 0;
}

int ParticleHandler::CreateEmitterHypotrochoid(ID3D11ShaderResourceView * texture, int circleRadius, int containedCircleRadius, int pointOffset)
{
	return 0;
}
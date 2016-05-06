#include "ParticleHandler.h"



ParticleHandler::ParticleHandler()
{
}


ParticleHandler::~ParticleHandler()
{
}

void ParticleHandler::Shutdown()
{
	this->myTextures.Shutdown();

	while (this->emitters.size())
	{
		ParticleEmitter* emitter = this->emitters.back();
		emitter->Shutdown();
		delete emitter;
		emitter = nullptr;
		this->emitters.pop_back();
	}
	this->emitters.clear();

}

void ParticleHandler::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	this->myTextures = Texture();
	std::string theNightSky = "Particles.mtl";
	bool victory = this->myTextures.Initialize(device, deviceContext, theNightSky);

	EmitterPlayerSpawn* newEmitter = new EmitterPlayerSpawn();
	newEmitter->Initialize(device, this->myTextures.GetTexture(0));
	this->emitters.push_back(newEmitter);
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

int ParticleHandler::Update(float dT, ID3D11DeviceContext * deviceContext)
{
	int result = 0;

	for (auto emitter = this->emitters.begin(); emitter != this->emitters.end(); emitter++)
	{
		(*emitter)->Update(dT, deviceContext);
	}

	return result;
}

int ParticleHandler::Render(GraphicHandler * gHandler, CameraHandler * camera)
{
	int result = 0;

	//this->RenderBuffers(gHandler->GetDeviceContext());

	ParticleShaderParameters parameters;

	/*for (auto emitter = this->emitters.begin(); emitter != this->emitters.end(); emitter++)
	{
		int amount
	}*/
	if (this->emitters.size())
	{
		int amountOfParticles = 0;
		this->emitters.at(0)->SetCameraPos(camera->GetCameraPos());
		this->emitters.at(0)->SortParticles();
		this->emitters.at(0)->Render(gHandler->GetDeviceContext(), parameters, amountOfParticles);

		parameters.diffTexture = this->myTextures.GetTexture(0);
		this->emitters.at(0)->GetWorld(parameters.worldMatrix);
		if (!parameters.diffTexture)
		{
			result = false;
		}

		gHandler->ParticleRender(&parameters, camera, amountOfParticles);
	}


	return result;
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

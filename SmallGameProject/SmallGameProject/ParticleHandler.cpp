#include "ParticleHandler.h"
#include "Player.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include "BomberEnemy.h"


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

	EmitterExplosion* newEmitter = new EmitterExplosion();
	newEmitter->Initialize(device, this->myTextures.GetTexture(0));
	this->emitters.push_back(newEmitter);
}

void ParticleHandler::OnNotify(Entity * entity, Events::ENTITY evnt)
{
	ParticleEmitter* newEmitter = nullptr;
	switch (evnt)
	{
	case Events::CREATED:
		break;
	case Events::PLAYER_CREATED:
	{
		newEmitter = new EmitterPlayerSpawn();
		newEmitter->Initialize(this->device, this->myTextures.GetTexture(0));
	}
		break;
	case Events::PLAYER_MOVING:
		break;
	case Events::PLAYER_DEAD:
		break;
	case Events::BOMBER_CREATED:
	{
		newEmitter = new EmitterEnemySpawn();
		newEmitter->Initialize(this->device, this->myTextures.GetTexture(0));
	}
		break;
	case Events::BOMBER_MOVING:
		break;
	case Events::BOMBER_DEAD:
	{
		newEmitter = new EmitterExplosion();
		newEmitter->Initialize(this->device, this->myTextures.GetTexture(0));
	}
		break;
	case Events::RANGED_CREATED:
	{
		newEmitter = new EmitterEnemySpawn();
		newEmitter->Initialize(this->device, this->myTextures.GetTexture(0));
	}
		break;
	case Events::RANGED_MOVING:
		break;
	case Events::RANGED_DEAD:
		break;
	case Events::MELEE_CREATED:
	{
		newEmitter = new EmitterEnemySpawn();
		newEmitter->Initialize(this->device, this->myTextures.GetTexture(0));
	}
		break;
	case Events::MELEE_MOVING:
		break;
	case Events::MELEE_DEAD:
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
	if (newEmitter)
	{
		this->emitters.push_back(newEmitter);
	}
}

void ParticleHandler::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{
}

void ParticleHandler::OnNotify(Entity * entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets)
{
}

void ParticleHandler::OnNotify(Entity * entity, Events::PICKUP evnt)
{
}

int ParticleHandler::Update(float dT, ID3D11DeviceContext * deviceContext)
{
	int result = 0;

	for (auto emitter = this->emitters.begin(); emitter != this->emitters.end(); emitter++)
	{
		(*emitter)->Update(dT, deviceContext);
	}
	this->KillEmitters();
	return result;
}

int ParticleHandler::Render(GraphicHandler * gHandler, CameraHandler * camera)
{
	int result = 0;

	ParticleShaderParameters parameters;

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

void ParticleHandler::KillEmitters()
{
	this->emitters.erase(std::remove_if(this->emitters.begin(), this->emitters.end(), Emitter_Removal_Predicate()), this->emitters.end());
}

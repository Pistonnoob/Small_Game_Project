#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter()
{
	this->particleDeviationX = this->particleDeviationY = this->particleDeviationZ = 0.0f;
	this->particleVelocity = 0.0f;
	this->particleSize = this->particlesPerSecond = 0.0f;

	this->maxParticles = 0;
	this->accumulatedTime = 0.0f;
	this->vertexCount = this->indexCount = 0;

	this->vertexBuffer = this->indexBuffer = nullptr;

	this->texture = nullptr;
}


ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::Shutdown()
{
	if (this->vertexBuffer)
	{
		this->vertexBuffer->Release();
		delete this->vertexBuffer;
		this->vertexBuffer = nullptr;
	}

	if (this->indexBuffer)
	{
		this->indexBuffer->Release();
		delete this->indexBuffer;
		this->indexBuffer = nullptr;
	}

	if (this->texture)
		this->texture = nullptr;

}

bool ParticleEmitter::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture)
{
	bool result = false;
	//Set the texture
	this->texture = texture;

	//Initialize the emitter
	result = this->InitializeEmitter();
	if (!result)
		return false;
	
	//Initialize the buffers
	result = this->InitializeBuffers(device);
	if (!result)
		return false;

	return true;
}

bool ParticleEmitter::Update(float dT, ID3D11DeviceContext * deviceContext)
{
	bool result = false;

	//Release old particles
	this->KillParticles();

	//Emitt new particles
	this->EmitParticles(dT);

	//Update the particles
	this->UpdateParticles(dT);

	//Update the dynamic vertex buffer with the new position of each particle
	result = this->UpdateBuffers(deviceContext);
	if (!result)
		return false;

	return true;
}

void ParticleEmitter::Render(ID3D11DeviceContext * deviceContext)
{
	//NOT IMPLEMENTED
}

ID3D11ShaderResourceView * ParticleEmitter::GetTexture()
{
	return nullptr;
}

int ParticleEmitter::GetIndexCount()
{
	return 0;
}

bool ParticleEmitter::InitializeEmitter()
{
	return false;
}

bool ParticleEmitter::InitializeBuffers(ID3D11Device * device)
{
	return false;
}

void ParticleEmitter::EmitParticles(float dT)
{
}

void ParticleEmitter::UpdateParticles(float dT)
{
}

void ParticleEmitter::KillParticles()
{
}

bool ParticleEmitter::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	return false;
}

void ParticleEmitter::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
}

#include "EmitterPlayerSpawn.h"



EmitterPlayerSpawn::EmitterPlayerSpawn()
{
	this->accumulatedTime = 0.0f;
	this->maxParticles = 0;
	this->currentParticleCnt = 0;
	this->vertexCount = this->indexCount = 0;

	this->vertexBuffer = this->indexBuffer = nullptr;
}


EmitterPlayerSpawn::~EmitterPlayerSpawn()
{
}

void EmitterPlayerSpawn::ShutdownSpecific()
{
}

bool EmitterPlayerSpawn::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture)
{
	return false;
}

bool EmitterPlayerSpawn::UpdateSpecific(float dT, ID3D11DeviceContext * deviceContext)
{
	return false;
}

void EmitterPlayerSpawn::Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters & emitterParameters, int & amountOfParticles)
{
}

ID3D11ShaderResourceView * EmitterPlayerSpawn::GetTexture()
{
	return nullptr;
}

int EmitterPlayerSpawn::GetIndexCount()
{
	return 0;
}

bool EmitterPlayerSpawn::SortParticles()
{
	return false;
}

bool EmitterPlayerSpawn::InitializeEmitter()
{
	return false;
}

bool EmitterPlayerSpawn::InitializeBuffers(ID3D11Device * device)
{
	return false;
}

void EmitterPlayerSpawn::EmitParticles(float dT)
{
}

void EmitterPlayerSpawn::UpdateParticles(float dT)
{
}

void EmitterPlayerSpawn::KillParticles()
{
}

bool EmitterPlayerSpawn::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	return false;
}

void EmitterPlayerSpawn::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
}

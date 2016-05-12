#include "EmitterSpawnPulse.h"



EmitterSpawnPulse::EmitterSpawnPulse()
{
}


EmitterSpawnPulse::~EmitterSpawnPulse()
{
}

void EmitterSpawnPulse::ShutdownSpecific()
{
}

bool EmitterSpawnPulse::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture, float timeLimit)
{
	return false;
}

bool EmitterSpawnPulse::UpdateSpecific(float dT, ID3D11DeviceContext * deviceContext)
{
	return false;
}

void EmitterSpawnPulse::Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters & emitterParameters, int & amountOfParticles)
{
}

int EmitterSpawnPulse::GetIndexCount()
{
	return 0;
}

bool EmitterSpawnPulse::SortParticles()
{
	return false;
}

bool EmitterSpawnPulse::InitializeEmitter()
{
	return false;
}

bool EmitterSpawnPulse::InitializeBuffers(ID3D11Device * device)
{
	return false;
}

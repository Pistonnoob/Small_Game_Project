#include "EmitterExplosion.h"



EmitterExplosion::EmitterExplosion()
{
}


EmitterExplosion::~EmitterExplosion()
{
}

void EmitterExplosion::ShutdownSpecific()
{
}

bool EmitterExplosion::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture)
{
	return false;
}

bool EmitterExplosion::UpdateSpecific(float dT, ID3D11DeviceContext * deviceContext)
{
	return false;
}

void EmitterExplosion::Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters & emitterParameters, int & amountOfParticles)
{
}

ID3D11ShaderResourceView * EmitterExplosion::GetTexture()
{
	return nullptr;
}

int EmitterExplosion::GetIndexCount()
{
	return 0;
}

bool EmitterExplosion::SortParticles()
{
	return false;
}

bool EmitterExplosion::InitializeEmitter()
{
	return false;
}

bool EmitterExplosion::InitializeBuffers(ID3D11Device * device)
{
	return false;
}

void EmitterExplosion::EmittParticles(float dT)
{
}

void EmitterExplosion::UpdateParticles(float dT)
{
}

void EmitterExplosion::KillParticles()
{
}

bool EmitterExplosion::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	return false;
}

void EmitterExplosion::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
}

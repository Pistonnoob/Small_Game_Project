#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter()
{
	this->particleDeviationX = this->particleDeviationY = this->particleDeviationZ = 0.0f;
	this->particleVelocity = 0.0f;
	this->particleSize = this->particlesPerSecond = 0.0f;

	this->currentParticleCnt = 0;
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
		this->vertexBuffer = nullptr;
	}

	if (this->indexBuffer)
	{
		this->indexBuffer->Release();
		this->indexBuffer = nullptr;
	}

	if (this->texture)
		this->texture = nullptr;

	if (this->particles)
	{
		delete[] this->particles;
		this->particles = nullptr;
	}

	if (this->vertices)
	{
		delete[] this->vertices;
		this->vertices = nullptr;
	}

	while (this->rootParticle->next != nullptr)
	{
		Particle* temp = this->rootParticle;
		this->rootParticle = this->rootParticle->next;
		delete temp;
	}
	if (this->rootParticle != nullptr)
	{
		delete this->rootParticle;
	}

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
	return this->texture;
}

int ParticleEmitter::GetIndexCount()
{
	return this->indexCount;
}

bool ParticleEmitter::InitializeEmitter()
{
	this->particleDeviationX = 0.5f;
	this->particleDeviationY = 0.1f;
	this->particleDeviationZ = 2.0f;

	this->particleVelocity = 1.0f;
	this->particleSize = 0.2f;
	this->particlesPerSecond = 100.0f;
	this->maxParticles = 5000;

	this->particles = new Particle[this->maxParticles];
	if (!this->particles)
		return false;

	//Initialize particle list
	for (int i = 0; i < this->maxParticles; i++)
	{
		this->particles[i].active = false;
	}

	this->rootParticle = new Particle{
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		nullptr,
		true
	};

	this->currentParticleCnt = 0;

	this->accumulatedTime = 0.0f;

	return true;
}

bool ParticleEmitter::InitializeBuffers(ID3D11Device * device)
{
	unsigned long* indices;
	int i;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Set the maximum number of vertices in the vertex array.
	this->vertexCount = this->maxParticles * 6;

	// Set the maximum number of indices in the index array.
	this->indexCount = this->vertexCount;

	// Create the vertex array for the particles that will be rendered.
	this->vertices = new VertexType[this->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[this->indexCount];
	if (!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * vertexCount));

	// Initialize the index array.
	for (i = 0; i < indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now finally create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &this->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * this->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &this->indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the index array since it is no longer needed.
	delete[] indices;
	indices = 0;

	return true;
}

void ParticleEmitter::EmitParticles(float dT)
{
}

void ParticleEmitter::UpdateParticles(float dT)
{
}

void ParticleEmitter::KillParticles()
{
	//Go through all particles
	for (int i = 0; i < this->maxParticles; i++)
	{
		//The conditions for killing / restarting the particle
		if (!this->particles[i].active)
		{
			//Kill the particle
		}
	}
}

bool ParticleEmitter::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	return false;
}

void ParticleEmitter::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
}

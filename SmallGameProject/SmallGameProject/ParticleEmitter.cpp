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

	/*while (this->rootParticle->next != nullptr)
	{
		Particle* temp = this->rootParticle;
		this->rootParticle = this->rootParticle->next;
		delete temp;
	}*/
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
	this->world = DirectX::XMMatrixIdentity();


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

void ParticleEmitter::Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters& emitterParameters)
{
	//NOT IMPLEMENTED
	this->RenderBuffers(deviceContext);

	ParticleShaderParameters parameters;

	parameters.worldMatrix = this->world;
	parameters.diffTexture = this->texture;
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
	this->particleVelocityVariation = 0.2f;

	this->particleSize = 0.2f;
	this->particlesPerSecond = 250.0f;
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
		1.0f,
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
	this->vertexCount = this->maxParticles;

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
	bool emitParticle, found;
	float positionX, positionY, positionZ, velocity, red, green, blue;
	int index, i, j;


	// Increment the frame time.
	this->accumulatedTime += dT;

	// Set emit particle to false for now.
	emitParticle = false;

	// Check if it is time to emit a new particle or not.
	if (this->accumulatedTime > (1000.0f / this->particlesPerSecond))
	{
		this->accumulatedTime = 0.0f;
		emitParticle = true;
	}

	// If there are particles to emit then emit one per frame.
	if ((emitParticle == true) && (this->currentParticleCnt < (this->maxParticles - 1)))
	{
		this->currentParticleCnt++;

		// Now generate the randomized particle properties.
		positionX = (((float)rand() - (float)rand()) / RAND_MAX) * particleDeviationX;
		positionY = (((float)rand() - (float)rand()) / RAND_MAX) * particleDeviationY;
		positionZ = (((float)rand() - (float)rand()) / RAND_MAX) * particleDeviationZ;

		velocity = particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) * particleVelocityVariation;

		red = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		green = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		blue = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;

		// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
		// We will sort using Z depth so we need to find where in the list the particle should be inserted.
		index = 0;
		found = false;
		while (!found)
		{
			if ((this->particles[index].active == false) || (this->particles[index].z < positionZ))
			{
				found = true;
			}
			else
			{
				index++;
			}
		}

		// Now that we know the location to insert into we need to copy the array over by one position from the index to make room for the new particle.
		i = this->currentParticleCnt;
		j = i - 1;

		while (i != index)
		{
			this->particles[i].x =this->particles[j].x;
			this->particles[i].y =this->particles[j].y;
			this->particles[i].z =this->particles[j].z;
			this->particles[i].r =this->particles[j].r;
			this->particles[i].g =this->particles[j].g;
			this->particles[i].b =this->particles[j].b;
			this->particles[i].velocity = this->particles[j].velocity;
			this->particles[i].active = this->particles[j].active;
			i--;
			j--;
		}

		// Now insert it into the particle array in the correct depth order.
		this->particles[index].x = positionX;
		this->particles[index].y = positionY;
		this->particles[index].z = positionZ;
		this->particles[index].r = red;
		this->particles[index].g = green;
		this->particles[index].b = blue;
		this->particles[index].velocity = velocity;
		this->particles[index].active = true;
	}

	return;
}

void ParticleEmitter::UpdateParticles(float dT)
{
	// Each frame we update all the particles by making them move downwards using their position, velocity, and the frame time.
	for (int i = 0; i<this->currentParticleCnt; i++)
	{
		this->particles[i].y = this->particles[i].y - (this->particles[i].velocity * dT * 0.001f);
	}

	return;
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
			this->particles[i].active = false;
			this->currentParticleCnt--;
			for (int j = i; j < this->maxParticles - 1; j++)
			{
				this->particles[j] = this->particles[j + 1];
				/*this->particles[j].x = this->particles[j + 1].x;
				this->particles[j].y = this->particles[j + 1].y;
				this->particles[j].z = this->particles[j + 1].z;
				this->particles[j].scale = this->particles[j + 1].scale;
				this->particles[j].r = this->particles[j + 1].r;
				this->particles[j].g = this->particles[j + 1].g;
				this->particles[j].b = this->particles[j + 1].b;
				this->particles[j].rotation = this->particles[j + 1].rotation;
				this->particles[j].active = this->particles[j + 1].active;
				this->particles[j].velocity = this->particles[j + 1].velocity;*/
			}
		}
	}
}

bool ParticleEmitter::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	// Initialize vertex array to zeros at first.
	memset(this->vertices, 0, (sizeof(VertexType) * this->vertexCount));

	for (int i = 0; i < this->currentParticleCnt; i++)
	{
		this->vertices[i].position = DirectX::XMFLOAT4(this->particles[i].x, this->particles[i].y, this->particles[i].z, this->particles[i].scale);
		this->vertices[i].color = DirectX::XMFLOAT4(this->particles[i].r, this->particles[i].g, this->particles[i].b, this->particles[i].rotation);

	}

	// Lock the vertex buffer.
	result = deviceContext->Map(this->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)this->vertices, (sizeof(VertexType) * this->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(this->vertexBuffer, 0);

	return true;


}

void ParticleEmitter::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	return;
}

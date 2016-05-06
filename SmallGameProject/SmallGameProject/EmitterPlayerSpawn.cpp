#include "EmitterPlayerSpawn.h"



EmitterPlayerSpawn::EmitterPlayerSpawn() :
	ParticleEmitter()
{
	this->particleVelocity = 0.0f;
	this->particleSize = this->particlesPerSecond = 0.0f;
}


EmitterPlayerSpawn::~EmitterPlayerSpawn()
{
}

void EmitterPlayerSpawn::ShutdownSpecific()
{
	while (this->root)
	{
		ParticleContainer* nextContainer = this->root->next;
		delete this->root;
		this->root = nextContainer;
	}
}

bool EmitterPlayerSpawn::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture)
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

bool EmitterPlayerSpawn::UpdateSpecific(float dT, ID3D11DeviceContext * deviceContext)
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

void EmitterPlayerSpawn::Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters & emitterParameters, int & amountOfParticles)
{
	//NOT IMPLEMENTED
	this->RenderBuffers(deviceContext);

	ParticleShaderParameters parameters;

	parameters.worldMatrix = this->world;
	parameters.diffTexture = this->texture;
	amountOfParticles = this->currentParticleCnt;
}

ID3D11ShaderResourceView * EmitterPlayerSpawn::GetTexture()
{
	return this->texture;
}

int EmitterPlayerSpawn::GetIndexCount()
{
	return this->indexCount;
}

bool EmitterPlayerSpawn::SortParticles()
{
	return true;
}

bool EmitterPlayerSpawn::InitializeEmitter()
{
	this->particleVelocity = 1.0f;

	this->particleSize = 0.1f;
	this->particlesPerSecond = 10.0f;
	this->maxParticles = 10;

	this->root = nullptr;

	this->currentParticleCnt = 0.0f;

	this->accumulatedTime = 0.0f;

	return true;
}

bool EmitterPlayerSpawn::InitializeBuffers(ID3D11Device * device)
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

void EmitterPlayerSpawn::EmitParticles(float dT)
{
	bool emitParticle, found;
	float positionX, positionY, positionZ, velocity, red, green, blue;
	int index, i, j;

	// Check if it is time to emit a new particle or not.
	float particleThresshold = (1000.0f / this->particlesPerSecond);
	float timeOverflow = dT;
	int timeIndex = 0;
	while (this->accumulatedTime > particleThresshold)
	{
		this->accumulatedTime = this->accumulatedTime - particleThresshold;

		// If there are particles to emit then emit one per frame.
		if (this->currentParticleCnt < this->maxParticles)
		{
			// Now generate the randomized particle properties.
			positionX = 0.0f;
			positionY = 10.0f;
			positionZ = 0.0f;
			velocity = particleVelocity;
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;

			// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
			// We will sort using Z depth so we need to find where in the list the particle should be inserted.
			index = this->currentParticleCnt;
			found = false;
			
			ParticleContainer* node = this->root;
			ParticleContainer* last = node;
			ParticleContainer* toInsert = new ParticleContainer();
			// Define the particle that we want to insert into our particle list
			toInsert->me.x = positionX;
			toInsert->me.y = positionY;
			toInsert->me.z = positionZ;
			toInsert->me.scale = this->particleSize;
			toInsert->me.r = red;
			toInsert->me.g = green;
			toInsert->me.b = blue;
			toInsert->me.uCoord = 0.25f;
			toInsert->me.time = timeIndex * particleThresshold;
			toInsert->me.timeCap = 1.0f;
			toInsert->me.velocity = velocity;
			toInsert->me.active = true;
			toInsert->next = nullptr;

			//If the root was empty, set it as the root
			if (node == nullptr)
				node = toInsert;
			else
			{
				//While the node is further from the camera than the node toInsert
				while (node && node < toInsert)
				{
					last = node;
					node = node->next;
				}
				last->next = toInsert;
				toInsert->next = node;
			}

			this->currentParticleCnt++;
		}
		timeIndex++;
	}

	return;
}

void EmitterPlayerSpawn::UpdateParticles(float dT)
{
	ParticleContainer* node = this->root;
	while (node)
	{
		node->me.time += dT / (1000);
		//node->me.y = node->me.y - (node->me.velocity * dT / 1000);
		float x = 0, y = 0;
		float period = 8.0f, min = 0, max = 4.0f;
		float time = node->me.time * node->me.velocity;
		float width = 40;

		float size = node->me.time;

		Algorithm::GetEllipse(x, y, time, size, size);


		node->me.x = x;
		node->me.z = y;

		node = node->next;
	}
}

void EmitterPlayerSpawn::KillParticles()
{
	ParticleContainer* node = this->root;
	ParticleContainer* last = this->root;

	while (node)
	{
		//Apply deactivation logic
		node->me.active = node->me.time < node->me.timeCap;

		//Check if not active
		if (!node->me.active)
		{
			//If root
			if (node == this->root)
			{
				this->root = nullptr;
				delete node;
			}
			else
			{
				last->next = node->next;;
				delete node;
			}
			this->currentParticleCnt--;
		}
		last = node;
		node = node->next;
	}
}

bool EmitterPlayerSpawn::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	// Initialize vertex array to zeros at first.
	memset(this->vertices, 0, (sizeof(VertexType) * this->vertexCount));

	ParticleContainer* node = this->root;

	for (int i = 0; i < this->currentParticleCnt; i++)
	{
		//If the next node doesn't exist, return false. Our particle cnt is wrong
		if (!node)
		{
			return false;
		}
		this->vertices[i].position = DirectX::XMFLOAT4(node->me.x, node->me.y, node->me.z, node->me.scale);
		this->vertices[i].color = DirectX::XMFLOAT4(node->me.r, node->me.g, node->me.b, node->me.uCoord);
		//Get to next node
		node = node->next;
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

void EmitterPlayerSpawn::RenderBuffers(ID3D11DeviceContext * deviceContext)
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

#include "EmitterHolder.h"



EmitterHolder::EmitterHolder()
{
}


EmitterHolder::~EmitterHolder()
{
}

void EmitterHolder::ShutdownSpecific()
{
	this->currentParticleCnt = 0;
	this->particles.clear();
}

bool EmitterHolder::AddParticle(float x, float y, float z, float minSize, float maxSize, float r, float g, float b, float textureIndex, float time, float movingX, float movingZ)
{
	bool result = true;

	//Define the particle we want to insert
	Particle toInsert;
	toInsert.x = x;
	toInsert.y = y;
	toInsert.z = z;
	toInsert.originX = x;
	toInsert.originZ = z;
	toInsert.scale = minSize;
	toInsert.minScale = minSize;
	toInsert.maxScale = maxSize;
	toInsert.dX = movingX;
	toInsert.dZ = movingZ;
	toInsert.timeCap = time;
	toInsert.time = 0.0f;
	toInsert.active = true;
	toInsert.r = r;
	toInsert.g = g;
	toInsert.b = b;
	toInsert.a = 0.4f;
	toInsert.uCoord = textureIndex;
	if (this->currentParticleCnt < this->maxParticles)
	{
		//Insert it into our particle list
		if (this->particles.size())
		{

			int index = 0;
			for (auto element : this->particles)
			{
				if (toInsert < element)
				{
					break;
				}
				index++;
			}
			this->particles.insert(this->particles.begin() + index, toInsert);
		}
		else
		{
			this->particles.push_back(toInsert);
		}
		this->currentParticleCnt++;
	}
	else
		result = false;
	return result;
}

bool EmitterHolder::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture, float timeLimit)
{
	bool result = false;
	//Set the texture
	this->texture = texture;
	this->world = DirectX::XMMatrixIdentity();
	this->emitterTime = timeLimit;

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

bool EmitterHolder::UpdateSpecific(float dT, ID3D11DeviceContext * deviceContext)
{
	bool result = false;
	this->accumulatedTime /= 1000000;

	//Release old particles
	this->KillParticles();

	//Update the particles
	this->UpdateParticles(dT);

	//Update the dynamic vertex buffer with the new position of each particle
	result = this->UpdateBuffers(deviceContext);
	if (!result)
		return false;

	return true;
}

void EmitterHolder::Render(ID3D11DeviceContext * deviceContext, ParticleShaderParameters * emitterParameters, int & amountOfParticles)
{
	this->RenderBuffers(deviceContext);

	emitterParameters->worldMatrix = this->world;
	emitterParameters->diffTexture = this->texture;
	amountOfParticles = this->currentParticleCnt;
}

int EmitterHolder::GetIndexCount()
{
	return this->indexCount;
}

bool EmitterHolder::SortParticles()
{
	return true;
}

bool EmitterHolder::IsCompleted()
{
	return false;
}

bool EmitterHolder::InitializeEmitter()
{
	this->height = 6.0f;
	this->maxParticles = 3000;
	this->isCompleted = false;
	this->currentParticleCnt = 0.0f;
	this->accumulatedTime = 0.0f;

	return true;
}

bool EmitterHolder::InitializeBuffers(ID3D11Device * device)
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

void EmitterHolder::UpdateParticles(float dT)
{
	Particle_Update up(dT / 1000000);
	std::transform(this->particles.begin(), this->particles.end(), this->particles.begin(), up);
}

void EmitterHolder::KillParticles()
{
	this->particles.erase(std::remove_if(this->particles.begin(), this->particles.end(), [](Particle p) { return !p.active; }), this->particles.end());
	this->currentParticleCnt = this->particles.size();
}

bool EmitterHolder::UpdateBuffers(ID3D11DeviceContext * deviceContext)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;

	// Initialize vertex array to zeros at first.
	memset(this->vertices, 0, (sizeof(VertexType) * this->vertexCount));
	int index = 0;
	for (auto node : this->particles)
	{
		//If the next node doesn't exist, return false. Our particle cnt is wrong
		this->vertices[index].position = DirectX::XMFLOAT4(node.x, node.y, node.z, node.scale);
		this->vertices[index].color = DirectX::XMFLOAT4(node.r, node.g, node.b, node.a);
		this->vertices[index].particleIndex = node.uCoord;
		index++;
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

void EmitterHolder::RenderBuffers(ID3D11DeviceContext * deviceContext)
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

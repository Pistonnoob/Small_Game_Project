#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter()
{
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

	/*if (this->indexBuffer)
	{
		this->indexBuffer->Release();
		this->indexBuffer = nullptr;
	}*/

	if (this->instanceBuffer)
	{
		this->instanceBuffer->Release();
		this->instanceBuffer = nullptr;
	}

	if (this->texture)
		this->texture = nullptr;

	if (this->vertices)
	{
		delete[] this->vertices;
		this->vertices = nullptr;
	}

	if (this->instances)
	{
		delete[] this->instances;
		this->instances = 0;
	}

	this->ShutdownSpecific();
}

bool ParticleEmitter::Initialize(ID3D11Device * device, ID3D11ShaderResourceView * texture)
{
	bool result = false;
	//Set the texture
	this->texture = texture;
	this->world = DirectX::XMMatrixIdentity();
	this->vertexBuffer = nullptr;
	this->instanceBuffer = nullptr;
	this->vertexCount = this->instanceCount = 0;
	this->maxParticles = 5000;
	this->currentParticleCnt = 0;
	this->accumulatedTime = 0.0f;



	//Initialize the buffers
	result = this->InitializeBuffers(device);
	if (!result)
		return false;

	return true;
}

bool ParticleEmitter::Update(float dT, ID3D11DeviceContext * deviceContext)
{
	// Increment the frame time.
	this->accumulatedTime += dT;
	return this->UpdateSpecific(dT, deviceContext);
}

bool ParticleEmitter::InitializeBuffers(ID3D11Device * device)
{
	unsigned long* indices;
	int i;
	D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData,	instanceData;
	HRESULT result;


	// Set the maximum number of vertices in the vertex array.
	this->vertexCount = 1;


	// Create the vertex array for the particles that will be rendered.
	this->vertices = new VertexType[this->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * vertexCount));
	vertices[0].position = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 2.0f);
	vertices[0].color = DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f);

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
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

	//Set the number of instances in the array
	this->instanceCount = this->maxParticles;

	//Create the instance array
	this->instances = new InstanceType[this->instanceCount];
	if (!instances)
	{
		return false;
	}

	// Load the instance array with data
	for (int i = 0; i < this->instanceCount; i++)
	{
		this->instances[i].position = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		this->instances[i].color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//Set up the description of the instance buffer
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * this->instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	//Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &this->instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	/*delete[] instances;
	instances = nullptr;*/


	return true;
}

void ParticleEmitter::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	unsigned int strides[2];
	unsigned int offsets[2];

	ID3D11Buffer* bufferPointers[2];


	// Set vertex buffer stride and offset.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(InstanceType);

	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = this->vertexBuffer;
	bufferPointers[1] = this->instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the index buffer to active in the input assembler so it can be rendered.
	/*deviceContext->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
*/
	// Set the type of primitive that should be rendered from this vertex buffer.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	return;
}



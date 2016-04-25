#include "ParticleHandler.h"



ParticleHandler::ParticleHandler()
{
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
}


ParticleHandler::~ParticleHandler()
{
}

void ParticleHandler::Shutdown()
{
	if (this->vertexBuffer)
	{
		this->vertexBuffer->Release();
		this->vertexBuffer = NULL;
	}

	if (this->indexBuffer)
	{
		this->indexBuffer->Release();
		this->indexBuffer = NULL;
	}

}

void ParticleHandler::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	HRESULT hresult;
	bool result = true;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	this->world = DirectX::XMMatrixIdentity();

	int particleCnt = _countof(this->particles);
	//sizeof(this->particles) / sizeof(Particle)
	for (int i = 0; i < particleCnt; i++)
	{
		this->particles[i] = Particle();

		this->particles[i].scale = 10.0f;
		this->particles[i].x = 0.0f + i * particles[i].scale;
		this->particles[i].y = 0.0f + i * particles[i].scale;
		this->particles[i].z = 0.0f + i * particles[i].scale;

		this->particles[i].r = 0.0f;
		this->particles[i].g = 0.0f;
		this->particles[i].b = 1.0f;
		this->particles[i].rotation = 0.0f;
	}

	for (int i = 0; i < particleCnt; i++)
	{
		this->vertices[i] = VertexType();
		this->vertices[i].position = DirectX::XMFLOAT4(this->particles[i].x, this->particles[i].y, this->particles[i].z, this->particles[i].scale);
		this->vertices[i].color = DirectX::XMFLOAT4(this->particles[i].r, this->particles[i].g, this->particles[i].b, this->particles[i].rotation);
	}

	//Set the description of the static vertex buffer
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * particleCnt;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = &this->vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create the vertex buffer
	hresult = device->CreateBuffer(&vertexBufferDesc, &vertexData, &this->vertexBuffer);
	if (FAILED(hresult)) {
		result = false;
	}

	unsigned long* indices = nullptr;
	//Create the index array
	indices = new unsigned long[particleCnt];
	if (!indices) {
		result = false;
	}

	//Set up the description of the static index buffer
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * particleCnt;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	ZeroMemory(&indexData, sizeof(indexData));
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create the index buffer
	hresult = device->CreateBuffer(&indexBufferDesc, &indexData, &this->indexBuffer);
	if (FAILED(hresult)) {
		result = false;
	}

}

void ParticleHandler::OnNotify(const Entity * entity, Events::ENTITY evnt)
{
	switch (evnt)
	{
	case Events::CREATED:
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
}

int ParticleHandler::Render(GraphicHandler * gHandler, CameraHandler * camera)
{
	int result = 0;

	return result;
}

int ParticleHandler::CreateEmitterParabola(ID3D11ShaderResourceView * texture)
{
	return 0;
}

int ParticleHandler::CreateEmitterCircle(ID3D11ShaderResourceView * texture)
{
	return 0;
}

int ParticleHandler::CreateEmitterEllipse(ID3D11ShaderResourceView * texture, int widthConstant, int heightConstant)
{
	return 0;
}

int ParticleHandler::CreateEmitterLissajous(ID3D11ShaderResourceView * texture, int widthConstant, int heightConstant, int xLobes, int yLobes)
{
	return 0;
}

int ParticleHandler::CreateEmitterHypotrochoid(ID3D11ShaderResourceView * texture, int circleRadius, int containedCircleRadius, int pointOffset)
{
	return 0;
}
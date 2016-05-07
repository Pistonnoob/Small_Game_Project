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

	this->myTextures.Shutdown();

	while (this->emitters.size())
	{
		ParticleEmitter* emitter = this->emitters.back();
		emitter->Shutdown();
		delete emitter;
		emitter = nullptr;
		this->emitters.pop_back();
	}
	this->emitters.clear();

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

	this->myTextures = Texture();
	std::string theNightSky = "Particles.mtl";
	bool victory = this->myTextures.Initialize(device, deviceContext, theNightSky);

	EmitterPrototype* newEmitter = new EmitterPrototype();
	newEmitter->Initialize(device, this->myTextures.GetTexture(0));
	this->emitters.push_back(newEmitter);

	int particleCnt = _countof(this->particles);
	//sizeof(this->particles) / sizeof(Particle)
	for (int i = 0; i < particleCnt; i++)
	{
		this->particles[i] = Particle();

		this->particles[i].scale = 1.0f;
		this->particles[i].x = 0.0f + i * particles[i].scale * 1.0f;
		this->particles[i].y = 0.0f + i * particles[i].scale * 1.0f;
		this->particles[i].z = 0.0f + i * particles[i].scale * 1.0f;

		this->particles[i].r = 0.0f + i * (i / float(particleCnt));
		this->particles[i].g = 0.0f;
		this->particles[i].b = 1.0f - i * (i / (float)particleCnt);
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
	for (int i = 0; i < particleCnt; i++)
	{
		indices[i] = i;
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

	delete[] indices;
}

void ParticleHandler::OnNotify(Entity * entity, Events::ENTITY evnt)
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

void ParticleHandler::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{
}

void ParticleHandler::OnNotify(Entity * entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets)
{
}

void ParticleHandler::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay)
{
}

void ParticleHandler::OnNotify(Entity * entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay, float arcOnSplit, int projectilesOnSplit)
{
}

void ParticleHandler::OnNotify(Entity * entity, Events::PICKUP evnt)
{
}

int ParticleHandler::Update(float dT, ID3D11DeviceContext * deviceContext)
{
	int result = 0;

	for (auto emitter = this->emitters.begin(); emitter != this->emitters.end(); emitter++)
	{
		(*emitter)->Update(dT, deviceContext);
	}

	return result;
}

int ParticleHandler::Render(GraphicHandler * gHandler, CameraHandler * camera)
{
	int result = 0;

	//this->RenderBuffers(gHandler->GetDeviceContext());

	ParticleShaderParameters parameters;

	/*for (auto emitter = this->emitters.begin(); emitter != this->emitters.end(); emitter++)
	{
		int amount
	}*/
	if (this->emitters.size())
	{
		int amountOfParticles = 0;
		this->emitters.at(0)->SetCameraPos(camera->GetCameraPos());
		this->emitters.at(0)->SortParticles();
		this->emitters.at(0)->Render(gHandler->GetDeviceContext(), parameters, amountOfParticles);
		parameters.worldMatrix = this->world;
		parameters.diffTexture = this->myTextures.GetTexture(1);

		gHandler->ParticleRender(&parameters, camera, amountOfParticles);
	}


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

int ParticleHandler::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	unsigned int stride;
	unsigned offset;

	//Set vertex buffer stride and offset
	int result = 0;
	stride = sizeof(VertexType);
	offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	return result;
}
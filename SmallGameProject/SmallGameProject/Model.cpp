#include "Model.h"

Model::Model()
{
	this->vertexBuffer = nullptr;
	this->indexBuffer = nullptr;
}

Model::~Model()
{
}

bool Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename)
{
	Vertex* vertices;
	unsigned long* indices = nullptr;
	int sizeVertices = 0;
	int sizeIndices = 0;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT hresult;
	bool result;

	//Set the number of vertices in the vertex array
	this->vertexCount = 3;
	//Set the numer of indices in the index array
	this->indexCount = 3;

	//Create the vertex array
	vertices = new Vertex[this->vertexCount];
	if (!vertices) {
		return false;
	}

	//Create the index array
	indices = new unsigned long[this->indexCount];
	if (!indices) {
		return false;
	}

	//Load the vertex array with data
	//Order is important, otherwise the triangle will be facing the opposite direction
	vertices[0].position = DirectX::XMFLOAT3(-1.0, -1.0f, 0.0f); //Bottom left
	vertices[0].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

	vertices[1].position = DirectX::XMFLOAT3(0.0, 1.0f, 0.0f); //Top Middle
	vertices[1].texture = DirectX::XMFLOAT2(0.5f, 0.0f);

	vertices[2].position = DirectX::XMFLOAT3(1.0, -1.0f, 0.0f); //Bottom right
	vertices[2].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	//Load the index array with data
	indices[0] = 0;	//Bottom left
	indices[1] = 1;	//Top Middle
	indices[2] = 2;	//Bottom right

	//Set the description of the static vertex buffer
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * this->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create the vertex buffer
	hresult = device->CreateBuffer(&vertexBufferDesc, &vertexData, &this->vertexBuffer);
	if (FAILED(hresult)) {
		return false;
	}

	//Set up the description of the static index buffer
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * this->indexCount;
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
		return false;
	}

	this->worldMatrix = DirectX::XMMatrixIdentity();
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned offset;

	//Set vertex buffer stride and offset
	stride = sizeof(Vertex);
	offset = 0;

	//Set the vertex buffer to active in the input assembly so it can rendered
	deviceContext->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &offset);

	//Set the index buffer to active in the input assembler so it can be rendered
	deviceContext->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Set the type od primitiv that should be rendered from this vertex buffer, in this case triangles
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void Model::Shutdown()
{
	if (this->vertexBuffer) {
		this->vertexBuffer->Release();
		this->vertexBuffer = nullptr;
	}

	if (this->indexBuffer) {
		this->indexBuffer->Release();
		this->indexBuffer = nullptr;
	}
}
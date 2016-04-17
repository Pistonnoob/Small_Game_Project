#ifndef MODEL_H
#define MODEL_H

#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "Texture.h"
#include "ShaderStructLibrary.h"

class Model {

public:
	struct Vertex {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
		DirectX::XMFLOAT3 normal;

		Vertex()
		{
			position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			texture = DirectX::XMFLOAT2(0.0f, 0.0f);
			normal = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		}
	};

private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int vertexCount;
	int indexCount;
	std::vector<int> subsetIndices;
	std::vector<std::string> materialNames;
	Texture* texture;
	DirectX::XMMATRIX worldMatrix;
	std::vector<DirectX::XMFLOAT3> vertPositions;

public:
	Model();
	~Model();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string objFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	void SetWorldMatrix(DirectX::XMMATRIX worldMatrix);
	void GetWorldMatrix(DirectX::XMMATRIX& worldMatrix);

	int GetVertexCount();

	void GetDeferredShaderParameters(DeferredShaderParameters* params);

	bool Model::LoadObj(const char* filename, std::vector<Vertex>* outputVertices, unsigned long*& outputIndices, std::string& materialLib);
};

#endif
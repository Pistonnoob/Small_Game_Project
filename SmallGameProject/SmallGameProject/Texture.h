#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <directxmath.h>
#include <string>
#include <vector>

class Texture {
public:
	struct Material
	{
		std::string name;
		DirectX::XMFLOAT4 diffColor;
		DirectX::XMFLOAT4 ambientColor;
		DirectX::XMFLOAT4 specColor;
		bool hasTexture;
		int textureIndex;
		bool hasNormMap;
		int normMapIndex;
	};
private:
	std::vector<ID3D11ShaderResourceView*> textureViews;
	std::vector<Material> materials;
	std::vector<std::string> textureNames;
public:
	Texture();
	~Texture();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string mtlFilename);
	void Shutdown();
};

#endif
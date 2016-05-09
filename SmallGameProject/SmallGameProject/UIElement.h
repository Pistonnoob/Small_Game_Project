#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

#include "Texture.h"

class UIElement {
private:
	struct VertexSimple {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	Texture texture;

	int width;
	int height;
	int posX;
	int posY;
	bool clickAble;
	int activeTexture;
	int nrOfTextures;
public:
	UIElement();
	~UIElement();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int width, int height, int posX, int posY, std::string& textureMtl, int nrOfTextures, bool clickAble);
	void Render(ID3D11DeviceContext* deviceContext);
	void Shutdown();

	bool IsClicked(DirectX::XMFLOAT2 mousePos);
	void ChangeTexture(int textureIndex);
};

#endif
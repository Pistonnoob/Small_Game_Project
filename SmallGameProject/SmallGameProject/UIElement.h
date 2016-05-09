#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <d3d11.h>
#include <DirectXMath.h>

class UIElement {
private:
	struct VertexSimple {
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
public:
	UIElement();
	~UIElement();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int width, int height, int posX, int posY, char* textureFilename, bool clickAble);
	void Render(ID3D11DeviceContext* deviceContext);
	void Shutdown();
};

#endif
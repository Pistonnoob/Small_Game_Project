#include "ScreenQuad.h"

ScreenQuad::ScreenQuad()
{
	this->vertexBuffer = nullptr;
	this->indexBuffer = nullptr;
}

ScreenQuad::~ScreenQuad()
{
}

bool ScreenQuad::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int screenWidth, int screenHeight)
{


	return true;
}
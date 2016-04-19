#ifndef GRAPHICHANDLER_H
#define GRAPHICHANDLER_H

#include "D3DHandler.h"
#include "DeferredShaderHandler.h"
#include "LightShaderHandler.h"
#include "ScreenQuad.h"
#include "TextHandler.h"

const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicHandler 
{
protected:
	D3DHandler* engine;
	DeferredShaderHandler* deferredShaderH;
	LightShaderHandler* lightShaderH;
	ScreenQuad* screenQuad;
	TextHandler* textH;

	int screenWidth;
	int screenHeight;

	DirectX::XMMATRIX perspectiveMatrix;
	DirectX::XMMATRIX orthographicMatrix;
public:
	GraphicHandler();
	virtual ~GraphicHandler();

	bool initialize(HWND* hwnd, int screenWidth, int screenHeight, DirectX::XMMATRIX baseViewMatrix);
	void DeferredRender(int indexCount, int indexStart, DeferredShaderParameters* shaderParams);
	void LightRender(LightShaderParameters* shaderParams);
	void TextRender();
	void Shutdown();

	void ClearRTVs();
	void SetDeferredRTVs();
	void SetLightRTV();

	void PresentScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	int CreateTextHolder(int maxLength);
	bool UpdateTextHolder(int id, const std::string& text, int posX, int posY, const DirectX::XMFLOAT3& color);
};

#endif

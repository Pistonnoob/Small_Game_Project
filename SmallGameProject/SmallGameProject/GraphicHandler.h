#ifndef GRAPHICHANDLER_H
#define GRAPHICHANDLER_H

#include <D3D11.h>
#include "D3DHandler.h"
#include "DeferredShaderHandler.h"
#include "LightShaderHandler.h"
#include "ParticleShaderHandler.h"
#include "ShadowShaderHandler.h"
#include "ScreenQuad.h"
#include "TextHandler.h"
#include "Model.h"
#include "CameraHandler.h"
#include "LightStructs.h"

const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicHandler 
{
protected:
	D3DHandler* engine;
	DeferredShaderHandler* deferredShaderH;
	LightShaderHandler* lightShaderH;
	ParticleShaderHandler* particleShaderH;
	ShadowShaderHandler* shadowShaderH;
	ScreenQuad* screenQuad;
	TextHandler* textH;
	ID3D11BlendState* transparencyBlendState;
	ID3D11BlendState* disableTransparencyBlendState;
	ID3D11BlendState* textTransparencyBlendState;

	
	int screenWidth;
	int screenHeight;

	DirectX::XMMATRIX perspectiveMatrix;
	DirectX::XMMATRIX orthographicMatrix;
	DirectX::XMMATRIX baseViewMatrix;

	DirectionalLight dirLight;
	std::vector<PointLight> pointLights;

	int activeRTV;

private:
	void SetDeferredRTVs();
	void SetLightRTV();
	void SetParticleRTV();
	void SetShadowRTV();

	DirectX::XMMATRIX lightPerspective;
	DirectX::XMMATRIX lightView;

	DirectX::XMFLOAT4 lightPos;
public:
	GraphicHandler();
	virtual ~GraphicHandler();

	bool initialize(HWND* hwnd, int screenWidth, int screenHeight, DirectX::XMMATRIX baseViewMatrix);
	
	void DeferredRender(Model* model, CameraHandler* camera);

	
	void LightRender(DirectX::XMFLOAT4 camPos);
	void ParticleRender(ParticleShaderParameters* shaderParams, CameraHandler* camera, int amountOfParticles);
	void ShadowRender(Model* model, CameraHandler* camera);

	void TextRender();
	void Shutdown();

	void ClearRTVs();

	void PresentScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	int CreateTextHolder(int maxLength);
	bool UpdateTextHolder(int id, const std::string& text, int posX, int posY, const DirectX::XMFLOAT3& color, float size);

	void SetDirectionalLight(DirectionalLight light);
	void AddPointLight(PointLight light);
	void UpdatePointLight(int index, PointLight newLight);
	void RemovePointLight(int index);
	void RemoveAllPointLights();
};

#endif

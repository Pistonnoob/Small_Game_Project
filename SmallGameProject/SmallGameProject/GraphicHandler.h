#ifndef GRAPHICHANDLER_H
#define GRAPHICHANDLER_H

#include "D3DHandler.h"
#include "DeferredShaderHandler.h"
#include "LightShaderHandler.h"
#include "ScreenQuad.h"

class GraphicHandler 
{
protected:
	D3DHandler* engine;
	DeferredShaderHandler* deferredShaderH;
	LightShaderHandler* lightShaderH;
	ScreenQuad* screenQuad;

	int screenWidth;
	int screenHeight;

public:
	GraphicHandler();
	virtual ~GraphicHandler();

	bool initialize(HWND hwnd, int screenWidth, int screenHeight);
	void DeferredRender();
	void LightRender();
	void Shutdown();
};

#endif

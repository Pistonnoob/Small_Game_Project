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

public:
	GraphicHandler();
	GraphicHandler(HWND &window);
	virtual ~GraphicHandler();

	bool setWindow(HWND &setWindow);
	bool initialize();
};

#endif

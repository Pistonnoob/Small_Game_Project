#ifndef GRAPHICHANDLER_H
#define GRAPHICHANDLER_H
#include "D3DHandler.h"


class GraphicHandler 
{
protected:
	D3DHandler* engine;
public:
	GraphicHandler();
	GraphicHandler(HWND &window);
	virtual ~GraphicHandler();

	bool setWindow(HWND &setWindow);
	bool initialize();
};

#endif

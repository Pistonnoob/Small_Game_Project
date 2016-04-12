#ifndef GRAPHICHANDLER_H
#define GRAPHICHANDLER_H
#include "D3DHandler.h"


class GraphicHandler 
{
protected:
	D3DHandler* engine;
public:
	GraphicHandler();
	virtual ~GraphicHandler();

	bool setWindow(HWND &setWindow);
};

#endif

#include "GraphicHandler.h"

GraphicHandler::GraphicHandler()
{
	this->engine = new D3DHandler();
}

GraphicHandler::~GraphicHandler()
{
	delete this->engine;
	this->engine = nullptr;
}

bool GraphicHandler::setWindow(HWND & setWindow)
{
	this->engine;
	return false;
}



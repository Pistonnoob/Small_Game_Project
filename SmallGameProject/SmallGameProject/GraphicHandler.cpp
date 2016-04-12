#include "GraphicHandler.h"

GraphicHandler::GraphicHandler()
{
	this->engine = new D3DHandler();
}

GraphicHandler::GraphicHandler(HWND & window)
{
	this->engine = new D3DHandler(window);
}

GraphicHandler::~GraphicHandler()
{
	delete this->engine;
	this->engine = nullptr;
}

bool GraphicHandler::setWindow(HWND & setWindow)
{
	this->engine->setWindowToEngine(setWindow);
	return true;
}

bool GraphicHandler::initialize()
{
	std::string errorMessage;

	try
	{
		this->engine->initialize();
	}

	catch (char* e)
	{
		errorMessage = e;
	}
	
	return false;
}



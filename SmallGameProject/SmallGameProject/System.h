#ifndef SYSTEM_H
#define SYSTEM_H

#include <Windows.h>
#include "GameStateHandler.h"
#include "GraphicHandler.h"
#include "InputHandler.h"

class System {

private:
	HWND hwnd;
	HINSTANCE hinstance;
	LPCWSTR applicationName;

	GameStateHandler* gameSH;
	GraphicHandler* graphicH;
	InputHandler* inputH;

	void InitWindow(int& screenWidth, int& screenHeight);
	void ShutdownWindow();
	bool Frame(float);

public:
	System();
	~System();

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static System* ApplicationHandle = nullptr;

#endif

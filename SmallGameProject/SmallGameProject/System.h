#ifndef SYSTEM_H
#define SYSTEM_H

#include <Windows.h>
#include "GameStateHandler.h"
#include "GraphicHandler.h"
#include "InputHandler.h"
#include "Model.h"
#include "CameraHandler.h"

#include "Ai.h"

const bool FULL_SCREEN = false;

class System {

private:
	HWND hwnd;
	HINSTANCE hinstance;
	LPCWSTR applicationName;

	GameStateHandler* gameSH;
	GraphicHandler* graphicH;
	InputHandler* inputH;
	CameraHandler* cameraH;

	void InitWindow(int& screenWidth, int& screenHeight);
	void ShutdownWindow();
	bool Update(float dTime);

	Model* testModel;
	Model* testModelGround;

    Ai* AI;
    Enemy* entity;
    vector<Enemy*> enemies;

	float testRot;
public:
	System();
	~System();

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT unmessage, WPARAM wparam, LPARAM lparam);
static System* ApplicationHandle = nullptr;

#endif

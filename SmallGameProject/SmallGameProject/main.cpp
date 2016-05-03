//FIRST!!

//#include <windows.h>
#include "System.h"
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <crtdbg.h>
#include "DXGIDebug.h"

void CreateConsole()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CreateConsole();

	printf("Console is working yao!\n");

	//MessageBox(NULL, L"TestBox", L"TestBox", MB_ICONEXCLAMATION | MB_OK);
	System* sH;
	bool result;

	//Create the system object
	sH = new System;

	if (!sH) {
		return 0;
	}

	//Initialize and run the system object
	result = sH->Initialize();
	if (result) {
		sH->Run();
	}

	//Shutdown and release the system object
	sH->Shutdown();
	delete sH;
	sH = nullptr;
	return 0;
}
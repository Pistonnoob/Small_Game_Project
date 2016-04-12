#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <dinput.h>

class InputHandler {

private:
	LPDIRECTINPUT8 directInput;
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
	DIMOUSESTATE DIMouseState;

	int mouseX;
	int mouseY;
	int screenWidth;
	int screenHeight;

public:
	InputHandler();
	~InputHandler();

	void Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight );
	void ShutDown();
};

#endif

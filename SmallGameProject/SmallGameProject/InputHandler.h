#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <dinput.h>
#include <DirectXMath.h>

class InputHandler {

private:
	LPDIRECTINPUT8 directInput;
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
	DIMOUSESTATE DIMouseState;
	bool KeyboarState[256];

	int mouseX;
	int mouseY;
	int screenWidth;
	int screenHeight;
	unsigned int lastKeyPressed;

	void ReadKeyboard();
	void ReadMouse();
	void ProcessInput();
	DirectX::XMVECTOR GetMouseDeltaPos();

public:
	InputHandler();
	~InputHandler();

	void Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight );
	void Shutdown();
	void Update();

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	bool isKeyDown(unsigned int key);
	bool isKeyReleased(unsigned int key);

};

#endif

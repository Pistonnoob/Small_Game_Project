#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include <DirectXMath.h>

class InputHandler {

private:
	IDirectInput8* directInput;
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;
	DIMOUSESTATE DIMouseState;
	unsigned char KeyboarState[256];
	unsigned char OldKeyboardState[256];

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

	void Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	void Update();

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	bool isKeyPressed(unsigned int key);
	bool isKeyDown(unsigned int key);
	bool isKeyReleased(unsigned int key);

	DirectX::XMFLOAT2 getMousePos();
	DirectX::XMFLOAT2 getMousePosInWindow();
};

#endif
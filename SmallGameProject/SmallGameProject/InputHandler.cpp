#include "InputHandler.h"

InputHandler::InputHandler()
{
	this->DIKeyboard = nullptr;
	this->DIMouse = nullptr;
}

InputHandler::~InputHandler()
{

}

void InputHandler::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT hr;
	//Mouse initial starting position set to the midle of the screen
	SetPhysicalCursorPos((GetSystemMetrics(SM_CXSCREEN)) / 2, (GetSystemMetrics(SM_CYSCREEN)) / 2);
	this->mouseX = (GetSystemMetrics(SM_CXSCREEN)) / 2;
	this->mouseY = (GetSystemMetrics(SM_CYSCREEN)) / 2;
	//Save the resolution for future use
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	//Initialize the DirectInput Object
	hr = DirectInput8Create(
		hInstance,					// Instance handle to the application
		DIRECTINPUT_VERSION,		//	dwVersion
		IID_IDirectInput8,			//	RefiID, Unique identifier of the desired interface
		(void**)&this->directInput,	//	The pointer who will recive the object
		NULL );						//	LPUNKNOWN punkOuter

	//Check if the object has been created
	if (FAILED(hr)) {
		MessageBox(hwnd, L"DirectInput8Create", L"Error", MB_OK);
	}

	//Create the keyboard device
	hr = this->directInput->CreateDevice(
		GUID_SysKeyboard,					// What type of device
		&this->DIKeyboard,					// Pointer who will recive the object
		NULL);								//	LPUNKNOWN punkOuter

	//Check if the keyboard object has been created
	if (SUCCEEDED(hr)) {

		//Set the options for the keyboard
		hr = this->DIKeyboard->SetDataFormat(&c_dfDIKeyboard);	// Data format of the device

		if (FAILED(hr)) {
			MessageBox(hwnd, L"SetDataFormat_Keyboard", L"Error", MB_OK);
		}
		
		hr = this->DIKeyboard->SetCooperativeLevel(
			hwnd,
			DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND
			);

		if (FAILED(hr)) {
			MessageBox(hwnd, L"SetCooperativeLevel_Keyboard", L"Error", MB_OK);
		}

		hr = this->DIKeyboard->Acquire();	//Aquire the keyboard

		if (FAILED(hr)) {
			MessageBox(hwnd, L"Acquire_Keyboard", L"Error", MB_OK);
		}

	}
	else {
		MessageBox(hwnd, L"CreateDevice_Keyboard", L"Error", MB_OK);
	}

	//Create the Mouse mouse device
	hr = this->directInput->CreateDevice(
		GUID_SysMouse,
		&this->DIMouse,
		NULL);

	//Check if the mouse object has been created
	if (SUCCEEDED(hr)) {

		//Set the options for the mouse
		hr = this->DIMouse->SetDataFormat(&c_dfDIMouse);	// Data format of the device

		if (FAILED(hr)) {
			MessageBox(hwnd, L"SetDataFormat_Mouse", L"Error", MB_OK);
		}

		hr = this->DIMouse->SetCooperativeLevel(
			hwnd,
			DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND
			);

		if (FAILED(hr)) {
			MessageBox(hwnd, L"SetCooperativeLevel_Mouse", L"Error", MB_OK);
		}

		hr = this->DIMouse->Acquire();	//Aquire the mouse

		if (FAILED(hr)) {
			MessageBox(hwnd, L"Acquire_Mouse", L"Error", MB_OK);
		}

	}
	else {
		MessageBox(hwnd, L"CreateDevice_Mouse", L"Error", MB_OK);
	}

	return;
}

void InputHandler::ShutDown()
{
	if (this->DIKeyboard){
		this->DIKeyboard->Unacquire();
		this->DIKeyboard->Release();
		this->DIKeyboard = nullptr;
	}

	if (this->DIMouse) {
		this->DIMouse->Unacquire();
		this->DIMouse->Release();
		this->DIMouse = nullptr;
	}

	if (this->directInput) {
		this->directInput->Release();
		this->directInput = nullptr;
	}
}

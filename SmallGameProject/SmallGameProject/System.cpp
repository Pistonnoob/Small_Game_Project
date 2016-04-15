#include "System.h"

System::System()
{
	this->gameSH = nullptr;
	this->graphicH = nullptr;
	this->inputH = nullptr;

	this->testModel = nullptr;
}

System::~System()
{

}

bool System::Initialize()
{
	int screenWidth = 0;
	int screenHeight = 0;
	bool result;

	//Initilize the window api
	InitWindow(screenWidth, screenHeight);

	//Create the inputHandler

	//Initialize the InputHandler

	//Create the graphicHandler.
	this->graphicH = new GraphicHandler();
	//Initialize the graphicHandler
	this->graphicH->initialize(&this->hwnd, screenWidth, screenHeight);

	//Create the GameStateHandler.

	//Initialize the GameStateHandler
	this->testModel = new Model;

	result = this->testModel->Initialize(this->graphicH->GetDevice(), this->graphicH->GetDeviceContext(), "");
	if (!result) {
		return false;
	}

	return true;
}

void System::Run()
{
	MSG msg;
	bool done = false;
	bool result;

	LARGE_INTEGER frequency, currTime, prevTime, elapsedTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevTime);

	int fpsLimit = 60; //Limit the application fps

	//Initialize the message structure
	ZeroMemory(&msg, sizeof(MSG));

	//Loop until there is quit message from the window or the user
	while (!done) {

		//Handle the window messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//If windows signals to end the application then exit out
		if (msg.message == WM_QUIT) {
			done = true;
		}

		else {
			QueryPerformanceCounter(&currTime);
			elapsedTime.QuadPart = currTime.QuadPart - prevTime.QuadPart;
			elapsedTime.QuadPart *= 1000000;
			elapsedTime.QuadPart /= frequency.QuadPart;

			//if (elapsedTime.QuadPart > (1000000 / fpsLimit)) { //If it's time to render a frame ->
			result = this->Update((float)elapsedTime.QuadPart); //do the frame processing
			if (!result) {
				done = true;
			}
			prevTime = currTime;
			//}
		}
	}

	return;
}

void System::Shutdown()
{
	//Release the graphicsHandler
	if (this->graphicH) {
		this->graphicH->Shutdown();
		delete this->graphicH;
		this->graphicH = nullptr;
	}
	//Release the inputHandler
	//Release the GameStateHandler
	//Shutdown the window
	ShutdownWindow();
}

void System::InitWindow(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX;
	int posY;

	//Get an external pointer to this object
	ApplicationHandle = this;

	//Get the instance if this application
	this->hinstance = GetModuleHandle(NULL);

	//Give the application a name
	this->applicationName = L"Small game project";

	//Setup the window class with default values
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register the window class
	RegisterClassEx(&wc);

	//Determine the resolution of the client desktop screen
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Setup the screen settings depending on whatever 
	//it is running in full screen or in windowed mode
	if (FULL_SCREEN) {
		// If full screen, set the screen to maximum size of the user desktop and 32 bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//Change the display settings to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//Set the pposition of the window to the top left corner
		posX = posY = 0;

	}
	else {
		//If windowed then set it to 800x600
		screenWidth = 800;
		screenHeight = 600;

		//Place the window in the middle of the screen
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//Create the window with the screen settings and get the handle to it
	this->hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		this->applicationName,
		this->applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight,
		NULL, NULL,
		this->hinstance,
		NULL);

	// Bring the window up on the screen and set it as main focus
	ShowWindow(this->hwnd, SW_SHOW);
	SetForegroundWindow(this->hwnd);
	SetFocus(this->hwnd);

	//Hide/show the mouse cursor.
	ShowCursor(true);

	return;
}

void System::ShutdownWindow()
{
	//Show the mouse cursor if it was hidden.
	ShowCursor(true);

	//Fix the display settings if leaving full screen mode
	if (FULL_SCREEN) {
		ChangeDisplaySettings(NULL, 0);
	}

	//Remove the window
	DestroyWindow(this->hwnd);	//Expects this to clear memory
	this->hwnd = nullptr;

	//Remove the application instance
	UnregisterClass(this->applicationName, this->hinstance);
	this->hinstance = nullptr;

	//Release the pointer to this class
	ApplicationHandle = nullptr;

	return;

}

bool System::Update(float dTime) 
{
	/*DeferredShaderParameters* deferredShaderParams = new DeferredShaderParameters;

	this->graphicH->ClearRTVs();

	this->graphicH->SetDeferredRTVs();

	this->testModel->GetDeferredShaderParameters(deferredShaderParams);
	this->testModel->Render(this->graphicH->GetDeviceContext());
	this->graphicH->DeferredRender(3, 0, deferredShaderParams);

	this->graphicH->SetLightRTV();

	this->graphicH->LightRender();

	delete deferredShaderParams;*/

	return true;
}

LRESULT CALLBACK System::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		//Check if a key is pressed on the keyboard
	case WM_KEYDOWN:
	{
		//if key is pressed send it to the input object to be recorded
		
		return 0;
	}
	//Check if a key is released on the keyboard
	case WM_KEYUP:
	{
		//If a key is released then send it to the input object
		
		return 0;
	}

	//Any other message
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT unmessage, WPARAM wparam, LPARAM lparam)
{
	switch (unmessage)
	{
		//Check if the window is being destroyed
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	//Check if the window is being closed
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	//All other messages pass to the message handler in the system class
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, unmessage, wparam, lparam);
	}

	}
}
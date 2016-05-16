#include "StartState.h"
#include "GameStateHandler.h"


StartState::StartState()
{
	this->startGame = false;
	this->manualClearing = false;
	this->startModel = Model();
	this->camera = CameraHandler();
}

StartState::StartState(GameStateHandler * GSH)
{
	this->m_GSH = GSH;
}

StartState::~StartState()
{
}

void StartState::Shutdown()
{
	GameState::Shutdown();
	
	this->startModel.Shutdown();
}

int StartState::Initialize(GraphicHandler* gHandler, GameStateHandler* GSH)
{
	int result = 0;
	this->startModel = Model();
	this->manualClearing = false;
	//Initialize the base class GameState

	ID3D11Device* device = gHandler->GetDevice();
	ID3D11DeviceContext* deviceContext = gHandler->GetDeviceContext();

	result = this->InitializeBase(GSH, device, deviceContext);
	if (result)
	{
		//Proceed to initialize thyself
		bool modelResult = this->startModel.Initialize(device, deviceContext, "StartGame");
		DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 40.0f);
		worldMatrix *= DirectX::XMMatrixScaling(0.02f, 0.02f, 0.02f);
		worldMatrix = DirectX::XMMatrixRotationX(DirectX::XM_PI / 2) * worldMatrix;
		modelResult = this->camera.Initialize();
		this->startModel.SetWorldMatrix(worldMatrix);

		PointLight light;
		light.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		light.Ambient = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		light.Specular = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		light.Position = DirectX::XMFLOAT4(0.0f, 0.0f, -4.0f, 1.0f);
		light.Attenuation = DirectX::XMFLOAT4(50.0f, 1.0f, 0.09f, 0.032f);

		this->pointLights.push_back(light);
	}

	return result;
}

int StartState::HandleInput(InputHandler * input)
{
	int result = 0;
	if (
			input->isKeyPressed(DIK_SPACE) ||
			input->isKeyPressed(DIK_1) ||
			input->isKeyPressed(DIK_2) ||
			input->isKeyPressed(DIK_3) ||
			input->isKeyPressed(DIK_4) ||
			input->isKeyPressed(DIK_5) ||
			input->isKeyPressed(DIK_6) ||
			input->isKeyPressed(DIK_7) ||
			input->isKeyPressed(DIK_8) ||
			input->isKeyPressed(DIK_9) ||
			input->isKeyPressed(DIK_0) ||
			input->isKeyPressed(DIK_MINUS) ||
			input->isKeyPressed(DIK_EQUALS) ||
			input->isKeyPressed(DIK_BACK	) ||
			input->isKeyPressed(DIK_TAB) ||
			input->isKeyPressed(DIK_Q) ||
			input->isKeyPressed(DIK_W) ||
			input->isKeyPressed(DIK_E) ||
			input->isKeyPressed(DIK_R) ||
			input->isKeyPressed(DIK_T) ||
			input->isKeyPressed(DIK_Y) ||
			input->isKeyPressed(DIK_U) ||
			input->isKeyPressed(DIK_I) ||
			input->isKeyPressed(DIK_O) ||
			input->isKeyPressed(DIK_P) ||
			input->isKeyPressed(DIK_LBRACKET) ||
			input->isKeyPressed(DIK_RBRACKET) ||
			input->isKeyPressed(DIK_RETURN) ||
			input->isKeyPressed(DIK_LCONTROL) ||
			input->isKeyPressed(DIK_A) ||
			input->isKeyPressed(DIK_S) ||
			input->isKeyPressed(DIK_D) ||
			input->isKeyPressed(DIK_F) ||
			input->isKeyPressed(DIK_G) ||
			input->isKeyPressed(DIK_H) ||
			input->isKeyPressed(DIK_J) ||
			input->isKeyPressed(DIK_K) ||
			input->isKeyPressed(DIK_L) ||
			input->isKeyPressed(DIK_SEMICOLON) ||
			input->isKeyPressed(DIK_APOSTROPHE) ||
			input->isKeyPressed(DIK_GRAVE) ||
			input->isKeyPressed(DIK_LSHIFT) ||
			input->isKeyPressed(DIK_BACKSLASH) ||
			input->isKeyPressed(DIK_Z) ||
			input->isKeyPressed(DIK_X) ||
			input->isKeyPressed(DIK_C) ||
			input->isKeyPressed(DIK_V) ||
			input->isKeyPressed(DIK_B) ||
			input->isKeyPressed(DIK_N) ||
			input->isKeyPressed(DIK_M) ||
			input->isKeyPressed(DIK_COMMA) ||
			input->isKeyPressed(DIK_PERIOD) ||
			input->isKeyPressed(DIK_SLASH) ||
			input->isKeyPressed(DIK_RSHIFT) ||
			input->isKeyPressed(DIK_MULTIPLY) ||
			input->isKeyPressed(DIK_LMENU) ||
			input->isKeyPressed(DIK_SPACE) ||
			input->isKeyPressed(DIK_CAPITAL) ||
			input->isKeyPressed(DIK_F1) ||
			input->isKeyPressed(DIK_F2) ||
			input->isKeyPressed(DIK_F3) ||
			input->isKeyPressed(DIK_F4) ||
			input->isKeyPressed(DIK_F5) ||
			input->isKeyPressed(DIK_F6) ||
			input->isKeyPressed(DIK_F7) ||
			input->isKeyPressed(DIK_F8) ||
			input->isKeyPressed(DIK_F9) ||
			input->isKeyPressed(DIK_F10) ||
			input->isKeyPressed(DIK_NUMLOCK) ||
			input->isKeyPressed(DIK_SCROLL) ||
			input->isKeyPressed(DIK_NUMPAD7) ||
			input->isKeyPressed(DIK_NUMPAD8) ||
			input->isKeyPressed(DIK_NUMPAD9) ||
			input->isKeyPressed(DIK_SUBTRACT) ||
			input->isKeyPressed(DIK_NUMPAD4) ||
			input->isKeyPressed(DIK_NUMPAD5) ||
			input->isKeyPressed(DIK_NUMPAD6) ||
			input->isKeyPressed(DIK_ADD) ||
			input->isKeyPressed(DIK_NUMPAD1) ||
			input->isKeyPressed(DIK_NUMPAD2) ||
			input->isKeyPressed(DIK_NUMPAD3) ||
			input->isKeyPressed(DIK_NUMPAD0) ||
			input->isKeyPressed(DIK_DECIMAL) ||
			input->isKeyPressed(DIK_OEM_102) ||
			input->isKeyPressed(DIK_F11) ||
			input->isKeyPressed(DIK_F12) ||
			input->isKeyPressed(DIK_F13) ||
			input->isKeyPressed(DIK_F14) ||
			input->isKeyPressed(DIK_F15) ||
			input->isKeyPressed(DIK_KANA	) ||
			input->isKeyPressed(DIK_ABNT_C1) ||
			input->isKeyPressed(DIK_CONVERT) ||
			input->isKeyPressed(DIK_NOCONVERT) ||
			input->isKeyPressed(DIK_YEN) ||
			input->isKeyPressed(DIK_ABNT_C2) ||
			input->isKeyPressed(DIK_NUMPADEQUALS) ||
			input->isKeyPressed(DIK_PREVTRACK) ||
			input->isKeyPressed(DIK_AT) ||
			input->isKeyPressed(DIK_COLON) ||
			input->isKeyPressed(DIK_UNDERLINE) ||
			input->isKeyPressed(DIK_KANJI) ||
			input->isKeyPressed(DIK_STOP	) ||
			input->isKeyPressed(DIK_AX) ||
			input->isKeyPressed(DIK_UNLABELED) ||
			input->isKeyPressed(DIK_NEXTTRACK) ||
			input->isKeyPressed(DIK_NUMPADENTER) ||
			input->isKeyPressed(DIK_RCONTROL	) ||
			input->isKeyPressed(DIK_MUTE) ||
			input->isKeyPressed(DIK_CALCULATOR) ||
			input->isKeyPressed(DIK_PLAYPAUSE) ||
			input->isKeyPressed(DIK_MEDIASTOP) ||
			input->isKeyPressed(DIK_VOLUMEDOWN) ||
			input->isKeyPressed(DIK_VOLUMEUP	) ||
			input->isKeyPressed(DIK_WEBHOME) ||
			input->isKeyPressed(DIK_NUMPADCOMMA) ||
			input->isKeyPressed(DIK_DIVIDE) ||
			input->isKeyPressed(DIK_SYSRQ) ||
			input->isKeyPressed(DIK_RMENU) ||
			input->isKeyPressed(DIK_PAUSE) ||
			input->isKeyPressed(DIK_HOME	) ||
			input->isKeyPressed(DIK_UP) ||
			input->isKeyPressed(DIK_PRIOR) ||
			input->isKeyPressed(DIK_LEFT	) ||
			input->isKeyPressed(DIK_RIGHT) ||
			input->isKeyPressed(DIK_END) ||
			input->isKeyPressed(DIK_DOWN	) ||
			input->isKeyPressed(DIK_NEXT	) ||
			input->isKeyPressed(DIK_INSERT) ||
			input->isKeyPressed(DIK_DELETE) ||
			input->isKeyPressed(DIK_LWIN	) ||
			input->isKeyPressed(DIK_RWIN	) ||
			input->isKeyPressed(DIK_APPS	) ||
			input->isKeyPressed(DIK_POWER) ||
			input->isKeyPressed(DIK_SLEEP) ||
			input->isKeyPressed(DIK_WAKE	) ||
			input->isKeyPressed(DIK_WEBSEARCH) ||
			input->isKeyPressed(DIK_WEBFAVORITES) ||
			input->isKeyPressed(DIK_WEBREFRESH) ||
			input->isKeyPressed(DIK_WEBSTOP) ||
			input->isKeyPressed(DIK_WEBFORWARD) ||
			input->isKeyPressed(DIK_WEBBACK) ||
			input->isKeyPressed(DIK_MYCOMPUTER) ||
			input->isKeyPressed(DIK_MAIL	) ||
			input->isKeyPressed(DIK_MEDIASELECT) ||
			input->isMouseKeyPressed(0) ||
			input->isMouseKeyPressed(1) ||
			input->isMouseKeyPressed(2) ||
			input->isMouseKeyPressed(3)
		)
	{
		this->startGame = true;
	}
	return result;
}

int StartState::Update(float deltaTime, InputHandler* input, GraphicHandler* gHandler)
{
	int result = 1;
	if (this->startGame)
	{
		this->startGame = false;
		//Create the menu and push it
 		MenuState* menu = new MenuState();
		menu->Initialize(gHandler, this->m_GSH);
		menu->SetManualClearing(false);
		this->m_GSH->PushState(menu);
	}
	return result;
}

int StartState::Render(GraphicHandler * gHandler, HWND hwnd)
{
	int result = 0;

	gHandler->DeferredRender(&this->startModel, &this->camera);

	gHandler->LightRender(this->camera.GetCameraPos(), this->pointLights);
	
	return result;
}

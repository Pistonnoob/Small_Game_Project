#include "CameraHandler.h"

#include <windows.h>
#include <Windows.h>

CameraHandler::CameraHandler()
{
	this->viewMatrix = DirectX::XMMatrixIdentity();
	this->cameraPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 0.0f);
    this->cameraPos2 = DirectX::XMFLOAT4(0, 0, 0, 0);
}
CameraHandler::~CameraHandler()
{

}

bool CameraHandler::Initialize()
{
	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	//DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f);
    DirectX::XMVECTOR camPos = DirectX::XMVectorSet(10, 15, -20, 0.0f);
	DirectX::XMVECTOR camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->viewMatrix = DirectX::XMMatrixLookAtLH(camPos, lookAt, camUp);

	return true;
}

void CameraHandler::GetViewMatrix(DirectX::XMMATRIX& viewMatrix)
{
	viewMatrix = this->viewMatrix;
}
DirectX::XMFLOAT4 CameraHandler::GetCameraPos()
{
	//DirectX::XMFLOAT4 camPosFloat;

	//DirectX::XMStoreFloat4(&camPosFloat, this->cameraPos);

	return this->cameraPos2;
}

void CameraHandler::updateCamera()
{
    //0x57 = W
    if (GetAsyncKeyState(0x57))
    {
        this->cameraPos2.z += 0.5f;
    }
    //0x53 = S
    if (GetAsyncKeyState(0x53))
    {
        this->cameraPos2.z -= 0.5f;
    }
    //0x44 = D
    if (GetAsyncKeyState(0x44))
    {
        this->cameraPos2.x += 0.5f;
    }
    //0x41 = A
    if (GetAsyncKeyState(0x41))
    {
        this->cameraPos2.x -= 0.5f;
    }
}

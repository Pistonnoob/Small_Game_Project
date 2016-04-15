#include "CameraHandler.h"

CameraHandler::CameraHandler()
{
	this->viewMatrix = DirectX::XMMatrixIdentity();
	this->cameraPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 0.0f);
}
CameraHandler::~CameraHandler()
{

}

bool CameraHandler::Initialize()
{
	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f);
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
	DirectX::XMFLOAT4 camPosFloat;

	DirectX::XMStoreFloat4(&camPosFloat, this->cameraPos);

	return camPosFloat;
}
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
	this->baseViewMatrix = this->viewMatrix;

	return true;
}

void CameraHandler::GetBaseViewMatrix(DirectX::XMMATRIX & baseViewMatrix)
{
	baseViewMatrix = this->baseViewMatrix;
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

void CameraHandler::SetCameraPos(DirectX::XMFLOAT3 newCamPos)
{
	this->cameraPos = DirectX::XMLoadFloat3(&newCamPos);
}

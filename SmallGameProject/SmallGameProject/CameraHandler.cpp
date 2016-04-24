#include "CameraHandler.h"

#include <windows.h>
#include <Windows.h>

CameraHandler::CameraHandler()
{
	this->viewMatrix = DirectX::XMMatrixIdentity();
	this->cameraPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f);
	this->lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	this->cameraUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
}
CameraHandler::~CameraHandler()
{

}

bool CameraHandler::Initialize()
{
	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f);
	DirectX::XMVECTOR camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->baseViewMatrix = DirectX::XMMatrixLookAtLH(camPos, lookAt, camUp);
	this->viewMatrix = DirectX::XMMatrixLookAtLH(this->cameraPos, this->lookAt, this->cameraUp);

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

DirectX::XMFLOAT3 CameraHandler::GetLookAt()
{
	DirectX::XMFLOAT3 lookAtFloat;

	DirectX::XMStoreFloat3(&lookAtFloat, this->lookAt);

	return lookAtFloat;
}

void CameraHandler::SetLookAt(DirectX::XMFLOAT3 newLookAt)
{
	this->lookAt = DirectX::XMLoadFloat3(&newLookAt);
}

DirectX::XMFLOAT3 CameraHandler::GetCameraUp()
{
	DirectX::XMFLOAT3 camUpFloat;

	DirectX::XMStoreFloat3(&camUpFloat, this->cameraUp);

	return camUpFloat;
}

void CameraHandler::SetCameraUp(DirectX::XMFLOAT3 newCamUp)
{
	this->cameraUp = DirectX::XMLoadFloat3(&newCamUp);
}

void CameraHandler::UpdateCamera()
{
	this->viewMatrix = DirectX::XMMatrixLookAtLH(this->cameraPos, this->lookAt, this->cameraUp);
}

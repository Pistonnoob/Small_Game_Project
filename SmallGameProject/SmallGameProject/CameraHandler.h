#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <DirectXMath.h>

class CameraHandler {
private:
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX baseViewMatrix;
	DirectX::XMVECTOR cameraPos;
	DirectX::XMVECTOR lookAt;
	DirectX::XMVECTOR cameraUp;

public:
	CameraHandler();
	~CameraHandler();

	bool Initialize();
	void GetBaseViewMatrix(DirectX::XMMATRIX& baseViewMatrix);
	void GetViewMatrix(DirectX::XMMATRIX& viewMatrix);

	DirectX::XMFLOAT4 GetCameraPos();
	void SetCameraPos(DirectX::XMFLOAT3 newCamPos);

	DirectX::XMFLOAT3 GetLookAt();
	void SetLookAt(DirectX::XMFLOAT3 newLookAt);

	DirectX::XMFLOAT3 GetCameraUp();
	void SetCameraUp(DirectX::XMFLOAT3 newCamUp);

	void UpdateCamera();
};

#endif
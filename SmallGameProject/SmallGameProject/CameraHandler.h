#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <DirectXMath.h>

class CameraHandler {
private:
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX baseViewMatrix;
	DirectX::XMVECTOR cameraPos;

public:
	CameraHandler();
	~CameraHandler();

	bool Initialize();
	void GetBaseViewMatrix(DirectX::XMMATRIX& baseViewMatrix);
	void GetViewMatrix(DirectX::XMMATRIX& viewMatrix);
	DirectX::XMFLOAT4 GetCameraPos();
	void SetCameraPos(DirectX::XMFLOAT3 newCamPos);
};

#endif
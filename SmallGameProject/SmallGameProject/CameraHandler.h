#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <DirectXMath.h>

class CameraHandler {
private:
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMVECTOR cameraPos;

public:
	CameraHandler();
	~CameraHandler();

	bool Initialize();
	void GetViewMatrix(DirectX::XMMATRIX& viewMatrix);
	DirectX::XMFLOAT4 GetCameraPos();
};

#endif
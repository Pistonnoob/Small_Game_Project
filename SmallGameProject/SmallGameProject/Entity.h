#ifndef ENTITY_H
#define ENTITY_H

#include "SphereBoundingVolume.h"
#include "EntitySubject.h"
#include "Model.h"

class Entity {

protected:
    float posX;
    float posZ;

	Model* entityModel;
	BoundingVolume* entityBV;
	EntitySubject entitySubject;

private:

public:
	Entity();	//Entitys without BoundingVolume
	virtual~Entity();

	//Initialize for unique Entity
	bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string objFilename,
					bool isSphere);
	// Secoundary initialize for instancing
	bool Initialize(Model* model, bool isSphere);	
	void Shutdown(bool isEnemy = false);

    Model* GetModel();
    BoundingVolume* GetBV();
    DirectX::XMFLOAT3 GetPosition();

};

#endif
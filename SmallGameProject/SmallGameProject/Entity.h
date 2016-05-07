#ifndef ENTITY_H
#define ENTITY_H

#include "SphereBoundingVolume.h"
#include "EntitySubject.h"
#include "Model.h"
enum Type {
	NONE,
    MELEEE,
    RANGED,
    BOMBER,
    PLAYER,
    BOSS
};

class Entity {

protected:
    float posX;
    float posZ;
    EntitySubject* entitySubject;
    Type myType;
	Model* entityModel;
	BoundingVolume* entityBV;
public:
	Entity();	//Entitys without BoundingVolume
	virtual~Entity();

	//Initialize for unique Entity
	bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string objFilename,
					bool isSphere, EntitySubject* entitySub);
	// Secoundary initialize for instancing
	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);	
	virtual void Shutdown(bool isEnemy = false);
    void AddObservers(Observer* observer);
	virtual DirectX::XMFLOAT3 GetAimDir();

	EntitySubject* GetEntitySubject() const;

    Type GetType();

    Model* GetModel();
    BoundingVolume* GetBV();
    DirectX::XMFLOAT3 GetPosition();

};

#endif
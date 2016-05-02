#ifndef ENTITY_H
#define ENTITY_H

#include "SphereBoundingVolume.h"
#include "EntitySubject.h"
#include "Model.h"
enum Type {
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
    
private:
	
	Model* entityModel;
	BoundingVolume* entityBV;

public:
	Entity();	//Entitys without BoundingVolume
	virtual~Entity();

	//Initialize for unique Entity
	bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::string objFilename,
					bool isSphere);
	// Secoundary initialize for instancing
	bool Initialize(Model* model, EntitySubject* entitySubject, bool isSphere);	
	void Shutdown(bool isEnemy = false);
    void addObservers(Observer* observer);
	virtual DirectX::XMFLOAT3 getAimDir();

	EntitySubject* getEntitySubject() const;

    Type getType();

    Model* getModel();
    BoundingVolume* getBV();
    DirectX::XMFLOAT3 getPosition();
};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#include "SphereBoundingVolume.h"
#include "EntitySubject.h"
#include "Model.h"

class Entity {

protected:
    float posX;
    float posZ;
private:
	
	Model* entityModel;
	BoundingVolume* entityBV;
	EntitySubject entitySubject;

public:
	Entity(Model* model);	//Entitys without BoundingVolume
	Entity(Model* model, bool isSphere);	//Entitus with BoundingVolume, true = sphere, false = OOBB
    void setModel(Model* model);
    Model* getModel();
    DirectX::XMFLOAT3 getPosition();
	virtual~Entity();
};

#endif
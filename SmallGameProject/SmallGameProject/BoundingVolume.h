#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include <DirectXMath.h>
#include "Model.h"

class BoundingVolume {

private:
	virtual void generateMinMax(DirectX::XMFLOAT3& minVert, DirectX::XMFLOAT3& maxVert, Model* model) = 0;


public:
	BoundingVolume();
	virtual ~BoundingVolume();

	virtual void generateBounds(Model* model) = 0;
	virtual bool intersect(BoundingVolume* otherBoundingVolume) = 0;
};

#endif
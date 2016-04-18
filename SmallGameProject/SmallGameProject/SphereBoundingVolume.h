#ifndef SPHEREBOUNDINGVOLUME_H
#define SPHEREBOUNDINGVOLUME_H

#include "BoundingVolume.h"
#include "BoxBoundingVolume.h"
#include "Model.h"
class SphereBoundingVolume : public BoundingVolume {

private:
	DirectX::XMFLOAT3 center;
	int radius;

	void generateMinMax(DirectX::XMFLOAT3& minVertex, DirectX::XMFLOAT3& maxVertex, Model* model);

public:
	SphereBoundingVolume();
	virtual ~SphereBoundingVolume();
	void generateBounds(Model* model);
	bool intersect(BoundingVolume* otherBoundingVolume);

};


#endif

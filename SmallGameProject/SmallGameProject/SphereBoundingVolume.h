#ifndef SPHEREBOUNDINGVOLUME_H
#define SPHEREBOUNDINGVOLUME_H

#include "BoundingVolume.h"
#include "Model.h"
class SphereBoundingVolume : public BoundingVolume {

private:
	DirectX::XMFLOAT3 pos;
	int radius;

	void generateMinMax(DirectX::XMFLOAT3& minVert, DirectX::XMFLOAT3& maxVert, Model* model);

public:
	SphereBoundingVolume();
	virtual ~SphereBoundingVolume();
	void generateBounds(Model* model);
	bool intersect(BoundingVolume* otherBoundingVolume);

};


#endif

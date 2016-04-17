#ifndef SPHEREBOUNDINGVOLUME_H
#define SPHEREBOUNDINGVOLUME_H

#include "BoundingVolume.h"

class SphereBoundingVolume : public BoundingVolume {

private:
	DirectX::XMFLOAT3 pos;
	int radius;

public:
	SphereBoundingVolume();
	virtual ~SphereBoundingVolume();

	void generateBounds(Model* model);
	bool intersect(BoundingVolume* otherBoundingVolume);

};


#endif

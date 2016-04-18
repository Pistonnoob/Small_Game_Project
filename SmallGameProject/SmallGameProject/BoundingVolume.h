#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include <DirectXMath.h>
#include "Model.h"

class BoundingVolume {

private:

public:
	BoundingVolume();
	virtual ~BoundingVolume();

	virtual void generateBounds(Model* model) = 0;
	virtual bool intersect(BoundingVolume* otherBoundingVolume) = 0;
};

#endif
#include "SphereBoundingVolume.h"

SphereBoundingVolume::SphereBoundingVolume()
: BoundingVolume()
{
	this->pos = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	this->radius = 0;
}

SphereBoundingVolume::~SphereBoundingVolume()
{

}

void SphereBoundingVolume::generateBounds(Model* model)
{

}

bool SphereBoundingVolume::intersect(BoundingVolume* otherBoundingVolume)
{
	SphereBoundingVolume* sphere = dynamic_cast<SphereBoundingVolume*>(otherBoundingVolume);
	
	if (otherBoundingVolume != nullptr) {	//If the volume is a sphere

		//The distance betwen the two centers
		int distance = sqrt(pow((this->pos.x - sphere->pos.x), 2) + pow((this->pos.y - sphere->pos.y), 2) + pow((this->pos.z - sphere->pos.z), 2));
		
		if (this->radius + sphere->radius <= distance) {
			return true;
		}
	}

	return false;
}
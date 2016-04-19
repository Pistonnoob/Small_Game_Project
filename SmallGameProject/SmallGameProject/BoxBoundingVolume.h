#ifndef BOXBOUNDINGVOLUME_H
#define BOXBOUNDINGVOLUME_H

#include "BoundingVolume.h"
#include "SphereBoundingVolume.h"
#include "Model.h"
class BoxBoundingBox : public BoundingVolume {

private:
	DirectX::XMFLOAT3 center;

	//The axices of the OBB
	DirectX::XMVECTOR axisX;
	DirectX::XMVECTOR axisY;
	DirectX::XMVECTOR axisZ;

	DirectX::XMVECTOR allAxises[6]; // first 3 = x,y,z  Last 3 = -x, -y, -z

	// Half the length of one side of the OBB
	float halfLengthX;
	float halfLengthY;
	float halfLengthZ;

	void generateMinMax(DirectX::XMFLOAT3& minVertex, DirectX::XMFLOAT3& maxVertex, Model* model);

public:
	BoxBoundingBox();
	virtual ~BoxBoundingBox();
	void generateBounds(Model* model);
	bool intersect(BoundingVolume* otherBoundingVolume);

};


#endif

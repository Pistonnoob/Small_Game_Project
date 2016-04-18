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

void SphereBoundingVolume::generateMinMax(DirectX::XMFLOAT3& minVertex, DirectX::XMFLOAT3& maxVertex, Model* model)
{
	DirectX::XMVECTOR vertVec;
	DirectX::XMFLOAT3 vertFloat;
	int vertCount = model->GetVertexCount();
	DirectX::XMFLOAT3 maxVert = DirectX::XMFLOAT3(-D3D11_FLOAT32_MAX, -D3D11_FLOAT32_MAX, -D3D11_FLOAT32_MAX);
	DirectX::XMFLOAT3 minVert = DirectX::XMFLOAT3(D3D11_FLOAT32_MAX, D3D11_FLOAT32_MAX, D3D11_FLOAT32_MAX);
	const std::vector<DirectX::XMFLOAT3>* vertPos = model->getVertexPositions();
	DirectX::XMMATRIX modelWorldMatrix;
	model->GetWorldMatrix(modelWorldMatrix);

	for (int i = 0; i < vertCount; i++) {
		
		vertVec = DirectX::XMLoadFloat3(&vertPos->at(i));
		vertVec = DirectX::XMVector3TransformCoord(vertVec, modelWorldMatrix);
		XMStoreFloat3(&vertFloat, vertVec);

		if (vertFloat.x > maxVert.x) {
			maxVert.x = vertFloat.x;
		}
		if (vertFloat.y > maxVert.y) {
			maxVert.y = vertFloat.y;
		}
		if (vertFloat.z > maxVert.z) {
			maxVert.z = vertFloat.z;
		}
		if (vertFloat.x < minVert.x) {
			minVert.x = vertFloat.x;
		}
		if (vertFloat.y < minVert.y) {
			minVert.y = vertFloat.y;
		}
		if (vertFloat.z < minVert.z) {
			minVert.z = vertFloat.z;
		}
	}

	minVertex = minVert;
	maxVertex = maxVert;
}

void SphereBoundingVolume::generateBounds(Model* model)
{
	DirectX::XMFLOAT3 minVert;
	DirectX::XMFLOAT3 maxVert;

	this->generateMinMax(minVert, maxVert, model);	// Generate the min max based on the model

	DirectX::XMFLOAT3 distanceToMid = DirectX::XMFLOAT3(abs(maxVert.x - minVert.x) / 2, abs(maxVert.y - minVert.y) / 2, abs(maxVert.z - minVert.z) / 2);	//Calculate offset to add to the min vertex to find the midle vertex

	DirectX::XMFLOAT3 midleVert = DirectX::XMFLOAT3(minVert.x + distanceToMid.x, minVert.y + distanceToMid.y, minVert.z + distanceToMid.z);	//Calculate the midle Vertex

	this->pos = DirectX::XMFLOAT3(midleVert);	//Set the bounding spheres midle to the center of the modle
	this->radius = sqrt(pow((distanceToMid.x), 2) + pow((distanceToMid.y), 2) + pow((distanceToMid.z), 2));	//Set the radius of the sphere to the distance from the midle to the minimum vertex
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
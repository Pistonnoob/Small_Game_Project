#include "BoxBoundingVolume.h"

BoxBoundingBox::BoxBoundingBox()
{
	this->center = DirectX::XMFLOAT3(0,0,0);
	this->axisX = DirectX::XMVectorSet(0, 0, 0, 0);
	this->axisY = DirectX::XMVectorSet(0, 0, 0, 0);
	this->axisZ = DirectX::XMVectorSet(0, 0, 0, 0);

	for (int i = 0; i < 6; i++) {
		this->allAxises[i] = DirectX::XMVectorSet(0, 0, 0, 0);
	}

	this->halfLengthX = 0;
	this->halfLengthY = 0;
	this->halfLengthZ = 0;

}

BoxBoundingBox::~BoxBoundingBox()
{
}

void BoxBoundingBox::generateMinMax(DirectX::XMFLOAT3 & minVertex, DirectX::XMFLOAT3 & maxVertex, Model * model)
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

void BoxBoundingBox::generateBounds(Model * model)
{
	DirectX::XMFLOAT3 minVert;
	DirectX::XMFLOAT3 maxVert;

	this->generateMinMax(minVert, maxVert, model);
	
	//Calculate the midle
	DirectX::XMFLOAT3 distanceToMid = DirectX::XMFLOAT3((maxVert.x - minVert.x) / 2, (maxVert.y - minVert.y) / 2, (maxVert.z - minVert.z) / 2);	//Calculate offset to add to the min vertex to find the midle vertex
	DirectX::XMFLOAT3 midleVert = DirectX::XMFLOAT3(minVert.x + distanceToMid.x, minVert.y + distanceToMid.y, minVert.z + distanceToMid.z);	//Calculate the midle Vertex

	this->center = DirectX::XMFLOAT3(midleVert);	//Set the bounding spheres midle to the center of the modle
	
	//Half the length of the box
	this->halfLengthX = distanceToMid.x;
	this->halfLengthY = distanceToMid.y;
	this->halfLengthZ = distanceToMid.z;

	//Calculate the axises
	this->axisX = DirectX::XMVectorSet(maxVert.x - minVert.x, 0, 0, 0);
	this->axisX = DirectX::XMVectorSet(0, (maxVert.y - minVert.y), 0, 0);
	this->axisX = DirectX::XMVectorSet(0, 0, (maxVert.z - minVert.z), 0);

	// Normalize the axises
	this->axisX = DirectX::XMVector3Normalize(this->axisX);
	this->axisY = DirectX::XMVector3Normalize(this->axisY);
	this->axisZ = DirectX::XMVector3Normalize(this->axisZ);
	
	//Save the axises and thier opposits in an array for easier use
	this->allAxises[0] = this->axisX;
	this->allAxises[1] = this->axisY;
	this->allAxises[2] = this->axisZ;
	this->allAxises[3] = DirectX::XMVectorSet(DirectX::XMVectorGetX(this->axisX) * -1, 0, 0, 0);
	this->allAxises[4] = DirectX::XMVectorSet(0, DirectX::XMVectorGetY(this->axisY) * -1, 0, 0);
	this->allAxises[5] = DirectX::XMVectorSet(0, 0, DirectX::XMVectorGetZ(this->axisZ) * -1, 0);

}

bool BoxBoundingBox::intersect(BoundingVolume * otherBoundingVolume)
{
	bool result = false;
	BoxBoundingBox* box;

	SphereBoundingVolume* sphere = dynamic_cast<SphereBoundingVolume*>(otherBoundingVolume);
	if (sphere != nullptr) {	//If the volume is a sphere
		


	}
	else{						//If the volume is a Box
		
		box = dynamic_cast<BoxBoundingBox*>(otherBoundingVolume);



	}


	if (sphere) {
		delete sphere;

	}

	if (box) {
		delete box;
	}

	return result;
}

cbuffer shadowConstant : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

float4 main( float4 pos : POSITIONL ) : SV_POSITION
{
	matrix worldViewProj = mul(worldMatrix, viewMatrix);
	worldViewProj = mul(worldViewProj, projectionMatrix);
	
	
	return mul(pos, worldViewProj);
}
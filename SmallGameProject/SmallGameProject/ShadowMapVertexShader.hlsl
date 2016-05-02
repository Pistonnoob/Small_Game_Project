cbuffer shadowConstant : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

float4 main( float3 pos : POSITIONL ) : SV_POSITION
{
	float4 outputPos = float4(pos, 1.0f);
	
	outputPos = mul(outputPos, worldMatrix);
	outputPos = mul(outputPos, viewMatrix);
	outputPos = mul(outputPos, projectionMatrix);

	return outputPos;
}
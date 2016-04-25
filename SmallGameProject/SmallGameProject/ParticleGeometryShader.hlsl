cbuffer CBPerEmitter
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;

	float4 camPos;
};

struct GSInput
{
	float4 position : POSITION; //.a = scale
	float4 color : COLOR; //.a = rotation
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
	float4 color : COLOR;
};

[maxvertexcount(6)]
void main(point GSInput input[1], inout TriangleStream< PSInput > output)
{
	PSInput element;
	float size = input[0].position.w;

	input[0].position.w = 1.0f;
	float4 worldPos = mul(input[0].position, worldMatrix);

	//Create roation matrix
	float3 look = worldPos.xyz - camPos.xyz;
	normalize(look);

	float3 camUp = float3(0.0f, 1.0f, 0.0f);

	float3 right = cross(camUp, look);

	float3 up = cross(look, right);

	float4x4 rotationMatrix = {
		right.x, up.x, look.x, worldPos.x,
		right.y, up.y, look.y, worldPos.y,
		right.z, up.z, look.z, worldPos.z,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	//Create quad
	//First triangle
	//Top-Left
	element.position = input[0].position;
	element.position = mul(element.position, rotationMatrix);
	element.position = mul(element.position, viewMatrix);
	element.position = mul(element.position, projectionMatrix);
	element.color = input[0].color;
	element.tex = float2(0.0f, 0.0f);
	output.Append(element);
	//Bottom-Right
	element.position = float4(input[0].position.x + size, input[0].position.y - size, input[0].position.z, 1.0f);
	element.position = mul(element.position, rotationMatrix);
	element.position = mul(element.position, viewMatrix);
	element.position = mul(element.position, projectionMatrix);
	element.color = input[0].color;
	element.tex = float2(1.0f, 1.0f);
	output.Append(element);
	//Bottom-Left
	element.position = float4(input[0].position.x, input[0].position.y - size, input[0].position.z, 1.0f);
	element.position = mul(element.position, rotationMatrix);
	element.position = mul(element.position, viewMatrix);
	element.position = mul(element.position, projectionMatrix);
	element.color = input[0].color;
	element.tex = float2(0.0f, 1.0f);
	output.Append(element);
	output.RestartStrip();
	//Second triangle
	//Top-Left
	element.position = input[0].position;
	element.position = mul(element.position, rotationMatrix);
	element.position = mul(element.position, viewMatrix);
	element.position = mul(element.position, projectionMatrix);
	element.color = input[0].color;
	element.tex = float2(0.0f, 0.0f);
	output.Append(element);
	//Top-Right
	element.position = float4(input[0].position.x + size, input[0].position.y, input[0].position.z, 1.0f);
	element.position = mul(element.position, rotationMatrix);
	element.position = mul(element.position, viewMatrix);
	element.position = mul(element.position, projectionMatrix);
	element.color = input[0].color;
	element.tex = float2(1.0f, 0.0f);
	output.Append(element);
	//Bottom-Right
	element.position = float4(input[0].position.x + size, input[0].position.y - size, input[0].position.z, 1.0f);
	element.position = mul(element.position, rotationMatrix);
	element.position = mul(element.position, viewMatrix);
	element.position = mul(element.position, projectionMatrix);
	element.color = input[0].color;
	element.tex = float2(1.0f, 1.0f);
	output.Append(element);
	output.RestartStrip();
}
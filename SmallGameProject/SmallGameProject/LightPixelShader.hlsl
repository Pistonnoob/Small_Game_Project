Texture2D diffTexture : register(t0);
Texture2D ambientTexture : register(t1);
Texture2D specularTexture : register(t2);
Texture2D normalTexture: register(t3);
Texture2D worldPosTexture: register(t4);
SamplerState pointSampler : register(s0);

cbuffer LightConstantBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;

	float4 camPos;
	float4 lightPos;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 main(PSInput input) : SV_TARGET
{
	float4 diffColor;
	float4 ambientColor;
	float4 specColor;
	float4 normal;
	float4 worldPos;
	float4 outputColor;

	float lightIntensity = 0.0f;

	//Sample the diffuse texture from deferred render
	diffColor = diffTexture.Sample(pointSampler, input.tex);

	//Sample the ambient texture from deferred render
	ambientColor = ambientTexture.Sample(pointSampler, input.tex);

	//Sample the specual texture from deferred render
	specColor = specularTexture.Sample(pointSampler, input.tex);

	//Sample the normal texture from deferred render
	normal = normalTexture.Sample(pointSampler, input.tex);
	
	//Sample the texture with positions in world space from deferred render
	worldPos = worldPosTexture.Sample(pointSampler, input.tex);

	//Create the normalized vector from position to light source
	float3 outVec = normalize(lightPos.xyz - (worldPos).xyz);

	//Create the normalized reflection vector
	float3 refVec = normalize(reflect(-outVec, normal));

	//Creathe the normalized vector from position to camera
	float3 viewDir = normalize(camPos - worldPos).xyz;

	float specIntesity = saturate(dot(refVec, viewDir));
	float shineFactor = 5.0f;
	float lightSpecular = 0.65f;

	//Calculate the specular part
	float4 specular = float4(specColor.rgb * lightSpecular * max(pow(specIntesity, shineFactor), 0.0f), 1.0f);

	//Combine everything for the output color
	outputColor = saturate(((diffColor.rgba + specular.rgba) * lightIntensity * 0.8f) + ((ambientColor.rgba) * 0.2f));

	return outputColor;
}
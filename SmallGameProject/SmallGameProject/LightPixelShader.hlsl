Texture2D diffTexture : register(t0);
Texture2D ambientTexture : register(t1);
Texture2D specularTexture : register(t2);
Texture2D normalTexture: register(t3);
Texture2D worldPosTexture: register(t4);
Texture2D shadowMapTexture: register(t5);

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
	float4 posLightH : TEXCOORD1;
};

float4 main(PSInput input) : SV_TARGET
{
	float depthValue;
	float4 diffColor;
	float4 ambientColor;
	float4 specColor;
	float4 normal;
	float4 worldPos;
	float4 outputColor;
	float2 textCoords = float2(input.position.x / 800, input.position.y / 600);
	float2 shadowUV;
	float4 positionLight;
	float lightDepthValue;
	float lightIntensity = 0.0f;

	// Set the bias value for fixing the floating point precision issues.
	float bias = 0.00005f;

	input.posLightH.xy /= input.posLightH; // now in NDC

	//Sample the diffuse texture from deferred render
	diffColor = diffTexture.Sample(pointSampler, textCoords);

	//Sample the ambient texture from deferred render
	ambientColor = ambientTexture.Sample(pointSampler, textCoords);

	//Sample the specual texture from deferred render
	specColor = specularTexture.Sample(pointSampler, textCoords);

	//Sample the normal texture from deferred render
	normal = normalTexture.Sample(pointSampler, textCoords);
	
	//Sample the texture with positions in world space from deferred render
	worldPos = worldPosTexture.Sample(pointSampler, textCoords);

	//compute pixel depth for shadowing
	float depth = input.posLightH.z / input.posLightH.w;
	float test = shadowMapTexture.Sample(pointSampler, textCoords).r;

	//Move the position to projection space for the light
	positionLight = mul(worldPos, lightViewMatrix);
	positionLight = mul(positionLight, lightProjectionMatrix);

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

	lightIntensity = dot(normal, outVec);
	if (lightIntensity < 0) {
		lightIntensity = 0;
	}

	//calculate the projected texture coordinate
	shadowUV.x = (positionLight.x / positionLight.w) * 0.5f + 0.5f;
	shadowUV.y = (-positionLight.y / positionLight.w) * 0.5f + 0.5f;

	//If point outside shadowMap
	if (saturate(shadowUV.x) != shadowUV.x || saturate(shadowUV.y) != shadowUV.y)
	{
		lightIntensity = saturate(dot(normal.xyz, outVec.xyz));
	}

	//calculate the depth of the light
	lightDepthValue = positionLight.z / positionLight.w;

	//sample the shadowmap
	depthValue = shadowMapTexture.Sample(pointSampler, shadowUV).r;

	// Subtract the bias from the lightDepthValue.
	lightDepthValue = lightDepthValue - bias;

	if (lightDepthValue < depthValue)
	{
		lightIntensity = saturate(dot(normal.xyz, outVec.xyz));
	}

	//Combine everything for the output color
	outputColor = saturate(((diffColor.rgba + specular.rgba) * lightIntensity * 0.8f) + ((ambientColor.rgba) * 0.2f));

	//return float4(input.tex.x, input.tex.y, 0.0f, 1.0f);
	//return float4(input.position.x / 800, input.position.y / 600, 0.0f, 1.0f);
	//return outputColor;
	//test *= 1000;

	return outputColor;
}
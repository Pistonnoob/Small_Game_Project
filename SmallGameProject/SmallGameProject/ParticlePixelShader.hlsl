Texture2D particleTexture : register(t0);
SamplerState mySampler : register(s0);

struct PSInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
	float4 color : COLOR;
};

float4 main(PSInput input) : SV_TARGET
{
	float4 outputColor = particleTexture.Sample(mySampler, input.tex);

	//If pixel is black, treat it as transparent
	if (outputColor.r == 1 && outputColor.g == 1 && outputColor.b == 1) {
		outputColor.a = 0.0f;
	}
	else {
		outputColor.a = 0.5f;
	}

	outputColor.rgb = outputColor.rgb * input.color.rgb;

	return outputColor;
}
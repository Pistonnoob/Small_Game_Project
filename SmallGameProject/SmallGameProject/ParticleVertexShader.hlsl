
struct VSInput
{
	float4 position : POSITION; //.a = scale
	float4 color : COLOR; //.a = rotation
	float4 instancePosition : POSITION1;
	float4 instanceColor : COLOR1;
};

struct GSInput
{
	float4 position : SV_POSITION; //.a = scale
	float4 color : COLOR; //.a = rotation
};

GSInput main(VSInput input)
{
	GSInput output;

	//Forward data to geo shader
	output.position = input.position + input.instancePosition;
	output.color = input.color + input.instanceColor;

	return output;
}
cbuffer cbPerObject
{
	matrix World;
	matrix View;
	matrix Proj;
	matrix ViewProj;
	float3 gEyePosW;
};

struct VertexInput
{
	float3 PosW  : POSITION;
	float2 SizeW : SIZE;
};

struct VertexOut
{
	float3 CenterW : POSITION;
	float2 SizeW   : SIZE;
};

struct GeoOut
{
	float4 PosH    : SV_POSITION;
	float3 PosW    : POSITION;
};
#include "BillboardHeader.hlsli"

[maxvertexcount(4)]
void main(point VertexOut input[1], inout TriangleStream<GeoOut> triStream)
{
	float3 planeNormal = input[0].CenterW - gEyePosW;
	planeNormal.y = 0.0f;
	planeNormal = normalize(planeNormal);

	float3 upVector = float3(0.0f, 1.0f, 0.0f);
	float3 rightVector = normalize(cross(planeNormal, upVector));

	float halfWidth = 0.5f * input[0].SizeW.x;
	float halfHeight = 0.5f * input[0].SizeW.y;

	// Build vertices
	float3 vert[4];
	vert[0] = input[0].CenterW + halfWidth * rightVector - halfHeight * upVector;
	vert[1] = input[0].CenterW + halfWidth * rightVector + halfHeight * upVector;
	vert[2] = input[0].CenterW - halfWidth * rightVector - halfHeight * upVector;
	vert[3] = input[0].CenterW - halfWidth * rightVector + halfHeight * upVector;

	// Map texture UV's
	float2 texCoord[4];
	texCoord[0] = float2(0, 1);
	texCoord[1] = float2(0, 0);
	texCoord[2] = float2(1, 1);
	texCoord[3] = float2(1, 0);

	// Output geometry
	[unroll]
	for (int i = 0; i < 4; i++)
	{
		GeoOut outputVert;
		outputVert.PosH = mul(float4(vert[i], 1.0f), World);
		outputVert.PosH = mul(outputVert.PosH, View);
		outputVert.PosH = mul(outputVert.PosH, Proj);

		outputVert.PosW = float4(vert[i], 0.0f);
		outputVert.Texture = texCoord[i];

		triStream.Append(outputVert);
	}
}
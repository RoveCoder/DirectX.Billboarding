#include "BillboardHeader.hlsli"

[maxvertexcount(4)]
void main(point VertexOut input[1], inout TriangleStream<GeoOut> triStream)
{
	float halfWidth = input[0].SizeW.x / 2.0f;

	float3 planeNormal = input[0].CenterW - gEyePosW;
	planeNormal.y = 0.0f;
	planeNormal = normalize(planeNormal);

	float3 upVector = float3(0.0f, 1.0f, 0.0f);
	float3 rightVector = normalize(cross(planeNormal, upVector));

	rightVector = rightVector * halfWidth;

	//float halfWidth = 0.5f * input[0].SizeW.x;
	//float halfHeight = 0.5f * input[0].SizeW.y;

	float3 vert[4];
	vert[0] = input[0].CenterW - rightVector; // Get bottom left vertex
	vert[1] = input[0].CenterW + rightVector; // Get bottom right vertex
	vert[2] = input[0].CenterW - rightVector + upVector; // Get top left vertex
	vert[3] = input[0].CenterW + rightVector + upVector; // Get top right vertex

	GeoOut outputVert[4];
	for (int i = 0; i < 4; i++)
	{

		outputVert[i].PosH = mul(float4(vert[i], 1.0f), World);
		outputVert[i].PosH = mul(outputVert[i].PosH, View);
		outputVert[i].PosH = mul(outputVert[i].PosH, Proj);

		outputVert[i].PosW = float4(vert[i], 0.0f);

		//triStream.Append(outputVert);
	}
	
	for (int i = 0; i < 4; i++)
	{
		triStream.Append(outputVert[i]);
	}


	//float3 up = float3(0.0f, 1.0f, 0.0f);
	//float3 look = gEyePosW - gin[0].CenterW;
	//look.y = 0.0f; // y-axis aligned, so project to xz-plane
	//look = normalize(look);
	//float3 right = cross(up, look);

	////
	//// Compute triangle strip vertices (quad) in world space.
	////

	//float halfWidth = 0.25f * gin[0].SizeW.x;
	//float halfHeight = 0.25f * gin[0].SizeW.y;

	//float4 v[4];
	//v[0] = float4(gin[0].CenterW + halfWidth * right - halfHeight * up, 1.0f);
	//v[1] = float4(gin[0].CenterW + halfWidth * right + halfHeight * up, 1.0f);
	//v[2] = float4(gin[0].CenterW - halfWidth * right - halfHeight * up, 1.0f);
	//v[3] = float4(gin[0].CenterW - halfWidth * right + halfHeight * up, 1.0f); 

	///*v[0] = float4(gin[0].CenterW.x, gin[0].CenterW.y + 1.0f, 0.0f, 1.0f);
	//v[1] = float4(gin[0].CenterW.x + 0.5f, gin[0].CenterW.y, 0.0f, 1.0f);
	//v[2] = float4(gin[0].CenterW.x, gin[0].CenterW.y - 1.0f, 0.0f, 1.0f);
	//v[3] = float4(gin[0].CenterW.x - 0.5f, gin[0].CenterW.y, 0.0f, 1.0f);*/


	////
	//// Transform quad vertices to world space and output 
	//// them as a triangle strip.
	////

	//[unroll]
	//for (int i = 0; i < 4; ++i)
	//{
	//	GeoOut gout;
	//	gout.PosH = mul(v[i], ViewProj);
	//	gout.PosW = v[i].xyz;

	//	triStream.Append(gout);
	//}
}
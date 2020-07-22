#include "BillboardHeader.hlsli"

VertexOut main(VertexInput input)
{
	VertexOut output;

	// Transform to world space.
	output.CenterW = input.PosW;
	output.SizeW = input.SizeW;

	return output;
}
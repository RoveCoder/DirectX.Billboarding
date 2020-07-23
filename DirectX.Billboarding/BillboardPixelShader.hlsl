#include "BillboardHeader.hlsli"

float4 main(GeoOut input) : SV_TARGET
{
	float4 texture_diffuse = TextureDiffuse.Sample(SamplerAnisotropic, input.Texture);
	clip(texture_diffuse.a - 0.1);

	return texture_diffuse;
}
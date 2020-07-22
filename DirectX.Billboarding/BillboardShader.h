#pragma once

#include "Renderer.h"

class BillboardShader
{
public:
	BillboardShader(Renderer* renderer);

	bool Create();
	void Use();

private:
	Renderer* m_Renderer = nullptr;

	ID3D11InputLayout* m_VertexLayout = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11GeometryShader* m_GeometryShader = nullptr;

	bool CreateVertexShader(const std::string& vertex_shader_path);
	bool CreatePixelShader(const std::string& pixel_shader_path);
	bool CreateGeometryShader(const std::string& geometry_shader_path);
};
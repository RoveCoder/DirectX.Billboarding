#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "Mesh.h"

class Tree
{
public:
	Tree(Renderer* renderer);

	bool Load();
	void Render(Camera* camera);

private:
	Renderer* m_Renderer = nullptr;

	ID3D11Buffer* m_VertexBuffer = nullptr;

	ID3D11Buffer* m_Buffer = nullptr;
};
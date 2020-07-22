#include "Tree.h"
#include <DirectXMath.h>
#include "GeometryGenerator.h"
#include <DirectXColors.h>
#include "DDSTextureLoader.h"

struct TreePointSprite
{
    float x;
    float y;
    float z;

    float width;
    float height;
};

struct Buffer
{
    DirectX::XMMATRIX World;
    DirectX::XMMATRIX View;
    DirectX::XMMATRIX Proj;
    DirectX::XMMATRIX ViewProj;
    DirectX::XMFLOAT3 CameraPos;
};

Tree::Tree(Renderer* renderer) : m_Renderer(renderer)
{
}

bool Tree::Load()
{
    TreePointSprite vertex;
    vertex.x = 0.0f;
    vertex.y = 0.0f;
    vertex.z = -2.0f;
    vertex.width = 4.0f;
    vertex.height = 6.0f;

    // Create vertex buffer
    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = (UINT)(sizeof(TreePointSprite) * 1);
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vInitData = {};
    vInitData.pSysMem = &vertex;

    DX::ThrowIfFailed(m_Renderer->GetDevice()->CreateBuffer(&vbd, &vInitData, &m_VertexBuffer));

    // Buffer
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Buffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    DX::ThrowIfFailed(m_Renderer->GetDevice()->CreateBuffer(&bd, nullptr, &m_Buffer));

    return true;
}

void Tree::Render(Camera* camera)
{
    // Bind the vertex buffer
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    m_Renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    // Set topology
    m_Renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

    // Set world buffer
    Buffer cb;
    cb.World = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
    cb.View = DirectX::XMMatrixTranspose(camera->GetView());
    cb.Proj = DirectX::XMMatrixTranspose(camera->GetProjection());
    cb.ViewProj = cb.View * camera->GetProjection();
    cb.CameraPos = camera->GetPosition();

    m_Renderer->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_Buffer);
    m_Renderer->GetDeviceContext()->GSSetConstantBuffers(0, 1, &m_Buffer);
    m_Renderer->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_Buffer);
    m_Renderer->GetDeviceContext()->UpdateSubresource(m_Buffer, 0, nullptr, &cb, 0, 0);

    // Render geometry
    m_Renderer->GetDeviceContext()->Draw(1, 0);
}
#include "Tree.h"
#include <DirectXMath.h>
#include "GeometryGenerator.h"
#include <DirectXColors.h>
#include "DDSTextureLoader.h"
#include <chrono>
#include <random>

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
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(-4.0, 4.0);

    float t = distr(gen);

    TreePointSprite vertex[m_TreeCount];
    for (int i = 0; i < m_TreeCount; ++i) 
    {
        TreePointSprite v;
        v.x = distr(gen);
        v.y = 0.5f;
        v.z = distr(gen);
        v.width = 4.0f;
        v.height = 4.0f;

        vertex[i] = v;
    }

    // Create vertex buffer
    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = (UINT)(sizeof(TreePointSprite) * m_TreeCount);
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vInitData = {};
    vInitData.pSysMem = &vertex[0];

    DX::ThrowIfFailed(m_Renderer->GetDevice()->CreateBuffer(&vbd, &vInitData, &m_VertexBuffer));

    // Buffer
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Buffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    DX::ThrowIfFailed(m_Renderer->GetDevice()->CreateBuffer(&bd, nullptr, &m_Buffer));

    // Load texture
    ID3D11Resource* resource = nullptr;
    DX::ThrowIfFailed(DirectX::CreateDDSTextureFromFile(m_Renderer->GetDevice(), L"Textures\\tree0.dds", &resource, &m_DiffuseTexture));
    resource->Release();

    return true;
}

void Tree::Render(Camera* camera)
{
    // Bind the vertex buffer
    UINT stride = sizeof(TreePointSprite);
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

    m_Renderer->GetDeviceContext()->PSSetShaderResources(0, 1, &m_DiffuseTexture);

    // Render geometry
    m_Renderer->GetDeviceContext()->Draw(m_TreeCount, 0);
}
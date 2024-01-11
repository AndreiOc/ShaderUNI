#include "Headers/Paddle.h"

/// <summary>
/// Construt first initialization of the vertices
/// </summary>
Paddle::Paddle()
{
    OurVertices[0] = { -0.2f, -0.9f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) };
    OurVertices[1] = { -0.2f, -0.8f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) };
    OurVertices[2] = { 0.2f, -0.9f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };
    OurVertices[3] = { 0.2f , -0.8f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };

    pVBufferPaddle = NULL;
}

Paddle::~Paddle()
{}

ID3D11Buffer* Paddle::GetBuffer()
{
    return pVBufferPaddle;
}

VERTEX *Paddle::GetVertices()
{
    return OurVertices;
}

float Paddle::Update(float shiftX, ID3D11Device* dev, ID3D11DeviceContext* devcon)
{

    OurVertices[0].X = OurVertices[0].X + shiftX;
    OurVertices[1].X = OurVertices[1].X + shiftX;
    OurVertices[2].X = OurVertices[2].X + shiftX;
    OurVertices[3].X = OurVertices[3].X + shiftX;
        
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * 4;             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    dev->CreateBuffer(&bd, NULL, &pVBufferPaddle);       // create the buffer
    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBufferPaddle, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);      // map the buffer
    memcpy(ms.pData, OurVertices, sizeof(OurVertices));                                                         // copy the data
    devcon->Unmap(pVBufferPaddle, NULL);

    devcon->IASetVertexBuffers(0, 1, &pVBufferPaddle, &stride, &offset);

    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // draw the vertex buffer to the back buffer
    devcon->Draw(4, 0);

    return OurVertices[2].X;

}


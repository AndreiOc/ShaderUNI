#include "Headers/Paddle.h"

/// <summary>
/// Construt first initialization of the vertices
/// </summary>
Paddle::Paddle()
{
    vertices[0] = { -0.2f, -0.9f, 0.0f, D3DXCOLOR(0.39215686274509803f, 0.43529411764705883f, 0.34509803921568627f, 1.0f) };
    vertices[1] = { -0.2f, -0.8f, 0.0f, D3DXCOLOR(0.39215686274509803f, 0.43529411764705883f, 0.34509803921568627f, 1.0f) };
    vertices[2] = { 0.2f, -0.9f, 0.0f,  D3DXCOLOR(0.39215686274509803f,  0.43529411764705883f, 0.34509803921568627f, 1.0f) };
    vertices[3] = { 0.2f , -0.8f, 0.0f, D3DXCOLOR(0.39215686274509803f, 0.43529411764705883f, 0.34509803921568627f, 1.0f) };

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
    return vertices;
}

bool Paddle::Update(float shiftX, ID3D11Device* dev, ID3D11DeviceContext* devcon, float ballX, float ballY)
{
    vertices[0].X = vertices[0].X + shiftX;
    vertices[1].X = vertices[1].X + shiftX;
    vertices[2].X = vertices[2].X + shiftX;
    vertices[3].X = vertices[3].X + shiftX;
        
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
    memcpy(ms.pData, vertices, sizeof(vertices));                                                         // copy the data
    devcon->Unmap(pVBufferPaddle, NULL);

    devcon->IASetVertexBuffers(0, 1, &pVBufferPaddle, &stride, &offset);

    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // draw the vertex buffer to the back buffer
    devcon->Draw(4, 0);

    //if it is between the x of the paddle and it is lower the the y bounce
    if (ballX > vertices[1].X + shiftX &&
        ballX < vertices[1].X + 0.4f + shiftX &&
        ballY < vertices[1].Y &&
        ballY > vertices[1].Y - 0.1f
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Paddle::GetX()
{
    return vertices[1].X;
}
float Paddle::GetY()
{
    return vertices[1].Y;
}
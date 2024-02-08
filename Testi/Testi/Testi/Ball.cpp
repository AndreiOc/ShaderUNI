#include "Headers/Ball.h"
Ball::Ball(ID3D11Device* dev )
{
    vertices[0] = { -0.025f, -0.55f, 0.0f,      D3DXCOLOR(0.8666666666666667f, 0.8901960784313725f, 0.5725490196078431f, 1.0f) };
    vertices[1] = { -0.025f, -0.5f, 0.0f,       D3DXCOLOR(0.8666666666666667f, 0.8901960784313725f, 0.5725490196078431f, 1.0f) };
    vertices[2] = { 0.025f, -0.55f, 0.0f,       D3DXCOLOR(0.8666666666666667f, 0.8901960784313725f, 0.5725490196078431f, 1.0f) };
    vertices[3] = { 0.025f , -0.5f, 0.0f,       D3DXCOLOR(0.8666666666666667f, 0.8901960784313725f, 0.5725490196078431f, 1.0f) };
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * 4;             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    dev->CreateBuffer(&bd, NULL, &pVBufferBall);       // create the buffer
}

Ball::~Ball()
{}

void Ball::Update( ID3D11DeviceContext* devcon, float shiftX, float shiftY)
{
    Bounce(shiftX, shiftY);
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBufferBall, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);      // map the buffer
    memcpy(ms.pData, vertices, sizeof(vertices));                                                         // copy the data
    devcon->Unmap(pVBufferBall, NULL);

    devcon->IASetVertexBuffers(0, 1, &pVBufferBall, &stride, &offset);

    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // draw the vertex buffer to the back buffer
    devcon->Draw(4, 0);
}



float Ball::GetX()
{
    return vertices[1].X;
}

float Ball::GetY()
{
    return vertices[1].Y;
}


void Ball::Bounce(float moveX, float moveY)
{
 
    vertices[0].X = vertices[0].X + moveX;
    vertices[1].X = vertices[1].X + moveX;
    vertices[2].X = vertices[2].X + moveX;
    vertices[3].X = vertices[3].X + moveX;

    vertices[0].Y = vertices[0].Y + moveY;
    vertices[1].Y = vertices[1].Y + moveY;
    vertices[2].Y = vertices[2].Y + moveY;
    vertices[3].Y = vertices[3].Y + moveY;

}




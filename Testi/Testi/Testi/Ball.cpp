#include "Headers/Ball.h"
Ball::Ball()
{
    OurVertices[0] = { -0.025f, -0.55f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)};
    OurVertices[1] = { -0.025f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) };
    OurVertices[2] = { 0.025f, -0.55f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };
    OurVertices[3] = { 0.025f , -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };

    pVBufferBall = NULL;
}


void Ball::Update(ID3D11Device* dev, ID3D11DeviceContext* devcon, float shift)
{

    Bounce(shift);
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;


    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * 4;             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    dev->CreateBuffer(&bd, NULL, &pVBufferBall);       // create the buffer
    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBufferBall, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);      // map the buffer
    memcpy(ms.pData, OurVertices, sizeof(OurVertices));                                                         // copy the data
    devcon->Unmap(pVBufferBall, NULL);

    devcon->IASetVertexBuffers(0, 1, &pVBufferBall, &stride, &offset);

    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // draw the vertex buffer to the back buffer
    devcon->Draw(4, 0);
}

Ball::~Ball()
{
}

void Ball::Bounce(float shift)
{
 
    OurVertices[0].X = OurVertices[0].X + shift;
    OurVertices[1].X = OurVertices[1].X + shift;
    OurVertices[2].X = OurVertices[2].X + shift;
    OurVertices[3].X = OurVertices[3].X + shift;

    OurVertices[0].Y = OurVertices[0].Y + shift;
    OurVertices[1].Y = OurVertices[1].Y + shift;
    OurVertices[2].Y = OurVertices[2].Y + shift;
    OurVertices[3].Y = OurVertices[3].Y + shift;

}
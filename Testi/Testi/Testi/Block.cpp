#include"Headers/Block.h"


Block::Block()
{}

Block::Block(float posX, float posY)
{
    vertices[0] = { posX,           posY - 0.1f,    0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) };
    vertices[1] = { posX,           posY + 0,       0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) };
    vertices[2] = { posX + 0.1f,    posY - 0.1f,    0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };
    vertices[3] = { posX + 0.1f,    posY + 0,       0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };

    pVBufferBlock = NULL;
}

Block::~Block()
{
}

void Block::Update(ID3D11Device* dev, ID3D11DeviceContext* devcon, float ballX, float ballY,float posX,float posY)
{
    
    if (!isHit)
    {
        UINT stride = sizeof(VERTEX);
        UINT offset = 0;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
        bd.ByteWidth = sizeof(VERTEX) * 4;             // size is the VERTEX struct * 3
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

        dev->CreateBuffer(&bd, NULL, &pVBufferBlock);       // create the buffer
        // copy the vertices into the buffer
        D3D11_MAPPED_SUBRESOURCE ms;
        devcon->Map(pVBufferBlock, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);      // map the buffer
        memcpy(ms.pData, vertices, sizeof(vertices));                                                         // copy the data
        devcon->Unmap(pVBufferBlock, NULL);

        devcon->IASetVertexBuffers(0, 1, &pVBufferBlock, &stride, &offset);

        // select which primtive type we are using
        devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

        // draw the vertex buffer to the back buffer
        devcon->Draw(4, 0);
    }

}


void Block::isBallHit(float ballX, float ballY)
{
    if (true)
    {
        //se la posizone della pallina � compresa tra 
        //i valore della posizione del blocco allora � stata colpita altrimenti no
        //devo fare un check dell'intorno
    }

}
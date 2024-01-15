#pragma once
#include "Headers/DirectX.h"

class Ball
{
public:
	Ball();
    void Update(ID3D11Device* dev, ID3D11DeviceContext* devcon, float shiftX, float shiftY);
	~Ball();
    float GetX();
    float GetY();

private:
    void Bounce(float moveX,float moveY);
    ID3D11Buffer* pVBufferBall;            // the poitner to the vertex buffer for the paddle

    VERTEX vertices[4] =
    {
        {-0.025f, -0.55f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
        {-0.025f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
        {0.025f, -0.55f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
        {0.025f , -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
    };

    float moveX = 0.0f;
    float moveY = 0.0f;
};

#pragma once
#include "Headers/DirectX.h"

class Ball
{
public:
	Ball();
	void Update(ID3D11Device* dev, ID3D11DeviceContext* devcon, float shift);
	~Ball();


private:
    void Bounce(float shift);
    ID3D11Buffer* pVBufferBall;            // the poitner to the vertex buffer for the paddle

    VERTEX OurVertices[4] =
    {
        {-0.025f, -0.55f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
        {-0.025f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
        {0.025f, -0.55f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
        {0.025f , -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
    };
};

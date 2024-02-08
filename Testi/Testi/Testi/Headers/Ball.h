#pragma once
#include "Headers/DirectX.h"

class Ball
{
public:
	Ball(ID3D11Device* dev);
    ~Ball();

    void Update( ID3D11DeviceContext* devcon, float shiftX, float shiftY);
	
    float GetX();
    float GetY();

private:
    void Bounce(float moveX,float moveY);
    ID3D11Buffer* pVBufferBall;            // the poitner to the vertex buffer for the paddle
    VERTEX vertices[4];

};

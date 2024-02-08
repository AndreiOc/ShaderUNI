#pragma once
#include "Headers/DirectX.h"

class Ball
{
public:
	Ball(ID3D11Device* dev);
    ~Ball();
    // Update the frame with new ball positionn
    void Update( ID3D11DeviceContext* devcon, float shiftX, float shiftY);
	
    //return the X and the Y value of the leftup corner
    float GetX();
    float GetY();

private:
    void Bounce(float moveX,float moveY);
    // the poitner to the vertex buffer for the paddle
    ID3D11Buffer* pVBufferBall;            
    VERTEX vertices[4];

};

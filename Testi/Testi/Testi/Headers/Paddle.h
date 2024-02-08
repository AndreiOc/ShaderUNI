#pragma once
#include "Headers/DirectX.h"

class Paddle
{
public:
	Paddle(ID3D11Device* dev);
	~Paddle();

	//update the paddle and the position 
	bool Update(float shiftX, ID3D11DeviceContext* devcon, float ballX, float ballY);

	//return the X and the Y value of the leftup corner
	float GetX();
	float GetY();

private:
	ID3D11Buffer* pVBufferPaddle;           // the poitner to the vertex buffer for the paddle
	VERTEX vertices[4];
	bool go = true;
};


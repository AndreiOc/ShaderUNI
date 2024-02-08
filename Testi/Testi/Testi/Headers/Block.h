#pragma once
#include "Headers/DirectX.h"

class Block
{
public:
	Block();
	Block(ID3D11Device* dev,float posX, float posY);
	~Block();

	//update thge block and check if it is hit by the ball
	bool Update( ID3D11DeviceContext* devcon, float ballX, float ballY);
	bool isBallHit(float ballX, float ballY);
	bool GetHit();

private:
	// the pointer to the vertex buffer, this is for only and only the blocks
	ID3D11Buffer* pVBufferBlock; 
	VERTEX vertices[4];
	bool isHit = false;
};


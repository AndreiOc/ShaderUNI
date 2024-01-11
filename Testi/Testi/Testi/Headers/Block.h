#pragma once
#include "Headers/DirectX.h"

class Block
{
public:
	Block();
	~Block();
	void Update(ID3D11Device* dev, ID3D11DeviceContext* devcon, float ballX, float ballY,float posX, float posY);

private:
	void isBallHit(float ballX, float ballY);

	ID3D11Buffer* pVBufferBlock; // the pointer to the vertex buffer, this is for only and only the blocks
	VERTEX vertices[4];
	bool isHit = false;
};


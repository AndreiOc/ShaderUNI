#pragma once
#include "Headers/DirectX.h"

class Block
{
public:
	/// <summary>
	/// Pass the biggest correct value and after thath i update all the positions
	/// </summary>
	/// <param name="posX"></param>
	/// <param name="posY"></param>
	Block();
	Block(float posX, float posY);
	~Block();
	bool Update(ID3D11Device* dev, ID3D11DeviceContext* devcon, float ballX, float ballY);
	bool isBallHit(float ballX, float ballY);
	bool GetHit();
private:

	ID3D11Buffer* pVBufferBlock; // the pointer to the vertex buffer, this is for only and only the blocks
	VERTEX vertices[4];
	bool isHit = false;
};


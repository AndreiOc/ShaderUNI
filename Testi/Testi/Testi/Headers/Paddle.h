#pragma once
#include "Headers/DirectX.h"

class Paddle
{
public:
	Paddle();
	/// <summary>
	/// I update the paddle so i can move it passing all the buffers and the shiftX for the moving 
	/// </summary>
	/// <param name="shiftX"></param>
	/// <param name="dev"></param>
	/// <param name="devcon"></param>
	float Update(float shiftX, ID3D11Device* dev, ID3D11DeviceContext* devcon);
	
	~Paddle();
	/// <summary>
	/// I get the buffer from the paddle  
	/// </summary>
	/// <returns></returns>
	ID3D11Buffer* GetBuffer();
	VERTEX *GetVertices();
private:
	ID3D11Buffer* pVBufferPaddle;           // the poitner to the vertex buffer for the paddle

    /// <summary>
    /// My paddle verrtices
    /// </summary>
	VERTEX OurVertices[4];
	bool go = true;
};


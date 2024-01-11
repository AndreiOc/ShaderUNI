#pragma once
#include "Vertex.h"
class Brick
{
public:

	// a struct to define a single vertex
	Brick(VERTEX b_one, VERTEX b_two, VERTEX b_three, VERTEX b_four);
	~Brick();
	VERTEX* GetVertexs();
	size_t VERTEX_SIZE();
	VERTEX all_Vertex[4];


private:
	bool isDestroyed = false;

	VERTEX B_one;
	VERTEX B_two;
	VERTEX B_three;
	VERTEX B_four;

};



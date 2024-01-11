#include "Brick.h"
Brick::Brick(	VERTEX b_one, 
				VERTEX b_two, 
				VERTEX b_three, 
				VERTEX b_four)
{
	B_one = b_one;
	B_two = b_two;
	B_three = b_three;
	B_four = b_four;

	all_Vertex[0] = b_one;
	all_Vertex[1] = b_two;
	all_Vertex[2] = b_three;
	all_Vertex[3] = b_four;



}

Brick::~Brick()
{
}

VERTEX *Brick::GetVertexs()
{
	return all_Vertex;
}

size_t Brick::VERTEX_SIZE() 
{
	return sizeof(all_Vertex);
}
#pragma once
#ifndef Node_h
#define Node_h
#include"Node.h"
#include"Coord.h"
class Node
{
public:
	Node(Coord* coord, Node* previous, Node* next);
	Node();
	~Node();
	int x;//left
	int y;//top
	int right;
	int bottom;
	Coord* coord;
	Node* previous;
	Node* next;
	void setCoord(Coord *coord);
};
#endif // !Node_h




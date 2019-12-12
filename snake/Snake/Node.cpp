
#include<stdio.h>
#include<stdlib.h>
#include"map.h"
#include "Node.h"
#include"Coord.h"
#include"globalvar.h"
Node::Node(Coord *coord,Node* previous,Node* next)
{
	this->coord = coord;
	this->next = next;
	this->previous = previous;
	this->x = coord->hor*width;
	this->y = coord->ver * height;
	this->right = this->x + width;
	this->bottom = this->y + height;

}
Node::Node()
{
	
}
void Node::setCoord(Coord* coord)
{
	this->coord = coord;
	this->x = coord->hor * width;
	this->y = coord->ver * height;
	this->right = this->x + width;
	this->bottom = this->y + height;
}
Node::~Node()
{
}

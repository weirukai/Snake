#pragma once
#ifndef Food_h
#define Food_h
#include"globalvar.h"
class Food
{
public:
	int x;
	int y;
	Coord* coord;
	int type;
	Food(Coord*, int);

};
void createOneFood(int Type);
void createAllFood();
#endif // !Food_h

#include"Coord.h"



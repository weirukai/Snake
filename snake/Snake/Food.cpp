#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<random>
#include<time.h>
#include<easyx.h>
#include"globalvar.h"
#include "Food.h"
using namespace std;

extern vector<Food*>foods;


Food::Food(Coord* coord, int type)
{
	this->x = coord->hor * width;
	this->y = coord->ver * height;
	this->coord = coord;
	this->type = type;
	foods.push_back(this);
}

Coord* createRandomCoord()
{
	vector<Food*> ::iterator it;//声明一个迭代器
	//食物的生成不能够生成在边界和蛇身，以及已经存在的食物的上面
	//下面是检测的过程
	Coord* coord = new Coord();
	int x = 0;
	int y = 0;
	bool getRightPlace = true;
	Node* ptr = playerSnake->head;
	srand(time(NULL));
	
		//生成的随机坐标，并且保证不会生成在边界上面
	x = createRandom() % (maxhor - 1) + 1;
	y = createRandom() % (maxver - 1) + 1;
	//检查蛇身
	while (ptr != NULL)
	{
		if (x == ptr->coord->hor && y == ptr->coord->ver)
		{
			getRightPlace = false;
		}
		ptr = ptr->next;
	}
     for (it = foods.begin();it != foods.end(); it++)
	{
		//遍历所有其它的食物
		
		if (x == (*it)->coord->hor && y == (*it)->coord->ver)//遇到空指针的情况
		{
			getRightPlace = false;
		}
	}
	


	while (!getRightPlace)
	{

		x = createRandom() % (maxhor - 2) + 1;
		y = createRandom() % (maxver - 2) + 1;
		//检查蛇身
		while (ptr != NULL)
		{
			if (x == ptr->coord->hor && y == ptr->coord->ver)
			{
				getRightPlace = false;
			}
		}

		for (it = foods.begin(); it != foods.end(); it++)
		{
			//遍历所有其它的食物
			if (x == (*it)->coord->hor && y == (*it)->coord->ver)
			{
				getRightPlace = false;
			}
		}
	}
	coord->hor = x;
	coord->ver = y;
	return coord;
}

void createOneFood(int Type)
{
	Coord* coord = createRandomCoord();
	Food* newFood = new Food(coord, Type);
}


void createAllFood()
{
	//srand(time(NULL));
	while (!GameOver)
	{

		if (foods.size()<4)
		{
			int num = createRandom() % 8;//
			if (num==0)
			{
				createOneFood(STRAWBERRY);
			}
			else  if (num==1)
			{
				createOneFood(BOMB);
			}
			else
			{
				createOneFood(APPLE);
			}
		}
		Sleep(100);
	}

}




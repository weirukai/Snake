#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<random>
#include<time.h>
#include<easyx.h>
#include"globalvar.h"
#include "Food.h"
#include"SnakeBody.h"

using namespace std;

extern vector<Food*>foods;
extern SnakeBody* playerSnake;

Food::Food(Coord* coord, int type)
{
	this->x = coord->hor * width;
	this->y = coord->ver * height;
	this->coord = coord;
	this->type = type;
	foods.push_back(this);
}



/*随机生成食物，给食物生成一个随机坐标*/
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

    
	for (int i = 0; i < foods.size(); i++)
	{
		if (x==foods[i]->coord->hor&&y==foods[i]->coord->ver)
		{
			getRightPlace = false;
		}
	}

	//检查墙体
	 if (walls[y][x]==WALL)
	 {
		 getRightPlace = false;
	 }


	while (!getRightPlace)
	{ 

		x = createRandom() % (maxhor - 3) + 1;
		y = createRandom() % (maxver - 3) + 1;
		//检查蛇身
		if (walls[y][x] == WALL)
		{
			getRightPlace = false;
		}
		while (ptr != NULL)
		{
			if (x == ptr->coord->hor && y == ptr->coord->ver)
			{
				getRightPlace = false;
			}
		}

		for (int i = 0; i < foods.size(); i++)
		{
			if (x == foods[i]->coord->hor && y == foods[i]->coord->ver)////////容易出错
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
	threadfood.lock();
	Coord* coord = createRandomCoord();
	Food* newFood = new Food(coord, Type);
	threadfood.unlock();
}


void createAllFood()
{

	
	//srand(time(NULL));
	Sleep(20);
	while (!GameOver)
	{

		if (foods.size()<6)
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




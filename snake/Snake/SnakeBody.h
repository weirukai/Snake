#pragma once
#include<stdio.h>
#include"Node.h"
#include"Coord.h"
#include"map.h"
using namespace std;


class SnakeBody
{
public:
	Node* head;//头指针指向的是第一个node
	Node* tail;
	int length;//表示的是蛇身的长度
	int direction;
	SnakeBody(Coord* coord);
	~SnakeBody();
	void snakeMove();
	void snakeTurn(int keyPressed);
	void sankeEat(int FoodType);
};

////碰撞检测，碰撞检测，碰撞检测，碰撞检测
void clissionDetect();



 

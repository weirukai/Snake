#pragma once
#include<stdio.h>
#include"Node.h"
#include"Coord.h"
#include"map.h"
using namespace std;


class SnakeBody
{
public:
	Node* head;//ͷָ��ָ����ǵ�һ��node
	Node* tail;
	int length;//��ʾ��������ĳ���
	int direction;
	SnakeBody(Coord* coord);
	~SnakeBody();
	void snakeMove();
	void snakeTurn(int keyPressed);
	void sankeEat(int FoodType);
};

////��ײ��⣬��ײ��⣬��ײ��⣬��ײ���
void clissionDetect();



 

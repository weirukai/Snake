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
	vector<Food*> ::iterator it;//����һ��������
	//ʳ������ɲ��ܹ������ڱ߽�������Լ��Ѿ����ڵ�ʳ�������
	//�����Ǽ��Ĺ���
	Coord* coord = new Coord();
	int x = 0;
	int y = 0;
	bool getRightPlace = true;
	Node* ptr = playerSnake->head;
	srand(time(NULL));
	
		//���ɵ�������꣬���ұ�֤���������ڱ߽�����
	x = createRandom() % (maxhor - 1) + 1;
	y = createRandom() % (maxver - 1) + 1;
	//�������
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
		//��������������ʳ��
		
		if (x == (*it)->coord->hor && y == (*it)->coord->ver)//������ָ������
		{
			getRightPlace = false;
		}
	}
	


	while (!getRightPlace)
	{

		x = createRandom() % (maxhor - 2) + 1;
		y = createRandom() % (maxver - 2) + 1;
		//�������
		while (ptr != NULL)
		{
			if (x == ptr->coord->hor && y == ptr->coord->ver)
			{
				getRightPlace = false;
			}
		}

		for (it = foods.begin(); it != foods.end(); it++)
		{
			//��������������ʳ��
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




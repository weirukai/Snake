#include<easyx.h>
#include<stdio.h>
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<dos.h>
#include"map.h"
#include"Node.h"
#include"Coord.h"
#include"SnakeBody.h"
#include"globalvar.h"
//////■
void drawSnake()
{
	setfillcolor(BLUE);
	//遍历所有的蛇身，然后把蛇身打印出
	Node* ptr = playerSnake->head;
	while (ptr != NULL)
	{
		solidrectangle(ptr->x, ptr->y, ptr->right, ptr->bottom);//left,top,right,bottom
		ptr = ptr->next;
	}


}
void initMap(int step)
{
	//初始化相应的地图元素
	//初始化欢迎界面
	//初始化墙体
	SnakeBody* snakeBody = new SnakeBody(new Coord(12, 12));
	playerSnake = snakeBody;
	while (true)
	{
		cleardevice();
		Sleep(10);
		snakeBody->snakeMove();
		
		drawSnake();
		Sleep(SPEEDFIRST);
	}
}




void draw(int step)
{
	setlinecolor(0xabcdef);
	setfillcolor(0xabcdef);
	while (!GameVoer)
	{
		setbkcolor(0xffffff);
		cleardevice();
		Sleep(200);

	    drawSnake();
		Sleep(10);
		
	}
}

void drawWelcome()
{
	settextcolor(0x2E8B57);
	settextstyle(100, 100,_T("menulis"));
	TCHAR ch[] = _T("WELCOME");
	outtextxy(50, 100, ch);
	TCHAR ch2[] = _T("SNAKE");
	outtextxy(150, 200, ch2);
	
}

void drawFood()
{

}
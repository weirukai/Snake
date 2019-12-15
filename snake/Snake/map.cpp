#include<stdio.h>
#include<iostream>
#include<easyx.h>
#include<list>
#include<conio.h>
#include<random>

#include"map.h"
#include"Node.h"
#include"Coord.h"
#include"SnakeBody.h"
#include"globalvar.h"
#include"Food.h"
using namespace std;
//////■


//定义一个用于遍历食物list的迭代器
vector<Food*>::iterator it;
extern vector<Food*>foods;
extern int** walls;//引用外部的walls数组记录所有墙体的信息
//图片资源文件

IMAGE image1,image2,image3;


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



/*绘制地图的围墙*/
void drwaWall(int step)
{
	
	Coord* wallCoord = new Coord(0,0);
	setfillcolor(0x90EE90);
	for (int i = 0; i < maxhor; i++)
	{
		for (int j = 0; j < maxver; j++)
		{
			if (i==0||i==maxhor-1||j==0||j==maxver-1)
			{
				//walls[j][i] = WALL;
				solidcircle(i * width + width / 2, j * width + width / 2, width / 2);
			}
		}

	}
}


void drawFood()
{
	
	for (it=foods.begin();it!=foods.end();it++)
	{
		if (APPLE==((*it)->type))
		{
			putimage((*it)->x, (*it)->y, &image1);
		}
		else if(STRAWBERRY==((*it)->type))
		{
			//保持闪烁，有时候过来绘制有时候不绘制
			if (createRandom() % 2== 0)
			{
				putimage((*it)->x, (*it)->y, &image2);
			}
		}
		else if(BOMB==(*it)->type)
		{
			putimage((*it)->x, (*it)->y, &image3);
		}
	}

	
}






/**/
void initMap(int step)
{
	//初始化相应的地图元素
	//初始化欢迎界面
	//初始化墙体
	SnakeBody* snakeBody = new SnakeBody(new Coord(12, 12));
	playerSnake = snakeBody;
	int keyPressed=0;

	/*for (int i = 0; i < maxver; i++)
	{
		walls[i] = new int[maxhor];
	}*/
	

	loadimage(&image1, _T("D:\\VS\\snake\\apple1.png"));//////////贴图的操作
	loadimage(&image2, _T("D:\\VS\\snake\\strawberry.png"));
	loadimage(&image3, _T("D:\\VS\\snake\\bomb.png"));

	//游戏的主题应该在这个循环中
	while (true)
	{
		//直行
		snakeBody->snakeMove();

		//转弯
		if (_kbhit()!=0)
		{
			keyPressed = _getch();//获得按键的键值
			snakeBody->snakeTurn(keyPressed);
		}
		//生成食物
		clissionDetect();
		Sleep(SPEEDFIRST);
	}
}



void drawGameOver()
{
	if (GameOver == false)
		return;
	cleardevice;
	settextcolor(0x2E8B57);
	settextstyle(10, 100, _T("menulis"));
	TCHAR ch[] = _T("GAMEOVER");
	outtextxy(50, 100, ch);
	//TCHAR ch2[] = _T("SNAKE");
	//outtextxy(150, 200, ch2);

}


void draw(int step)
{
	setlinecolor(0xabcdef);
	setfillcolor(0xabcdef);
	while (!GameOver)
	{
		setbkcolor(0xD4F2E7);
		cleardevice();
		
		BeginBatchDraw();
		drwaWall(step);
	    drawSnake();
		drawFood();
		FlushBatchDraw();
		EndBatchDraw();
		
		Sleep(200);
	}
	//drawGameOver();
}

void drawWelcome()
{


	settextcolor(0x2E8B57);
	settextstyle(100, 100,_T("menulis"));
	TCHAR ch[] = _T("WELCOME");
	outtextxy(50, 100, ch);
	TCHAR ch2[] = _T("SNAKE");
	outtextxy(150, 200, ch2);
	
	
		/*for (int y = 0; y <= 600; y++)
		{
			setlinecolor(RGB(0, 0, y / 3));
			line(0, y, 800, y);
		}
		settextcolor(GREEN);
		settextstyle(50, 20, _T("menulis"));
		outtextxy(140, 100 + 40, _T("welcome to the game time!"));
		settextstyle(60, 30, _T("menulis"));
		outtextxy(450, 200 + 40, _T("——"));
		outtextxy(500, 200 + 40, _T("snake"));
		*/



		setbkcolor(RGB(255, 127, 36));
		settextcolor(LIGHTGRAY);
		settextstyle(40, 20, _T("menulis"));
		outtextxy(130, 350, _T("start"));
		outtextxy(350, 350, _T("about"));
		outtextxy(560, 350, _T("quit"));
		outtextxy(250, 450, _T("制作人：魏如凯"));
		//ne(0, 390, 800, 390);
		//以上仅画图，没有页面的跳转

		
		int page;
		MOUSEMSG m;
		while (1)
		{
			m = GetMouseMsg();
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN:     //左键按下
				if (m.x > 130 && m.x < 230 && m.y>350 && m.y < 390)
				{
					//第一个按钮
					setlinecolor(GREEN);
					circle(400, 300, 10);
				}
				else if (m.x > 350 && m.x < 450 && m.y>350 && m.y < 390)
				{
					setlinecolor(RED);
					circle(400, 300, 10);           //第二个按钮
				}
				else if (m.x > 560 && m.x < 660 && m.y>350 && m.y < 390)
				{
					setlinecolor(DARKGRAY);
					circle(400, 300, 10);        //第三个按钮
				}
			}
		}
    //return 1;
}



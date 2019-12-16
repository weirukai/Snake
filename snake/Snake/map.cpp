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
#include"IO.h"
using namespace std;
//////■


//定义一个用于遍历食物list的迭代器
vector<Food*>::iterator it;
extern vector<Food*>foods;
extern int walls[60][80];//引用外部的walls数组记录所有墙体的信息

int* rankList;


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
				walls[j][i] = WALL;
				solidcircle(i * width + width / 2, j * width + width / 2, width / 2);
			}
		}

	}
	if (step==STEPTWO)
	{
		
		for (int i = 0; i < maxhor; i++)
		{

			for (int j = 0; j < maxver; j++)
			{
				if (i==maxhor/3&&j<maxver/2||i==2*maxhor/3&&j>maxver/2)
				{
					walls[j][i] = WALL;
					solidcircle(i * width + width / 2, j * width + width / 2, width / 2);

				}

			}

		}

		

	}
	else if(step==STEPTHREE)
	{
		for (int i = 0; i < maxhor; i++)
		{
			for (int j = 0; j < maxver; j++)
			{

				if ((j==maxver/4&&i<maxhor/2)||(j==maxver/2&&i>maxhor/2)||(j==3*maxver/4&&i<maxhor/2))
				{
					walls[j][i] = WALL;
					solidcircle(i * width + width / 2, j * width + width / 2, width / 2);
				}
			}
		}

	}

}


/*绘制所有的食物*/
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
			if (createRandom() % 4== 0)
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


/*绘制分数*/
void drawMarks()
{
	//分数就设置成蛇身的长度
	settextcolor(0xDC143C);
	settextstyle(15, 15, _T("Didot"));
	TCHAR ch[] = _T("CurrentMarks:");
	outtextxy(10, 10, ch);
	settextcolor(0xF4A460);
	TCHAR ch2[4];
	 swprintf_s(ch2,_T("%d"),playerSnake->length-3);
	 outtextxy(210, 10, ch2);
	 //显示记录中的最高分
	 TCHAR ch3[] = _T("HighestMark:");
	 outtextxy(10, 25, ch3);
	 TCHAR ch4[4];
	 swprintf_s(ch4, _T("%d"), rankList[0]);
	 outtextxy(210, 25, ch4);
	 
}


/**/
void initMap(int step)
{
	//初始化相应的地图元素
	//初始化欢迎界面
	//初始化墙体
	rankList = rankRead();

	SnakeBody* snakeBody = new SnakeBody(new Coord(12, 12));
	playerSnake = snakeBody;
	

	for (int i = 0; i < maxver; i++)
	{
		for (int j = 0; j < maxhor; j++)
		{
			walls[i][j]= 0;
		}
		
	}
	loadimage(&image1, _T("D:\\VS\\snake\\apple1.png"));//////////贴图的操作
	loadimage(&image2, _T("D:\\VS\\snake\\strawberry.png"));
	loadimage(&image3, _T("D:\\VS\\snake\\bomb.png"));

	//游戏的主题应该在这个循环中
	
}


void Game()
{
	int keyPressed = 0;
	while (!GameOver)
	{
		//直行
		 playerSnake->snakeMove();

		//转弯
		if (_kbhit() != 0)
		{
			keyPressed = _getch();//获得按键的键值
			playerSnake->snakeTurn(keyPressed);
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


	//将游戏的得分存储
	rankwrite(playerSnake->length - 3);
	setbkcolor(0xD4F2E7);
	//cleardevice();
	//clearcircle(200, 200, 200);
	settextcolor(0x2E8B57);
	settextstyle(100, 100, _T("menulis"));
	TCHAR over[] = _T("GAMEOVER");
	outtextxy(0, 120, over);
	//绘制排行榜，仅仅绘前五名
	TCHAR rank[5][4];
	for (int i = 0; i < 5; i++)
	{
		swprintf_s(rank[i], _T("%d"), rankList[i]);
	}
	TCHAR rankNum[5][2];
	int  number[5] = { 1,2,3,4,5 };
	for (int i = 0; i < 5; i++)
	{
		swprintf_s(rankNum[i], _T("%d"), number[i]);
	}
	settextstyle(20, 20, _T("menulis"));

	TCHAR tips[5] = _T("NO");
	TCHAR comma[2] = _T(".");

	for (int i = 0; i < 5; i++)
	{
		settextstyle(20, 20, _T("menulis"));
		outtextxy(300, i * 22 + 300, tips);
		settextstyle(2, 20, _T("menulis"));
		outtextxy(340, i * 22 + 320, comma);
		settextstyle(20, 20, _T("menulis"));
		outtextxy(346, i * 22 + 300, rankNum[i]);
		outtextxy(400, i * 22 + 300, rank[i]);
	}
	


	
	Sleep(10);
	
	

}


void draw(int step)
{
	Sleep(10);
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
		drawMarks();

		FlushBatchDraw();
		EndBatchDraw();
		
		Sleep(200);
	}
	drawGameOver();
}

int  drawWelcome()
{
	settextcolor(0x2E8B57);
	settextstyle(100, 100,_T("menulis"));
	TCHAR ch[] = _T("WELCOME");
	outtextxy(50, 100, ch);
	TCHAR ch2[] = _T("SNAKE");
	outtextxy(150, 200, ch2);

		//setbkcolor(RGB(255, 127, 36));
		settextcolor(LIGHTGRAY);
		settextstyle(30, 20, _T("menulis"));
		outtextxy(130, 350, _T("map I"));
		//solidroundrect(130, 370, 210, 200, 20, 20);
		outtextxy(350, 350, _T("map II"));
		outtextxy(560, 350, _T("map III"));
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
					return STEPONE;
				}
				else if (m.x > 350 && m.x < 450 && m.y>350 && m.y < 390)
				{
				   return	STEPTWO;         //第二个按钮
				}
				else if (m.x > 560 && m.x < 660 && m.y>350 && m.y < 390)
				{
					return STEPTHREE;       //第三个按钮
				}
			}
		}
    //return 1;
}




/*下面是一个文件的读取的操作**/

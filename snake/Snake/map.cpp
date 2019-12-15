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
//////��


//����һ�����ڱ���ʳ��list�ĵ�����
vector<Food*>::iterator it;
extern vector<Food*>foods;
extern int** walls;//�����ⲿ��walls�����¼����ǽ�����Ϣ
//ͼƬ��Դ�ļ�

IMAGE image1,image2,image3;


void drawSnake()
{
	setfillcolor(BLUE);
	//�������е�����Ȼ��������ӡ��
	Node* ptr = playerSnake->head;
	
	while (ptr != NULL)
	{	    
		solidrectangle(ptr->x, ptr->y, ptr->right, ptr->bottom);//left,top,right,bottom
		ptr = ptr->next;	
	}
}



/*���Ƶ�ͼ��Χǽ*/
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
			//������˸����ʱ�����������ʱ�򲻻���
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
	//��ʼ����Ӧ�ĵ�ͼԪ��
	//��ʼ����ӭ����
	//��ʼ��ǽ��
	SnakeBody* snakeBody = new SnakeBody(new Coord(12, 12));
	playerSnake = snakeBody;
	int keyPressed=0;

	/*for (int i = 0; i < maxver; i++)
	{
		walls[i] = new int[maxhor];
	}*/
	

	loadimage(&image1, _T("D:\\VS\\snake\\apple1.png"));//////////��ͼ�Ĳ���
	loadimage(&image2, _T("D:\\VS\\snake\\strawberry.png"));
	loadimage(&image3, _T("D:\\VS\\snake\\bomb.png"));

	//��Ϸ������Ӧ�������ѭ����
	while (true)
	{
		//ֱ��
		snakeBody->snakeMove();

		//ת��
		if (_kbhit()!=0)
		{
			keyPressed = _getch();//��ð����ļ�ֵ
			snakeBody->snakeTurn(keyPressed);
		}
		//����ʳ��
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
		outtextxy(450, 200 + 40, _T("����"));
		outtextxy(500, 200 + 40, _T("snake"));
		*/



		setbkcolor(RGB(255, 127, 36));
		settextcolor(LIGHTGRAY);
		settextstyle(40, 20, _T("menulis"));
		outtextxy(130, 350, _T("start"));
		outtextxy(350, 350, _T("about"));
		outtextxy(560, 350, _T("quit"));
		outtextxy(250, 450, _T("�����ˣ�κ�翭"));
		//ne(0, 390, 800, 390);
		//���Ͻ���ͼ��û��ҳ�����ת

		
		int page;
		MOUSEMSG m;
		while (1)
		{
			m = GetMouseMsg();
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN:     //�������
				if (m.x > 130 && m.x < 230 && m.y>350 && m.y < 390)
				{
					//��һ����ť
					setlinecolor(GREEN);
					circle(400, 300, 10);
				}
				else if (m.x > 350 && m.x < 450 && m.y>350 && m.y < 390)
				{
					setlinecolor(RED);
					circle(400, 300, 10);           //�ڶ�����ť
				}
				else if (m.x > 560 && m.x < 660 && m.y>350 && m.y < 390)
				{
					setlinecolor(DARKGRAY);
					circle(400, 300, 10);        //��������ť
				}
			}
		}
    //return 1;
}



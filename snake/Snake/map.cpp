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
extern int walls[60][80];//�����ⲿ��walls�����¼����ǽ�����Ϣ
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


/*�������е�ʳ��*/
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


/*���Ʒ���*/
void drawMarks()
{
	//���������ó�����ĳ���
	settextcolor(0xDC143C);
	settextstyle(15, 15, _T("Didot"));
	TCHAR ch[] = _T("CurrentMarks:");
	outtextxy(10, 10, ch);
	settextcolor(0xF4A460);
	TCHAR ch2[4];
	 swprintf_s(ch2,_T("%d"),playerSnake->length-3);
	 outtextxy(210, 10, ch2);
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

	for (int i = 0; i < maxver; i++)
	{
		for (int j = 0; j < maxhor; j++)
		{
			walls[i][j]= 0;
		}
		
	}
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
	settextstyle(100, 100, _T("menulis"));
	TCHAR ch[] = _T("GAMEOVER");
	outtextxy(0, 100, ch);
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
		drawMarks();


		FlushBatchDraw();
	//	EndBatchDraw();
		
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
					return STEPONE;
				}
				else if (m.x > 350 && m.x < 450 && m.y>350 && m.y < 390)
				{
				   return	STEPTWO;         //�ڶ�����ť
				}
				else if (m.x > 560 && m.x < 660 && m.y>350 && m.y < 390)
				{
					return STEPTHREE;       //��������ť
				}
			}
		}
    //return 1;
}




/*������һ���ļ��Ķ�ȡ�Ĳ���**/
int* rankRead()
{
	
	FILE* rank;
	fopen_s(&rank,"D:\\VS\\snake\\Snake\\rank.txt", "r+");
	int* rankArray = new int[15]{-1};
	int index =0;
	while (!feof(rank))
	{
		fscanf_s(rank, "%d,", &rankArray[index++]);
	}
	//int b = rankArray[2];
	return rankArray;
 }
void rankwrite()
{

}
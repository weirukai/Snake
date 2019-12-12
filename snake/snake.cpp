// snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//非图形库，利用光标跳转完成的图形制作

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>//windows编程头文件
#include <time.h>
#include <conio.h>//控制台输入输出头文件
#define SNAKESIZE 100 //定义最长的蛇身
#define MAPWIDTH 100    //地图大小
#define MAPHEIGHT 29
//key
#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'p'

void position(int x,int y);
//食物对象
struct food {
	int x, y;//食物坐标
	bool glass;
	void printfood()
	{

		position(x, y);
		if (glass)
			printf("0");
		else
		{
			printf("o");
		}
	}
}* snakefood;
//蛇身对象
struct snake
{
	int x;
	int y;
	struct snake *prior,*next;
	void printsnake()
	{
		position(x, y);
		printf("*");
	}
};
//开局属性设置,全局变量区
snake* head, *tail;
int key = 1;
int speed=200;
int score = 0;

//绘制游戏边框
void drawMap();
//随机生成食物
food* createFood();
//按键操作
int keyDown();
//蛇的移动
void snaketurn();
//尾巴的迁移
void tailmove(int,int);
//蛇吃食物
void snakeeat();

//边界和蛇身的触碰检查
bool judge();
//游戏的分数的显示
void printscore();
////游戏的运行刷新界面
void rungame();
//从控制台移动光标
void position(int x, int y)
{
	HANDLE output;
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pst;  //字符在控制台上面的坐标
	pst.X = x;
	pst.Y = y;
	SetConsoleCursorPosition(output, pst);
};
//利用position函数绘制地图
//初始化地图以及蛇身，初始化游戏界面
void drawMap()
{
	//上下边界
	for (int i = 0; i < MAPWIDTH; i++)
	{
		position(i, 0);
		printf("*");
		position(i, MAPHEIGHT);
		printf("*");
	}
	//左右边界
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		position(0, i);
		printf("*");
		position(MAPWIDTH, i);
		printf("*");
	}        //■
	position(101, 13);
	printf("****************");
	position(101, 16);
	printf("****************");
	position(102, 15);
	printf("当前得分：%d", score);
	//蛇身初始化
	head = new snake;
	tail = new snake;
	head->x = 10;
	head->y = 10;
	head->next = tail;
	head->prior = NULL;
	head->printsnake();
	tail->x = 9;
	tail->y = 10;
	tail->prior = head;
	tail->next = NULL;
	tail->printsnake();
};
food* createFood()
{
	int x, y;
	LARGE_INTEGER seed;//取硬件精度计数器，在1s之内可以创建多个随机数
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(seed.QuadPart);
	x = rand() % 99 + 1;
	srand(seed.QuadPart);
	y = rand() % (MAPHEIGHT - 1) + 1;

	//检查是否生成在了蛇身之上
	snake* judge = head;
	while (x==judge->x&&y==judge->y)
	{
		srand(seed.QuadPart);
		x = rand() % 99 + 1;
		srand(seed.QuadPart);
		y = rand() % (MAPHEIGHT - 1) + 1;
		judge = judge->next;
	}
	food* snakefood;
	int glass;
	snakefood = new food;
	snakefood->x = x;
	snakefood->y = y;
	srand(seed.QuadPart);
	glass = rand() % 4;
	if (glass==0)
	{
		snakefood->glass = true;
	}
	else
	{
		snakefood->glass = false;
	}
	snakefood->printfood();
	return snakefood;
}
//蛇身的转弯移动效果
void snaketurn()
{
	//重新打印蛇身就好了，还要保证蛇是在连续跑动
	switch (key)
	{
	case up:
		if ((head->x > head->next->x))
		{
			tailmove(head->x,head->y-1);
			break;
		}
		else if (head->x<head->next->x)
		{
			tailmove(head->x, head->y - 1);
			break;
		}
	case down:
		if (head->y==head->next->y)
		{
			tailmove(head->x, head->y + 1);
			break;
		}
	case left:
		if (head->x==head->next->x)
		{
			tailmove(head->x - 1, head->y);
			break;
		}
	case right:
		if (head->x==head->next->x)
		{
			tailmove(head->x + 1, head->y);
			break;
		}
	default:
		break;
	}
	//重新打印蛇身
	    snake* ptr;//这个ptr用来辅助打印蛇身
		ptr = head;
		while (ptr!=NULL)
		{
			ptr->printsnake();
			ptr = ptr->next;
		}
		Sleep(speed);
}
//蛇身直行效果
void movestraight()
{
	if (head->x>head->next->x)
	{
		tailmove(head->x + 1, head->y);
	}
	else if (head->x < head->next->x)
	{
		tailmove(head->x - 1, head->y);
	}
	else if (head->y<head->next->y)
	{
		tailmove(head->x, head->y - 1);
	}
	else
	{
		tailmove(head->x, head->y + 1);
	}
	//打印蛇身
	snake* ptr;
	ptr = head;
	while (ptr!=NULL)
	{
		ptr->printsnake();
		ptr = ptr->next;
	}
	Sleep(speed);
}
//尾巴的移动,双向链表的优越性
void tailmove(int x,int y)
{
	//去除尾巴，然后重新打印蛇身
	position(tail->x, tail->y);
	printf(" ");
	tail->x = x;
	tail->y = y;
	tail->next = head;
	head->prior = tail;
	head = tail;
	tail = tail->prior;
	head->prior = NULL;
	tail->next = NULL;
}
//处理按键信息,仅仅用来获取按键
int keyDown()
{
	if (_kbhit())
	{
		key = _getch();
		return 0;
	}
	return 1;
}
//蛇吃东西的操作
void snakeeat()
{
	//吃到智慧草，加两分，身长不变
	if ((head->x==snakefood->x&&head->y==snakefood->y)&&(snakefood->glass==true))
	{
		score += 2;
		snakefood = createFood();
	}
	//普通食物，加一分，身长加1
	else if ((head->x == snakefood->x && head->y == snakefood->y) && (snakefood->glass == false))
	{
		score += 1;
		snake* newsk;
		newsk = new snake;
		newsk->x = 2 * tail->x - tail->prior->x;
		newsk->y = 2 * tail->y - tail->prior->y;
		newsk->prior = tail;
		tail->next = newsk;
		tail = newsk;
		tail->next = NULL;
		snakefood = createFood();

	}
	
}
bool judge()
{
	snake* ptr = head->next;//协助遍历蛇身，判断是否蛇头触碰到蛇身
	bool touch = false;
	while (ptr != NULL)
	{
		if (ptr->x == head->x && ptr->y == head->y)
		{
			touch = true;
		}
		ptr = ptr->next;
	}
	if (head->x == 0 || head->y == 0 || head->x == MAPWIDTH || head->y == MAPHEIGHT || touch)
	{
		return false;
	}
	return true;
}
void printscore()
{
	position(112, 15);
	printf("%d", score);
}
void rungame()
{
	while (1)
	{
		if (keyDown()==0)
		{
			snaketurn();
			snakeeat();
			printscore();
			if (!judge())
			{
				Sleep(1000);
			}
		}
		else
		{
			movestraight();
			snakeeat();
			printscore();
			if(!judge())
			{
				Sleep(1000);
			}
		}
	}
}

int main()
{
	drawMap();
	snakefood=createFood();
	rungame();
	return 0;
}





















// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

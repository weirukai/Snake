#include<Windows.h>
#include<random>
#include"globalvar.h"



 int screenWidth = 800;
  int screenHeight = 600;
 int width = 10;
 int height = 10;
 int walls[60][80] = {0};
 int  maxhor = screenWidth / width;//80
 int  maxver = screenHeight / height;//60
 bool GameOver = false;
 SnakeBody* playerSnake = NULL;
vector<Food*> foods;

//int marks = playerSnake->length;

int createRandom()
{
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(seed.QuadPart);
    return rand();
}

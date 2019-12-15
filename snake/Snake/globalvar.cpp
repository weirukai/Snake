#include<Windows.h>
#include<random>
#include"globalvar.h"



 int screenWidth = 800;
  int screenHeight = 600;
 int width = 10;
 int height = 10;

 int  maxhor = screenWidth / width;
 int  maxver = screenHeight / height;
 bool GameVoer = false;
 SnakeBody* playerSnake = NULL;
vector<Food*> foods;
int createRandom()
{
    LARGE_INTEGER seed;
    QueryPerformanceFrequency(&seed);
    QueryPerformanceCounter(&seed);
    srand(seed.QuadPart);
    return rand();
}

#pragma once
#ifndef globalvar_h
#define globalvar_h
#include"SnakeBody.h"
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

//蛇的移动速度
#define SPEEDFIRST 1000
extern int screenWidth;
extern  int screenHeight;
extern int width;
extern int height;
extern int  maxhor;
extern int  maxver;
extern bool GameVoer;
extern SnakeBody* playerSnake;
#endif // !globalvar_h

#pragma once

#ifndef globalvar_h
#define globalvar_h
#include <vector>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include"SnakeBody.h"
#include"Food.h"
using namespace std;
//���巽��
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
//���幦�ܰ���
#define VK_LEFT 65
#define VK_RIGHT 68
#define VK_UP 87
#define VK_DOWN 83
#define ESC 27
#define ENTER 13
//�ߵ��ƶ��ٶ�
#define SPEEDFIRST 1000
#define SPEEDSECOND  500

//����ʳ�������
#define APPLE 10
#define STRAWBERRY 20
#define BOMB 30
#define SMARTGRASS 40



extern vector<Food*> foods;
extern int screenWidth;
extern  int screenHeight;
extern int width;
extern int height;
extern int  maxhor;
extern int  maxver;
extern bool GameVoer;
extern SnakeBody* playerSnake;


int createRandom();
//
#endif // !globalvar_h

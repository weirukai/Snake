#pragma once

#ifndef globalvar_h
#define globalvar_h
#include <vector>
#include<conio.h>
#include<thread>
#include<stdio.h>
#include<iostream>
#include<mutex>
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
#define SPEEDFIRST 100
#define SPEEDSECOND  500

//����ʳ�������
#define APPLE 10
#define STRAWBERRY 20
#define BOMB 30
#define SMARTGRASS 40

#define WALL -1236567

///����ؿ�
#define STEPONE  111
#define STEPTWO  222
#define STEPTHREE 333

#define FOODNUM 6


extern vector<Food*> foods;
extern int screenWidth;
extern  int screenHeight;
extern int width;
extern int height;
extern int  maxhor;
extern int  maxver;
extern bool GameOver;
extern SnakeBody* playerSnake;

extern int walls[60][80];//�����е�ǽ����Ϣ������һ����ά������

//��ǰ�ķ���
extern int marks;


extern mutex threadfood;

int createRandom();
//
#endif // !globalvar_h

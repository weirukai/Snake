#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include "SnakeBody.h"
#include"Coord.h"
#include"map.h"
#include"Node.h"
#include"globalvar.h"



extern int walls[60][80];


SnakeBody::SnakeBody(Coord* coord)
{
	this->head = new Node(coord, NULL, NULL);//��Ϊһ���սڵ㣻
	head->next = new Node(new Coord(coord->hor - 1, coord->ver), head, NULL);
	this->tail = new Node(new Coord(coord->hor - 2, coord->ver), head->next, NULL);
	tail->previous->next = tail;
	this->length = 3;//��ʼ����ʱ��ֻ�������ڵ�
	this->direction = RIGHT;

}



//�ߵ����ߣ�ֻ������һ��
void SnakeBody::snakeMove()
{
	Node* tailePre = tail->previous;
	Node* headNext = head->next;
	Coord* headCoord = this->head->coord;
	switch (this->direction)
	{
		//ͷ�ڵ����ߣ����һ���ڵ��䵽ͷ�ڵ����
	case RIGHT:
		//������������
		this->head->setCoord(new Coord(headCoord->hor+1,head->coord->ver));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tail->setCoord(new Coord(head->coord->hor - 1, head->coord->ver));
		tail = tailePre;
		tail->next = NULL;
		break;
	case LEFT:
		//������������
		this->head->setCoord(new Coord(headCoord->hor-1,headCoord->ver));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tail->setCoord(new Coord(head->coord->hor + 1, head->coord->ver));
		tail = tailePre;
		tail->next = NULL;
		break;
	case UP:
		this->head->setCoord(new Coord(headCoord->hor, headCoord->ver-1));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tail->setCoord(new Coord(head->coord->hor , head->coord->ver+1));
		tail = tailePre;
		tail->next = NULL;
		break;
	case DOWN:
		this->head->setCoord(new Coord(headCoord->hor, headCoord->ver + 1));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tail->setCoord(new Coord(head->coord->hor, head->coord->ver - 1));
		tail = tailePre;
		tail->next = NULL;
		break;
	}
}


void SnakeBody::snakeTurn(int keyPressed)
{
	Coord* headCoord = this->head->coord;
	Node* tailePre = this->tail->previous;
	Node* headNext = this->head->next;
	//�����û��İ��������룬�����ת��
	if (keyPressed==VK_DOWN&&this->direction!=UP)
	{
		this->direction = DOWN;
		this->head->setCoord(new Coord(headCoord->hor, headCoord->ver + 1));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tailePre->next = NULL;
		tail->setCoord(new Coord(headCoord->hor, headCoord->ver ));
		tail = tailePre;
	}
	else if(keyPressed==VK_LEFT&&this->direction!=RIGHT)
	{
		this->direction = LEFT;
		this->head->setCoord(new Coord(headCoord->hor-1, headCoord->ver ));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tailePre->next = NULL;
		tail->setCoord(new Coord(headCoord->hor, headCoord->ver ));
		tail = tailePre;
	}
	else if (keyPressed==VK_RIGHT&&this->direction!=LEFT)
	{
		this->direction = RIGHT;
		this->head->setCoord(new Coord(headCoord->hor +1, headCoord->ver));
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tailePre->next = NULL;
		tail->setCoord(new Coord(headCoord->hor , headCoord->ver));
		tail = tailePre;
	}
	else if(keyPressed==VK_UP&&this->direction!=DOWN)
	{
		this->direction = UP;
		this->head->setCoord(new Coord(headCoord->hor , headCoord->ver-1));
		//��һ������headCoord��ֵ��Ȼ��û�б�ģ�Ϊʲô��ָ��������е�ֵ�����Ѿ��ı�����
		head->next = tail;
		tail->previous = head;
		tail->next = headNext;
		headNext->previous = tail;
		tailePre->next = NULL;
		tail->setCoord(new Coord(headCoord->hor , headCoord->ver));//����headCoord��ֵû�з����ı�
		tail = tailePre;
	}
}
void SnakeBody::snakeEat(int type)
{
	

	if (type==APPLE)
	{
		this->length++;//�÷�ͨ��������ȷ����
		int newHor = 2 * tail->coord->hor - tail->previous->coord->hor;
		int newVer = 2 * tail->coord->ver - tail->previous->coord->ver;
		Node* newtail = new Node(new Coord(newHor, newVer), this->tail, NULL);
		tail->next = newtail;
		tail = newtail;
	}
	else if(type==STRAWBERRY)
	{
		if (this->length<=3)
		{
			GameOver = true;
		}
		this->length--;
		tail = tail->previous;
		tail->next->previous = NULL;
		tail->next = NULL;
	}
	else if(type==BOMB)
	{
		if (this->length < 6)
		{
			//ִ�н������
			GameOver = true;
		}
		else
		{
			this->length = this->length / 2;
			Node* newTail = playerSnake->head;
			for (int i = 0; i < this->length-1 ; i++)
			{
				newTail = newTail->next;
			}
			tail = newTail;
			tail->next->previous = NULL;
			tail->next = NULL;
			
		}
	}

}


/**/
void clissionDetect()
{
	Node* head = playerSnake->head;
	//����ǽ��
	if (walls[head->coord->ver][head->coord->hor]==WALL)
	{
		GameOver = true;
	}
	

	 //����ʳ��
	for (std::vector<Food*>::iterator i=foods.begin(); i!=foods.end(); )
	{
		if (head->coord->hor==(*i)->coord->hor&&head->coord->ver==(*i)->coord->ver)
		{
			playerSnake->snakeEat((*i)->type);
			i=foods.erase(i);
		}
		else
		{
			i++;
		}
	}

	//��������,��Ϸ����
    if(false)
	{

	}



}
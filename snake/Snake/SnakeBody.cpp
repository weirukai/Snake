#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include "SnakeBody.h"
#include"Coord.h"
#include"map.h"
#include"Node.h"
#include"globalvar.h"

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

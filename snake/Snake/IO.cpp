#include<stdio.h>
#include<vector>
#include"IO.h"
#include"map.h"
#include"globalvar.h"
#include"Food.h"
extern vector<Food *> foods;

void sort(int* rankArray, int length)
{
	//对rankArray中的数据进行一个排序的操作
	//采用插入排序
	int temp;
	int j;
	for (int i = 0; i < length; i++)
	{
		temp = rankArray[i];
		for (j = i; j > 0 && rankArray[j-1] < temp; j--)
		{
			rankArray[j] = rankArray[j - 1];
		}
		rankArray[j] = temp;
	}
}
int* rankRead()
{
	FILE* rank;
	fopen_s(&rank, "D:\\VS\\snake\\Snake\\rank.txt", "r+");
	int* rankArray = new int[15]{ -1 };
	int index = 0;
	while (!feof(rank))
	{
		fscanf_s(rank, "%d,", &rankArray[index++]);
	}
	//int b = rankArray[2];
	fclose(rank);
	sort(rankArray,15);
	return rankArray;
}

void rankwrite(int newMark)
{
	FILE* rank;
	fopen_s(&rank, "D:\\VS\\snake\\Snake\\rank.txt", "a+");
	fprintf_s(rank, "%d,", newMark);
	fclose(rank);
}



//保存游戏的状态
void saveScene(int  step)
{

	
	FILE* scene; 
	fopen_s(&scene, "D:\\VS\\snake\\Snake\\scene.txt", "w");//每次过来之后覆盖掉这个信息
	//保存关卡信息
	fprintf_s(scene, "游戏地图：%d\n", step);

	//保存蛇身所有节点的位置，
	Node* ptr = playerSnake->head;
	while (ptr!=NULL)
	{
		//需要保存每个节点的
		fprintf_s(scene, "(%d,%d)\t", ptr->coord->hor, ptr->coord->ver);
		ptr = ptr->next;
	}
	fputc('\n', scene);
	//保存所有的食物的信息
	for (int i = 0; i < foods.size(); i++)
	{
		fprintf_s(scene, "%d:(%d,%d)\t",foods[i]->type,foods[i]->coord->hor,foods[i]->coord->ver);
	}
	fputc('\n', scene);
	//保存游戏的得分情况
	fprintf_s(scene, "%d", playerSnake->length - 3);
	fclose(scene);

	
}
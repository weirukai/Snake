#include<stdio.h>
#include"IO.h"


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

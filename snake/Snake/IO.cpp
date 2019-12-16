#include<stdio.h>
#include<vector>
#include"IO.h"
#include"map.h"
#include"globalvar.h"
#include"Food.h"
extern vector<Food *> foods;

void sort(int* rankArray, int length)
{
	//��rankArray�е����ݽ���һ������Ĳ���
	//���ò�������
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



//������Ϸ��״̬
void saveScene(int  step)
{

	
	FILE* scene; 
	fopen_s(&scene, "D:\\VS\\snake\\Snake\\scene.txt", "w");//ÿ�ι���֮�󸲸ǵ������Ϣ
	//����ؿ���Ϣ
	fprintf_s(scene, "��Ϸ��ͼ��%d\n", step);

	//�����������нڵ��λ�ã�
	Node* ptr = playerSnake->head;
	while (ptr!=NULL)
	{
		//��Ҫ����ÿ���ڵ��
		fprintf_s(scene, "(%d,%d)\t", ptr->coord->hor, ptr->coord->ver);
		ptr = ptr->next;
	}
	fputc('\n', scene);
	//�������е�ʳ�����Ϣ
	for (int i = 0; i < foods.size(); i++)
	{
		fprintf_s(scene, "%d:(%d,%d)\t",foods[i]->type,foods[i]->coord->hor,foods[i]->coord->ver);
	}
	fputc('\n', scene);
	//������Ϸ�ĵ÷����
	fprintf_s(scene, "%d", playerSnake->length - 3);
	fclose(scene);

	
}
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 25  // ��Ϸ����ߴ�
#define Width 50

// ȫ�ֱ���
int cells[High][Width]; // ����λ��ϸ����1����0

void gotoxy(int x,int y) //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup() // ���ݳ�ʼ��
{
	int i,j;
	for (i=0;i<High;i++) // ��ʼ��
		for (j=0;j<Width;j++)
		{
			cells[i][j] = 1;
		}
}

void show()  // ��ʾ����
{
	gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������ػ�����
	int i,j;
	for (i=1;i<=High-1;i++)
	{
		for (j=1;j<=Width-1;j++)
		{
			if (cells[i][j]==1)
				printf("*");  //   ������ϸ��
			else
				printf(" ");  //   ����ո�			
		}
		printf("\n");
	}
	Sleep(50);
}	

void updateWithoutInput()  // ���û������޹صĸ���
{	
	int NewCells[High][Width]; // ��һ֡��ϸ�����
	int NeibourNumber; //ͳ���ھӵĸ���
	int i,j;
	for (i=1;i<=High-1;i++)
	{
		for (j=1;j<=Width-1;j++)
		{
			NeibourNumber = cells[i-1][j-1] + cells[i-1][j] + cells[i-1][j+1]
				+ cells[i][j-1] + cells[i][j+1] + cells[i+1][j-1] + cells[i+1][j] + cells[i+1][j+1];
			if (NeibourNumber==3)
				NewCells[i][j] = 1;  
			else if (NeibourNumber==2)
				NewCells[i][j] = cells[i][j];
			else
				NewCells[i][j] = 0; 
		}
	}
	
	for (i=1;i<=High-1;i++)
		for (j=1;j<=Width-1;j++)
			cells[i][j] = NewCells[i][j];
}

void updateWithInput()  // ���û������йصĸ���
{
}

int main()
{
	startup();  // ���ݳ�ʼ��	
	while (1) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 20  // ��Ϸ����ߴ�
#define Width 30

// ȫ�ֱ���
int moveDirection; // С���ƶ�λ�ã��������ҷֱ���1��2��3��4��ʾ
int food_x,food_y; // ʳ���λ��
int canvas[High][Width] = {0}; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
	// 0Ϊ�ո�0��-1Ϊ�߿�#��-2Ϊʳ��F��1Ϊ��ͷ@������1������Ϊ����*

void gotoxy(int x,int y)  //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

// �ƶ�С��
// ��һ��ɨ������canvas����Ԫ�أ��ҵ�����Ԫ�ض�+1
// �ҵ����Ԫ�أ�����β�ͣ��������Ϊ0
// �ҵ�=2��Ԫ�أ�����ͷ�����ٸ���������������ҷ��򣬰Ѷ�Ӧ����һ������ֵ��Ϊ1������ͷ��
void moveSnakeByDirection()
{
	int i,j;
	for (i=1;i<High-1;i++)
		for (j=1;j<Width-1;j++)
			if (canvas[i][j]>0)
				canvas[i][j]++;

	int oldTail_i,oldTail_j,oldHead_i,oldHead_j;
	int max = 0;

	for (i=1;i<High-1;i++)
		for (j=1;j<Width-1;j++)
			if (canvas[i][j]>0)
			{
				if (max<canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}
				if (canvas[i][j]==2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}
			}

	int newHead_i,newHead_j;

	if (moveDirection==1) // �����ƶ�
	{
		newHead_i = oldHead_i-1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==2) // �����ƶ�
	{
		newHead_i = oldHead_i+1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==3) // �����ƶ�
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j-1;
	}
	if (moveDirection==4) // �����ƶ�
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j+1;
	}

	// ����ͷ����Ե�ʳ��
	if (canvas[newHead_i][newHead_j]==-2)
	{
		canvas[food_x][food_y] = 0;
		// ����һ���µ�ʳ��
		food_x = rand()%(High-5) + 2;
		food_y = rand()%(Width-5) + 2;
		canvas[food_x][food_y] = -2;

		// ԭ���ľ���β���ţ������Զ�+1
	}
	else // ����ԭ���ľ���β���������ֳ��Ȳ���
		canvas[oldTail_i][oldTail_j] = 0;

	// �Ƿ�С�ߺ�����ײ�����ߺͱ߿�ײ����Ϸʧ��
	if (canvas[newHead_i][newHead_j]>0 || canvas[newHead_i][newHead_j]==-1)
	{
		printf("��Ϸʧ�ܣ�\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	else
		canvas[newHead_i][newHead_j] = 1;
}

void startup() // ���ݳ�ʼ��
{
	int i,j;
	
	// ��ʼ���߿�
	for (i=0;i<High;i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width-1] = -1;
	}
	for (j=0;j<Width;j++)
	{
		canvas[0][j] = -1;
		canvas[High-1][j] = -1;
	}
	
	// ��ʼ����ͷλ��
	canvas[High/2][Width/2] = 1;
	// ��ʼ������������Ԫ��ֵ�ֱ�Ϊ2,3,4,5....
	for (i=1;i<=4;i++)
		canvas[High/2][Width/2-i] = i+1;

	// ��ʼС�������ƶ�
	moveDirection = 4;
	
	food_x = rand()%(High-5) + 2;
	food_y = rand()%(Width-5) + 2;
	canvas[food_x][food_y] = -2;
}

void show()  // ��ʾ����
{
	gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������ػ�����
	int i,j;
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]==0)
				printf(" ");   //   ����ո�
			else if (canvas[i][j]==-1)
				printf("#");   //   ����߿�#
			else if (canvas[i][j]==1)
				printf("@");   //   �����ͷ@
			else if (canvas[i][j]>1)
				printf("*");   //   �������*
			else if (canvas[i][j]==-2)
				printf("F");   //   ���ʳ��F
		}
		printf("\n");
	}
	Sleep(100);
}	

void updateWithoutInput()  // ���û������޹صĸ���
{
	moveSnakeByDirection();
}

void updateWithInput()  // ���û������йصĸ���
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a') 
		{
			moveDirection = 3;   // λ������
			moveSnakeByDirection();
		}
		else if (input == 'd')
		{
			moveDirection = 4;  // λ������
			moveSnakeByDirection();
		}
		else if (input == 'w')
		{
			moveDirection = 1;  // λ������
			moveSnakeByDirection();
		}
		else if (input == 's')
		{
			moveDirection = 2;   // λ������
			moveSnakeByDirection();
		}
	}
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

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h> 
#include<math.h>
#define width 4//������򳤶�
#define length 4//�������򳤶�

int xp, yp;//���λ��
int xb, yb;//���׵�λ��
int a[width][length];//0����Ϊ��ʼ����1����Ϊ�п��ܵ�����,2����Ϊ�û���ѡ��λ�ã�3����Ϊ�û���Ϊ�е���,4Ϊ����
int End = 1;

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	return;
}

void Setup()
{
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < width; j++)
		{
			a[j][i] = 0;
		}
	}
	xp = width / 2;;
	yp = length / 2;;
	a[xp][yp] = 2;
	xb = rand() % width;
	yb = rand() % length;
	a[xb][yb] = 4;
}

void Show()
{
	int i, j;
	//gotoxy(0, 0);
	//for (i = 0; i < length; i++)
	//{
	//	for (j = 0; j < width; j++)
	//	{
	//		printf(" ");
	//	}
	//	printf("\n");
	//}
	gotoxy(0, 0);
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (a[j][i] == 0)
			{
				printf(" ");
			}
			if (a[j][i] == 1)
			{
				printf("*");
			}
			if (a[j][i] == 2)
			{
				printf("!");
			}
			if (a[j][i] == 3)
			{
				printf("#");
			}
		}
		printf("\n");
	}
}

void Control()
{
	int i, j;
	if (_kbhit())
	{
		char input;
		input = _getch();
		if ((input == 'a') && (xp > 0))
		{
			for (i = 0; i < length; i++)
			{
				for (j = 0; j < width; j++)
				{
					if ((a[j][i] != 3) && (a[j][i] != 4))
					{
						a[j][i] = 0;
					}
				}
			}
			xp--;
			if ((a[xp][yp] != 3) && (a[xp][yp] != 4))
			{
				a[xp][yp] = 2;
			}
		}
		if ((input == 'd') && (xp < width - 1))
		{
			for (i = 0; i < length; i++)
			{
				for (j = 0; j < width; j++)
				{
					if ((a[j][i] != 3) && (a[j][i] != 4))
					{
						a[j][i] = 0;
					}
				}
			}
			xp++;
			if ((a[xp][yp] != 3) && (a[xp][yp] != 4))
			{
				a[xp][yp] = 2;
			}
		}
		if ((input == 'w') && (yp > 0))
		{
			for (i = 0; i < length; i++)
			{
				for (j = 0; j < width; j++)
				{
					if ((a[j][i] != 3) && (a[j][i] != 4))
					{
						a[j][i] = 0;
					}
				}
			}
			yp--;
			if ((a[xp][yp] != 3) && (a[xp][yp] != 4))
			{
				a[xp][yp] = 2;
			}
		}
		if ((input == 's') && (yp < length - 1))
		{
			for (i = 0; i < length; i++)
			{
				for (j = 0; j < width; j++)
				{
					if ((a[j][i] != 3) && (a[j][i] != 4))
					{
						a[j][i] = 0;
					}
				}
			}
			yp++;
			if ((a[xp][yp] != 3) && (a[xp][yp] != 4))
			{
				a[xp][yp] = 2;
			}
		}
		if (input == ' ')
		{
			if (a[xp][yp] != 4)
			{
				a[xp][yp] = 3;
			}
			else
			{
				a[xp][yp] = 3;
				End = 0;
			}
		}
	}
}

void Judge()
{
	if (End == 0)
	{
		gotoxy(width + 2, length + 2);
		printf("Game Over!");
	}

}

int main()
{
	Setup();
	while (1)
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cci;
		GetConsoleCursorInfo(hOut, &cci);//��ȡ�����Ϣ
		cci.bVisible = FALSE;//���ع��
		SetConsoleCursorInfo(hOut, &cci);//���ù����Ϣ
		Show();
		Control();
		Judge();
	}
	system("pause");
	return 0;
}
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h> 
#include<math.h>
#define width 4//定义横向长度
#define length 4//定义纵向长度

int xp, yp;//玩家位置
int xb, yb;//地雷的位置
int a[width][length];//0定义为初始化，1定义为有可能的区域,2定义为用户所选的位置，3定义为用户认为有地雷,4为地雷
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
		GetConsoleCursorInfo(hOut, &cci);//获取光标信息
		cci.bVisible = FALSE;//隐藏光标
		SetConsoleCursorInfo(hOut, &cci);//设置光标信息
		Show();
		Control();
		Judge();
	}
	system("pause");
	return 0;
}
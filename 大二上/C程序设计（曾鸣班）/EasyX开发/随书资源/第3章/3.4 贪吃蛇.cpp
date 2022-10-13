#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 20  // 游戏画面尺寸
#define Width 30

// 全局变量
int moveDirection; // 小蛇移动位置，上下左右分别用1，2，3，4表示
int food_x,food_y; // 食物的位置
int canvas[High][Width] = {0}; // 二维数组存储游戏画布中对应的元素
	// 0为空格0，-1为边框#，-2为食物F，1为蛇头@，大于1的正数为蛇身*

void gotoxy(int x,int y)  //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

// 移动小蛇
// 第一步扫描数组canvas所有元素，找到正数元素都+1
// 找到最大元素（即蛇尾巴），把其变为0
// 找到=2的元素（即蛇头），再根据输出的上下左右方向，把对应的另一个像素值设为1（新蛇头）
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

	if (moveDirection==1) // 向上移动
	{
		newHead_i = oldHead_i-1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==2) // 向下移动
	{
		newHead_i = oldHead_i+1;
		newHead_j = oldHead_j;
	}
	if (moveDirection==3) // 向左移动
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j-1;
	}
	if (moveDirection==4) // 向右移动
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j+1;
	}

	// 新蛇头如果吃到食物
	if (canvas[newHead_i][newHead_j]==-2)
	{
		canvas[food_x][food_y] = 0;
		// 产生一个新的食物
		food_x = rand()%(High-5) + 2;
		food_y = rand()%(Width-5) + 2;
		canvas[food_x][food_y] = -2;

		// 原来的旧蛇尾留着，长度自动+1
	}
	else // 否则，原来的旧蛇尾减掉，保持长度不变
		canvas[oldTail_i][oldTail_j] = 0;

	// 是否小蛇和自身撞，或者和边框撞，游戏失败
	if (canvas[newHead_i][newHead_j]>0 || canvas[newHead_i][newHead_j]==-1)
	{
		printf("游戏失败！\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	else
		canvas[newHead_i][newHead_j] = 1;
}

void startup() // 数据初始化
{
	int i,j;
	
	// 初始化边框
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
	
	// 初始化蛇头位置
	canvas[High/2][Width/2] = 1;
	// 初始化蛇身，画布中元素值分别为2,3,4,5....
	for (i=1;i<=4;i++)
		canvas[High/2][Width/2-i] = i+1;

	// 初始小蛇向右移动
	moveDirection = 4;
	
	food_x = rand()%(High-5) + 2;
	food_y = rand()%(Width-5) + 2;
	canvas[food_x][food_y] = -2;
}

void show()  // 显示画面
{
	gotoxy(0,0);  // 光标移动到原点位置，以下重画清屏
	int i,j;
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]==0)
				printf(" ");   //   输出空格
			else if (canvas[i][j]==-1)
				printf("#");   //   输出边框#
			else if (canvas[i][j]==1)
				printf("@");   //   输出蛇头@
			else if (canvas[i][j]>1)
				printf("*");   //   输出蛇身*
			else if (canvas[i][j]==-2)
				printf("F");   //   输出食物F
		}
		printf("\n");
	}
	Sleep(100);
}	

void updateWithoutInput()  // 与用户输入无关的更新
{
	moveSnakeByDirection();
}

void updateWithInput()  // 与用户输入有关的更新
{
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'a') 
		{
			moveDirection = 3;   // 位置左移
			moveSnakeByDirection();
		}
		else if (input == 'd')
		{
			moveDirection = 4;  // 位置右移
			moveSnakeByDirection();
		}
		else if (input == 'w')
		{
			moveDirection = 1;  // 位置上移
			moveSnakeByDirection();
		}
		else if (input == 's')
		{
			moveDirection = 2;   // 位置下移
			moveSnakeByDirection();
		}
	}
}

int main()
{
	startup();  // 数据初始化	
	while (1) //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();  // 与用户输入有关的更新
	}
	return 0;
}

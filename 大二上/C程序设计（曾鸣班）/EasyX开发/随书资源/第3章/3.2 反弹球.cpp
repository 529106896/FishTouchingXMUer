#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cwindow.h>

#define High 15  // 游戏画面尺寸
#define Width 20

// 全局变量
int ball_x,ball_y; // 小球的坐标
int ball_vx,ball_vy; // 小球的速度
int position_x,position_y; // 挡板中心坐标
int ridus;  // 挡板半径大小
int left,right; // 挡板左右位置
int canvas[High][Width] = {0}; // 二维数组存储游戏画布中对应的元素
// 0为空格，1为小球O，2为挡板*，3为方块#

void gotoxy(int x,int y)  //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup()  // 数据初始化
{
	ridus = 5;
	position_x = High-1;
	position_y = Width/2;
	left = position_y - ridus;
	right = position_y + ridus;

	ball_x = position_x-1;
	ball_y = position_y;
	ball_vx = -1;
	ball_vy = 1;
	canvas[ball_x][ball_y] = 1;	

	int k,i;
	for (k=left;k<=right;k++)  // 挡板
		canvas[position_x][k] = 2;	

	for (k=0;k<Width;k++)  // 加几排砖块
		for (i=0;i<High/4;i++)  
			canvas[i][k] = 3;
}

void show()  // 显示画面
{
	gotoxy(0,0);    // 光标移动到原点位置，以下重画清屏
	int i,j;
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]==0)
				printf(" ");   //   输出空格
			else if (canvas[i][j]==1)
				printf("0");   //   输出小球0
			else if (canvas[i][j]==2)
				printf("*");   //   输出挡板*
			else if (canvas[i][j]==3)
				printf("#");   //   输出砖块#
		}
		printf("|\n"); // 显示右边界
	}
	for (j=0;j<Width;j++)
		printf("-"); // 显示下边界
	printf("\n");
}	

void updateWithoutInput()  // 与用户输入无关的更新
{
	if (ball_x==High-2)
	{
		if ( (ball_y>=left) && (ball_y<=right) )   // 被挡板挡住
		{			
		}
		else    // 没有被挡板挡住
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}	
	}
	
	static int speed = 0;  
	if (speed<7)
		speed++;
	if (speed == 7)
	{
		speed = 0;
		
		canvas[ball_x][ball_y] = 0;		
		// 更新小球坐标
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;		
		canvas[ball_x][ball_y] = 1;
		
		// 碰到边界后反弹		
		if ((ball_x==0)||(ball_x==High-2))
			ball_vx = -ball_vx;
		if ((ball_y==0)||(ball_y==Width-1))
			ball_vy = -ball_vy;			
		
		// 碰到砖块后反弹
		if (canvas[ball_x-1][ball_y]==3)
		{
			ball_vx = -ball_vx;
			canvas[ball_x-1][ball_y] = 0;
			printf("\a");
		}
	}
}

void updateWithInput()  // 与用户输入有关的更新
{	
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'a' && left>0)   
		{
			canvas[position_x][right] = 0;
			position_y--;  // 位置左移
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][left] = 2;
		}
		if (input == 'd' && right<Width-1)
		{
			canvas[position_x][left] = 0;
			position_y++;  // 位置右移
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][right] = 2;
		}
	}
}

int main()
{
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	return 0;
}

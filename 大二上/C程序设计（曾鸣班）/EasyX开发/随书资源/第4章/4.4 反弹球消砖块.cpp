#include <conio.h>
#include <graphics.h>

#define High 480  // 游戏画面尺寸
#define Width 640
#define Brick_num 10 // 砖块个数

// 全局变量
int ball_x,ball_y; // 小球的坐标
int ball_vx,ball_vy; // 小球的速度
int radius;  // 小球的半径
int bar_x,bar_y; // 挡板中心坐标
int bar_high,bar_width;  // 挡板的高度和宽度
int bar_left,bar_right,bar_top,bar_bottom; // 挡板的上下左右位置坐标

int isBrickExisted[Brick_num]; // 每个砖块是否存在，1为存在，0为没有了
int brick_high,brick_width; // 每个砖块的高度和宽度

void startup()  // 数据初始化
{
	ball_x = Width/2;
	ball_y = High/2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;
	
	bar_high = High/20;
	bar_width = Width/2;
	bar_x = Width/2;
	bar_y = High - bar_high/2;
	bar_left = bar_x - bar_width/2;
	bar_right = bar_x + bar_width/2;
	bar_top = bar_y - bar_high/2;
	bar_bottom = bar_y + bar_high/2;

	brick_width = Width/Brick_num;
	brick_high = High/Brick_num;

	int i;
	for (i=0;i<Brick_num;i++)
		isBrickExisted[i] = 1;
	
	initgraph(Width, High);
	BeginBatchDraw();
}

void clean()  // 消除画面
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius); 	// 绘制黑线、黑色填充的圆
	bar(bar_left,bar_top,bar_right,bar_bottom);	// 绘制黑线、黑色填充的挡板

	int i,brick_left,brick_right,brick_top,brick_bottom;	
	for (i=0;i<Brick_num;i++)
	{
		brick_left = i*brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_high;
		if (!isBrickExisted[i])	 // 砖块没有了，绘制黑色
			fillrectangle(brick_left,brick_top,brick_right,brick_bottom);
	}
}	

void show()  // 显示画面
{
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);	// 绘制黄线、绿色填充的圆
	bar(bar_left,bar_top,bar_right,bar_bottom);	// 绘制黄线、绿色填充的挡板

	int i,brick_left,brick_right,brick_top,brick_bottom;

	for (i=0;i<Brick_num;i++)
	{
		brick_left = i*brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_high;

		if (isBrickExisted[i])	 // 砖块存在，绘制砖块
		{
			setcolor(WHITE);
			setfillcolor(RED);
			fillrectangle(brick_left,brick_top,brick_right,brick_bottom);	// 绘制砖块
		}
	}

	FlushBatchDraw();
	// 延时
	Sleep(3);	
}	

void updateWithoutInput()  // 与用户输入无关的更新
{
	// 挡板和小圆碰撞，小圆反弹
	if ( ( (ball_y+radius >= bar_top) && (ball_y+radius < bar_bottom-bar_high/3) )
		||  ( (ball_y-radius <= bar_bottom) && (ball_y-radius > bar_top-bar_high/3) ) )
		if ( (ball_x>=bar_left) && (ball_x<=bar_right) )
				ball_vy = -ball_vy;

	// 更新小圆坐标
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;
	
	// 小圆和边界碰撞
	if ((ball_x==radius)||(ball_x==Width-radius))
		ball_vx = -ball_vx;
	if ((ball_y==radius)||(ball_y==High-radius))
		ball_vy = -ball_vy;	

	// 判断小圆是否和某个砖块碰撞
	int i,brick_left,brick_right,brick_bottom;
	for (i=0;i<Brick_num;i++)
	{
		if (isBrickExisted[i])	 // 砖块存在，才判断
		{
			brick_left = i*brick_width;
			brick_right = brick_left + brick_width;
			brick_bottom = brick_high;
			if ( (ball_y==brick_bottom+radius) && (ball_x>=brick_left) && (ball_x<=brick_right) )
			{
				isBrickExisted[i] = 0;
				ball_vy = -ball_vy;	
			}
		}
	}
}

void updateWithInput()  // 与用户输入有关的更新
{	
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == 'a' && bar_left>0)   
		{
			bar_x = bar_x-15;  // 位置左移
			bar_left = bar_x - bar_width/2;
			bar_right = bar_x + bar_width/2;
		}
		if (input == 'd' && bar_right<Width)
		{
			bar_x = bar_x+15;  // 位置右移
			bar_left = bar_x - bar_width/2;
			bar_right = bar_x + bar_width/2;
		}
		if (input == 'w' && bar_top>0)   
		{
			bar_y = bar_y-15;  // 位置左移
			bar_top = bar_y - bar_high/2;
			bar_bottom = bar_y + bar_high/2;
		}
		if (input == 's' && bar_bottom<High)
		{
			bar_y = bar_y+15;  // 位置右移
			bar_top = bar_y - bar_high/2;
			bar_bottom = bar_y + bar_high/2;
		}
	}
}

void gameover()
{
	EndBatchDraw();
	closegraph();
}

int main()
{
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		clean();  // 把之前绘制的内容取消
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
		show();  // 显示新画面
	}
	gameover();     // 游戏结束、后续处理
	return 0;
}

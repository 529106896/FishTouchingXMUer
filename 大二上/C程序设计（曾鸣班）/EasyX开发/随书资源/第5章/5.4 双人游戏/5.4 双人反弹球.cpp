#include <conio.h>
#include <graphics.h>
#include<windows.h>
#define High 480  // 游戏画面尺寸
#define Width 640
// 全局变量
int ball_x,ball_y; // 小球的坐标
int ball_vx,ball_vy; // 小球的速度
int radius; // 小球的半径
int bar1_left,bar1_right,bar1_top,bar1_bottom; // 挡板1的上下左右位置坐标
int bar2_left,bar2_right,bar2_top,bar2_bottom; // 挡板2的上下左右位置坐标
int bar_height,bar_width; // 挡板的高度、宽度

void startup()  // 数据初始化
{
	ball_x = Width/2;
	ball_y = High/2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;

	bar_width = Width/30;
	bar_height = High/2;

	bar1_left = Width * 1/20;
	bar1_top = High/4;
	bar1_right = bar1_left + bar_width;	
	bar1_bottom = bar1_top + bar_height;	

	bar2_left = Width * 18.5/20;
	bar2_top = High/4;
	bar2_right = bar2_left + bar_width;	
	bar2_bottom = bar2_top + bar_height;

	initgraph(Width,High);
	BeginBatchDraw();
}

void clean()  // 消除画面
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius); 	
	fillcircle(ball_x, ball_y, radius); 
	bar(bar1_left,bar1_top,bar1_right,bar1_bottom);	
	bar(bar2_left,bar2_top,bar2_right,bar2_bottom);	
}	

void show()  // 显示画面
{
	setcolor(GREEN);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);	// 绘制绿圆	
	
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	bar(bar1_left,bar1_top,bar1_right,bar1_bottom);	// 绘制黄色挡板
	bar(bar2_left,bar2_top,bar2_right,bar2_bottom);	

	FlushBatchDraw();
	// 延时
	Sleep(3);	
}	

void updateWithoutInput()  // 与用户输入无关的更新
{
	// 挡板和小圆碰撞，小圆反弹
	if (ball_x+radius>=bar2_left && ball_y+radius>=bar2_top && ball_y+radius<=bar2_bottom)
		ball_vx = -ball_vx;	
	else if (ball_x-radius<=bar1_right && ball_y+radius>=bar1_top && ball_y+radius<=bar1_bottom)
		ball_vx = -ball_vx;	
	
	// 更新小圆坐标
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;
		
	if ((ball_x<=radius)||(ball_x>=Width-radius))
		ball_vx = -ball_vx;
	if ((ball_y<=radius)||(ball_y>=High-radius))
		ball_vy = -ball_vy;	
}

void updateWithInput()  // 与用户输入有关的更新
{	
		int step = 1;
		if (GetAsyncKeyState(0x57) & 0x8000 )  // w
			bar1_top-=step;
		if ((GetAsyncKeyState(0x53) & 0x8000)) //s
			bar1_top+=step;
		if ((GetAsyncKeyState(VK_UP) & 0x8000))     // 上方向键
			bar2_top-=step;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000))  // 下方向键
			bar2_top+=step;	

		bar1_bottom = bar1_top + bar_height;	
		bar2_bottom = bar2_top + bar_height;
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

#include <graphics.h>
#include <conio.h>
#define High 480  // 游戏画面尺寸
#define Width 640

int main()
{
	float ball_x,ball_y; // 小球的坐标
	float ball_vx,ball_vy; // 小球的速度
	float radius;  // 小球的半径
	
	initgraph(Width, High);
	ball_x = Width/2;
	ball_y = High/2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;
	
	while (1)
	{
		// 绘制黑线、黑色填充的圆
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(ball_x, ball_y, radius);
		
		// 更新小圆坐标
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;
		
		if ((ball_x<=radius)||(ball_x>=Width-radius))
			ball_vx = -ball_vx;
		if ((ball_y<=radius)||(ball_y>=High-radius))
			ball_vy = -ball_vy;	
		
		// 绘制黄线、绿色填充的圆
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(ball_x, ball_y, radius);
		// 延时
		Sleep(3);
	}
	closegraph();
	return 0;
}

// 绘制围棋棋盘
#include <graphics.h>
#include <conio.h>
int main()
{
	int step = 30;
	// 初始化绘图窗口
	initgraph(600, 600);	
	// 设置背景色为蓝色
	setbkcolor(YELLOW);
	// 用背景色清空屏幕
	cleardevice();
	
	setlinestyle(PS_SOLID, 2);  // 画实线，宽度为2个像素
	setcolor(RGB(0,0,0));  // 设置为黑色
	
	int i;
	for(i=1; i<=19; i++)  // 画横线和竖线
	{
		line(i*step, 1*step, i*step,  19*step);
		line(1*step, i*step, 19*step, i*step);
	}
	getch();
	closegraph();
	return 0;
}

// 绘制国际象棋棋盘
#include <graphics.h>
#include <conio.h>
int main()
{
	int step = 50;
	// 初始化绘图窗口
	initgraph(500, 500);	
	// 设置背景色为蓝色
	setbkcolor(YELLOW);
	// 用背景色清空屏幕
	cleardevice();
	
	int i,j;
	for(i=1;i<=8;i++)  
	{
		for(j=1;j<=8;j++)  
		{
			if ((i+j)% 2 ==1)
			{
				setfillcolor(BLACK);
				solidrectangle(i*step,j*step,(i+1)*step,(j+1)*step); 	// 绘制黑色方块
			}
			else
			{
				setfillcolor(WHITE);
				solidrectangle(i*step,j*step,(i+1)*step,(j+1)*step); 	// 绘制白色方块
			}
		}
	}
	getch();
	closegraph();
	return 0;
}

#include <graphics.h>
#include <conio.h>
int main()
{
	initgraph(640, 200);
	for(int y=0; y<=200; y=y+5)
	{
		if ( y/5 % 2 == 1)    // 判断奇数行偶数行
			setcolor(RGB(255,0,0));
		else
			setcolor(RGB(0,0,255));
		line(0, y, 640, y);
	}
	getch();
	closegraph();
	return 0;
}

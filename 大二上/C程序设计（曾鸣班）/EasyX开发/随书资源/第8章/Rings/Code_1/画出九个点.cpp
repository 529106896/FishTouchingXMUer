#include<graphics.h>
#include<conio.h>

void main()
{
	//画背景
	int x,y;
	initgraph(390,550);
	setfillcolor(RGB(31,78,121));
	solidrectangle(0,0,390,550);

	//画点
	setcolor(WHITE);
	setfillcolor(WHITE);
	for(x = 100; x<=290; x+=95)
	{
		fillcircle(x, 180, 4);	//第一排的点
	}
	for(x = 100; x<=290; x+=95)
	{
		fillcircle(x, 275, 4);	//第一排的点
	}
	for(x = 100; x<=290; x+=95)
	{
		fillcircle(x, 370, 4);	//第一排的点
	}
	
	getch();
	closegraph();

}
#include <graphics.h>
#include <conio.h>

void main()
{
	
	
	int x,y;//¡Á?¡À¨º
	int get;
	
	
	//»­±³¾°
	initgraph(390,550);
	setfillcolor(RGB(31,78,121));
	solidrectangle(0,0,390,550);
	MOUSEMSG m;
	get=0;
	//»­³öÒ»¸öÔ²
	x=100;
	y=100;
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(x,y,10);
	while(1)
	{
		m=GetMouseMsg();
		if(m.uMsg == WM_LBUTTONDOWN && m.x<=110 && m.x>=90 && m.y>=90 && m.y<=110)
		{
			get=1;
		}
		if(get==1)
		{
			setcolor(RGB(31,78,121));
			setfillcolor(RGB(31,78,121));
			fillcircle(x,y,10);
			x=m.x;
			y=m.y;
			setcolor(WHITE);
			setfillcolor(WHITE);
			fillcircle(x,y,10);
			if(m.uMsg == WM_LBUTTONUP)
				get=0;
		}
	}	
	
	getch();
	closegraph();
}


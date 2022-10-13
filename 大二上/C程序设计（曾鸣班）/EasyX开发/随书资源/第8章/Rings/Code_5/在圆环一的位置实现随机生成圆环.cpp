#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//123分别代表红黄蓝，
int high,wedith;
int x,y;	//坐标
int gap;	//点与点之间的间距
int i;		//循环使用的变量
int size;	//点到能拖动边界的距离
MOUSEMSG m;

struct Circle
{
	int x;
	int y;
	int get;
	int exist;
	int type[3];
};


struct point
{
	int x;
	int y;
	int middle;
};

point p[10];
Circle c[4];

void back1()	//圆环1回到初始位置
{
	c[1].x=p[1].x;
	c[1].y=p[9].y+gap;	
}


void back2()	//圆环2回到初始位置
{
	c[2].x=p[2].x;
	c[2].y=p[9].y+gap;	
}


void back3()	//圆环3回到初始位置
{
	c[3].x=p[3].x;
	c[3].y=p[9].y+gap;	
}


void stay1()	//圆环1在鼠标弹起位置定位到临近点
{
	c[1].x=p[i].x;
	c[1].y=p[i].y;
}


void stay2()	//圆环2在鼠标弹起位置定位到临近点
{
	c[2].x=p[i].x;
	c[2].y=p[i].y;
}


void stay3()	//圆环3在鼠标弹起位置定位到临近点
{
	c[3].x=p[i].x;
	c[3].y=p[i].y;
}


void starup()	//游戏初始化
{	
	high=390;
	wedith=550;
	initgraph(high,wedith);		//画布大小
	gap=95;		//点之间的间隔

	p[1].x=100;p[2].x=100+gap;p[3].x=100+gap*2;		//九个点的横坐标
	p[4].x=100;p[5].x=100+gap;p[6].x=100+gap*2;
	p[7].x=100;p[8].x=100+gap;p[9].x=100+gap*2;	

	p[1].y=180;p[4].y=180+gap;p[7].y=180+gap*2;		//九个点的纵坐标		
	p[2].y=180;p[5].y=180+gap;p[8].y=180+gap*2;
	p[3].y=180;p[6].y=180+gap;p[9].y=180+gap*2;	

	for(i=1;i<=3;i++)		//画出三个圆并定位
	{	
		c[i].x=p[i].x;
		c[i].y=p[9].y+gap;
		c[i].get=0;
		c[i].exist=0;
	}	
	for(i=1;i<=9;i++)
	{
		p[i].middle=0;
	}
	srand((unsigned)time(NULL));
}
void show()
{
	BeginBatchDraw();	//这个函数用于开始批量绘图。
						//执行后，任何绘图操作都将暂时不输出到屏幕上
						//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出

	setfillcolor(RGB(31,78,121));//设置背景颜色
	solidrectangle(0,0,high,wedith);//画背景
	setwritemode(R2_MERGEPEN);//设置画图方式为OR

	//画出三个圆环

		setlinestyle(PS_SOLID,5);
		setlinecolor(WHITE);
		if(c[1].exist==0)
		{
			for (i=0;i<3;i++)
			{
				c[1].type[i]=rand()%2;
			}
			c[1].exist=1;
		}
		
		if (c[1].type[0]==1)
			circle(c[1].x,c[1].y,10);
		if(c[1].type[1]==1)
			circle(c[1].x,c[1].y,17);
		if(c[1].type[0]==1&&c[1].type[1]==1)
			c[1].type[2]=0;
		if(c[1].type[2]==1)
			circle(c[1].x,c[1].y,24);
		if (c[1].type[0]==0 && c[1].type[1]==0 && c[1].type[2]==0)
			circle(c[1].x,c[1].y,10);
		
	/*for (i=1;i<=3;i++)
	{
		circle(c[i].x,c[i].y,24);
	}	
	*/
		setwritemode(R2_COPYPEN);
	
	//画九个点
	setcolor(WHITE);
	setfillcolor(WHITE);
	for(x=p[1].x;x<=p[3].x;x+=gap)
	{
		fillcircle(x,p[1].y,1);//第一排的点
	}
	for(x=p[4].x;x<=p[6].x;x+=gap)
	{
		fillcircle(x,p[4].y,1);//第二排的点
	}
	for(x=p[7].x;x<=p[9].x;x+=gap)
	{
		fillcircle(x,p[7].y,1);//第三排的点
	}
		FlushBatchDraw();
	// 执行未完成的绘制任务

}


void withoutinput()
{
	
}


void withinput()
{
	m=GetMouseMsg();
	size = 53;
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=c[1].x+24 && m.x>=c[1].x-24 && m.y>=c[1].y-24 && m.y<=c[1].y+24 )	//判断鼠标左键有没有在圆环1内按下//最后记得改成环1初始位置
	{
		c[1].get=1;	
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=c[2].x+24 && m.x>=c[2].x-24 && m.y>=c[2].y-24 && m.y<=c[2].y+24 )	//判断鼠标左键有没有在圆环2内按下
	{
		c[2].get=1;		
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=c[3].x+24 && m.x>=c[3].x-24 && m.y>=c[3].y-24 && m.y<=c[3].y+24 )	//判断鼠标左键有没有在圆环3内按下
	{
		c[3].get=1;		
	}
	

	if(c[1].get==1)	//当鼠标按下后圆环跟着鼠标移动
	{
		c[1].x=m.x;
		c[1].y=m.y;
		for (i=1;i<=9;i++)
		{
			if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==0)
			{
				stay1();	//在游戏边界内松开鼠标圆环1定位到临近点坐标
				c[1].get=0;   
				p[i].middle=1;	//所定位置点的坐标为1
			}			
			else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
			{	
				back1();	//游戏边界外松开鼠标圆环1回到原位
				c[1].get=0;		
			}
			else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==1)
			{
				back1();	
				c[1].get=0;
			}
		}
	}
	if(c[2].get==1)//当鼠标按下后圆环2跟着鼠标移动
		{
			c[2].x=m.x;
			c[2].y=m.y;
			for (i=1;i<=9;i++)
			{
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==0)
				{
					stay2();	//在游戏边界内松开鼠标圆环2定位到临近点坐标
					c[2].get=0;   
					p[i].middle=1;
				}			
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
				{	
					back2();	//游戏边界外松开鼠标圆环2回到原位
					c[2].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==1)
				{
					back2();
					c[2].get=0;
				}
			}
		}
	if(c[3].get==1)//当鼠标按下后圆环3跟着鼠标移动
		{
			c[3].x=m.x;
			c[3].y=m.y;
			for (i=1;i<=9;i++)
			{
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==0)//size/2会使得判断范围更好可是同时也会使得判断back失效
				{ 
					stay3();	//在游戏边界内松开鼠标圆环3定位到临近点坐标
					c[3].get=0;  
					p[i].middle=1;
				}	
				
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size/2 || m.x>=p[3].x+size/2 || m.y<=p[1].y-size/2 || m.y>=p[7].y+size/2|| m.x))
				{	
					back3();	//游戏边界外松开鼠标圆环3回到原位
					c[3].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==1)
				{
					back3();
					c[3].get=0;
				}
			}		
		}	
}
void main()
{	
	starup();
	while(1)
	{
		show();
		withoutinput();
		withinput();
	}
	EndBatchDraw();
	getch();
	closegraph();	
}
/*
setlinestyle(PS_SOLID,5);
setfillcolor(RGB(31,78,121));
fillcircle(195,275,24);
fillcircle(195,275,17);	
fillcircle(195,275,10);
*/

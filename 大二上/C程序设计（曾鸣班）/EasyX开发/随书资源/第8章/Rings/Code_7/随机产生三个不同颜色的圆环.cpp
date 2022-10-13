#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//123分别代表红黄蓝，

int z;//测试数据
int high,wedith;
int x,y;	//坐标
int gap;	//点与点之间的间距
int i,j,smallC,middleC,largeC;		//循环使用的变量
int size;	//点到能拖动边界的距离
MOUSEMSG m;
	IMAGE img_bk;
struct Circle
{
	int x;
	int y;
	int get;
	int exist;
	int type[3];
	int color1;
	int color2;
	int color3;
};

struct point{
	int x;
	int y;
	int getcircle[3];
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
	smallC=0;middleC=0;largeC=0;
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
		c[i].color1=rand()%4+1;
		c[i].color2=rand()%4+1;
		c[i].color3=rand()%4+1;
	}	
	for(i=1;i<=9;i++)//给点上的三个环全部初始化
	{
		for(j=0;j<3;j++)
		{
			p[i].getcircle[j]=0;
		}
	}
	loadimage(&img_bk, "E:\\la.jpg");	// 读取图片到 img 对象中
	srand((unsigned)time(NULL));//随机种子生成
}
void show()
{
	BeginBatchDraw();	//这个函数用于开始批量绘图。
						//执行后，任何绘图操作都将暂时不输出到屏幕上
						//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出


	// 定义 IMAGE 对象
	
	putimage(0, 0, &img_bk);	// 在坐标 (0, 0) 位置显示 IMAGE 对象

/*	setfillcolor(RGB(31,78,121));//设置背景颜色
	solidrectangle(0,0,high,wedith);//画背景*/
	setwritemode(R2_MERGEPEN);//设置画图方式为OR

	//画出三个圆环
	
		//画出白色的环
		//判断环1是否存在并随机生成三个环是否存在
		if(c[1].exist==0){
			for (i=0;i<3;i++)
			c[1].type[i]=rand()%2;
			c[1].exist=1;
		}
		//判断环2是否存在并随机生成三个环是否存在
		if(c[2].exist==0){
			for (i=0;i<3;i++)
				c[2].type[i]=rand()%2;
			c[2].exist=1;
		}
		//判断环3是否存在并随机生成三个环是否存在
		if(c[3].exist==0){
			for (i=0;i<3;i++)
				c[3].type[i]=rand()%2;
			c[3].exist=1;
		}
		//画第一个地点的环
	{
		setlinestyle(PS_SOLID,5);//线条颜色为5
		setlinecolor(RED);//暂时默认环的颜色为红
		if (c[1].type[0]==0 && c[1].type[1]==0 && c[1].type[2]==0)
			c[1].type[0]=1;
		if(c[1].type[0]==1&&c[1].type[1]==1)
			c[1].type[2]=0;
		if (c[1].type[0]==1&&c[1].color1==1)
			circle(c[1].x,c[1].y,10);
		if(c[1].type[1]==1&&c[1].color2==1)
			circle(c[1].x,c[1].y,17);
		if(c[1].type[2]==1&&c[1].color3==1)
			circle(c[1].x,c[1].y,24);
		//画第二个地点的环
		if (c[2].type[0]==0 && c[2].type[1]==0 && c[2].type[2]==0)
			c[2].type[0]=1;
		if(c[2].type[0]==1&&c[2].type[1]==1)
			c[2].type[2]=0;
		if (c[2].type[0]==1&&c[2].color1==1)
			circle(c[2].x,c[2].y,10);
		if (c[2].type[1]==1&&c[2].color2==1)
			circle(c[2].x,c[2].y,17);
		if (c[2].type[2]==1&&c[2].color3==1)
			circle(c[2].x,c[2].y,24);
		//画第三个地点的环
		if (c[3].type[0]==0 && c[3].type[1]==0 && c[3].type[2]==0)
			c[3].type[0]=1;
		if(c[3].type[0]==1&&c[3].type[1]==1)
			c[3].type[2]=0;		
		if (c[3].type[0]==1&&c[3].color1==1)
			circle(c[3].x,c[3].y,10);
		if(c[3].type[1]==1&&c[3].color2==1)
			circle(c[3].x,c[3].y,17);
		if(c[3].type[2]==1&&c[3].color3==1)
			circle(c[3].x,c[3].y,24);
		//画点上的环
		for(i=1;i<=9;i++)
		{
			if(p[i].getcircle[0]==1)
				circle(p[i].x,p[i].y,10);
		}
		for(i=1;i<=9;i++)
		{
			if(p[i].getcircle[1]==1)
				circle(p[i].x,p[i].y,17);
		}
		for(i=1;i<=9;i++)
		{
			if(p[i].getcircle[2]==1)
				circle(p[i].x,p[i].y,24);
		}
	}
	{
		setlinestyle(PS_SOLID,5);//线条颜色为5
		setlinecolor(YELLOW);//暂时默认环的颜色为黄
		if (c[1].type[0]==0 && c[1].type[1]==0 && c[1].type[2]==0)
			c[1].type[0]=1;
		if(c[1].type[0]==1&&c[1].type[1]==1)
			c[1].type[2]=0;
		if (c[1].type[0]==1&&c[1].color1==2)
			circle(c[1].x,c[1].y,10);
		if(c[1].type[1]==1&&c[1].color2==2)
			circle(c[1].x,c[1].y,17);
		if(c[1].type[2]==1&&c[1].color3==2)
			circle(c[1].x,c[1].y,24);
		//画第二个地点的环
		if (c[2].type[0]==0 && c[2].type[1]==0 && c[2].type[2]==0)
			c[2].type[0]=1;
		if(c[2].type[0]==1&&c[2].type[1]==1)
			c[2].type[2]=0;
		if (c[2].type[0]==1&&c[2].color1==2)
			circle(c[2].x,c[2].y,10);
		if (c[2].type[1]==1&&c[2].color2==2)
			circle(c[2].x,c[2].y,17);
		if (c[2].type[2]==1&&c[2].color3==2)
			circle(c[2].x,c[2].y,24);
		//画第三个地点的环
		if (c[3].type[0]==0 && c[3].type[1]==0 && c[3].type[2]==0)
			c[3].type[0]=1;
		if(c[3].type[0]==1&&c[3].type[1]==1)
			c[3].type[2]=0;		
		if (c[3].type[0]==1&&c[3].color1==2)
			circle(c[3].x,c[3].y,10);
		if(c[3].type[1]==1&&c[3].color2==2)
			circle(c[3].x,c[3].y,17);
		if(c[3].type[2]==1&&c[3].color3==2)
			circle(c[3].x,c[3].y,24);
	}
	{
		setlinestyle(PS_SOLID,5);//线条颜色为5
		setlinecolor(BLUE);//暂时默认环的颜色为蓝色
		if (c[1].type[0]==0 && c[1].type[1]==0 && c[1].type[2]==0)
			c[1].type[0]=1;
		if(c[1].type[0]==1&&c[1].type[1]==1)
			c[1].type[2]=0;
		if (c[1].type[0]==1&&c[1].color1==3)
			circle(c[1].x,c[1].y,10);
		if(c[1].type[1]==1&&c[1].color2==3)
			circle(c[1].x,c[1].y,17);
		if(c[1].type[2]==1&&c[1].color3==3)
			circle(c[1].x,c[1].y,24);
		//画第二个地点的环
		if (c[2].type[0]==0 && c[2].type[1]==0 && c[2].type[2]==0)
			c[2].type[0]=1;
		if(c[2].type[0]==1&&c[2].type[1]==1)
			c[2].type[2]=0;
		if (c[2].type[0]==1&&c[2].color1==3)
			circle(c[2].x,c[2].y,10);
		if (c[2].type[1]==1&&c[2].color2==3)
			circle(c[2].x,c[2].y,17);
		if (c[2].type[2]==1&&c[2].color3==3)
			circle(c[2].x,c[2].y,24);
		//画第三个地点的环
		if (c[3].type[0]==0 && c[3].type[1]==0 && c[3].type[2]==0)
			c[3].type[0]=1;
		if(c[3].type[0]==1&&c[3].type[1]==1)
			c[3].type[2]=0;		
		if (c[3].type[0]==1&&c[3].color1==3)
			circle(c[3].x,c[3].y,10);
		if(c[3].type[1]==1&&c[3].color2==3)
			circle(c[3].x,c[3].y,17);
		if(c[3].type[2]==1&&c[3].color3==3)
			circle(c[3].x,c[3].y,24);
	}
	{
		setlinestyle(PS_SOLID,5);//线条颜色为5
		setlinecolor(GREEN);//暂时默认环的颜色为绿色
		if (c[1].type[0]==0 && c[1].type[1]==0 && c[1].type[2]==0)
			c[1].type[0]=1;
		if(c[1].type[0]==1&&c[1].type[1]==1)
			c[1].type[2]=0;
		if (c[1].type[0]==1&&c[1].color1==4)
			circle(c[1].x,c[1].y,10);
		if(c[1].type[1]==1&&c[1].color2==4)
			circle(c[1].x,c[1].y,17);
		if(c[1].type[2]==1&&c[1].color3==4)
			circle(c[1].x,c[1].y,24);
		//画第二个地点的环
		if (c[2].type[0]==0 && c[2].type[1]==0 && c[2].type[2]==0)
			c[2].type[0]=1;
		if(c[2].type[0]==1&&c[2].type[1]==1)
			c[2].type[2]=0;
		if (c[2].type[0]==1&&c[2].color1==4)
			circle(c[2].x,c[2].y,10);
		if (c[2].type[1]==1&&c[2].color2==4)
			circle(c[2].x,c[2].y,17);
		if (c[2].type[2]==1&&c[2].color3==4)
			circle(c[2].x,c[2].y,24);
		//画第三个地点的环
		if (c[3].type[0]==0 && c[3].type[1]==0 && c[3].type[2]==0)
			c[3].type[0]=1;
		if(c[3].type[0]==1&&c[3].type[1]==1)
			c[3].type[2]=0;		
		if (c[3].type[0]==1&&c[3].color1==4)
			circle(c[3].x,c[3].y,10);
		if(c[3].type[1]==1&&c[3].color2==4)
			circle(c[3].x,c[3].y,17);
		if(c[3].type[2]==1&&c[3].color3==4)
			circle(c[3].x,c[3].y,24);
	}
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
	if(c[1].exist==2 && c[2].exist==2 && c[3].exist==2)
	{
		c[1].exist=0;
		c[2].exist=0;
		c[3].exist=0;
		back1();
		back2();
		back3();
	}
	


}


void withinput()
{
	m=GetMouseMsg();
	size = 53;
	
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=314 && m.x>=266 && m.y>=441 && m.y<=489)	//判断鼠标左键有没有在圆环3内按下
	{
		c[3].get=1;		
	}if(m.uMsg == WM_LBUTTONDOWN && m.x<=124 && m.x>=76 && m.y>=441 && m.y<=489)	//判断鼠标左键有没有在圆环1内按下
	{
		c[1].get=1;	
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=219 && m.x>=171 && m.y>=441 && m.y<=489 )	//判断鼠标左键有没有在圆环2内按下
	{
		c[2].get=1;		
	}
	

	if(c[1].get==1)	//当鼠标按下后圆环跟着鼠标移动
	{
		c[1].x=m.x;
		c[1].y=m.y;
		for (i=1;i<=9;i++)
		{
			if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
			{
				//错误原因未知的函数拿出来在这里完美实现
				for(j=0;j<3;j++)
				{
				if(c[1].type[j]==1&&p[i].getcircle[j]==1)
						z=1;
				}
				for(j=0;j<3;j++)
				{
					if(c[1].type[j]==1&&p[i].getcircle[j]==0&&z==0)
						p[i].getcircle[j]=1;
					
				}
				if(z==0)
				{
					stay1();	//在游戏边界内松开鼠标圆环1定位到临近点坐标
					c[1].get=0;
					c[1].exist=2;//存在过但是移走了
				}
				else
				{
				back1();
				c[1].get=0;
				z=0;
				}
			
			}			
			else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
			{	
				back1();	//游戏边界外松开鼠标圆环1回到原位
				c[1].get=0;		
			}
			else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
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
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
				{
					for(j=0;j<3;j++)
					{
					if(c[2].type[j]==1&&p[i].getcircle[j]==1)
							z=1;
					}
					for(j=0;j<3;j++)
					{
						if(c[2].type[j]==1&&p[i].getcircle[j]==0&&z==0)
							p[i].getcircle[j]=1;
					}
					if(z==0)
					{
					stay2();//在游戏边界内松开鼠标圆环2定位到临近点坐标
					c[2].get=0;  
					c[2].exist=2;//存在过但是移走了
					}
					else
					{
						back2();
						c[2].get=0;
						z=0;
					}
				}			
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
				{	
					back2();	//游戏边界外松开鼠标圆环2回到原位
					c[2].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
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
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)//size/2会使得判断范围更好可是同时也会使得判断back失效
				{ 
					for(j=0;j<3;j++)
					{
					 if(c[3].type[j]==1&&p[i].getcircle[j]==1)
							z=1;
					}
					for(j=0;j<3;j++)
					{
						if(c[3].type[j]==1&&p[i].getcircle[j]==0&&z==0)
							p[i].getcircle[j]=1;
					}
					if(z==0)
					{
					stay3();	//在游戏边界内松开鼠标圆环3定位到临近点坐标
					c[3].get=0;
					c[3].exist=2;//存在过但是移走了
					}
					else
					{
						back3();
						c[3].get=0;
						z=0;
					}
				}	
				
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
				{	
					back3();	//游戏边界外松开鼠标圆环3回到原位
					c[3].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
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

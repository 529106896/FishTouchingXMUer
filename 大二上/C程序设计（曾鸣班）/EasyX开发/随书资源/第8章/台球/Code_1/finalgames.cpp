#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define Width 762
#define High 381

//全局变量
float BALL_x,BALL_y;   //母球坐标
float ball_x,ball_y;
float start_x,start_y;       //杆的开端位置
float end_x,end_y;      //杆的末端位置
float sinA,cosA;       //角的正、余弦值
float dist;            //鼠标到母球的距离
int r,l,L;     //r为球的半径，l为杆开端到母球的距离，L为杆长
int V;     //合速度
float V_x,V_y;    //x,y方向的分速度 
int hit;          //鼠标是否点击的判断变量

MOUSEMSG m;   //定义鼠标消息

void startup()
{
	BALL_x=Width/4;
	BALL_y=High/2;      
	ball_x=Width*3/4;
	ball_y=High/2;      
	r=10;               
	l=50;
	L=100;
	hit=0;
	V=0;
	V_x=(-1)*V*cosA;
	V_y=(-1)*V*sinA;
	initgraph(Width,High);
}

void show()
{
	BeginBatchDraw();

	//画白色母球
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(BALL_x,BALL_y,r);
	//画蓝色球
	setcolor(BLUE);
	setfillcolor(BLUE);
	fillcircle(ball_x,ball_y,r);
	//画杆
	if(hit!=1)
	{
		setlinestyle(PS_SOLID, 8);
		setcolor(YELLOW);
		line(start_x,start_y,end_x,end_y);
	}

	FlushBatchDraw();   //开始批量绘图

	setcolor(BLACK);
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 8);
	fillcircle(BALL_x,BALL_y,r);        //隐藏上一帧母球
	line(start_x,start_y,end_x,end_y);  //隐藏上一帧球杆
}

void updatewithinput()
{
	if(MouseHit())     //检测是否有鼠标消息
	{
		m=GetMouseMsg();
		if((m.uMsg==WM_MOUSEMOVE)&&(hit==0))
		{
			dist=sqrt((m.x-BALL_x)*(m.x-BALL_x)+(m.y-BALL_y)*(m.y-BALL_y));  //鼠标到母球的距离
			sinA=(m.y-BALL_y)/dist;     //算出鼠标与母球连线与水平夹角的正弦值
			cosA=(m.x-BALL_x)/dist;     //算出鼠标与母球连线与水平夹角的余弦值
			start_x=BALL_x+l*cosA;      //算出球杆开端位置
			start_y=BALL_y+l*sinA;
			end_x=start_x+L*cosA;       //算出球杆末端位置
			end_y=start_y+L*sinA;
		}
		else if(m.uMsg==WM_LBUTTONUP)
		{
			hit=1;
		}
		if(hit==1)
		{
			V=5;
			V_x=(-1)*V*cosA;
			V_y=(-1)*V*sinA;

		}
	}
}

void updatewithoutinput()
{
	int static speed=0;    //放慢球运动的速度
	if(speed<50)
	{
		speed++;
	}
	if(speed==50)
	{
		speed=0;
		BALL_x=BALL_x+V_x;
		BALL_y=BALL_y+V_y;
	}
}

void main()
{
	startup();
	while(1)
	{
		show();
		updatewithinput();
		updatewithoutinput();
	}
	EndBatchDraw();
	getch();
	closegraph();
}
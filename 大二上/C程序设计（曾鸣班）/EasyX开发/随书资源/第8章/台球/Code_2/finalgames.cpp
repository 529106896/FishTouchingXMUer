#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define Width 508
#define High 254
#define Num 9
#define PI 3.141592656535

//全局变量
float ball_x[Num],ball_y[Num]; //设母球为0号球
float start_x,start_y;       //杆的开端位置
float end_x,end_y;      //杆的末端位置
float sinA[Num],cosA[Num];       //各个球的角的正、余弦值
float dist;            //鼠标到母球的距离
float r,l,L;     //r为球的半径，l为杆开端到母球的距离，L为杆长
float ball_v[Num];     //合速度
float ball_vx[Num],ball_vy[Num];    //x,y方向的分速度 
float ball_direction[Num];
int hit;          //鼠标是否点击的判断变量
int i;
int ballrunning[Num] = {0};   //记录球的运动状态，1表示运动，0表示静止
int nowrunning = 0;
MOUSEMSG m;   //定义鼠标消息

void startup()
{
	ball_x[0]=Width/4;
	ball_y[0]=High/2; //初始化白球位置
	for (i=0; i<Num; i++) //初始化其他球位置
	{
		ball_x[i] = rand()%Width-5;
		if(ball_x[i]<=0) ball_x[i] = 7; 
		ball_y[i] = rand()%High-5;
		if(ball_y[i]<=0)  ball_y[i] = 7;
	}
	r=6;               
	l=30;
	L=100;
	hit=0;
	initgraph(Width,High);
	BeginBatchDraw();
}
void boom()
{

	if (hit == 1)
	{
		ball_vx[nowrunning] =(-1)*cosA[nowrunning]*ball_v[nowrunning];
		ball_vy[nowrunning] =(-1)*sinA[nowrunning]*ball_v[nowrunning];
		ball_x[nowrunning] =ball_x[nowrunning]+ball_vx[nowrunning];
		ball_y[nowrunning] =ball_y[nowrunning]+ball_vy[nowrunning];               //四种镜面反射
		if(ball_x[nowrunning] <=r&&ball_y[nowrunning]>r&&ball_y[nowrunning]<High)           //与左边界碰撞 
			cosA[nowrunning] = (-1)*cosA[nowrunning];    
		if(ball_x[nowrunning]>=Width-r&&ball_y[nowrunning]>r&&ball_y[nowrunning]<High)      //与右边界碰撞
			cosA[nowrunning] = (-1)*cosA[nowrunning];  
		if(ball_y[nowrunning]<=r&&ball_x[nowrunning]>r&&ball_x[nowrunning]<Width)           //与上边界碰撞
			sinA[nowrunning] = (-1)*sinA[nowrunning];
		if(ball_y[nowrunning] >= High-r&&ball_x[nowrunning]>r&&ball_x[nowrunning]<Width)    //与下边界碰撞
			sinA[nowrunning] = (-1)*sinA[nowrunning];
		if((ball_x[nowrunning]<=r&&ball_y[nowrunning]<=r)||(ball_x[nowrunning]<=r&&ball_y[nowrunning]>=High)||(ball_x[nowrunning]>=Width&&ball_y[nowrunning]<=r)||(ball_x[nowrunning]>=Width&&ball_y[nowrunning]<=r))
			sinA[nowrunning] = (-1)*sinA[nowrunning];                   //与四角碰撞
		float mindistance[2];   //储存与nowrunning的球距离最近的球的下标和距离
		mindistance[0] = 99999;
		mindistance[1] = -1;
		for (i=0;i<Num;i++)
		{
			if(i!=nowrunning)     //距离不与自己比
			{
				float d;
				d =  (ball_x[i]-ball_x[nowrunning])*(ball_x[i]-ball_x[nowrunning])+(ball_y[nowrunning]-ball_y[i])*(ball_y[nowrunning]-ball_y[i]);  //球之间的距离
				if(mindistance[0]>d)  
				{
					mindistance[0] = d;         //获取距离最小值
					mindistance[1] = i;
				}
			}
		}
		if (mindistance[0]<=4*r*r)            //判断是否碰撞，若是进行速度方向交换
		{
			ball_v[(int)mindistance[1]] = ball_v[nowrunning];
			cosA[(int)mindistance[1]] = cosA[nowrunning];
			sinA[(int)mindistance[1]] = sinA[nowrunning];
			ballrunning[(int)mindistance[1]] = 1;
			cosA[nowrunning] = 0;
			sinA[nowrunning] = 0;
			ballrunning[nowrunning] = 0;
			ball_v[nowrunning] = 0;
			nowrunning = mindistance[1];

		}
	}
	Sleep(3);
}

void show()
{
	//画白色母球
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(ball_x[0],ball_y[0],r);
	//画蓝色球
	for (i=1;i<Num;i++)
	{	
		setcolor(BLUE);
		setfillcolor(BLUE);
		fillcircle(ball_x[i],ball_y[i],r);
	}

	//画杆
	if(hit!=1)
	{
		setlinestyle(PS_SOLID, 6);
		setcolor(YELLOW);
		line(start_x,start_y,end_x,end_y);
	}
	FlushBatchDraw();   //开始批量绘图
}
void clean()
{	
	if (hit == 1)
	{	
		for (i=0;i<Num;i++)
		{
			if (ballrunning[i]==1)
			{			
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillcircle(ball_x[i],ball_y[i],r);        //隐藏上一帧球
			}

		}
	}
	setlinestyle(PS_SOLID, 6);
	setcolor(BLACK);
	line(start_x,start_y,end_x,end_y);  //隐藏上一帧球杆
}


void updatewithinput()
{
	if(MouseHit())     //检测是否有鼠标消息
	{
		m=GetMouseMsg();
		if((m.uMsg==WM_MOUSEMOVE)&&(ballrunning[0]==0))
		{
			dist=sqrt((m.x-ball_x[0])*(m.x-ball_x[0])+(m.y-ball_y[0])*(m.y-ball_y[0]));  //鼠标到母球的距离
			sinA[0]=(m.y-ball_y[0])/dist;     //算出鼠标与母球连线与水平夹角的正弦值
			cosA[0]=(m.x-ball_x[0])/dist;     //算出鼠标与母球连线与水平夹角的余弦值
			start_x=ball_x[0]+l*cosA[0];      //算出球杆开端位置
			start_y=ball_y[0]+l*sinA[0];
			end_x=start_x+L*cosA[0];       //算出球杆末端位置
			end_y=start_y+L*sinA[0];
		}
		if(m.uMsg==WM_LBUTTONUP)
		{
			hit=1;
			ball_v[0] = 1;
			ballrunning[0] = 1;
		}

	}
}

void updatewithoutinput()
{
	boom();
}

void main()
{
	startup();
	while(1)
	{
		show();
		clean();
		updatewithoutinput();
		updatewithinput();
	}
	EndBatchDraw();
	getch();
	closegraph();
}
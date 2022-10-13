#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>

#define HIGH 640 // 游戏画面尺寸
#define WIDTH 640
#define num_call 100000 //节奏总量
#define PI 3.1415 
#define	FRICTION 1.01	 // 摩擦力/阻尼系数
#define v 1

struct Call
{
	int type;	//类型
	double angle;	//角度
	double x;	
	double y;	//坐标
	double v_x;
	double v_y;	//移动方向
	COLORREF color;	//颜色
}call[num_call], *p, *p1, *p2, *q;

int speed;
int flag = 1;

//绝对延时
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();
	while(GetTickCount()-oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}

//文件写入
void write()
{
	char s;
	FILE *fp;
	fp = fopen("asd.txt","a");
	
	if(flag)
	{
		getch();
		flag = 0;
	}
	
	delay(5);
	
	if(kbhit())
	{
		s = getch();
		while(kbhit())
			getch();
		if(s == 'z')
		{
			p->type = 1;		
		}
		else if(s == 'x')
		{
			p->type = 2; 
		}
		else
		{
			p->type = 5;
		}
	}
	else
		p->type = 0;
		
	p->angle = 2*PI/60*(rand()%60+1);
	p->x = WIDTH/2+200*cos(p->angle);
	p->y = HIGH/2+200*sin(p->angle);
	p->v_x = cos(p->angle)*10;
	p->v_y = sin(p->angle)*10;
	fprintf(fp,"%.3lf %d ", p->angle,p->type);

	p++;

	fclose(fp);
}

//文件读取
void read()
{
	static FILE *fp1;
	if(flag)
	{
		fp1=fopen("asd.txt","r");
		flag = 0;
		getch();
	}

	delay(10);
	fscanf(fp1,"%lf %d ", &p->angle,&p->type);
	if(p->type == 5)
	{
		fclose(fp1);
	}
	else
	{
		p->x = WIDTH/2+200*cos(p->angle);
		p->y = HIGH/2+200*sin(p->angle);
		p->v_x = cos(p->angle)*v;
		p->v_y = sin(p->angle)*v;
		p++;
	}
	
}

//绘图
void painting()
{
	COLORREF color;	//颜色
	for(q = p1; q != p2+1; q++)
	{
		switch(q->type)
		{
		case 1:color = BLUE;break;
		case 2:color = GREEN;break;
		case 0:color = BLACK;break;
		case -1:
		case -2:color = WHITE;break;
		}
		setfillcolor(color);
		if(q->type != 0)
			solidcircle(q->x, q->y, 10);
		else
			solidcircle(q->x, q->y, 0);
	}

	setfillcolor(RED);
	solidcircle(WIDTH/2, HIGH/2, 10);

	setlinecolor(BLUE);
	circle(WIDTH/2, HIGH/2, 200);
	for(q = p1; q != p2+1; q++)
		if(q->type != 0)
			circle(WIDTH/2, HIGH/2, sqrt(pow(q->x-WIDTH/2,2)+pow(q->y-HIGH/2,2)));
}

//判定
void judge()
{
	char s;
	int a = 0;
	for(q = p1; q->type == 0; q++);
	if(kbhit())
	{
		s = getch();
		if(s == 'z')
			a = 1;
		else if(s == 'x')
			a = 2;
	}
	if(pow(q->x-WIDTH/2,2)+pow(q->y-HIGH/2,2) <= 300*v && a == q->type)
		q->type *= -1;
	a = 0;
}

void startup()
{
	initgraph(WIDTH, HIGH);		// 初始化 640 x 480 的绘图窗口
	speed = 0;
	p = p1 = p2 = call;
}

void show()
{	
	painting();
}

void clean()
{
	setfillcolor(BLACK);	
	for(q = p1; q != p2+1; q++)
	{
		solidcircle(q->x, q->y, 10);
		setlinecolor(BLACK);
		if(q->type != 0)
			circle(WIDTH/2, HIGH/2, sqrt(pow(q->x-WIDTH/2,2)+pow(q->y-HIGH/2,2)));
	}
}

void UpdateWithoutInput()
{
	if(speed < 5)
		speed++;
	if(speed == 5)
	{
		for(q = p1; q != p2+1; q++)
		{
			q->x -= q->v_x;
			q->y -= q->v_y;
		}
		speed = 0;
	}
	for(q = p1; q != p2+1; q++)
	{
		q->v_x *= FRICTION;
		q->v_y *= FRICTION;
	}
	
	if(pow(p1->x-WIDTH/2,2)+pow(p1->y-HIGH/2,2) <= 10*10)
		p1++;
	if(pow(p1->x-WIDTH/2,2)+pow(p1->y-HIGH/2,2) <= 195*195)
		p2++;

}

void UpdateWithInput()
{
//	write();
	read();
	judge();
} 

void main()
{
	startup();
	BeginBatchDraw();
	while(1)
	{
		clean();
		UpdateWithoutInput();
		UpdateWithInput();
		show();
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}

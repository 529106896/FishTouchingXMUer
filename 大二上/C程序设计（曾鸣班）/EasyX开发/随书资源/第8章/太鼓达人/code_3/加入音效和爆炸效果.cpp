#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib") 


#define HIGH  480// 游戏画面尺寸
#define WIDTH 640
#define num_call 100000 //节奏总量
#define PI 3.1415 
#define NUM_BALLS 50	 // 小球数量
#define NUM_MOVERS 80 //内圈球总数
#define NUM_LINES 160 //外圈线总数
#define	FRICTION 1.01	 // 摩擦力/阻尼系数
#define v 7 //速度调节
#define R 200 //主画面半径

void setlight();

struct Ball
{
	COLORREF color;	 // 颜色
	float x, y;	 // 坐标
	float vX, vY;	 // 速度
	float radius;         // 半径
}balls[NUM_BALLS];

struct LINE
{
	COLORREF color;	 // 颜色
	float x, y, x0, y0;	 // 坐标
	double d;
	float vd;
	float radius;         // 半径
}lines[NUM_LINES];

struct Mover
{
	COLORREF color;	 // 颜色
	float x, y;	 // 坐标
	double d;
	float vd;
	float radius;         // 半径
}movers[NUM_MOVERS];

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

int pl;
int speed;
int flag = 1;
int flag_g = 0;
IMAGE img_p,img[32], ball[8], *pi = img, *bi = ball;

//绝对延时
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();
	while(GetTickCount()-oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}

void menu1()
{  
	IMAGE img_bk,img_1,img_2;
	loadimage(&img_bk,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\201038580_1.jpg"));
	loadimage(&img_1,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\b1.bmp"));
	loadimage(&img_2,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\b1_mask.bmp"));
	putimage(0,0,&img_bk);
    PlaySound (TEXT ("C:\\Users\\DELL\\Desktop\\音游\\Blu - MitiS.wav"), NULL,SND_FILENAME| SND_ASYNC|SND_LOOP) ;
	static int speed=0;
	BeginBatchDraw();

	while(1)
	{
	  
		if(speed<=3000)
	    speed++;
		if(speed==1)
		putimage(0,0,&img_bk);
	    if(speed==1500)
	{  
		putimage(210, 430, &img_2,SRCAND);	    
		putimage(210, 430, &img_1,SRCINVERT);
		
	}	
		if(speed==3000)
		speed=0;
	FlushBatchDraw();
	if(kbhit())
	{ 
		PlaySound(0,0,SND_FILENAME);
		break;
	}
	}EndBatchDraw();
}

void menu2()
{   int op=0;
     PlaySound (TEXT ("C:\\Users\\DELL\\Desktop\\音游\\Fly - Ludovico Einaudi.wav"), NULL,SND_FILENAME| SND_ASYNC|SND_LOOP) ;
	IMAGE img_1,img_2;
	loadimage(&img_1,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\2-1.jpg"));
	loadimage(&img_2,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\options.jpg"));
    putimage(0,0,&img_1);
	TCHAR s1[] =_T("Play");
	TCHAR s2[]=_T("Write");
    TCHAR s3[]=_T("Options");
    TCHAR s4[]=_T("Exit");
	
	settextcolor(WHITE);
	settextstyle(16, 0, _T("黑体"));
	MOUSEMSG m;
	
	while(1)
    { 
	  m = GetMouseMsg();
      if((m.x>49&&m.x<89)&&(m.y>339&&m.y<409)&&op==0)
			{
				outtextxy(55,409,s1); 
				setlight();
				FlushBatchDraw(48,339,92,410);
				if(m.uMsg==WM_LBUTTONDOWN)
				{   
					pl=1;
					PlaySound(0,0,SND_FILENAME);
                    break;
	   
				}
			}
	 else if((m.x>146&&m.x<198)&&(m.y>344&&m.y<399)&&op==0)
		    {
				outtextxy(152,410,s2);
				setlight();
				FlushBatchDraw(146,344,199,399);
				if(m.uMsg==WM_LBUTTONDOWN)
				{
                   
					PlaySound(0,0,SND_FILENAME);break;
				}
	  }
	 else if((m.x>482&&m.x<532)&&(m.y>349&&m.y<413)&&op==0)
		    {  
				outtextxy(482,413,s3);
				setlight();
				FlushBatchDraw(482,349,532,413);
				if(m.uMsg==WM_LBUTTONDOWN)
				 { 
					 putimage(100,20,&img_2);
					 op=1;
				 }
					   
	 }
		
     else if((m.x>573&&m.x<623)&&(m.y>358&&m.y<408)&&op==0)
			{
				outtextxy(580,413,s4);
				setlight();
				FlushBatchDraw(573,358,623,409);
		      if(m.uMsg==WM_LBUTTONDOWN)
						break;
	        }
	 else if(op==1)
	 {    
		 if((m.x>500&&m.x<530)&&(m.y>29&&m.y<56))
		 
			    if(m.uMsg==WM_LBUTTONDOWN)
				 {
					putimage(0,0,&img_1);
		            op=0;
				}
	
	 }
	else
		  putimage(0,0,&img_1);
	}
}
//亮度调整
void setlight()
{
	IMAGE img_1;
	loadimage(&img_1,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\2-1.jpg"));
	DWORD *pbWnd = GetImageBuffer();
	DWORD *pbImg = GetImageBuffer(&img_1);
    
	int r,g,b,i,light;//调整亮度
	for(light=1;light<=64;light++)
	for(i=222000;i<630*419;i++)
	{        
		r = (int)(GetRValue(pbImg[i]) * light >>8);
		g = (int)(GetGValue(pbImg[i]) * light >>7);
		b = (int)(GetBValue(pbImg[i]) * light >>6);
		pbWnd[i] = RGB(r, g, b);
	}
}

//内圈特效
void Update_Mover(int M, int n, int high)
{
	double dx, dy;
	static int speed = 0;
	
	for(int i = M-1; i > M-n && i >= 0; i--)
		if(movers[i].vd <= 0 && movers[i+1].vd > 0)
			movers[i].vd = pow(2.0,n-(M-i));
	for(int i = M+1; i < M+n && i < NUM_MOVERS; i++)
		if(movers[i].vd <= 0 && movers[i-1].vd > 0)
			movers[i].vd = pow(2.0,n-(i-M));

	if(speed < 5)
		speed++;
	if(speed == 5)
	{
		for(int i = M; i > M-n && i >= 0; i--)
		{
			dx = movers[i].x-WIDTH/2;
			dy = movers[i].y-HIGH/2;
			movers[i].d = sqrt(dx*dx+dy*dy);
			
			movers[i].d -= movers[i].vd;
			movers[i].x = WIDTH/2+movers[i].d*cos(i*PI/NUM_MOVERS-PI/2);
			movers[i].y = HIGH/2+movers[i].d*sin(i*PI/NUM_MOVERS-PI/2);

			if(movers[i].d <= R+1e-3 && movers[i].d >= R-1e-3)
				movers[i].vd = 0;
		}


		for(int i = M+1; i < M+n && i < NUM_MOVERS; i++)
		{
			dx = movers[i].x-WIDTH/2;
			dy = movers[i].y-HIGH/2;
			movers[i].d = sqrt(dx*dx+dy*dy);
				
			movers[i].d -= movers[i].vd;
			movers[i].x = WIDTH/2+movers[i].d*cos(i*PI/NUM_MOVERS-PI/2);
			movers[i].y = HIGH/2+movers[i].d*sin(i*PI/NUM_MOVERS-PI/2);

			if(movers[i].d <= R+1e-3 && movers[i].d >= R-1e-3)
				movers[i].vd = 0;
		}
		speed = 0;
	}

	if(movers[M].d <= high+1e-3 && movers[M].vd > 0)
	{
		movers[M].vd *= -1;	
		for(int i = M-1; i > M-n && i >= 0; i--)
			movers[i].vd *= -1;	
		for(int i = M+1; i < M+n && i < NUM_MOVERS; i++)
			movers[i].vd *= -1;
	}

}

//外圈特效
void Update_LINE(int l, int r, int vl, int vr)
{
	double dx, dy;
	for(int i = l; i <= r; i++)
		lines[i].vd = vl+(i-l)*(vr-vl)/(r-l);

	for(int i = l; i < r; i++)
	{
		dx = lines[i].x-WIDTH/2;
		dy = lines[i].y-HIGH/2;
		lines[i].d = sqrt(dx*dx+dy*dy);

		lines[i].d += lines[i].vd;
		lines[i].x = WIDTH/2+lines[i].d*cos(i*PI/NUM_LINES-PI/2);
		lines[i].y = HIGH/2+lines[i].d*sin(i*PI/NUM_LINES-PI/2);

		if(lines[i].d <= R+1e-3 && lines[i].d >= R-1e-3)
			lines[i].vd = 0;
		if(lines[i].vd == 0)
		{
			lines[i].x = lines[i].x0;
			lines[i].y = lines[i].y0;
		}
	}

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
		if(s == 'd')
		{
			p->type = 1;		
		}
		else if(s == 'f')
		{
			p->type = 2; 
		}
		else if(s == 'j')
		{
			p->type = 3; 
		}
		else if(s == 'k')
		{
			p->type = 4; 
		}
		else
		{
			p->type = 5;
		}
	}
	else
		p->type = 0;
		
	p->angle = 2*PI/60*(rand()%60+1);
	p->x = WIDTH/2+R*cos(p->angle);
	p->y = HIGH/2+R*sin(p->angle);
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
		p->x = WIDTH/2+R*cos(p->angle);
		p->y = HIGH/2+R*sin(p->angle);
		p->v_x = cos(p->angle)*v;
		p->v_y = sin(p->angle)*v;
		p++;
	}
	
}

//绘图
void painting()
{
	
   COLORREF color;
	for(q = p1; q != p2+1; q++)
	{
		switch(q->type)
		{
		case 1:
			{
				putimage(q->x-10, q->y-15, bi, SRCAND);
				putimage(q->x-10, q->y-15, bi+1, SRCINVERT);
				break;
			}
		case 2:			
			{
				putimage(q->x-10, q->y-15, bi+2, SRCAND);
				putimage(q->x-10, q->y-15, bi+3, SRCINVERT);
				break;
			}
		case 3:			
			{
				putimage(q->x-10, q->y-15, bi+4, SRCAND);
				putimage(q->x-10, q->y-15, bi+5, SRCINVERT);
				break;
			}
		case 4:			
			{
				putimage(q->x-10, q->y-15, bi+6, SRCAND);
				putimage(q->x-10, q->y-15, bi+7, SRCINVERT);
				break;
			}
		case 0:break;
/*		case -1:
		case -2:color = WHITE;break;
		}
/*		setfillcolor(color);
		if(q->type != 0)
			solidcircle(q->x, q->y, 7);
		else
			solidcircle(q->x, q->y, 0);
			}*/}}
	
//	setfillcolor(WHITE);
//	solidcircle(WIDTH/2, HIGH/2, 10);

/*	setlinecolor(BLUE);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	for(q = p1; q != p2+1; q++)
		if(q->type != 0)
			circle(WIDTH/2, HIGH/2, sqrt(pow(q->x-WIDTH/2,2)+pow(q->y-HIGH/2,2)));*/

	for(int i = 0; i < NUM_MOVERS; i++)
	{
//		if(i%(NUM_MOVERS/8))
//		setfillcolor(BLUE);
//		else
		setfillcolor(BLACK);
		solidrectangle(movers[i].x-2, movers[i].y-2, movers[i].x+2, movers[i].y+2);
		solidrectangle(WIDTH-movers[i].x+2, movers[i].y-2, WIDTH-movers[i].x-2, movers[i].y+2);
	}

	for(int i = 0; i < NUM_LINES; i++)
	{
//		if(i%(NUM_LINES/8))
//		setlinecolor(BLUE);
//		else
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		line(lines[i].x0, lines[i].y0, lines[i].x, lines[i].y);
		line(WIDTH-lines[i].x0, HIGH-lines[i].y0, WIDTH-lines[i].x, HIGH-lines[i].y);
	}
	
	for (int i = 0; i < NUM_BALLS; i++)
	{
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 0);
		setcolor(balls[i].color);
		setfillcolor(balls[i].color);
		fillcircle(balls[i].x, balls[i].y, balls[i].radius);
	}

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
		if(s == 'd')
			{
				a = 1;
		        PlaySound(TEXT("C:\\Users\\DELL\\Desktop\\音游\\853.wav"),NULL,SND_FILENAME|SND_SYNC);
		}
		else if(s == 'f')
			{
				a = 2;
                PlaySound(TEXT("C:\\Users\\DELL\\Desktop\\音游\\853.wav"),NULL,SND_FILENAME|SND_SYNC);
		}

		else if(s == 'j' )
			{
				a = 3;
				 PlaySound(TEXT("C:\\Users\\DELL\\Desktop\\音游\\853.wav"),NULL,SND_FILENAME|SND_SYNC);
		}

		else if(s == 'k')
			{
				a = 4;
		        PlaySound(TEXT("C:\\Users\\DELL\\Desktop\\音游\\853.wav"),NULL,SND_FILENAME|SND_SYNC);
		}
	}
	if(pow(q->x-WIDTH/2,2)+pow(q->y-HIGH/2,2) <= 300*v && a == q->type)
		for (int i = 0; i < NUM_BALLS; i++)
		{	
			balls[i].x   = WIDTH/2;
			balls[i].y   = HIGH/2;
			balls[i].vX  = float(cos(float(i))) * (rand() % 34);
			balls[i].vY  = float(sin(float(i))) * (rand() % 34);
		}

	a = 0;
}

void startup()
{
	initgraph(WIDTH, HIGH);		// 初始化 640 x 480 的绘图窗口
	speed = 0;
	p = p1 = p2 = call;

	for(int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].d = R;
		movers[i].vd = 0;
		movers[i].x = WIDTH/2+movers[i].d*cos(i*PI/NUM_MOVERS-PI/2);
		movers[i].y = HIGH/2+movers[i].d*sin(i*PI/NUM_MOVERS-PI/2);
		movers[i].radius = 4;
	}
	
	for(int i = 0; i < NUM_LINES; i++)
	{
		lines[i].d = R;
		lines[i].vd = 0;
		lines[i].x = lines[i].x0 = WIDTH/2+lines[i].d*cos(i*PI/NUM_LINES-PI/2);
		lines[i].y = lines[i].y0 = HIGH/2+lines[i].d*sin(i*PI/NUM_LINES-PI/2);
	}

	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		balls[i].x   = WIDTH/2;
		balls[i].y   = HIGH/2;
		balls[i].vX  = 0;
		balls[i].vY  = 0;
		balls[i].radius  = (rand() % 34)/8.0;
	}


	loadimage(&img_p,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\play.jpg"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\001_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\001.bmp"));
    loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\002_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\002.bmp"));
    loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\003_mask.bmp"));
    loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\003.bmp"));
    loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\004_mask.bmp"));
    loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\004.bmp"));
 	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\005_mask.bmp"));
    loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\005.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\006_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\006.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\007_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\007.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\008_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\008.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\009_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\009.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\010_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\010.bmp"));	
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\011_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\011.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\012_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\012.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\013_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\013.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\014_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\014.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\015_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\015.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\016_mask.bmp"));
	loadimage(pi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\016.bmp"));
    pi = img;

	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\blue_mask.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\blue.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\yellow_mask.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\yellow.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\green_mask.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\green.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\red_mask.bmp"));
	loadimage(bi++,_T("C:\\Users\\DELL\\Desktop\\音游\\beats\\red.bmp"));
	bi = ball;
}

void show()
{	
	painting();	
	static int speed = 0;
	if(speed < 5)
		speed++;
	if(speed == 5)
	{
		putimage(292, 205, pi++,SRCAND);	 
		putimage(292, 205, pi++,SRCINVERT);
		if(pi-img==32)
			pi = img+2;
		speed = 0;
	}
}

void clean()
{
	static int speed = 0;

	if(speed < 5)
		speed++;
	if(speed == 5)
	{	
		putimage(0,0,&img_p);
		speed = 0;
	}


	for(int i = 0; i < NUM_MOVERS; i++)
	{
		setfillcolor(BLACK);
		solidcircle(movers[i].x, movers[i].y, movers[i].radius);
		solidcircle(WIDTH-movers[i].x, movers[i].y, movers[i].radius);
	}
	
	for(int i = 0; i < NUM_LINES; i++)
	{
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 0);
		line(lines[i].x0, lines[i].y0, lines[i].x, lines[i].y);
		line(WIDTH-lines[i].x0, HIGH-lines[i].y0, WIDTH-lines[i].x, HIGH-lines[i].y);
	}

	for (int i = 0; i < NUM_BALLS; i++)
	{
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(balls[i].x, balls[i].y, balls[i].radius);
	}

}

void UpdateWithoutInput()
{
/*	int type = 0;
	{
//	int n = NUM_MOVERS/8;
//	int k = 4;
//	for(int i = 0; i < 8; i++)
//		Update_Mover(i*n, k, R*3/4);
//		Update_Mover(NUM_MOVERS/2, k, R*3/4);
	}
	Update_Mover(NUM_MOVERS/2, 4, R*3/4);*/


	for(q = p1; q->type == 0; q++);
	if(pow(q->x-WIDTH/2,2)+pow(q->y-HIGH/2,2) <= 200)
	{
		int n = NUM_LINES/8;
		for(int i = 1; i < 8; i++)
			if(lines[i*n].vd == 0)
				lines[i*n].vd = rand()%16;

	//		if(movers[NUM_MOVERS/2].vd == 0)
	//			movers[NUM_MOVERS/2].vd = 16;
/*		int m = NUM_MOVERS/8;
		for(int i = 0; i < 8; i++)
			if(movers[i*m].vd == 0)
				movers[i*m].vd = 16;
		if(movers[NUM_MOVERS/2].vd == 0)
			movers[NUM_MOVERS/2].vd = 16;*/

	}
	{
	int n = NUM_LINES/8;
	for(int i = 0; i < 8; i++)
		Update_LINE(i*n, (i+1)*n, lines[i*n].vd, lines[(i+1)*n].vd);

	for(int i = 0; i < NUM_LINES; i++)
		if(lines[i].d >= R*4/3+1e-3 && lines[i].vd > 0)
			for(int j = 0; j < NUM_LINES; j++)
				lines[j].vd *= -1;
	}


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
	
	if(pow(p1->x-WIDTH/2,2)+pow(p1->y-HIGH/2,2) <= 195*195)
		p2++;
	if(pow(p1->x-WIDTH/2,2)+pow(p1->y-HIGH/2,2) <= 10*10)
		p1++;
	
	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i].x += balls[i].vX;
		balls[i].y += balls[i].vY;
		if(balls[i].vX)
		{
			balls[i].vX *= 0.99;
			balls[i].vY *= 0.99;
		}
		/*if(pow(balls[i].x-WIDTH/2,2)+pow(balls[i].y-HIGH/2,2)>200*200)
		{
			balls[i].x = WIDTH/2;
			balls[i].y = HIGH/2;
			balls[i].vX = balls[i].vY = 0;
		}*/
	}

}

void UpdateWithInput()
{
//	write();
	read();
	judge();
}

void main()
{
	initgraph(WIDTH,HIGH);
    menu1();
    menu2();
	if(pl==1)

	startup();
	BeginBatchDraw();
	while(1)
	{
//		Sleep(80);
		clean();
		UpdateWithoutInput();
		UpdateWithInput();
		show();
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}

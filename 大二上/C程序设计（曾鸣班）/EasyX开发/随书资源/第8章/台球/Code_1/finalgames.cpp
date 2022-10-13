#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define Width 762
#define High 381

//ȫ�ֱ���
float BALL_x,BALL_y;   //ĸ������
float ball_x,ball_y;
float start_x,start_y;       //�˵Ŀ���λ��
float end_x,end_y;      //�˵�ĩ��λ��
float sinA,cosA;       //�ǵ���������ֵ
float dist;            //��굽ĸ��ľ���
int r,l,L;     //rΪ��İ뾶��lΪ�˿��˵�ĸ��ľ��룬LΪ�˳�
int V;     //���ٶ�
float V_x,V_y;    //x,y����ķ��ٶ� 
int hit;          //����Ƿ������жϱ���

MOUSEMSG m;   //���������Ϣ

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

	//����ɫĸ��
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(BALL_x,BALL_y,r);
	//����ɫ��
	setcolor(BLUE);
	setfillcolor(BLUE);
	fillcircle(ball_x,ball_y,r);
	//����
	if(hit!=1)
	{
		setlinestyle(PS_SOLID, 8);
		setcolor(YELLOW);
		line(start_x,start_y,end_x,end_y);
	}

	FlushBatchDraw();   //��ʼ������ͼ

	setcolor(BLACK);
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 8);
	fillcircle(BALL_x,BALL_y,r);        //������һ֡ĸ��
	line(start_x,start_y,end_x,end_y);  //������һ֡���
}

void updatewithinput()
{
	if(MouseHit())     //����Ƿ��������Ϣ
	{
		m=GetMouseMsg();
		if((m.uMsg==WM_MOUSEMOVE)&&(hit==0))
		{
			dist=sqrt((m.x-BALL_x)*(m.x-BALL_x)+(m.y-BALL_y)*(m.y-BALL_y));  //��굽ĸ��ľ���
			sinA=(m.y-BALL_y)/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
			cosA=(m.x-BALL_x)/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
			start_x=BALL_x+l*cosA;      //�����˿���λ��
			start_y=BALL_y+l*sinA;
			end_x=start_x+L*cosA;       //������ĩ��λ��
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
	int static speed=0;    //�������˶����ٶ�
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
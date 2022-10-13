#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define Width 508
#define High 254
#define Num 9
#define PI 3.141592656535

//ȫ�ֱ���
float ball_x[Num],ball_y[Num]; //��ĸ��Ϊ0����
float start_x,start_y;       //�˵Ŀ���λ��
float end_x,end_y;      //�˵�ĩ��λ��
float sinA[Num],cosA[Num];       //������Ľǵ���������ֵ
float dist;            //��굽ĸ��ľ���
float r,l,L;     //rΪ��İ뾶��lΪ�˿��˵�ĸ��ľ��룬LΪ�˳�
float ball_v[Num];     //���ٶ�
float ball_vx[Num],ball_vy[Num];    //x,y����ķ��ٶ� 
float ball_direction[Num];
int hit;          //����Ƿ������жϱ���
int i;
int ballrunning[Num] = {0};   //��¼����˶�״̬��1��ʾ�˶���0��ʾ��ֹ
int nowrunning = 0;
MOUSEMSG m;   //���������Ϣ

void startup()
{
	ball_x[0]=Width/4;
	ball_y[0]=High/2; //��ʼ������λ��
	for (i=0; i<Num; i++) //��ʼ��������λ��
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
		ball_y[nowrunning] =ball_y[nowrunning]+ball_vy[nowrunning];               //���־��淴��
		if(ball_x[nowrunning] <=r&&ball_y[nowrunning]>r&&ball_y[nowrunning]<High)           //����߽���ײ 
			cosA[nowrunning] = (-1)*cosA[nowrunning];    
		if(ball_x[nowrunning]>=Width-r&&ball_y[nowrunning]>r&&ball_y[nowrunning]<High)      //���ұ߽���ײ
			cosA[nowrunning] = (-1)*cosA[nowrunning];  
		if(ball_y[nowrunning]<=r&&ball_x[nowrunning]>r&&ball_x[nowrunning]<Width)           //���ϱ߽���ײ
			sinA[nowrunning] = (-1)*sinA[nowrunning];
		if(ball_y[nowrunning] >= High-r&&ball_x[nowrunning]>r&&ball_x[nowrunning]<Width)    //���±߽���ײ
			sinA[nowrunning] = (-1)*sinA[nowrunning];
		if((ball_x[nowrunning]<=r&&ball_y[nowrunning]<=r)||(ball_x[nowrunning]<=r&&ball_y[nowrunning]>=High)||(ball_x[nowrunning]>=Width&&ball_y[nowrunning]<=r)||(ball_x[nowrunning]>=Width&&ball_y[nowrunning]<=r))
			sinA[nowrunning] = (-1)*sinA[nowrunning];                   //���Ľ���ײ
		float mindistance[2];   //������nowrunning����������������±�;���
		mindistance[0] = 99999;
		mindistance[1] = -1;
		for (i=0;i<Num;i++)
		{
			if(i!=nowrunning)     //���벻���Լ���
			{
				float d;
				d =  (ball_x[i]-ball_x[nowrunning])*(ball_x[i]-ball_x[nowrunning])+(ball_y[nowrunning]-ball_y[i])*(ball_y[nowrunning]-ball_y[i]);  //��֮��ľ���
				if(mindistance[0]>d)  
				{
					mindistance[0] = d;         //��ȡ������Сֵ
					mindistance[1] = i;
				}
			}
		}
		if (mindistance[0]<=4*r*r)            //�ж��Ƿ���ײ�����ǽ����ٶȷ��򽻻�
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
	//����ɫĸ��
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(ball_x[0],ball_y[0],r);
	//����ɫ��
	for (i=1;i<Num;i++)
	{	
		setcolor(BLUE);
		setfillcolor(BLUE);
		fillcircle(ball_x[i],ball_y[i],r);
	}

	//����
	if(hit!=1)
	{
		setlinestyle(PS_SOLID, 6);
		setcolor(YELLOW);
		line(start_x,start_y,end_x,end_y);
	}
	FlushBatchDraw();   //��ʼ������ͼ
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
				fillcircle(ball_x[i],ball_y[i],r);        //������һ֡��
			}

		}
	}
	setlinestyle(PS_SOLID, 6);
	setcolor(BLACK);
	line(start_x,start_y,end_x,end_y);  //������һ֡���
}


void updatewithinput()
{
	if(MouseHit())     //����Ƿ��������Ϣ
	{
		m=GetMouseMsg();
		if((m.uMsg==WM_MOUSEMOVE)&&(ballrunning[0]==0))
		{
			dist=sqrt((m.x-ball_x[0])*(m.x-ball_x[0])+(m.y-ball_y[0])*(m.y-ball_y[0]));  //��굽ĸ��ľ���
			sinA[0]=(m.y-ball_y[0])/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
			cosA[0]=(m.x-ball_x[0])/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
			start_x=ball_x[0]+l*cosA[0];      //�����˿���λ��
			start_y=ball_y[0]+l*sinA[0];
			end_x=start_x+L*cosA[0];       //������ĩ��λ��
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
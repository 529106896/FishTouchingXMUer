#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//123�ֱ����������
int high,wedith;
int x,y;	//����
int gap;	//�����֮��ļ��
int i;		//ѭ��ʹ�õı���
int size;	//�㵽���϶��߽�ľ���
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

void back1()	//Բ��1�ص���ʼλ��
{
	c[1].x=p[1].x;
	c[1].y=p[9].y+gap;	
}


void back2()	//Բ��2�ص���ʼλ��
{
	c[2].x=p[2].x;
	c[2].y=p[9].y+gap;	
}


void back3()	//Բ��3�ص���ʼλ��
{
	c[3].x=p[3].x;
	c[3].y=p[9].y+gap;	
}


void stay1()	//Բ��1����굯��λ�ö�λ���ٽ���
{
	c[1].x=p[i].x;
	c[1].y=p[i].y;
}


void stay2()	//Բ��2����굯��λ�ö�λ���ٽ���
{
	c[2].x=p[i].x;
	c[2].y=p[i].y;
}


void stay3()	//Բ��3����굯��λ�ö�λ���ٽ���
{
	c[3].x=p[i].x;
	c[3].y=p[i].y;
}


void starup()	//��Ϸ��ʼ��
{	
	high=390;
	wedith=550;
	initgraph(high,wedith);		//������С
	gap=95;		//��֮��ļ��

	p[1].x=100;p[2].x=100+gap;p[3].x=100+gap*2;		//�Ÿ���ĺ�����
	p[4].x=100;p[5].x=100+gap;p[6].x=100+gap*2;
	p[7].x=100;p[8].x=100+gap;p[9].x=100+gap*2;	

	p[1].y=180;p[4].y=180+gap;p[7].y=180+gap*2;		//�Ÿ����������		
	p[2].y=180;p[5].y=180+gap;p[8].y=180+gap*2;
	p[3].y=180;p[6].y=180+gap;p[9].y=180+gap*2;	

	for(i=1;i<=3;i++)		//��������Բ����λ
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
	BeginBatchDraw();	//����������ڿ�ʼ������ͼ��
						//ִ�к��κλ�ͼ����������ʱ���������Ļ��
						//ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ���

	setfillcolor(RGB(31,78,121));//���ñ�����ɫ
	solidrectangle(0,0,high,wedith);//������
	setwritemode(R2_MERGEPEN);//���û�ͼ��ʽΪOR

	//��������Բ��

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
	
	//���Ÿ���
	setcolor(WHITE);
	setfillcolor(WHITE);
	for(x=p[1].x;x<=p[3].x;x+=gap)
	{
		fillcircle(x,p[1].y,1);//��һ�ŵĵ�
	}
	for(x=p[4].x;x<=p[6].x;x+=gap)
	{
		fillcircle(x,p[4].y,1);//�ڶ��ŵĵ�
	}
	for(x=p[7].x;x<=p[9].x;x+=gap)
	{
		fillcircle(x,p[7].y,1);//�����ŵĵ�
	}
		FlushBatchDraw();
	// ִ��δ��ɵĻ�������

}


void withoutinput()
{
	
}


void withinput()
{
	m=GetMouseMsg();
	size = 53;
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=c[1].x+24 && m.x>=c[1].x-24 && m.y>=c[1].y-24 && m.y<=c[1].y+24 )	//�ж���������û����Բ��1�ڰ���//���ǵøĳɻ�1��ʼλ��
	{
		c[1].get=1;	
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=c[2].x+24 && m.x>=c[2].x-24 && m.y>=c[2].y-24 && m.y<=c[2].y+24 )	//�ж���������û����Բ��2�ڰ���
	{
		c[2].get=1;		
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=c[3].x+24 && m.x>=c[3].x-24 && m.y>=c[3].y-24 && m.y<=c[3].y+24 )	//�ж���������û����Բ��3�ڰ���
	{
		c[3].get=1;		
	}
	

	if(c[1].get==1)	//����갴�º�Բ����������ƶ�
	{
		c[1].x=m.x;
		c[1].y=m.y;
		for (i=1;i<=9;i++)
		{
			if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==0)
			{
				stay1();	//����Ϸ�߽����ɿ����Բ��1��λ���ٽ�������
				c[1].get=0;   
				p[i].middle=1;	//����λ�õ������Ϊ1
			}			
			else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
			{	
				back1();	//��Ϸ�߽����ɿ����Բ��1�ص�ԭλ
				c[1].get=0;		
			}
			else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==1)
			{
				back1();	
				c[1].get=0;
			}
		}
	}
	if(c[2].get==1)//����갴�º�Բ��2��������ƶ�
		{
			c[2].x=m.x;
			c[2].y=m.y;
			for (i=1;i<=9;i++)
			{
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==0)
				{
					stay2();	//����Ϸ�߽����ɿ����Բ��2��λ���ٽ�������
					c[2].get=0;   
					p[i].middle=1;
				}			
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
				{	
					back2();	//��Ϸ�߽����ɿ����Բ��2�ص�ԭλ
					c[2].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==1)
				{
					back2();
					c[2].get=0;
				}
			}
		}
	if(c[3].get==1)//����갴�º�Բ��3��������ƶ�
		{
			c[3].x=m.x;
			c[3].y=m.y;
			for (i=1;i<=9;i++)
			{
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size&&p[i].middle==0)//size/2��ʹ���жϷ�Χ���ÿ���ͬʱҲ��ʹ���ж�backʧЧ
				{ 
					stay3();	//����Ϸ�߽����ɿ����Բ��3��λ���ٽ�������
					c[3].get=0;  
					p[i].middle=1;
				}	
				
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size/2 || m.x>=p[3].x+size/2 || m.y<=p[1].y-size/2 || m.y>=p[7].y+size/2|| m.x))
				{	
					back3();	//��Ϸ�߽����ɿ����Բ��3�ص�ԭλ
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

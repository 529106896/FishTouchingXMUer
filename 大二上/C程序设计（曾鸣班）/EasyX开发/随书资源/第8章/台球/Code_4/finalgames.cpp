#include <stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define Width 1016
#define High 508
#define Num 10

//ȫ�ֱ���
float ball_x[Num],ball_y[Num]; //��ĸ��Ϊ0����
float start_x,start_y;       //�˵Ŀ���λ��
float end_x,end_y;      //�˵�ĩ��λ��
float sinA,cosA;       //������Ľǵ���������ֵ
float dist;            //��굽ĸ��ľ���
float r,l,L;     //rΪ��İ뾶��lΪ�˿��˵�ĸ��ľ��룬LΪ�˳�
float ball_vx[Num] = {0},ball_vy[Num] = {0};    //x,y����ķ��ٶ� 
int hit;          //����Ƿ������жϱ���
int ballrunning[Num] = {0};   //��¼����˶�״̬��1��ʾ�˶���0��ʾ��ֹ
int i = 0,j = 0;
MOUSEMSG m;   //���������Ϣ

void startup()
{
	 
	ball_x[0]=Width/4;
	ball_y[0]=High/2; 
	//��ʼ������λ��
	//��ʼ��������λ��
	r=10; 
	ball_x[1]=Width/2;
	ball_y[1]=High/2;
	ball_x[2]=ball_x[1]+(r+4)*1.73;
	ball_x[3]=ball_x[2];
	ball_x[4]=ball_x[3]+(r+4)*1.73;
	ball_x[6]=ball_x[5]=ball_x[4];
	ball_x[7]=ball_x[6]+(r+4)*1.73;
	ball_x[8]=ball_x[7];
	ball_x[9]=ball_x[8]+(r+4)*1.73;

	ball_y[5]=ball_y[9]=ball_y[1];
	ball_y[2]=ball_y[7]=ball_y[1]+(r+4);
	ball_y[3]=ball_y[8]=ball_y[1]-(r+4);
	ball_y[4]=ball_y[1]+2*(r+4);
	ball_y[6]=ball_y[1]-2*(r+4);
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
		for (i=0;i<Num;i++)
		{	         
			if((ball_x[i]<=r&&ball_y[i]<=r)||(ball_x[i]<=r&&ball_y[i]>=High)||(ball_x[i]>=Width&&ball_y[i]<=r)||(ball_x[i]>=Width&&ball_y[i]<=r))
			{
				ball_vx[i] = ball_vx[i]*(-1); 
				ball_vy[i] = ball_vy[i]*(-1);
			}	                //���Ľ���ײ
			else
			{
				if((ball_x[i] <=r&&ball_y[i]>r&&ball_y[i]<High)||(ball_x[i]>=Width-r&&ball_y[i]>r&&ball_y[i]<High))           //����߽���ײ 
					ball_vx[i] = ball_vx[i]*(-1);                   //�����ұ߽���ײ 
				if((ball_y[i]<=r&&ball_x[i]>r&&ball_x[i]<Width)||ball_y[i] >= High-r&&ball_x[i]>r&&ball_x[i]<Width)           //���ϱ߽���ײ
					ball_vy[i] = ball_vy[i]*(-1);                   //�����±߽���ײ 
			}
			ball_x[i] =ball_x[i]+ball_vx[i];
			ball_y[i] =ball_y[i]+ball_vy[i];
			//����������
			ball_vx[i] = ball_vx[i]*0.999;
			ball_vy[i] = ball_vy[i]*0.999;
			//�ٶ�С��ĳֵʱֱ�����侲ֹ
			if (sqrt(ball_vx[i]*ball_vx[i]+ball_vy[i]*ball_vy[i])<=0.1)
			{
				ball_vx[i] = 0;
				ball_vy[i] = 0;
				ballrunning[i] = 0;
			}

		}
		float mindistance[Num][2];  //������nowrunning����������������±�;���
		float d1,d2;
		float cosA1,sinA1;
		float p;
		struct Vectors
		{
			float s_x,s_y,t_x,t_y;     //�������������봹ֱ��������
			float s1_x,s1_y,t1_x,t1_y;   //�������������봹ֱ���ߵ�λ����
			float v1s,v2s,v1t,v2t;  //v1,v2��s��t��ͶӰ
			float v1s_x,v1s_y,v2s_x,v2s_y,v1t_x,v1t_y,v2t_x,v2t_y;     //����ͶӰ������
		};
		Vectors a;
		for (i=0;i<Num;i++)
		{
			mindistance[i][0] = 99999;
			mindistance[i][1] = -1;
		}
		for (i=0;i<Num;i++)
		{
			for (j=0;j<Num;j++)
			{
				if(i!=j)     //���벻���Լ���
				{
					float d;
					d =  (ball_x[i]-ball_x[j])*(ball_x[i]-ball_x[j])+(ball_y[j]-ball_y[i])*(ball_y[j]-ball_y[i]);  //��֮��ľ���
					if(mindistance[i][0]>d)  
					{
						mindistance[i][0] = d;         //��ȡ������Сֵ
						mindistance[i][1] = j;            //��ȡ��i�������������±�
					}
				}
			}

		}
		for(i=0;i<Num;i++)
		{

			if (mindistance[i][0]<=4*r*r)
					{
						j = mindistance[i][1];
						p = 2*r-sqrt(mindistance[i][0])+2; /*С����ճ����Ϊ��һ˲��С��֮�����С���벢����2r������С��2r���Ͼ���С�����˶��ٽ�����ײ	
					                                       �ж�����ײС�����û���˶���4*r*r�ľ��룬���Բ�ͣ��ײ���ٶȲ�ͣ��С��
						                                   p�������Ӧ�������ľ���*/
						d1 = ball_x[i]-ball_x[j];
						d2 = ball_y[i]-ball_y[j];
						cosA1 = sqrt(d1*d1/(d1*d1+d2*d2));       //С��������x�������cos,sinֵ
						sinA1 =sqrt(d2*d2/(d1*d1+d2*d2));
						if (d1>0)
						{
							cosA1=(-1)*cosA1;
						}
						if (d2>0)
						{
							sinA1=(-1)*sinA1;
						}
						setcolor(BLACK);
						setfillcolor(BLACK);
						fillcircle(ball_x[j],ball_y[j],r); //������ײ�� 
						//����С������
						ball_x[j]+=p*cosA1;
						ball_y[j]+=p*sinA1;
						if (j==0)
						{
							setcolor(WHITE);
							setfillcolor(WHITE);
							fillcircle(ball_x[j],ball_y[j],r);
						}
						else
						{
							setcolor(BLUE);
							setfillcolor(BLUE);
							fillcircle(ball_x[j],ball_y[j],r);
						}
					}
		}
		
		
		for (i=0;i<Num;i++)
		{
			float temp;
			if(mindistance[i][0]<=4*r*r&&ballrunning[i]==1)            //�ж��Ƿ���ײ�����ǽ����ٶȶ������䣬���򴫵�
			{
				j =mindistance[i][1];
				a.s_x = ball_x[i]-ball_x[j];
				a.s_y = ball_y[i]-ball_y[j];    //����s(��������)����
				a.t_x = a.s_y*(-1);
				a.t_y = a.s_x;
				a.s1_x = a.s_x/(sqrt(a.s_x*a.s_x+a.s_y*a.s_y));
				a.s1_y = a.s_y/(sqrt(a.s_x*a.s_x+a.s_y*a.s_y));  //s��λ����
				a.t1_x = a.t_x/(sqrt(a.t_x*a.t_x+a.t_y*a.t_y));
				a.t1_y = a.t_y/(sqrt(a.t_x*a.t_x+a.t_y*a.t_y));  //t��λ����
				a.v1s = ball_vx[i]*a.s1_x+ball_vy[i]*a.s1_y;
				a.v1t = ball_vx[i]*a.t1_x+ball_vy[i]*a.t1_y;     //v1��s,t�ϵ�ͶӰ
				a.v2s = ball_vx[j]*a.s1_x+ball_vy[j]*a.s1_y;
				a.v2t = ball_vx[j]*a.t1_x+ball_vy[j]*a.t1_y;     //v2��s,t�ϵ�ͶӰ
				temp = a.v1s;
				a.v1s =a.v2s;
				a.v2s = temp;                                      //����s������ٶȵ�ֵ
				//ת��Ϊ����
				a.v1s_x = a.v1s*a.s1_x;
				a.v1s_y = a.v1s*a.s1_y;
				a.v1t_x = a.v1t*a.t1_x;
				a.v1t_y =a.v1t*a.t1_y;
				ball_vx[i] = 1.0*(a.v1s_x*1+a.v1t_x*1);
				ball_vy[i] = 1.0*(a.v1s_y*1+a.v1t_y*1);

				a.v2s_x = a.v2s*a.s1_x;
				a.v2s_y = a.v2s*a.s1_y;
				a.v2t_x = a.v2t*a.t1_x;
				a.v2t_y =a.v2t*a.t1_y;
				ball_vx[j] = 1.0*(a.v2s_x*1+a.v2t_x*1);   //��ԭ���ٶ�
				ball_vy[j] = 1.0*(a.v2s_y*1+a.v2t_y*1);
				ballrunning[j] = 1;
				mindistance[j][0] = 999999999;   // ���⽻�������ٶȣ��ֻ�ȥ��
				mindistance[j][1] = -1;

			}
		}
	}
		
			
	Sleep(3);
}
void againboom()
{
	int count = 0; //���������
	if (hit==1)     //����һ�λ������֮ǰһֱΪ0
	{
		count = 0;
	}
	for (i=0;i<Num;i++)      //������Ļ��ͣ�µ�С������
	{
		if (ballrunning[i]==0)
		{
			count++;
		}
	}
	if (count==10)       //ȫͣ��ʱ���ʾ�������
	{
		hit = 0;
		//ʹ�ø˳����ڰ�����Χ
		dist=sqrt((m.x-ball_x[0])*(m.x-ball_x[0])+(m.y-ball_y[0])*(m.y-ball_y[0]));  //��굽ĸ��ľ���
		sinA=(m.y-ball_y[0])/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
		cosA=(m.x-ball_x[0])/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
		start_x=ball_x[0]+l*cosA;      //�����˿���λ��
		start_y=ball_y[0]+l*sinA;
		end_x=start_x+L*cosA;       //������ĩ��λ��
		end_y=start_y+L*sinA;
	}

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
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillcircle(ball_x[i],ball_y[i],r);        //������һ֡��

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
		if((m.uMsg==WM_MOUSEMOVE)&&(hit == 0))
		{
			dist=sqrt((m.x-ball_x[0])*(m.x-ball_x[0])+(m.y-ball_y[0])*(m.y-ball_y[0]));  //��굽ĸ��ľ���
			sinA=(m.y-ball_y[0])/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
			cosA=(m.x-ball_x[0])/dist;     //��������ĸ��������ˮƽ�нǵ�����ֵ
			start_x=ball_x[0]+l*cosA;      //�����˿���λ��
			start_y=ball_y[0]+l*sinA;
			end_x=start_x+L*cosA;       //������ĩ��λ��
			end_y=start_y+L*sinA;

		}
		if(m.uMsg==WM_LBUTTONUP)
		{
			hit=1;
			ballrunning[0] = 1;			
			ball_vx[0] =(-1)*cosA*5;
			ball_vy[0] =(-1)*sinA*5;
		}
		

	}
}

void updatewithoutinput()
{
	boom();
	againboom();
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
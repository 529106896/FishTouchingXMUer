#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
float man_x;						//��������ĺ�����
float man_y;						//���������������
float man_vy_begin;					//��������Ĵ�ֱ�������ٶ�
float man_vx;						//���������ˮƽ�ٶ�
float man_vy;						//���������ʵʱ��ֱ�ٶ�
float a_vy;							//���崹ֱ�ٶȷ�����������ٶ�
int sky_if;							//����������ڼ�������״̬ ����״̬Ϊ1 �ǿ���״̬Ϊ0 ֻ�е��ǿ���״̬ʱ�ſ��԰���w������ ����״̬����������
float bullet_x[4],bullet_y[4];		//�����ͼ�Զ�������ӵ�������
float bullet_vx[4],bullet_vy[4];	//�����ͼ�Զ�������ӵ����ٶ�
float bullet_v1,bullet_v0;			//���������ٶ����
int shoot_time;						//�����������ʵ�����ӵ��̶�ʱ��η���һ��
int shoot_if;						//����������������ӵ���÷���һ��
IMAGE img_bk;						//���� IMAGE ���� ����
IMAGE img_man;						//���� IMAGE ���� ����
IMAGE img_bullet;					//���� IMAGE ���� ��ͼ�Զ������ӵ�
void begining()						//��Ϸ��ʼ��ģ��
{
	man_x=100;
	man_y=633;
	man_vx=2;
	man_vy_begin=-6.5;
	man_vy=0;
	shoot_time=0;
	shoot_if=180;

	bullet_v1=5;
	bullet_v0=0;
	int i;
	for(i=0;i<4;i++)
	{
		bullet_x[i]=bullet_y[i]=50;
		bullet_vx[i]=bullet_v1;
		bullet_vy[i]=bullet_v0;
	}
	
	a_vy=0.24;
	sky_if=0;
	loadimage(&img_bk, ".\\��ɫҩˮ�ڰ˹�.jpg",696,696);			// ��ȡ����ͼƬ�� img_bk ������
	loadimage(&img_man,".\\����1.jpg",37,37);			//��ȡ����ͼƬ��img_man ������
	loadimage(&img_bullet,".\\�ӵ�.jpg",30,30);					//��ȡ�ӵ�ͼƬ�� img_bullet ������

}
int map_y_down(float x1,float y1)						//�����ͼ���� ��ͼ�����ж������Ƿ�ȵ����� �ȵ����ط�0 ���򷵻�0
{
	int judge;
	if(y1>=633)
		judge=633;
	else if(y1>=573&&y1<=580&&x1>393&&x1<527)//1
		judge=573;
	else if(y1>=533&&y1<=540&&x1>533&&x1<629)//2
		judge=533;
	else if(y1>=472&&y1<=479&&x1>413&x1<508)//3
		judge=472;	
	else if(y1>=472&&y1<=479&&x1>250&&x1<346)//4
		judge=472;
	else if(y1>=472&&y1<=479&&x1>90&&x1<185)//6
		judge=472;
	else if(y1>=533&&y1<=540&&x1<185)//5
		judge=533;
	else if(y1>=411&&y1<=418&&x1<65)//7
		judge=411;
	else if(y1>=350&&y1<=357&&x1>90&&x1<185)//8
		judge=350;
	else if(y1>=290&&y1<=297&&x1<65)//9
		judge=290;
	else if(y1>=230&&y1<=237&&x1>90&&x1<185)//10
		judge=230;
	else if(y1>=169&&y1<=176&&x1<65)//11
		judge=169;
	else if(y1>=330&&y1<=337&&x1>213&&x1<260)//������1
		judge=330;
	else if(y1>=252&&y1<=259&&x1>311&&x1<547)//12
		judge=252;
	else if(y1>=252&&y1<=259&&x1>550&&x1<632)//13
		judge=252;
	else if(y1>=330&&y1<=337&&x1>620)//14
		judge=330;
	else if(y1>=370&&y1<=377&&x1>524&&x1<629)//15
		judge=370;
	else if(y1>=330&&y1<=337&&x1>505&&x1<547)//������2
		judge=330;
	else if(y1>=330&&y1<=337&&x1>470&&x1<490)//������3
		judge=330;
	else if(y1>=88&&y1<=95&&x1<632)//16
		judge=88;
	else 
		judge=0;
	return judge;

}
int map_y_up(float x2,float y2)						//�����ͼ���� �ж������ͷ���Ƿ���ǽ ���򷵻ط�0 ���򷵻�0
{
	int judge;
	if(y2<=23)
		judge=23;
	else 
		judge=0;
	return judge;
}
int map_x_left(float x3,float y3)						//�����ͼ���� �ж����������Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	return judge;
}
int map_x_right(float x4,float y4)					//�����ͼ���� �ж�������ұ��Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	return judge;
}
void show()				//��Ϸ��ʾģ��
{
	putimage(0, 0, &img_bk);				// ������ (0, 0) λ����ʾ IMAGE ����
	putimage(man_x, man_y, &img_man);		//��ʾ������
	
	
	putimage(bullet_x[0],bullet_y[0],&img_bullet);
	if(shoot_time>=shoot_if)
		putimage(bullet_x[1],bullet_y[1],&img_bullet);
	if(shoot_time>=2*shoot_if)
		putimage(bullet_x[2],bullet_y[2],&img_bullet);
	if(shoot_time>=3*shoot_if)
		putimage(bullet_x[3],bullet_y[3],&img_bullet);

}

void without_input()				//���û������޹صĸ���
{
	man_y=man_y+man_vy;				//����Ĵ�ֱ�ٶ�man_y��ʼ����0��������Ȼ����α��ʽ�������ﲢ��������
	
		
		bullet_x[0]=bullet_x[0]+bullet_vx[0];
		bullet_y[0]=bullet_y[0]+bullet_vy[0];

		if(shoot_time>=shoot_if)
		{
			bullet_x[1]=bullet_x[1]+bullet_vx[1];
			bullet_y[1]=bullet_y[1]+bullet_vy[1];
		}
		if(shoot_time>=2*shoot_if)
		{
			bullet_x[2]=bullet_x[2]+bullet_vx[2];
			bullet_y[2]=bullet_y[2]+bullet_vy[2];
		}
		if(shoot_time>=3*shoot_if)
		{
			bullet_x[3]=bullet_x[3]+bullet_vx[3];
			bullet_y[3]=bullet_y[3]+bullet_vy[3];
		}
		shoot_time++;
		


	int i=0;
	for(i=0;i<4;i++)
	{
		if(bullet_x[i]==630&&bullet_y[i]==50)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==630&&bullet_y[i]==625)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==545&&bullet_y[i]==625)
		{
			bullet_vy[i]=-bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==545&&bullet_y[i]==180)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==80&&bullet_y[i]==180)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==80&&bullet_y[i]==525)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==0&&bullet_y[i]==525)
		{
			bullet_x[i]=695;
		}
		if(bullet_x[i]==385&&bullet_y[i]==525)
		{
			bullet_vy[i]=-bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==385&&bullet_y[i]==325)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==210&&bullet_y[i]==325)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_y[i]==650)
		{
			bullet_vx[i]=bullet_v1;
			bullet_vy[i]=bullet_v0;
			bullet_x[i]=50;
			bullet_y[i]=50;
		}
	}

	

	if(!map_y_down(man_x,man_y))					//���õ�ͼ�������ж������Ƿ��ڿ���״̬
	{
		sky_if=1;					//������ﴦ�ڿ���״̬����sky_if��Ϊ1��
	}
	if(sky_if==1)				//���������״̬Ϊ1��ʱ�� �����ڿ���Ӧ���е��Զ����� 
	{
	
		if(man_vy>=man_vy_begin)			//��������ٶ�Ϊ�������ٶ�
		{
			man_vy=man_vy+a_vy;		//�ڿ��е�ʱ���ٶ����������ٶȶ��ı�;	
		}
		
		if(map_y_up(man_x,man_y))					//���õ�ͼ���� ��ͼ�����ж�����ͷ���Ƿ���ǽ ���򷵻�1 ���򷵻�0
		{
			man_vy=0;										//����ͷ��ײ��ǽ ��ֱ�ٶȱ�Ϊ0	
			man_y=map_y_up(man_x,man_y)+1;
		}
		if(map_y_down(man_x,man_y))			//���õ�ͼ���� ��ͼ�����ж������Ƿ�ȵ����� �ȵ����ط�0 ���򷵻�0
		{
			man_vy=0;
			sky_if=0;						//����ȵ����� ��Ϊ�ǿ���״̬ 0
			man_y=map_y_down(man_x,man_y);
		}
	}
}

void user_input()				//���û������йصĸ���
{
		if(GetAsyncKeyState('A')&0x8000)  
		{
			//if(!map_x_left(man_x,man_y))			//���õ�ͼ���� �ж����������Ƿ���ǽ ���򷵻�1 ���򷵻�0��ǰ����һ����!������ û��ǽ����0 ��!0����Ϊ�棩 
			//{
				man_x-=2.2;  // λ������
			//}
		}
		if(GetAsyncKeyState('D')&0x8000)
		{
			//if(!map_x_right(man_x,man_y))			//���õ�ͼ���� �ж������ұ��Ƿ���ǽ ���򷵻�1 ���򷵻�0 (ǰ�����һ����!�� û��ǽ����0 ��!0��Ϊ��)
			//{
				man_x+=2.2;  // λ������
			//}		
		}
		if(sky_if==0)			//������ȵ�����Ϊ�ǿ���״̬ʱ ��w����������Ч����
		{
			if(GetAsyncKeyState('W')&0x8000)
			{
				man_vy=man_vy_begin;			//��w������Ч����֮�� ��������ӵ��һ����ֱ�����ϵĳ��ٶ�
			}
		}	
}
void main()				//������
{
	initgraph(696,696);
	begining();
	BeginBatchDraw();
	while(1)
	{
		show();
		FlushBatchDraw();
		without_input();
		Sleep(15);
		user_input();
	}
	EndBatchDraw();
	getch();
	closegraph();
}

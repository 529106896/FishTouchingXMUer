#include <conio.h>
#include <graphics.h>
#include <stdio.h>
int man_x;				//��������ĺ�����
int man_y;				//���������������
int man_vy_begin;		//��������Ĵ�ֱ�������ٶ�
int man_vx;				//���������ˮƽ�ٶ�
int man_vy;				//���������ʵʱ��ֱ�ٶ�
int a_vy;				//���崹ֱ�ٶȷ�����������ٶ�
int a[560][560];		//���廭����С
int jump_if;			//����������ڼ�������״̬ ����״̬Ϊ1 �ǿ���״̬Ϊ0 ֻ�е��ǿ���״̬ʱ�ſ��԰���w������
//int speed_control;	//���ڿ����ٶ�
//int speed;			//���ڿ����ٶ�
IMAGE img_bk;			// ���� IMAGE ���� ����
IMAGE img_man;			//���� IMAGE ���� ����
void begining()						//��Ϸ��ʼ��ģ��
{
	man_x=100;
	man_y=509;
	man_vx=2;
	man_vy_begin=13;
	man_vy=man_vy_begin;
	a_vy=1;
	//speed_control=5;
	//speed=0;
	jump_if=0;
	loadimage(&img_bk, ".//��ɫҩˮ1��.jpg",560,560);			// ��ȡ����ͼƬ�� img_bk ������
	loadimage(&img_man,".//����1.jpg",30,30);			//��ȡ����ͼƬ��ima_man ������			

}
int map_y_down(int man_x,int man_y)						//�����ͼ���� ��ͼ�����ж������Ƿ�ȵ����� �ȵ�����1 ���򷵻�0
{
	int judge;
	return judge;
}
int map_y_up(int man_x,int man_y)						//�����ͼ���� �ж������ͷ���Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	return judge;

}
int map_x_left(int man_x,int man_y)						//�����ͼ���� �ж����������Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	return judge;
}
int map_x_right(int man_x,int man_y)					//�����ͼ���� �ж�������ұ��Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	return judge;
}
void show()				//��Ϸ��ʾģ��
{
	putimage(0, 0, &img_bk);				// ������ (0, 0) λ����ʾ IMAGE ����
	putimage(man_x, man_y, &img_man);		//��ʾ������
}

void without_input()			//���û������޹صĸ���
{
	if(jump_if==1)				//��������������״̬Ϊ1��ʱ�� ��������
	{
		man_y=man_y-man_vy;
		man_vy=man_vy-a_vy;		//�ٶ�������������ٶȶ��ı�
		/*if(map_y_up(int man_x,int man_y))					//���õ�ͼ���� ��ͼ�����ж�����ͷ���Ƿ���ǽ ���򷵻�1 ���򷵻�0
		{
			man_vy=0;										//����ͷ��ײ��ǽ ��ֱ�ٶȱ�Ϊ0	
		}
		*/
		if(man_y==509/*map_y_down(man_x,man_y)*/)			//���õ�ͼ���� ��ͼ�����ж������Ƿ�ȵ����� �ȵ�����1 ���򷵻�0
		{
			man_vy=0;
			jump_if=0;										//����ȵ����� ��Ϊ�ǿ���״̬ 0
			man_vy=man_vy_begin;							//����ȵ����� ���������ٶȵ��ڴ�ֱ�ٶ�
		}
	}
}

void user_input()				//���û������йصĸ���
{
		if(GetAsyncKeyState('A')&0x8000)  
		{
			//if(/*!map_x_left(man_x,man_y)*/)			//���õ�ͼ���� �ж����������Ƿ���ǽ ���򷵻�1 ���򷵻�0��ǰ����һ����!������ û��ǽ����0 ��!0����Ϊ�棩 
			//{
				man_x-=2;  // λ������
			//}
		}
		if(GetAsyncKeyState('D')&0x8000)
		{
			//if(/*!!map_x_left(man_x,man_y)*/)			//���õ�ͼ���� �ж������ұ��Ƿ���ǽ ���򷵻�1 ���򷵻�0 (ǰ�����һ����!�� û��ǽ����0 ��!0��Ϊ��)
			//{
				man_x+=2;  // λ������
			//}		
		}
		if(jump_if==0)			//������ȵ�����ʱ ��w����������Ч����
		{
			if(GetAsyncKeyState('W')&0x8000)
			{
				jump_if=1;			//��w������Ч����֮�� ����״̬��Ϊ1
			}
		}
	
}
void main()				//������
{
	initgraph(560,560);
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


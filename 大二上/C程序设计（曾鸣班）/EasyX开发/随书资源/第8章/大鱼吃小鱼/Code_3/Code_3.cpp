//��ʾ������Ϸ�˵�

//�������⣺��������ƶ������п��ܳ����໥ճ����һ��������
//�������⣺ʳ���㲿�� �����ظ�����



#include<graphics.h>
#include<conio.h>
#include<time.h>


#define length 1000//��Ϸ������
#define high 640//��Ϸ����߶�


struct yu
{
	double position_x;//������
	double position_y;//������
	double v_x;//ˮƽ�ٶ�
	double v_y;//��ֱ�ٶ�
};
yu player;//���
yu timer;//����
yu zhadan;//
yu food1;//1����
yu food2;//2����
yu food3;//3����
yu food4;//4����
yu food5;//5����

IMAGE img_p1;//���ͼƬ
IMAGE img_p1bei;
IMAGE img_bk;//����ͼƬ
IMAGE img_bk0;//�������ͼ
IMAGE img_time;
IMAGE img_timebei;//����ͼƬ
IMAGE img_zha;
IMAGE img_zhabei;//ͼƬ
IMAGE img_f1;
IMAGE img_f1bei;//1����ͼƬ
IMAGE img_f2;
IMAGE img_f2bei;//2����ͼƬ
IMAGE img_f3;
IMAGE img_f3bei;//3����ͼƬ
IMAGE img_f4;
IMAGE img_f4bei;//4����ͼƬ
IMAGE img_f5;
IMAGE img_f5bei;//5����ͼƬ
char input;
double  p1size;//����һ�����������������ĳߴ磻
double  start_p1size;//����һ��������������ҵĳ�ʼ��С��
int score_p1;//����
int gameStatus=0; // ��Ϸ״̬��0Ϊѡ����棬1Ϊ��ʼ���棬2Ϊ������Ϸ



void startMenu()
{
	putimage(0, 0, &img_bk0);//��ʾ����
	settextcolor(RGB(123,90,254));
	settextstyle(70,0, _T("��������"));
	outtextxy(length*0.36, high*0.19, _T("�����С��"));

	setbkmode(TRANSPARENT);
	settextcolor(RGB(106,0,0));
	settextstyle(37,0, _T("��Բ"));
	outtextxy(length*0.35, high*0.36, _T("1 ����Ϸ"));
	outtextxy(length*0.35, high*0.44, _T("2 �˳���Ϸ"));


	settextcolor(RGB(64,0,128));
	settextstyle(25,0, _T("΢���ź�"));
	outtextxy(length*0.36, high*0.6, _T("����������ƶ��Ե�С��"));
	outtextxy(length*0.36, high*0.65, _T("����ʱ�ڴﵽĿ���"));
	outtextxy(length*0.36, high*0.7, _T("��������ʱ�� ը������ʱ��"));
	outtextxy(length*0.36, high*0.75, _T("�������� ײ����ʧȥһ��"));
	FlushBatchDraw();
	Sleep(2);

	char input;
	if(kbhit())//�ж��Ƿ�������
	{
		input=getch();//�����û��Ĳ�ͬ�������ƶ�
		if (input=='1') 
			gameStatus=1;
		else if(input=='2')
		{
			gameStatus=2;
			exit(0);
		}
	}
}



void startup()
{
	score_p1=0;
	p1size=60;//��ҳ�ʼ��СΪ60
	start_p1size=p1size;
	srand((unsigned) time(NULL));//�����

	//�Ƿ���� IMAGE �Ĵ�С����ӦͼƬ
	loadimage(&img_bk0, _T("D:\\enter.jpg"),1000,640,true);//�������
	loadimage(&img_bk, _T("D:\\background.jpg"),1000,640,true);//����

	loadimage(&img_time, _T("D:\\time.jpg"),50,50,true);
	loadimage(&img_timebei, _T("D:\\timebei.jpg"),50,50,true);//����

	loadimage(&img_zha, _T("D:\\zhadan1.jpg"),50,50,true);
	loadimage(&img_zhabei, _T("D:\\zhadan1bei.jpg"),50,50,true);//ը��

	loadimage(&img_f1, _T("D:\\food1.jpg"),45,45,true);
	loadimage(&img_f1bei, _T("D:\\food1bei.jpg"),45,45,true);//1����

	loadimage(&img_f2, _T("D:\\food2.jpg"),80,80,true);
	loadimage(&img_f2bei, _T("D:\\food2bei.jpg"),80,80,true);//2����

	loadimage(&img_f3, _T("D:\\food3.jpg"),110,110,true);
	loadimage(&img_f3bei, _T("D:\\food3bei.jpg"),110,110,true);//3����

	loadimage(&img_f4, _T("D:\\food4.jpg"),130,130,true);
	loadimage(&img_f4bei, _T("D:\\food4bei.jpg"),130,130,true);//4����

	loadimage(&img_f5, _T("D:\\food5.jpg"),200,160,true);
	loadimage(&img_f5bei, _T("D:\\food5bei.jpg"),200,160,true);//5����


	player.position_x=length/2.0;//��Һ�����
	player.position_y=high/2.0;//���������
	player.v_x=0.4;//���ˮƽ�ٶ�
	player.v_y=0.4;//�����ֱ�ٶ�

	timer.position_x=-2000;//���Ӻ�����
	timer.position_y=rand()%500;//��������������趨
	timer.v_x=0.6;//�����ٶ�

	zhadan.position_x=length+500;//������
	zhadan.position_y=rand()%500;//����������趨
	zhadan.v_x=0.6;//�ٶ�

	food1.position_x=0;//1���������
	food1.position_y=rand()%400;//1��������������趨
	food1.v_x=0.45;//1�����ٶ�

	food2.position_x=-200;//2���������
	food2.position_y=rand()%400;//2��������������趨
	food2.v_x=0.45;//2�����ٶ�

	food3.position_x=-500;//3���������
	food3.position_y=rand()%400;//3��������������趨
	food3.v_x=0.5;//3�����ٶ�

	food4.position_x=-800;//4���������
	food4.position_y=rand()%400;//4��������������趨
	food4.v_x=0.5;//4�����ٶ�

	food5.position_x=-1000;//5���������
	food5.position_y=rand()%400;//5��������������趨
	food5.v_x=0.4;//5�����ٶ�

	initgraph(length,high);//�����С
	BeginBatchDraw();

	while (gameStatus==0)
		startMenu();//��ʼ�˵�����

}


void show()
{
	putimage(0, 0, &img_bk);//��ʾ����

	loadimage(&img_p1, _T("D:\\player.jpg"),p1size,p1size,true);
	loadimage(&img_p1bei, _T("D:\\playerbei.jpg"),p1size,p1size,true);//���

	putimage(timer.position_x, timer.position_y, &img_timebei,NOTSRCERASE);//��ʾ����
	putimage(timer.position_x, timer.position_y, &img_time,SRCINVERT);

	putimage(zhadan.position_x, zhadan.position_y, &img_zhabei,NOTSRCERASE);//��ʾը��
	putimage(zhadan.position_x, zhadan.position_y, &img_zha,SRCINVERT);

	putimage(food1.position_x, food1.position_y, &img_f1bei,NOTSRCERASE);//��ʾ1����
	putimage(food1.position_x, food1.position_y, &img_f1,SRCINVERT);

	putimage(food2.position_x, food2.position_y, &img_f2bei,NOTSRCERASE);//��ʾ2����
	putimage(food2.position_x, food2.position_y, &img_f2,SRCINVERT);

	putimage(food3.position_x, food3.position_y, &img_f3bei,NOTSRCERASE);//��ʾ3����
	putimage(food3.position_x, food3.position_y, &img_f3,SRCINVERT);

	putimage(food4.position_x, food4.position_y, &img_f4bei,NOTSRCERASE);//��ʾ4����
	putimage(food4.position_x, food4.position_y, &img_f4,SRCINVERT);

	putimage(food5.position_x, food5.position_y, &img_f5bei,NOTSRCERASE);//��ʾ5����
	putimage(food5.position_x, food5.position_y, &img_f5,SRCINVERT);

	putimage(player.position_x, player.position_y, &img_p1bei,NOTSRCERASE);//��ʾ���
	putimage(player.position_x, player.position_y, &img_p1,SRCINVERT);//����ҷŵ������ʾΪ��ʹ���С��ʱ����������ʵ


	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	settextstyle(20,0, _T("����"));
	TCHAR a[] = _T("���һ:score");
	outtextxy(length*0.15,high*0.02, a);
	TCHAR m[20];
	_stprintf(m, _T("%d"),score_p1);        // �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(length*0.15,high*0.02+30,m);

	FlushBatchDraw();
}



void updateWithoutInput()
{

	timer.position_x = timer.position_x + timer.v_x;//���������ƶ�
	zhadan.position_x = zhadan.position_x - zhadan.v_x;//�����ƶ�
	food1.position_x = food1.position_x + food1.v_x;//1���������ƶ�
	food2.position_x = food2.position_x + food2.v_x;//2���������ƶ�
	food3.position_x = food3.position_x + food3.v_x;//3���������ƶ�
	food4.position_x = food4.position_x + food4.v_x;//4���������ƶ�
	food5.position_x = food5.position_x + food5.v_x;//5���������ƶ�

	if(timer.position_x>=length)
	{
		timer.position_x=-8000;
		timer.position_y=rand()%500;//�����ظ�����
	}
	if(zhadan.position_x<=0)
	{
		zhadan.position_x=5000;
		zhadan.position_y=rand()%500;//�ظ�����
	}
	if(food1.position_x>=length)
	{
		food1.position_x=-400;
		food1.position_y=rand()%400;//1�����ظ�����
	}
	if(food2.position_x>=length)
	{
		food2.position_x=-900;
		food2.position_y=rand()%400;//2�����ظ�����
	}
	if(food3.position_x>=length)
	{
		food3.position_x=-1500;
		food3.position_y=rand()%400;//3�����ظ�����
	}
	if(food4.position_x>=length)
	{
		food4.position_x=-1800;
		food4.position_y=rand()%400;//4�����ظ�����
	}
	if(food5.position_x>=length)
	{
		food5.position_x=-2500;
		food5.position_y=rand()%400;//5�����ظ�����
	}

	if( (timer.position_x+25>=player.position_x+20 && timer.position_x+25<=player.position_x+p1size ) && (timer.position_y+25>=player.position_y+20 && timer.position_y+25<=player.position_y+p1size))
	{
		timer.position_x=-5000;
		timer.position_y=rand()%500;//��ҳԵ�����
	}
	if( (zhadan.position_x+25>=player.position_x+20 && zhadan.position_x+25<=player.position_x+p1size ) && (zhadan.position_y+25>=player.position_y+20 && zhadan.position_y+25<=player.position_y+p1size))
	{
		zhadan.position_x=4000;
		zhadan.position_y=rand()%500;//��ҳԵ�ը��
	}

	if(food1.position_x+25.5>player.position_x && food1.position_x+25.5<player.position_x+p1size && food1.position_y+25.5>player.position_y && food1.position_y+25.5<player.position_y+p1size)
		//�ж�һ�����Ƿ񱻳ԡ��ж�����Ϊһ������������������һ�ڲ�������
	{
		p1size+=0.5;
		score_p1++;
		food1.position_x=-400;
		food1.position_y=rand()%(high-45);//С�㱻�ԣ������������
	}
	if(p1size>80)
	{
		if(food2.position_x+40>player.position_x && food2.position_x+40<player.position_x+p1size && food2.position_y+40>player.position_y && food2.position_y+40<player.position_y+p1size)
		{
			p1size+=1;
			score_p1+=2;
			food2.position_x=-900;
			food2.position_y=rand()%(high-80);
		}

	}
	else
	{
		if(player.position_x+p1size/2.0>food2.position_x && player.position_x+p1size/2.0<food2.position_x+80 && player.position_y+p1size/2.0>food2.position_y && player.position_y+p1size/2.0<food2.position_y+80 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//���������λ��
			player.position_y=rand()%(high-60);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط����ɣ�

	if(p1size>110)
	{
		if(food3.position_x+55.5>player.position_x && food3.position_x+55.5<player.position_x+p1size && food3.position_y+55.5>player.position_y && food3.position_y+55.5<player.position_y+p1size)
		{
			p1size+=1.5;
			score_p1+=3;
			food3.position_x=-1500;
			food3.position_y=rand()%(high-110);
		}

	}
	else
	{
		if(player.position_x+p1size/2.0>food3.position_x && player.position_x+p1size/2.0<food3.position_x+110 && player.position_y+p1size/2.0>food3.position_y && player.position_y+p1size/2.0<food3.position_y+110 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//���������λ��
			player.position_y=rand()%(high-60);
		}
	}
	if(p1size>130)
	{
		if(food4.position_x+65>player.position_x && food4.position_x+65<player.position_x+p1size && food4.position_y+65>player.position_y && food4.position_y+65<player.position_y+p1size)
		{
			p1size+=2;
			score_p1+=4;
			food4.position_x=-1800;
			food4.position_y=rand()%(high-130);
		}

	}
	else
	{
		if(player.position_x+p1size/2.0>food4.position_x && player.position_x+p1size/2.0<food4.position_x+130 && player.position_y+p1size/2.0>food4.position_y && player.position_y+p1size/2.0<food4.position_y+130 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//���������λ��
			player.position_y=rand()%(high-60);
		}
	}
	if(p1size>200)
	{
		if(food5.position_x+100>player.position_x&&food5.position_x+100<player.position_x+p1size&&food5.position_y+80>player.position_y&&food5.position_y+80<player.position_y+p1size)
		{
			p1size+=2.5;
			score_p1+=5;
			food5.position_x =-2500;
			food5.position_y =rand()%(high-160);
		}
	}
	else
	{
		if(player.position_x+p1size/2.0>food5.position_x && player.position_x+p1size/2.0<food5.position_x+200 && player.position_y+p1size/2.0>food5.position_y && player.position_y+p1size/2.0<food5.position_y+160 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//���������λ��
			player.position_y=rand()%(high-60);
		}
	}
}


void updateWithInput()
{

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (player.position_x>0))
		player.position_x=player.position_x-player.v_x;  //����
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (player.position_x<length-80))
		player.position_x=player.position_x+player.v_x;  //����
	if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  player.position_y>0)
		player.position_y=player.position_y-player.v_y;  //����
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  player.position_y<high-80)
		player.position_y=player.position_y+player.v_y;  //����

}



void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}


void main()
{
	startup();
	while(1)
	{
		show();
		updateWithoutInput() ;
		updateWithInput(); 
	}
	gameover();
}
//ʵ����Ϸ����ͣ
//�����Ӽ�ʱ ��ը����ʱ
//������Һ�ʳ��Ĵ�С�������3

//����1��������ֺ�����ƶ������п��ܳ����໥ճ����һ��������
//����2��ʳ���㲿�� �����ظ�����
//����3�������ж��������ж������


#include<graphics.h>
#include<conio.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")

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
yu zhadan;//ը��
yu food1,f_food1;//1����
yu food2,f_food2;//2����
yu food3,f_food3;//3����
yu food4,f_food4;//4����
yu food5,f_food5;//5����

IMAGE img_p1;//���ͼƬ
IMAGE img_p1bei;
IMAGE img_bk;//����ͼƬ
IMAGE img_bk0;//�������ͼ
IMAGE img_time;
IMAGE img_timebei;//����ͼƬ
IMAGE img_zha;
IMAGE img_zhabei;//ͼƬ
IMAGE img_f1,img_f_f1;
IMAGE img_f1bei,img_f_f1bei;//1����ͼƬ
IMAGE img_f2,img_f_f2;
IMAGE img_f2bei,img_f_f2bei;//2����ͼƬ
IMAGE img_f3,img_f_f3;
IMAGE img_f3bei,img_f_f3bei;//3����ͼƬ
IMAGE img_f4,img_f_f4;
IMAGE img_f4bei,img_f_f4bei;//4����ͼƬ
IMAGE img_f5,img_f_f5;
IMAGE img_f5bei,img_f_f5bei;//5����ͼƬ

char input;//�����������ʹ��

double  p1size;//����һ�����������������ĳߴ�
double  start_p1size;//����һ��������������ҵĳ�ʼ��С

int score_p1;//����

int startTime;//��ʱ
int endTime;//��ʱ
double resttime;//ʣ��ʱ�� 
int timelong=150;//ʱ������

int yuhead=0; //�ж���ͷ����

static int shengming = 3;//�������

int gameStatus=0; // ��Ϸ״̬��0Ϊ��ʼ�˵����棬1Ϊ������Ϸ��2Ϊ������Ϸ״̬��3Ϊ��Ϸ��ͣ



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
	settextstyle(30,0, _T("΢���ź�"));
	outtextxy(length*0.36, high*0.55, _T("ESC���������˵�"));

	settextcolor(RGB(64,0,128));
	settextstyle(25,0, _T("΢���ź�"));
	outtextxy(length*0.36, high*0.65, _T("����������ƶ��Ե�С��"));
	outtextxy(length*0.36, high*0.7, _T("����ʱ�ڴﵽĿ���"));
	outtextxy(length*0.36, high*0.75, _T("��������ʱ�� ը������ʱ��"));
	outtextxy(length*0.36, high*0.8, _T("�������� ײ����ʧȥһ��"));

	FlushBatchDraw();
	Sleep(2);

	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == '1') 
			gameStatus = 1;
		else if (input == '2')
		{
			gameStatus = 2;
			exit(0);
		}
	}
}



void pauseMenu() // ��Ϸ��ͣ��˵����棬һ�㰴ESC���������ý���
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
	settextstyle(30,0, _T("΢���ź�"));
	outtextxy(length*0.36, high*0.55, _T("ESC���������˵�"));

	settextcolor(RGB(64,0,128));
	settextstyle(25,0, _T("΢���ź�"));
	outtextxy(length*0.36, high*0.65, _T("����������ƶ��Ե�С��"));
	outtextxy(length*0.36, high*0.7, _T("����ʱ�ڴﵽĿ���"));
	outtextxy(length*0.36, high*0.75, _T("��������ʱ�� ը������ʱ��"));
	outtextxy(length*0.36, high*0.8, _T("�������� ײ����ʧȥһ��"));

	FlushBatchDraw();
	Sleep(2);

	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == '1') 
			gameStatus = 1;
		else if (input == '2')
		{
			gameStatus = 2;
			exit(0);
		}
	}
}



void startup()
{
	mciSendString(_T("open D:\\music.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // ѭ������

	initgraph(length,high);
	// ��ȡ���ھ��
	HWND hwnd = GetHWnd();
	// ���ô��ڱ�������
	SetWindowText(hwnd, _T("�����С��"));

	score_p1=0;
	p1size=40;//��ҳ�ʼ��СΪ40
	start_p1size=p1size;

	srand((unsigned) time(NULL));//�����

	//�Ƿ���� IMAGE �Ĵ�С����ӦͼƬ
	loadimage(&img_bk0, _T("D:\\enter.jpg"),1000,640,true);//�������
	loadimage(&img_bk, _T("D:\\background.jpg"),1000,640,true);//����

	loadimage(&img_time, _T("D:\\time.jpg"),35,35,true);
	loadimage(&img_timebei, _T("D:\\timebei.jpg"),35,35,true);//����

	loadimage(&img_zha, _T("D:\\zhadan1.jpg"),40,40,true);
	loadimage(&img_zhabei, _T("D:\\zhadan1bei.jpg"),40,40,true);//ը��

	loadimage(&img_f1, _T("D:\\food1.jpg"),40,30,true);
	loadimage(&img_f1bei, _T("D:\\food1bei.jpg"),40,30,true);//1����
	loadimage(&img_f_f1, _T("D:\\f_food1.jpg"),40,30,true);
	loadimage(&img_f_f1bei, _T("D:\\f_food1bei.jpg"),40,30,true);//1���㷴��

	loadimage(&img_f2, _T("D:\\food2.jpg"),65,40,true);
	loadimage(&img_f2bei, _T("D:\\food2bei.jpg"),65,40,true);//2����
	loadimage(&img_f_f2, _T("D:\\f_food2.jpg"),65,40,true);
	loadimage(&img_f_f2bei, _T("D:\\f_food2bei.jpg"),65,40,true);//2���㷴��

	loadimage(&img_f3, _T("D:\\food3.jpg"),80,80,true);
	loadimage(&img_f3bei, _T("D:\\food3bei.jpg"),80,80,true);//3����
	loadimage(&img_f_f3, _T("D:\\f_food3.jpg"),80,80,true);
	loadimage(&img_f_f3bei, _T("D:\\f_food3bei.jpg"),80,80,true);//3���㷴��

	loadimage(&img_f4, _T("D:\\food4.jpg"),120,110,true);
	loadimage(&img_f4bei, _T("D:\\food4bei.jpg"),120,110,true);//4����
	loadimage(&img_f_f4, _T("D:\\f_food4.jpg"),120,110,true);
	loadimage(&img_f_f4bei, _T("D:\\f_food4bei.jpg"),120,110,true);//4���㷴��

	loadimage(&img_f5, _T("D:\\food5.jpg"),250,125,true);
	loadimage(&img_f5bei, _T("D:\\food5bei.jpg"),250,125,true);//5����
	loadimage(&img_f_f5, _T("D:\\f_food5.jpg"),250,125,true);
	loadimage(&img_f_f5bei, _T("D:\\f_food5bei.jpg"),250,125,true);//5���㷴��

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
	f_food1.position_x=length+(rand()%10)*100;//����1���������
	f_food1.position_y=rand()%400;//����1��������������趨
	f_food1.v_x=0.45;//����1�����ٶ�

	food2.position_x=-200;//2���������
	food2.position_y=rand()%400;//2��������������趨
	food2.v_x=0.45;//2�����ٶ�
	f_food2.position_x=length+length+(rand()%15)*100;//����2���������
	f_food2.position_y=rand()%400;//����2��������������趨
	f_food2.v_x=0.45;//����2�����ٶ�

	food3.position_x=-500;//3���������
	food3.position_y=rand()%400;//3��������������趨
	food3.v_x=0.43;//3�����ٶ�
	f_food3.position_x=length+length+(rand()%20)*100;//����3���������
	f_food3.position_y=rand()%400;//����3��������������趨
	f_food3.v_x=0.43;//����3�����ٶ�

	food4.position_x=-800;//4���������
	food4.position_y=rand()%400;//4��������������趨
	food4.v_x=0.42;//4�����ٶ�
	f_food4.position_x=length+length+(rand()%20)*150;//����4���������
	f_food4.position_y=rand()%400;//����4��������������趨
	f_food4.v_x=0.42;//����4�����ٶ�

	food5.position_x=-10000;//5���������
	food5.position_y=rand()%400;//5��������������趨
	food5.v_x=0.4;//5�����ٶ�
	f_food5.position_x=length+length+(rand()%10)*1000;//����5���������
	f_food5.position_y=rand()%400;//����5��������������趨
	f_food5.v_x=0.4;//����5�����ٶ�

	initgraph(length,high);//�����С
	BeginBatchDraw();

	while (gameStatus==0)
		startMenu();//��ʼ�˵�����

	startTime=clock();
}



void show()
{
	while (gameStatus==2)
		pauseMenu(); // ��Ϸ��ͣ��˵����棬һ�㰴ESC���������ý���

	putimage(0, 0, &img_bk);//��ʾ����

	if (yuhead==0)
	{
		loadimage(&img_p1,  _T("D:\\player.jpg"),p1size,p1size,true);
		loadimage(&img_p1bei, _T("D:\\playerbei.jpg"),p1size,p1size,true);//�������
	}
	else
	{
		loadimage(&img_p1,  _T("D:\\f_player.jpg"),p1size,p1size,true);
		loadimage(&img_p1bei,  _T("D:\\f_playerbei.jpg"),p1size,p1size,true);//�������
	}

	putimage(timer.position_x, timer.position_y, &img_timebei,NOTSRCERASE);//��ʾ����
	putimage(timer.position_x, timer.position_y, &img_time,SRCINVERT);

	putimage(zhadan.position_x, zhadan.position_y, &img_zhabei,NOTSRCERASE);//��ʾը��
	putimage(zhadan.position_x, zhadan.position_y, &img_zha,SRCINVERT);

	putimage(food1.position_x, food1.position_y, &img_f1bei,NOTSRCERASE);//��ʾ1����
	putimage(food1.position_x, food1.position_y, &img_f1,SRCINVERT);
	putimage(f_food1.position_x, f_food1.position_y, &img_f_f1bei,NOTSRCERASE);//��ʾ����1����
	putimage(f_food1.position_x, f_food1.position_y, &img_f_f1,SRCINVERT);

	putimage(food2.position_x, food2.position_y, &img_f2bei,NOTSRCERASE);//��ʾ2����
	putimage(food2.position_x, food2.position_y, &img_f2,SRCINVERT);
	putimage(f_food2.position_x, f_food2.position_y, &img_f_f2bei,NOTSRCERASE);//��ʾ����2����
	putimage(f_food2.position_x, f_food2.position_y, &img_f_f2,SRCINVERT);

	putimage(food3.position_x, food3.position_y, &img_f3bei,NOTSRCERASE);//��ʾ3����
	putimage(food3.position_x, food3.position_y, &img_f3,SRCINVERT);
	putimage(f_food3.position_x, f_food3.position_y, &img_f_f3bei,NOTSRCERASE);//��ʾ����3����
	putimage(f_food3.position_x, f_food3.position_y, &img_f_f3,SRCINVERT);

	putimage(food4.position_x, food4.position_y, &img_f4bei,NOTSRCERASE);//��ʾ4����
	putimage(food4.position_x, food4.position_y, &img_f4,SRCINVERT);
	putimage(f_food4.position_x, f_food4.position_y, &img_f_f4bei,NOTSRCERASE);//��ʾ����4����
	putimage(f_food4.position_x, f_food4.position_y, &img_f_f4,SRCINVERT);

	putimage(food5.position_x, food5.position_y, &img_f5bei,NOTSRCERASE);//��ʾ5����
	putimage(food5.position_x, food5.position_y, &img_f5,SRCINVERT);
	putimage(f_food5.position_x, f_food5.position_y, &img_f_f5bei,NOTSRCERASE);//��ʾ����5����
	putimage(f_food5.position_x, f_food5.position_y, &img_f_f5,SRCINVERT);

	putimage(player.position_x, player.position_y, &img_p1bei,NOTSRCERASE);//��ʾ���
	putimage(player.position_x, player.position_y, &img_p1,SRCINVERT);//����ҷŵ������ʾΪ��ʹ���С��ʱ����������ʵ

	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	settextstyle(20,0, _T("����"));

	//��ʾ��ҷ���
	TCHAR a[] = _T("���һ:score");
	outtextxy(length*0.15,high*0.02, a);
	TCHAR m[20];
	_stprintf(m, _T("%d"),score_p1);//�߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(length*0.15,high*0.02+30,m);

	//��ʾʣ������
	TCHAR b[] = _T("������");
	outtextxy(length*0.05,high*0.02, b);
	TCHAR c[20];
	_stprintf(c, _T("%d"),shengming);//�߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(length*0.05+10,high*0.02+30,c);

	//��ʾ��ʣʱ��
	endTime=clock();
	setcolor(WHITE);
	TCHAR t[] = _T("��Ϸ��ʣ:");
	outtextxy(length*0.3,high*0.02, t);
	TCHAR s[20];
	resttime = timelong- (endTime-startTime)/1000.0;
	_stprintf(s, _T("%.f s"),resttime);//�߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(length*0.3, high*0.02+30, s);

	FlushBatchDraw();
}



void updateWithoutInput()
{
	if (shengming==0)
	{
		gameStatus=0;
	}
	if(resttime<0)
	{
		gameStatus=0;
	}

	timer.position_x = timer.position_x + timer.v_x;//���������ƶ�
	zhadan.position_x = zhadan.position_x - zhadan.v_x;//�����ƶ�

	food1.position_x = food1.position_x + food1.v_x;//1���������ƶ�
	food2.position_x = food2.position_x + food2.v_x;//2���������ƶ�
	food3.position_x = food3.position_x + food3.v_x;//3���������ƶ�
	food4.position_x = food4.position_x + food4.v_x;//4���������ƶ�
	food5.position_x = food5.position_x + food5.v_x;//5���������ƶ�

	f_food1.position_x = f_food1.position_x - f_food1.v_x;//1���������ƶ�
	f_food2.position_x = f_food2.position_x - f_food2.v_x;//2���������ƶ�
	f_food3.position_x = f_food3.position_x - f_food3.v_x;//3���������ƶ�
	f_food4.position_x = f_food4.position_x - f_food4.v_x;//4���������ƶ�
	f_food5.position_x = f_food5.position_x - f_food5.v_x;//5���������ƶ�

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
		food2.position_x=-1000;
		food2.position_y=rand()%400;//2�����ظ�����
	}
	if(food3.position_x>=length)
	{
		food3.position_x=-1800;
		food3.position_y=rand()%400;//3�����ظ�����
	}
	if(food4.position_x>=length)
	{
		food4.position_x=-2700;
		food4.position_y=rand()%400;//4�����ظ�����
	}
	if(food5.position_x>=length)
	{
		food5.position_x=-6000;
		food5.position_y=rand()%400;//5�����ظ�����
	}
	if(f_food1.position_x<=-300)
	{
		f_food1.position_x=length+1000;
		f_food1.position_y=rand()%400;//����1�����ظ�����
	}
	if(f_food2.position_x<=-300)
	{
		f_food2.position_x=length+1200;
		f_food2.position_y=rand()%400;//����2�����ظ�����
	}
	if(f_food3.position_x<=-300)
	{
		f_food3.position_x=length+2000;
		f_food3.position_y=rand()%400;//����3�����ظ�����
	}
	if(f_food4.position_x<=-300)
	{
		f_food4.position_x=length+3000;
		f_food4.position_y=rand()%400;//����4�����ظ�����
	}
	if(f_food5.position_x<=-300)
	{
		f_food5.position_x=length+5000;
		f_food5.position_y=rand()%400;//����5�����ظ�����
	}

	//�ж������Ƿ񱻳ԡ��ж�����Ϊ���ӵ���������������ڲ�������
	if( (timer.position_x+25>=player.position_x+20 && timer.position_x+25<=player.position_x+p1size ) && (timer.position_y+25>=player.position_y+20 && timer.position_y+25<=player.position_y+p1size))
	{
		mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
		mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
		mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

		timelong+=20;
		timer.position_x=-5000;
		timer.position_y=rand()%500;
	}
	//�ж�ը���Ƿ񱻳ԡ��ж�����Ϊը������������������ڲ�������
	if( (zhadan.position_x+25>=player.position_x+20 && zhadan.position_x+25<=player.position_x+p1size ) && (zhadan.position_y+25>=player.position_y+20 && zhadan.position_y+25<=player.position_y+p1size))
	{
		mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
		mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
		mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

		timelong-=20;
		zhadan.position_x=4000;
		zhadan.position_y=rand()%500;
	}
	//�ж�һ�����Ƿ񱻳ԡ��ж�����Ϊһ�������������������ڲ�������
	if(food1.position_x+20>player.position_x && food1.position_x+20<player.position_x+p1size && food1.position_y+15>player.position_y && food1.position_y+15<player.position_y+p1size)
	{
		mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
		mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
		mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

		p1size+=2;
		score_p1++;
		food1.position_x=-400;
		food1.position_y=rand()%(high-30);//С�㱻�ԣ������������
	}
	//�ж�2�����Ƿ񱻳ԡ��ж�����Ϊ2�������������������ڲ�������
	if(p1size>45)
	{
		if(food2.position_x+32.5>player.position_x && food2.position_x+32.5<player.position_x+p1size && food2.position_y+20>player.position_y && food2.position_y+20<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=4;
			score_p1+=2;
			food2.position_x=-1000;
			food2.position_y=rand()%(high-40);
		}
	}
	//����������������ײ����С�ص���ʼ״̬������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>food2.position_x && player.position_x+p1size/2.0<food2.position_x+65 && player.position_y+p1size/2.0>food2.position_y && player.position_y+p1size/2.0<food2.position_y+40 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�3�����Ƿ񱻳ԡ��ж�����Ϊ3�������������������ڲ�������
	if(p1size>70)
	{
		if(food3.position_x+40>player.position_x && food3.position_x+40<player.position_x+p1size && food3.position_y+40>player.position_y && food3.position_y+40<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=7;
			score_p1+=3;
			food3.position_x=-1800;
			food3.position_y=rand()%(high-80);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>food3.position_x && player.position_x+p1size/2.0<food3.position_x+80 && player.position_y+p1size/2.0>food3.position_y && player.position_y+p1size/2.0<food3.position_y+80 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�4�����Ƿ񱻳ԡ��ж�����Ϊ4�������������������ڲ�������
	if(p1size>100)
	{
		if(food4.position_x+60>player.position_x && food4.position_x+60<player.position_x+p1size && food4.position_y+50>player.position_y && food4.position_y+50<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=8;
			score_p1+=4;
			food4.position_x=-2700;
			food4.position_y=rand()%(high-100);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>food4.position_x && player.position_x+p1size/2.0<food4.position_x+110 && player.position_y+p1size/2.0>food4.position_y && player.position_y+p1size/2.0<food4.position_y+100 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�5�����Ƿ񱻳ԡ��ж�����Ϊ5�������������������ڲ�������
	if(p1size>185)
	{
		if(food5.position_x+125>player.position_x&&food5.position_x+125<player.position_x+p1size&&food5.position_y+62.5>player.position_y&&food5.position_y+62.5<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=5;
			score_p1+=5;
			food5.position_x =-4000;
			food5.position_y =rand()%(high-125);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>food5.position_x && player.position_x+p1size/2.0<food5.position_x+250 && player.position_y+p1size/2.0>food5.position_y && player.position_y+p1size/2.0<food5.position_y+125 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�1�����Ƿ񱻳ԡ��ж�����Ϊ1�������������������ڲ�������
	if(f_food1.position_x+20>player.position_x && f_food1.position_x+20<player.position_x+p1size && f_food1.position_y+15>player.position_y && f_food1.position_y+15<player.position_y+p1size)
	{
		mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
		mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
		mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

		p1size+=2;
		score_p1++;
		f_food1.position_x=length+600;
		f_food1.position_y=rand()%(high-30);//С�㱻�ԣ������������
	}
	//�ж�2�����Ƿ񱻳ԡ��ж�����Ϊ2�������������������ڲ�������
	if(p1size>45)
	{
		if(f_food2.position_x+32.5>player.position_x && f_food2.position_x+32.5<player.position_x+p1size && f_food2.position_y+20>player.position_y && f_food2.position_y+20<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=4;
			score_p1+=2;
			f_food2.position_x=length+1800;
			f_food2.position_y=rand()%(high-40);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>f_food2.position_x && player.position_x+p1size/2.0<f_food2.position_x+65 && player.position_y+p1size/2.0>f_food2.position_y && player.position_y+p1size/2.0<f_food2.position_y+40 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�3�����Ƿ񱻳ԡ��ж�����Ϊ3�������������������ڲ�������
	if(p1size>70)
	{
		if(f_food3.position_x+40>player.position_x && f_food3.position_x+40<player.position_x+p1size && f_food3.position_y+40>player.position_y && f_food3.position_y+40<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=7;
			score_p1+=3;
			f_food3.position_x=length+2800;
			f_food3.position_y=rand()%(high-80);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>f_food3.position_x && player.position_x+p1size/2.0<f_food3.position_x+80 && player.position_y+p1size/2.0>f_food3.position_y && player.position_y+p1size/2.0<f_food3.position_y+80 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�4�����Ƿ񱻳ԡ��ж�����Ϊ4�������������������ڲ�������
	if(p1size>100)
	{
		if(f_food4.position_x+60>player.position_x && f_food4.position_x+60<player.position_x+p1size && f_food4.position_y+50>player.position_y && f_food4.position_y+50<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=8;
			score_p1+=4;
			f_food4.position_x=length+6000;
			f_food4.position_y=rand()%(high-100);
		}

	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>f_food4.position_x && player.position_x+p1size/2.0<f_food4.position_x+120 && player.position_y+p1size/2.0>f_food4.position_y && player.position_y+p1size/2.0<f_food4.position_y+100 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
	//�ж�5�����Ƿ񱻳ԡ��ж�����Ϊ5�������������������ڲ�������
	if(p1size>185)
	{
		if(f_food5.position_x+125>player.position_x&&f_food5.position_x+125<player.position_x+p1size&&f_food5.position_y+62.5>player.position_y&&f_food5.position_y+62.5<player.position_y+p1size)
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\1.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size+=5;
			score_p1+=5;
			f_food5.position_x =length+3300;
			f_food5.position_y =rand()%(high-125);
		}
	}
	//����������������ײ����С�ص���ʼ״̬��������������ط�����
	else
	{
		if(player.position_x+p1size/2.0>f_food5.position_x && player.position_x+p1size/2.0<f_food5.position_x+250 && player.position_y+p1size/2.0>f_food5.position_y && player.position_y+p1size/2.0<f_food5.position_y+125 )
		{
			mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString(_T("open D:\\2.mp3 alias gemusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��

			p1size=start_p1size;
			shengming--;
			player.position_x=rand()%(length-40);//���������λ��
			player.position_y=rand()%(high-40);
		}
	}
}



void updateWithInput()
{

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (player.position_x>0))
	{
		yuhead=1;//תͷ
		player.position_x=player.position_x-player.v_x;  //����
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (player.position_x<length-80))
	{
		yuhead=0;
		player.position_x=player.position_x+player.v_x;  //����
	}
	if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  player.position_y>0)
		player.position_y=player.position_y-player.v_y;  //����
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  player.position_y<high-80)
		player.position_y=player.position_y+player.v_y;  //����


	if(kbhit())//�ж��û��Ƿ���Ҫ��ͣ��Ϸ
	{
		input = getch();
		if (input == 27) // ESC����ACSII��Ϊ27
		{
			gameStatus = 2;
		}
	}

}



void gameover()
{
	//��Ϸ���� ��ʾ���շ���
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	settextstyle(60,0, _T("����"));
	TCHAR a[] = _T("GAME OVER");
	outtextxy(length/2-100,high/3.0, a);
	setcolor(RED);
	TCHAR b[] = _T("score");
	outtextxy(length/2-50,high/3.0+50,b);
	TCHAR m[20];
	_stprintf(m, _T("%d"),score_p1);//�߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(length/2-20,high/3.0+110,m);
	EndBatchDraw();
	Sleep(100000);
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
		if(!gameStatus)
			break;
	}
	gameover();
}
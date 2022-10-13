#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")

void startup();
void show();
void updatewithoutinput();
void status_change();
void updatewithinput();
void gameover();

#define high 670//�����ĸ߶�
#define width 900//�����Ŀ��
#define person_high 72//�����ڵ�С�ӵĸ߶�
#define person_width 64//�����ڵ�С�ӵĿ��
#define shoesperson_high 92//�����ڵ�С�ӷ���ʱ�ĸ߶�
#define shoesperson_width 64//�����ڵ�С�ӷ���ʱ�Ŀ��
#define digdownperson_high 80//�����ڵ�С��������ʱ�ĸ߶�
#define digdownperson_width 64//�����ڵ�С��������ʱ�Ŀ��
#define digleftperson_high 78//�����ڵ�С��������ʱ�ĸ߶�
#define digleftperson_width 64//�����ڵ�С��������ʱ�Ŀ��
#define digrightperson_high 78//�����ڵ�С��������ʱ�ĸ߶�
#define digrightperson_width 64//�����ڵ�С��������ʱ�Ŀ��
#define num_stonewidth 14//����ʯ�����
#define num_stonehigh 11//����ʯ�����
#define num_scene 3//�ؿ�����
#define stone_high 64//ש��ĸ�
#define stone_width 64//ש��Ŀ�
#define apper_1stone 414//��һ���п�ʼ����ש���yλ��
#define apper_2stone 0//�ڶ����п�ʼ����ש���yλ��


IMAGE img_bk;//���屳��ͼƬ
IMAGE img_1;//�����һ�ص�ͼƬ
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7;//����ʯ���ͼƬ
IMAGE img_coal_1, img_coal_2, img_coal_3, img_coal_4, img_coal_5, img_coal_0;//����ú���ͼƬ
IMAGE img_copper_1, img_copper_2, img_copper_3, img_copper_4, img_copper_5, img_copper_6, img_copper_0;//����ͭ���ͼƬ
IMAGE img_silver_1, img_silver_2, img_silver_3, img_silver_4, img_silver_5, img_silver_0;//���������ͼƬ
IMAGE img_person_0, img_person_00;//�����ڵ�С�ӵ�����ͼƬ 0��ʾ�ڰװ� 00��ʾ�ʰ�
IMAGE img_person_1, img_person_2;//�����ڵ�С�������ߵ�ͼƬ 1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_shoes_1, img_shoes_2;//������ЬͼƬ 1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digleftperson_1, img_digleftperson_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digrightperson_1, img_digrightperson_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digdownperson_1, img_digdownperson_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_shop;//�̵�
MOUSEMSG m;//����һ��������

int scene;//�����л�����
int left_i;//��¼�����ƶ���ͼƬ
int right_i;//��¼�����ƶ���ͼƬ
int G;//�������ٶ�
int shoes_a;//���Ь���ٶ�
int digbf;//���ڼ�¼�ж��Ƿ��������� 0��ʾû�� 1��ʾ��
int digleftbf;//���ڼ�¼�ж��Ƿ��������� 0��ʾû�� 1��ʾ��
int digrightbf;//���ڼ�¼�ж��Ƿ��������� 0��ʾû�� 1��ʾ��
int flyleftbf;//���ڼ�¼�ж��Ƿ�������� 0��ʾû�� 1��ʾ��
int flyrightbf;//���ڼ�¼�ж��Ƿ������ҷ� 0��ʾû�� 1��ʾ��
int exist_leftstone;//���ڼ�¼�ж��Ƿ������ש�� 0��ʾû�� 1��ʾ��
int exist_rightstone;//���ڼ�¼�ж��Ƿ��Ҷ���ש�� 0��ʾû�� 1��ʾ��
int exist_downstone;//���ڼ�¼�ж��Ƿ��¶���ש�� 0��ʾû�� 1��ʾ��
int exist_flyleftstone; //���ڼ�¼�жϷ���ʱ�Ƿ������ש�� 0��ʾû�� 1��ʾ��
int exist_flyrightstone; //���ڼ�¼�жϷ���ʱ�Ƿ��Ҷ���ש�� 0��ʾû�� 1��ʾ��
int score;//������¼

typedef struct thing//����ṹ��������
{
	float left_x;//���x����
	float left_y;//���y����
	float right_x;//�Ҷ�x����
	float right_y;//�Ҷ�y����
	float top_x;//�϶�x����
	float top_y;//�϶�y����
	float bottom_x;//�ײ�x����
	float bottom_y;//�ײ�y����
	float center_x;//����x����
	float center_y;//����y����
	float v;//�ڵ�С����ֱ�����ٶ�
}thing;
thing person;//������

struct stone//����ṹ����������
{
	float left_x;//���x����
	float left_y;//���y����
	float right_x;//�Ҷ�x����
	float right_y;//�Ҷ�y����
	float top_x;//�϶�x����
	float top_y;//�϶�y����
	float bottom_x;//�ײ�x����
	float bottom_y;//�ײ�y����
	float center_x;//����x����
	float center_y;//����y����
	float status;//��ʾש���״̬ 0��ʾ�� 1Ϊԭʼ 2����1 3����2 4����3 5����4 6����5 7����6
}stone[num_scene][num_stonehigh][num_stonewidth];//����Ľṹ��һ��56��ש��

void main()
{
	startup();
	while (1)
	{
		show();
		updatewithoutinput();
		status_change();
		updatewithinput();
	}
	gameover();
}
/*count 0 ��ʼ���棻1 ��һ�ؽ��� */
void startup()
{
	initgraph(width, high);//����
	loadimage(&img_bk, _T("background.jpg"));//������Ϸ��ʼ����
	loadimage(&img_1, _T("level_1.jpg"));//�����һ�ص�ͼƬ
	loadimage(&img_shop, _T("shop.jpg"));//�����̵��ͼƬ
	loadimage(&img_person_0, _T("person_0.jpg"));//�������������ͼƬ�ڰװ�
	loadimage(&img_person_00, _T("person_00.jpg"));//�������������ͼƬ�ʰ�
	loadimage(&img_person_1, _T("person_1.jpg"));//��������������·��ͼƬ�ĺڰװ�
	loadimage(&img_person_2, _T("person_2.jpg"));//��������������·��ͼƬ�ʰ�
	loadimage(&img_stone_0, _T("stone_0.jpg"));//����յ�ͼƬ
	loadimage(&img_stone_1, _T("stone_1.jpg"));//����ʯ��ԭͼ��ͼƬ
	loadimage(&img_stone_2, _T("stone_2.jpg"));//��������1��ͼƬ
	loadimage(&img_stone_3, _T("stone_3.jpg"));//��������2��ͼƬ
	loadimage(&img_stone_4, _T("stone_4.jpg"));//��������3��ͼƬ
	loadimage(&img_stone_5, _T("stone_5.jpg"));//��������4��ͼƬ
	loadimage(&img_stone_6, _T("stone_6.jpg"));//��������5��ͼƬ
	loadimage(&img_stone_7, _T("stone_7.jpg"));//��������6��ͼƬ
	loadimage(&img_coal_1, _T("coal_1.jpg"));//��������ú
	loadimage(&img_coal_2, _T("coal_2.jpg"));//��������1ú
	loadimage(&img_coal_3, _T("coal_3.jpg"));//��������2,ú
	loadimage(&img_coal_4, _T("coal_4.jpg"));//��������3ú
	loadimage(&img_coal_5, _T("coal_5.jpg"));//��������4ú
	loadimage(&img_coal_0, _T("coal_0.jpg"));//��ȫ�����ú
	loadimage(&img_copper_1, _T("Copper_1.jpg"));//��������ͭ
	loadimage(&img_copper_2, _T("Copper_2.jpg"));//��������1ͭ
	loadimage(&img_copper_3, _T("Copper_3.jpg"));//��������2ͭ
	loadimage(&img_copper_4, _T("Copper_4.jpg"));//��������3ͭ
	loadimage(&img_copper_5, _T("Copper_5.jpg"));//��������4ͭ
	loadimage(&img_copper_6, _T("Copper_6.jpg"));//��������5ͭ
	loadimage(&img_copper_0, _T("Copper_0.jpg"));//��ȫ�����ͭ
	loadimage(&img_silver_1, _T("silver_1.jpg"));//����������
	loadimage(&img_silver_2, _T("silver_2.jpg"));//��������1��
	loadimage(&img_silver_3, _T("silver_3.jpg"));//��������2��
	loadimage(&img_silver_4, _T("silver_4.jpg"));//��������3��
	loadimage(&img_silver_5, _T("silver_5.jpg"));//��������4��
	loadimage(&img_silver_0, _T("silver_0.jpg"));//��ȫ�������
	loadimage(&img_shoes_1, _T("shoes_1.jpg"));//����������ͼƬ�ڰװ�
	loadimage(&img_shoes_2, _T("shoes_2.jpg"));//����������ͼƬ�ʰ�
	loadimage(&img_digleftperson_1, _T("digleftperson_1.jpg"));//���������ڵ�ͼƬ�ĺڰװ�
	loadimage(&img_digleftperson_2, _T("digleftperson_2.jpg"));//���������ڵ�ͼƬ�Ĳʰ�
	loadimage(&img_digrightperson_1, _T("digrightperson_1.jpg"));//���������ڵ�ͼƬ�ĺڰװ�
	loadimage(&img_digrightperson_2, _T("digrightperson_2.jpg"));//���������ڵ�ͼƬ�Ĳʰ�
	loadimage(&img_digdownperson_1, _T("digdownperson_1.jpg"));//���������ڵ�ͼƬ�ĺڰװ�
	loadimage(&img_digdownperson_2, _T("digdownperson_2.jpg"));//���������ڵ�ͼƬ�Ĳʰ�
	mciSendString(_T("open bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);//���뱳������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ����������

	scene = 0;//�����л�����
	shoes_a = 0;//���Ь���ٶ�
	exist_leftstone = 0;//��ʼʱ���û��ש�� exist_leftstone==0��ʾ���û��ש�� exist_leftstone==1��ʾ�����ש��
	exist_rightstone = 0;//��ʼʱ�ұ�û��ש�� exist_rightstone==0��ʾ���û��ש�� exist_leftrightstone==1��ʾ�����ש��
	exist_downstone = 0;//��ʼʱ�±�û��ש�� exist_downstone==0��ʾ���û��ש�� exist_downstone==1��ʾ�����ש��
	exist_flyleftstone = 0;
	exist_flyrightstone = 0;
	digleftbf = 0;//�ж��Ƿ�����ʼ��
	digrightbf = 0;//�ж��Ƿ����ҿ�ʼ��
	flyleftbf = 0;//�ж��Ƿ������
	flyrightbf = 0;//�ж��Ƿ����ҷ�

 /*��ÿ��ש����г�ʼ��*/
	int i, j, k;
	for (k = 0; k < 3; k++)
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				stone[k][i][j].center_x = -1000;
				stone[k][i][j].center_y = -1000;
				stone[k][i][j].left_x = -1000;
				stone[k][i][j].left_y = -1000;
				stone[k][i][j].right_x = -1000;
				stone[k][i][j].right_y = -1000;
				stone[k][i][j].top_x = -1000;
				stone[k][i][j].top_y = -1000;
				stone[k][i][j].bottom_x = -1000;
				stone[k][i][j].bottom_y = -1000;
				stone[k][i][j].status = -1000;
			}
	for (i = 7; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)//��һ�ص�ʯ��λ��
		{
			stone[1][i][j].center_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש�������x����
			stone[1][i][j].center_y = apper_1stone + stone_high / 2 + (i - 7) * stone_high;//��ʼ��ÿ��ש�������y����
			stone[1][i][j].left_x = j * stone_width;//��ʼ��ÿ��ש������x����
			stone[1][i][j].left_y = apper_1stone + stone_high / 2 + (i - 7) * stone_high;//��ʼ��ÿ��ש������y����
			stone[1][i][j].right_x = stone_width + j * stone_width;//��ʼ��ÿ��ש����Ҷ�x����
			stone[1][i][j].right_y = apper_1stone + stone_high / 2 + (i - 7) * stone_high;//��ʼ��ÿ��ש����Ҷ�y����
			stone[1][i][j].top_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש����϶�x����
			stone[1][i][j].top_y = apper_1stone + (i - 7) * stone_high;//��ʼ��ÿ��ש����϶�y����
			stone[1][i][j].bottom_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש����¶�x����
			stone[1][i][j].bottom_y = apper_1stone + stone_high + (i - 7) * stone_high;//��ʼ��ÿ��ש����¶�y����
			stone[1][i][j].status = 31;//ԭʼ״̬
		}

	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)//��һ�ص�ʯ��λ��
		{
			stone[2][i][j].center_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש�������x����
			stone[2][i][j].center_y = apper_2stone + stone_high / 2 + i * stone_high;//��ʼ��ÿ��ש�������y����
			stone[2][i][j].left_x = j * stone_width;//��ʼ��ÿ��ש������x����
			stone[2][i][j].left_y = apper_2stone + stone_high / 2 + i * stone_high;//��ʼ��ÿ��ש������y����
			stone[2][i][j].right_x = stone_width + j * stone_width;//��ʼ��ÿ��ש����Ҷ�x����
			stone[2][i][j].right_y = apper_2stone + stone_high / 2 + i * stone_high;//��ʼ��ÿ��ש����Ҷ�y����
			stone[2][i][j].top_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש����϶�x����
			stone[2][i][j].top_y = apper_2stone + i * stone_high;//��ʼ��ÿ��ש����϶�y����
			stone[2][i][j].bottom_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש����¶�x����
			stone[2][i][j].bottom_y = apper_2stone + stone_high + i * stone_high;//��ʼ��ÿ��ש����¶�y����
			stone[2][i][j].status = 31;//ԭʼ״̬
		}
	/*�ڵ�С�Ӹ���ʼλ��ֵ */
	person.center_x = width / 2;
	person.center_y = apper_1stone-person_high/2;
	/*�ƶ�������ֵ*/
	left_i = 0;
	right_i = 0;
	person.v = 0;
	/*������ʼ*/
	score = 0;
	BeginBatchDraw();
}
void show()
{
	int i, j, k;//ѭ������
	k = 0;
	if (scene == 0)//�л�����
	{
		putimage(0, 0, &img_bk);//��������ͼƬ
		FlushBatchDraw();
	}
	/* ���� 0��ʾ�� 1Ϊԭʼ 2����1 3����2 4����3 5����4 6����5 7����6*/
	/*ú�� 11��ʾԭʼ 12��ʾ����1 13��ʾ����2 14��ʾ����3 15��ʾ����4  16��ʾú
	ͭ��  21��ʾԭʼ  22��ʾ����1 23��ʾ����2 24��ʾ����3  25��ʾ����4 26��ʾ����5 27��ʾͭ��
	����   31��ʾԭʼ  32��ʾ����1 33��ʾ����2 34��ʾ����3 35��ʾ����4 36��ʾ����*/
	else if (scene == 1)//�л�������1
	{
		putimage(0, 0, &img_1);//������һ�ص�ͼ
		k = 1;
	}
	else if (scene == 2)
	{
		putimage(0, 0, &img_1);//������һ�ص�ͼ
		k = 2;
	}
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			/*ԭʼ����*/
			if (stone[k][i][j].status == 0)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_0);////��ȫ�����ͼƬ
			else if (stone[k][i][j].status == 1)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_1);//ש���ʼ��
			else if (stone[k][i][j].status == 2)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_2);////����1��ͼƬ
			else if (stone[k][i][j].status == 3)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_3);////����2��ͼƬ
			else if (stone[k][i][j].status == 4)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_4);////����3��ͼƬ
			else if (stone[k][i][j].status == 5)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_5);////����4��ͼƬ
			else if (stone[k][i][j].status == 6)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_6);////����5��ͼƬ
			else if (stone[k][i][j].status == 7)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_7);////����6��ͼƬ
																					/*ú��*/
			else if (stone[k][i][j].status == 11)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_1);//����ú��ͼƬ
			else if (stone[k][i][j].status == 12)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_2);//ú����1��ͼƬ
			else if (stone[k][i][j].status == 13)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_3);//ú����2��ͼƬ
			else if (stone[k][i][j].status == 14)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_4);//ú����3��ͼƬ
			else if (stone[k][i][j].status == 15)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_5);//ú����4��ͼƬ
			else if (stone[k][i][j].status == 16)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_0);//��ȫú�����ͼƬ
																				   /*ͭ��*/
			else if (stone[k][i][j].status == 21)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_1);//����ͭ��ͼƬ
			else if (stone[k][i][j].status == 22)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_2);//ͭ����1��ͼƬ
			else if (stone[k][i][j].status == 23)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_3);//ͭ����2��ͼƬ
			else if (stone[k][i][j].status == 24)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_4);//ͭ����3��ͼƬ
			else if (stone[k][i][j].status == 25)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_5);//ͭ����4��ͼƬ
			else if (stone[k][i][j].status == 26)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_6);//ͭ����5��ͼƬ
			else if (stone[k][i][j].status == 27)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_0);//ͭ
																					 /*����*/
			else if (stone[k][i][j].status == 31)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_1);//����ú��ͼƬ
			else if (stone[k][i][j].status == 32)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_2);//ú����1��ͼƬ
			else if (stone[k][i][j].status == 33)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_3);//ú����2��ͼƬ
			else if (stone[k][i][j].status == 34)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_4);//ú����3��ͼƬ
			else if (stone[k][i][j].status == 35)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_5);//ú����4��ͼƬ
			else if (stone[k][i][j].status == 36)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_0);//��ȫú�����ͼƬ
		}
	if (scene == -1)//�л��������̵�
	{
		putimage(0, 0, &img_shop);//��������ͼƬ
		FlushBatchDraw();
	}
	/*����������� ÿ��ֵ������������������� ��ǿ����������*/
	person.left_x = person.center_x - person_width / 2;
	person.left_y = person.center_y;
	person.right_x = person.center_x + person_width / 2;
	person.right_y = person.center_y;
	person.top_x = person.center_x;
	person.top_y = person.center_y - person_high / 2;
	person.bottom_x = person.center_x;
	person.bottom_y = person.center_y + person_high / 2;
}
void updatewithoutinput()
{
	int i, j, k;
	/*�ж������Ƿ�վ��ש����*/
	G = 1;//�������ٶȳ�ֵ
	if (scene == 1)
		k = 1;
	else if (scene == 2)
		k = 2;
	else
		k = 1;
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[k][i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//ͨ���ж�������ש��֮�����������
				person.center_x <= stone[k][i][j].center_x + stone_width / 2 + 1 &&
				person.center_x >= stone[k][i][j].center_x - stone_width / 2 - 1 &&//�ж�������ש��֮�������֮��Ĺ�ϵ
				stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36
				)//�ж��Ƿ����ש���ϣ�ͨ���ж�������ש��֮�����������,�ж�������ש��֮�������֮��Ĺ�ϵ,ש���״̬��
			{
				exist_downstone = 1;//�¶˴���ש��
				G = 0;//�������ٶȱ�Ϊ0
				person.v = 0;//�ȵ�ש�������ﲻ����
				person.center_y = stone[k][i][j].center_y - person_high / 2 - stone_high / 2;//����������ש��ļ��
				break;
			}
		}
	/*�ж��������ʱ�Ƿ��Ϸ���ש��*/
	if (shoes_a == -2)//����������ʱ�����Ϸ�ͷ������ש�飬�������Ϸ�
	{
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				if (person.center_y - stone[k][i][j].center_y <= stone_high - person_high / 2 + stone_high / 2 &&
					person.center_y - stone[k][i][j].center_y >= (stone_high - person_high / 2 + stone_high / 2) / 2 &&//ͨ���ж�������ש��֮�����������
					person.center_x <= stone[k][i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
					person.center_x >= stone[k][i][j].center_x - person_width / 2 - stone_width / 2 + 10 &&//�ж�������ש��֮�������֮��Ĺ�ϵ
					stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
				{
					person.v = 0;//�ٶ�Ϊ��
					shoes_a = -1;//���������ٶȵ��������������Ϊ�㣬�ô���1.����ʱͼƬ����Ϊ��������ͼƬ 2.���ֺ�������£�
					break;
				}
			}
	}
	/*�ж��Ƿ���������*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[k][i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//ͨ���ж�������ש��֮�����������
				person.center_x <= stone[k][i][j].center_x + stone_width / 2 &&
				person.center_x >= stone[k][i][j].center_x - stone_width / 2  //�ж�������ש��֮�������֮��Ĺ�ϵ
				)//�ж��Ƿ����ש���ϣ�ͨ���ж�������ש��֮�����������,�ж�������ש��֮�������֮��Ĺ�ϵ,ש���״̬��
			{
				if (digbf == 1 && stone[k][i][j].status != 0 && exist_downstone == 1 && stone[k][i][j].status != 16
					&& stone[k][i][j].status != 27 && stone[k][i][j].status != 36)//�����������·���ש��
				{
					person.center_x = stone[k][i][j].center_x;//����������ש��d�ĺ��������
					static int speed_2 = 0;//�������������ڵ��ٶ�
					if (speed_2 < 70)
						speed_2++;
					else if (speed_2 == 70)
					{
						stone[k][i][j].status++;//״̬��1
						speed_2 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//ש����ʧ
				}
			}
		}
	/*�ж���������Ƿ���ש��*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.center_x - stone[k][i][j].center_x <= stone_width / 2 + person_width / 2 &&
				person.center_x - stone[k][i][j].center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[k][i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
			{
				exist_leftstone = 1;//��˴���ש��
				if (digleftbf == 1)//��ʼ������
				{
					person.center_x = stone[k][i][j].center_x + stone_width / 2 + person_width / 2;//����ڹ�λ
					static int speed_3 = 0;//�������������ڵ��ٶ�
					if (speed_3 < 70)
						speed_3++;
					else if (speed_3 == 70)
					{
						stone[k][i][j].status++;//״̬��1
						speed_3 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//ש����ʧ
				}
			}
		}
	/*�ж������ұ��Ƿ���ש��*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_x - person.center_x <= stone_width / 2 + person_width / 2 &&
				stone[k][i][j].center_x - person.center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[k][i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
			{
				exist_rightstone = 1;//�Ҷ˴���ש��
				if (digrightbf == 1)//��ʼ������
				{
					person.center_x = stone[k][i][j].center_x - stone_width / 2 - person_width / 2;//�ұ��ڹ�λ
					static int speed_3 = 0;//�������������ڵ��ٶ�
					if (speed_3 < 70)
						speed_3++;
					else if (speed_3 == 70)
					{
						stone[k][i][j].status++;//״̬��1
						speed_3 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//ש����ʧ
				}
			}
		}
	/*�ж��������ʱ����Ƿ���ש��*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.left_x == stone[k][i][j].right_x && person.left_y - stone[k][i][j].right_y <= person_high / 2 + stone_high / 2
				&& person.left_y - stone[k][i][j].right_y >= -person_high / 2 - stone_high / 2
				&& stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36 && shoes_a < 0)
				exist_flyleftstone = 1;
		}
	/*�ж��������ʱ�ұ��Ƿ���ש��*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.right_x == stone[k][i][j].left_x && person.right_y - stone[k][i][j].left_y <= person_high / 2 + stone_high / 2
				&& person.right_y - stone[k][i][j].left_y >= -person_high / 2 - stone_high / 2
				&& stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36 && shoes_a < 0)
				exist_flyrightstone = 1;
		}
	/*�����������*/
	static int speed_1 = 0;//��������������ٶ�
	if (speed_1 < 10)
		speed_1++;
	else if (speed_1 == 10)
	{
		person.v = person.v + G + shoes_a;//�ٶȵı仯��
		if (person.v >= 25)//�����趨
			person.v = 25;
		if (person.v <= -12)//�����趨
			person.v = -12;
		person.center_y = person.center_y + person.v;//������ֱ����λ�ñ仯
		speed_1 = 0;
	}
	/*ʰȡ��Ʒ*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].status == 16 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10)//ʰȡú��
			{
				stone[k][i][j].status = 0;
				score = score + 10;//һ��ú��10��
			}
			if (stone[k][i][j].status == 27 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10)//ʰȡͭ��
			{
				stone[k][i][j].status = 0;
				score = score + 20;//һ��ͭ��20��
			}
			if (stone[k][i][j].status == 36 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10)//ʰȡ����
			{
				stone[k][i][j].status = 0;
				score = score + 50;//һ������50��
			}
		}
	/*��ʾ����*/
	TCHAR s[5];
	_stprintf(s, _T("%d"), score);
	outtextxy(100, 15, s);
	settextcolor(WHITE);
	/*��Ϸ���Ʊ߽�*/
	if (scene == 1)
	{
		if (person.left_x < 0)//������߽�
			person.center_x = person_width / 2;
		else if (person.right_x > 900)//�����ұ߽�
			person.center_x = 900 - person_width / 2;
		else if (person.top_y < 0)//�����ϱ߽�
			person.center_y = person_high / 2;
	}
	/*�ؿ���Ծ*/
	if (scene == 1 && person.bottom_y > high)//��һ�ص��ڶ���
	{
		scene = 2;
		person.center_y = -person_width / 2;
	}
	else if (scene == 2 && person.bottom_y < 0)//�ӵڶ��ط��ص�һ��
	{
		scene = 1;
		person.center_y = high - person_high;
	}
}
void status_change()//״̬�ı����ͼƬ
{
	int i, j;
	if (scene != 0 && scene != -1)
	{
		/*�����ﲻ��ʱת������ */
		if (shoes_a == 0 && digbf == 0 && digleftbf == 3 && digrightbf == 3)//��ֵ��Ϊ��ʼֵʱ��ʱ����ʾ����ͼƬ
		{
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//��������ڰװ�
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//��������ʰ�
			FlushBatchDraw();
			Sleep(1);
		}
		/*����wʱ�������Ϸ�*/
		else if (shoes_a < 0 && flyleftbf == 0 && flyrightbf == 0)
		{
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//�������Ϸɺڰװ�
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//�������Ϸɲʰ�
			FlushBatchDraw();
			Sleep(1);
		}
		/*����������� ��wa*/
		else if (shoes_a < 0 && flyleftbf == 1)
		{
			if (exist_flyleftstone == 0)
				person.center_x = person.center_x - 1;//�������������x����
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//�������Ϸɺڰװ�
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//�������Ϸɲʰ�
			FlushBatchDraw();
			Sleep(1);
		}
		/*�������ҷ��� ��wd*/
		else if (shoes_a < 0 && flyrightbf == 1)
		{
			if (exist_flyrightstone == 0)
				person.center_x = person.center_x + 1;//�������������x����
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//�������Ϸɺڰװ�
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//�������Ϸɲʰ�
			FlushBatchDraw();
			Sleep(1);
		}
		/*����ת��Ϊ�����ڵ�ͼƬ*/
		else if (digbf == 1)
		{
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_1, NOTSRCERASE);//���������ںڰ�
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_2, SRCINVERT);//���������ڲ�
			FlushBatchDraw();
			Sleep(1);
		}
		/*�������*/
		else if (digleftbf == 0)
		{
			person.center_x = person.center_x - 15;//�������������x����
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, left_i * person_width, 0, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, left_i * person_width, 0, SRCINVERT);//���������ߵĲ�ͼ
			FlushBatchDraw();
			left_i++;
			Sleep(100);
			if (left_i == 3)
				left_i = 0;
		}
		/*��������*/
		else if (digleftbf == 1)
		{
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_1, NOTSRCERASE);//���������ںڰ�
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_2, SRCINVERT);//���������ڲ�
			FlushBatchDraw();
			Sleep(1);
		}
		/*�ұ�����*/
		else if (digrightbf == 0)
		{
			person.center_x = person.center_x + 15;//�������������x����
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, right_i * person_width, person_high, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, right_i * person_width, person_high, SRCINVERT);//���������ߵĲ�ͼ
			FlushBatchDraw();
			right_i++;//������ͼ
			Sleep(100);
			if (right_i == 3)
				right_i = 0;
		}
		/*��������*/
		else if (digrightbf == 1)
		{
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_1, NOTSRCERASE);//���������ںڰ�
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_2, SRCINVERT);//���������ڲ�
			FlushBatchDraw();
			Sleep(1);
		}
	}
	/*�ع�ԭֵ���� �·����Ʋ��ֿ��Ըı�ֵ*/
	shoes_a = 0;//�����ٶȹ�Ϊԭֵ����w�ı䣩
	digbf = 0;//�����ڻع�ԭֵ����s�ı䣩
	digleftbf = 3;//�����ڻع�ԭֵ����a�ı䣩
	digrightbf = 3;//�����ڻع�ԭֵ����d�ı䣩
	flyleftbf = 0;//����ɻع�ԭֵ
	flyrightbf = 0;//���ҷɻع�ԭֵ
}
void updatewithinput()
{
	/*����������ʱ����������������롯������Ϸ*/
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONUP && scene == 0)
		{
			if (m.x <= 563 && m.x >= 316 && m.y <= 602 && m.y >= 570)//������Χ�ж�
			{
				scene = 1;//��תΪ��һ��
			}
		}
	}
	if (scene == 1 || scene == 2)//��һ��
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 0 && exist_downstone == 1)//�������a���·���ʯ�飬���ƶ�
		{
			digleftbf = 0;//��ʾ������
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 1)//�������a������
		{
			digleftbf = 1;//��ʾ����
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 0 && exist_downstone == 0)//�������a���·�ûʯ�飬����ƶ�
		{
			flyleftbf = 1;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 0 && exist_downstone == 1)//�������d���·���ʯ�飬���ƶ�
		{
			digrightbf = 0;//��ʾ������
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 1)//�������d������
		{
			digrightbf = 1;//��ʾ����
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 0 && exist_downstone == 0)//�������d���·�ûʯ�飬���ƶ�
		{
			flyrightbf = 1;
		}
		if (GetAsyncKeyState(0x57) & 0x8000)//��w	
		{
			shoes_a = -2;
		}
		if (GetAsyncKeyState(0x53) & 0x8000 && exist_downstone == 1)//��s
		{
			digbf = 1;//��ʾ������
		}
		if (GetAsyncKeyState(0x20) & 0x8000 && person.bottom_y == apper_1stone && person.center_x<570 && person.center_x>500)//���ո�
		{
			scene = -1;//�����̵�
		}
	}
	if (scene == -1)
	{
		char input;
		if (kbhit())
		{
			input = getch();
			if (input == 'q')
				scene = 1;//�˳��̵�
		}
	}
	/*�ع�ԭֵ���� �ع������ƶ��жϵ�ֵ*/
	exist_leftstone = 0;
	exist_rightstone = 0;
	exist_downstone = 0;
	exist_flyleftstone = 0;
	exist_flyrightstone = 0;
}
void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

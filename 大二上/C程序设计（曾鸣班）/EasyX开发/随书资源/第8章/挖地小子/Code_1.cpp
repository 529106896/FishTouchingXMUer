#include<graphics.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

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
#define shoesperson_high 82//�����ڵ�С�ӷ���ʱ�ĸ߶�
#define shoesperson_width 64//�����ڵ�С�ӷ���ʱ�Ŀ��
#define digdownperson_high 80//�����ڵ�С��������ʱ�ĸ߶�
#define digdownperson_width 64//�����ڵ�С��������ʱ�Ŀ��
#define digleftperson_high 78//�����ڵ�С��������ʱ�ĸ߶�
#define digleftperson_width 64//�����ڵ�С��������ʱ�Ŀ��
#define digrightperson_high 78//�����ڵ�С��������ʱ�ĸ߶�
#define digrightperson_width 64//�����ڵ�С��������ʱ�Ŀ��
#define num_1_stonewidth 14//��һ���к���ʯ�����
#define num_1_stonehigh 4//��һ��������ʯ��ĸ���
#define stone_high 64//ש��ĸ�
#define stone_width 64//ש��Ŀ�
#define apper_1stone 414//��һ���п�ʼ����ש���yλ��


IMAGE img_bk;//���屳��ͼƬ
IMAGE img_1;//�����һ�ص�ͼƬ
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7;//����ʯ���ͼƬ
IMAGE img_person_0, img_person_00;//�����ڵ�С�ӵ�����ͼƬ 0��ʾ�ڰװ� 00��ʾ�ʰ�
IMAGE img_person_1, img_person_2;//�����ڵ�С�������ߵ�ͼƬ 1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_shoes_1, img_shoes_2;//������ЬͼƬ 1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digleftperson_1, img_digleftperson_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digrightperson_1, img_digrightperson_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
IMAGE img_digdownperson_1, img_digdownperson_2;//�����ڵ�С�������ڵ���Ƭ  1��ʾ�ڰװ� 2��ʾ�ʰ�
MOUSEMSG m;//����һ��������

typedef struct thing//����ṹ��������
{
	int left_x;//���x����
	int left_y;//���y����
	int right_x;//�Ҷ�x����
	int right_y;//�Ҷ�y����
	int top_x;//�϶�x����
	int top_y;//�϶�y����
	int bottom_x;//�ײ�x����
	int bottom_y;//�ײ�y����
	int center_x;//����x����
	int center_y;//����y����
	int v;//�ڵ�С����ֱ�����ٶ�
}thing;
thing person;//������

struct stone//����ṹ����������
{
	int left_x;//���x����
	int left_y;//���y����
	int right_x;//�Ҷ�x����
	int right_y;//�Ҷ�y����
	int top_x;//�϶�x����
	int top_y;//�϶�y����
	int bottom_x;//�ײ�x����
	int bottom_y;//�ײ�y����
	int center_x;//����x����
	int center_y;//����y����
	int status;//��ʾש���״̬ 0��ʾ�� 1Ϊԭʼ 2����1 3����2 4����3 5����4 6����5 7����6
}stone[num_1_stonehigh][num_1_stonewidth];//����Ľṹ��һ��56��ש��

int scene;//�����л�����
int left_i;//��¼�����ƶ���ͼƬ
int right_i;//��¼�����ƶ���ͼƬ
int G;//�������ٶ�
int shoes_a;//���Ь���ٶ�
int count_1;//���ڼ�¼����ʱ��һ����Ƭ,�Ӷ�ѡ������ͼƬ��СΪ����,��ʼֵΪ����ͼ������Ϊ��¼���У�count_1==1��ʾ�������� count_1==2��ʾ����������
int count_2;//���ڼ�¼������ʱ��һ����Ƭ,�Ӷ�ѡ������ͼƬ��СΪ����,��ʼֵΪ����ͼ������Ϊ��¼����w�ڣ�count_2==1��ʾ�������� count_2==2��ʾ����������
int count_3;//���ڼ�¼������ʱ��һ����Ƭ,�Ӷ�ѡ������ͼƬ��СΪ����,��ʼֵΪ����ͼ������Ϊ��¼�����ڣ�count_3==1��ʾ�������� count_3==2��ʾ����������
int count_4;//���ڼ�¼������ʱ��һ����Ƭ,�Ӷ�ѡ������ͼƬ��СΪ����,��ʼֵΪ����ͼ������Ϊ��¼�����ڣ�count_4==1��ʾ�������� count_4==2��ʾ����������
int digbf;//���ڼ�¼�ж��Ƿ��������� 0��ʾû�� 1��ʾ��
int digleftbf;//���ڼ�¼�ж��Ƿ��������� 0��ʾû�� 1��ʾ��
int digrightbf;//���ڼ�¼�ж��Ƿ��������� 0��ʾû�� 1��ʾ��
int exist_leftstone;//���ڼ�¼�ж��Ƿ������ש�� 0��ʾû�� 1��ʾ��
int exist_rightstone;//���ڼ�¼�ж��Ƿ��Ҷ���ש�� 0��ʾû�� 1��ʾ��
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
	count_1 = 1;//��ʼʱ�������� count_1==1��ʾ�������� count_1==2��ʾ�������Ϸ�
	count_2 = 1;//��ʼʱ�������� count_2==1��ʾ�������� count_2==2��ʾ����������
	count_3 = 1;//��ʼʱ�������� count_3==1��ʾ�������� count_3==2��ʾ����������
	count_4 = 1;//��ʼʱ�������� count_3==1��ʾ�������� count_3==2��ʾ����������
	exist_leftstone = 0;//��ʼʱ���û��ש�� exist_leftstone==0��ʾ���û��ש�� exist_leftstone==1��ʾ�����ש��
	exist_rightstone = 0;//��ʼʱ�ұ�û��ש�� exist_leftstone==0��ʾ���û��ש�� exist_leftstone==1��ʾ�����ש��
	digleftbf = 0;//�ж��Ƿ�����ʼ��
	digrightbf = 0;//�ж��Ƿ����ҿ�ʼ��
/*��ÿ��ש����г�ʼ��*/
	int i, j;
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			stone[i][j].center_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש�������x����
			stone[i][j].center_y = apper_1stone + stone_high / 2 + i * stone_high;//��ʼ��ÿ��ש�������y����
			stone[i][j].left_x = j * stone_width;//��ʼ��ÿ��ש������x����
			stone[i][j].left_y = apper_1stone + stone_high / 2 + i * stone_high;//��ʼ��ÿ��ש������y����
			stone[i][j].right_x = stone_width + j * stone_width;//��ʼ��ÿ��ש����Ҷ�x����
			stone[i][j].right_y = apper_1stone + stone_high / 2 + i * stone_high;//��ʼ��ÿ��ש����Ҷ�y����
			stone[i][j].top_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש����϶�x����
			stone[i][j].top_y = apper_1stone + i * stone_high;//��ʼ��ÿ��ש����϶�y����
			stone[i][j].bottom_x = stone_width / 2 + j * stone_width;//��ʼ��ÿ��ש����¶�x����
			stone[i][j].bottom_y = apper_1stone + stone_high + i * stone_high;//��ʼ��ÿ��ש����¶�y����
			stone[i][j].status = 1;//ԭʼ״̬
		}
	/*�ڵ�С�Ӹ���ʼλ��ֵ */
	person.center_x = width / 2;
	person.center_y = apper_1stone - person_high / 2;

	/*�ƶ�������ֵ*/
	left_i = 0;
	right_i = 0;
	person.v = 0;
	BeginBatchDraw();
}
void show()
{
	int i, j;//ѭ������
	if (scene == 0)//�л�����
	{
		putimage(0, 0, &img_bk);//��������ͼƬ
		FlushBatchDraw();
	}

	else if (scene == 1)//�л�������1
	{
		putimage(0, 0, &img_1);//������һ�ص�ͼƬ

  /*0��ʾ�� 1Ϊԭʼ 2����1 3����2 4����3 5����4 6����5 7����6*/
		for (i = 0; i < num_1_stonehigh; i++)
			for (j = 0; j < num_1_stonewidth; j++)
			{
				if (stone[i][j].status == 1)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_1);//ש���ʼ��
				else if (stone[i][j].status == 2)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_2);////����1��ͼƬ
				else if (stone[i][j].status == 3)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_3);////����2��ͼƬ
				else if (stone[i][j].status == 4)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_4);////����3��ͼƬ
				else if (stone[i][j].status == 5)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_5);////����4��ͼƬ
				else if (stone[i][j].status == 6)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_6);////����5��ͼƬ
				else if (stone[i][j].status == 7)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_7);////����6��ͼƬ
				else if (stone[i][j].status == 0)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_0);////��ȫ�����ͼƬ
			}

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
	int i, j;
	/*�ж������Ƿ�վ��ש����*/
	G = 1;//�������ٶȳ�ֵ
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (stone[i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//ͨ���ж�������ש��֮�����������
				person.center_x <= stone[i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
				person.center_x >= stone[i][j].center_x - person_width / 2 - stone_width / 2 + 10 &&//�ж�������ש��֮�������֮��Ĺ�ϵ
				stone[i][j].status != 0)//�ж��Ƿ����ש���ϣ�ͨ���ж�������ש��֮�����������,�ж�������ש��֮�������֮��Ĺ�ϵ,ש���״̬��
			{
				G = 0;//�������ٶȱ�Ϊ0
				person.v = 0;//�ȵ�ש�������ﲻ����
				person.center_y = stone[i][j].center_y - person_high / 2 - stone_high / 2;//����������ש��ļ��
				break;
			}

		}
	/*�ж��������ʱ�Ƿ��Ϸ���ש��*/
	if (shoes_a == -2)//����������ʱ�����Ϸ�ͷ������ש�飬�������Ϸ�
	{
		for (i = 0; i < num_1_stonehigh; i++)
			for (j = 0; j < num_1_stonewidth; j++)
			{
				if (person.center_y - stone[i][j].center_y <= stone_high - person_high / 2 + stone_high / 2 &&
					person.center_y - stone[i][j].center_y >= (stone_high - person_high / 2 + stone_high / 2) / 2 &&//ͨ���ж�������ש��֮�����������
					person.center_x <= stone[i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
					person.center_x >= stone[i][j].center_x - person_width / 2 - stone_width / 2 + 10 &&//�ж�������ש��֮�������֮��Ĺ�ϵ
					stone[i][j].status != 0)
				{
					person.v = 0;//�ٶ�Ϊ��
					shoes_a = -1;//���������ٶȵ��������������Ϊ�㣬�ô���1.����ʱͼƬ����Ϊ��������ͼƬ 2.���ֺ�������£�
					break;
				}
			}
	}
	/*�ж��Ƿ���������*/
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (stone[i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//ͨ���ж�������ש��֮�����������
				person.center_x <= stone[i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
				person.center_x >= stone[i][j].center_x - person_width / 2 - stone_width / 2 + 10 //�ж�������ש��֮�������֮��Ĺ�ϵ
				 )//�ж��Ƿ����ש���ϣ�ͨ���ж�������ש��֮�����������,�ж�������ש��֮�������֮��Ĺ�ϵ,ש���״̬��
			{
				if (digbf == 1 && stone[i][j].status != 0)//�����������·���ש��
				{
					person.center_x = stone[i][j].center_x;//����������ש��d�ĺ��������
					static int speed_2 = 0;//�������������ڵ��ٶ�
					if (speed_2 < 100)
						speed_2++;
					else if (speed_2 == 100)
					{
						stone[i][j].status++;//״̬��1
						speed_2 = 0;
					}
					if (stone[i][j].status == 8)
						stone[i][j].status = 0;//ש����ʧ
				}
			}
		}

	/*�ж���������Ƿ���ש��*/
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (person.center_x - stone[i][j].center_x <= stone_width / 2 + person_width / 2 &&
				person.center_x - stone[i][j].center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[i][j].status != 0)
			{
				exist_leftstone = 1;//��˴���ש��
				if (digleftbf == 1)//��ʼ������
				{
					person.center_x = stone[i][j].center_x + stone_width / 2 + person_width / 2;//����ڹ�λ
					static int speed_3 = 0;//�������������ڵ��ٶ�
					if (speed_3 < 100)
						speed_3++;
					else if (speed_3 == 100)
					{
						stone[i][j].status++;//״̬��1
						speed_3 = 0;
					}
					if (stone[i][j].status == 8)
						stone[i][j].status = 0;//ש����ʧ
				}
			}
			
		}
	/*�ж������ұ��Ƿ���ש��*/
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (stone[i][j].center_x - person.center_x <= stone_width / 2 + person_width / 2 &&
				stone[i][j].center_x - person.center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[i][j].status != 0)
			{
				exist_rightstone = 1;//��˴���ש��
				if (digrightbf == 1)//��ʼ������
				{
					person.center_x = stone[i][j].center_x - stone_width / 2 - person_width / 2;//����ڹ�λ
					static int speed_3 = 0;//�������������ڵ��ٶ�
					if (speed_3 < 100)
						speed_3++;
					else if (speed_3 == 100)
					{
						stone[i][j].status++;//״̬��1
						speed_3 = 0;
					}
					if (stone[i][j].status == 8)
						stone[i][j].status = 0;//ש����ʧ
				}
			}
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
		if (person.v <= -15)//�����趨
			person.v = -15;
		person.center_y = person.center_y + person.v;//������ֱ����λ�ñ仯
		speed_1 = 0;
	}
}
void status_change()
{
	int i, j;
	/*�����ﲻ��ʱת������ */
	if (scene == 1)
	{
		if (shoes_a == 0 && digbf == 0 && digleftbf == 3 && digrightbf == 3)//digbf==0���������ڵ�ʱ����ʾ����ͼƬ
		{
			if (count_1 == 1)//�����ж�����ʲô��С
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//����һ��ͼƬ�����治��ʱ���ԭ����
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//���뱳��������������ɫ
			}
			else if (count_1 == 2)//���ڴӷ���״̬ת��Ϊ����
			{
				clearrectangle(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, person.center_x - shoesperson_width / 2 + shoesperson_width, person.center_y - shoesperson_high / 2 + shoesperson_high);//��������״̬��ͼƬ
				putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, shoesperson_width + 1, shoesperson_high + 1, &img_1, person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2);//���ϱ���ͼ
			}
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//��������ڰװ�
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//��������ʰ�
			count_1 = 1;//��countΪ1ʱΪ����ͼ��
			FlushBatchDraw();
			Sleep(1);
		}
		/*����wʱ�������Ϸ�*/
		else if (shoes_a < 0)
		{
			if (count_1 == 1)
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//���ڴ�����ͼ��ת��Ϊ����ͼ��
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//����������ɫ
			}
			else if (count_1 == 2)
			{
				clearrectangle(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, person.center_x - shoesperson_width / 2 + shoesperson_width, person.center_y - shoesperson_high / 2 + shoesperson_high);//���ַ���״̬ʱ�������ϴε���
				putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, shoesperson_width + 1, shoesperson_high + 1, &img_1, person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2);//�����µ�ͼ��
			}
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//��������ڰ�
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//���������
			count_1 = 2;//��countΪ2ʱΪ����ͼ��
			FlushBatchDraw();
			Sleep(1);
		}



		/*û����ʱ��������*/
		if (digbf == 0 && shoes_a == 0 && digleftbf == 3 && digrightbf == 3)//shoes==0�����������Ϸɵ�ʱ����ʾ����ͼƬ
		{
			if (count_2 == 1)
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//����һ��ͼƬ�����治��ʱ���ԭ����
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//���뱳��������������ɫ
			}
			else if (count_2 == 2)//���ڴ�������״̬ת��Ϊ����
			{
				clearrectangle(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, person.center_x - digdownperson_width / 2 + digdownperson_width, person.center_y - digdownperson_high / 2 + digdownperson_high);//��������״̬��ͼƬ
				putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, digdownperson_width + 1, digdownperson_high + 1, &img_1, person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2);//���ϱ���ͼ
			}
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//��������ڰװ�
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//��������ʰ�
			count_2 = 1;//��countΪ1ʱΪ����ͼ��
			FlushBatchDraw();
			Sleep(1);
		}
		/*����ת��Ϊ�����ڵ�ͼƬ*/
		else if (digbf == 1)
		{
			if (count_2 == 1)
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//���ڴ�����ͼ��ת��Ϊ������ͼ��
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//����������ɫ
			}
			else if (count_2 == 2)
			{
				clearrectangle(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, person.center_x - digdownperson_width / 2 + digdownperson_width, person.center_y - digdownperson_high / 2 + digdownperson_high);//����������״̬ʱ�������ϴε���
				putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, digdownperson_width + 1, digdownperson_high + 1, &img_1, person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2);//�����µ�ͼ��
			}
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_1, NOTSRCERASE);//��������ڰ�
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_2, SRCINVERT);//���������
			count_2 = 2;//��countΪ2ʱΪ������ͼ��
			FlushBatchDraw();
			Sleep(1);
		}

	}
	/*����������������*/
	if (digleftbf == 0 && scene==1)
	{
		if (count_3 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//����һ��ͼƬ�����治��ʱ���ԭ����
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//���뱳��������������ɫ
		}
		else if (count_3 == 2)//���ڴ�������ת��Ϊ������
		{
			clearrectangle(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, person.center_x - digleftperson_width / 2 + digleftperson_width, person.center_y - digleftperson_high / 2 + digleftperson_high);//��������״̬��ͼƬ
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, digleftperson_width + 1, digleftperson_high + 1, &img_1, person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2);//���ϱ���ͼ
		}
		left_i++;
		person.center_x = person.center_x - 15;//�������������x����
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, left_i * person_width, 0, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, left_i * person_width, 0, SRCINVERT);//���������ߵĲ�ͼ
		FlushBatchDraw();
		count_3 = 1;
		Sleep(100);
		if (left_i == 3)
			left_i = 0;
	}
	else if (digleftbf == 1)
	{
		if (count_3 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//���ڴ�����ͼ��ת��Ϊ������ͼ��
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//����������ɫ
		}
		else if (count_3 == 2)
		{
			clearrectangle(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, person.center_x - digleftperson_width / 2 + digleftperson_width, person.center_y - digleftperson_high / 2 + digleftperson_high);//��������״̬��ͼƬ
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, digleftperson_width + 1, digleftperson_high + 1, &img_1, person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2);//���ϱ���ͼ
		}
		putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_1, NOTSRCERASE);//��������ڰ�
		putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_2, SRCINVERT);//���������
		count_3 = 2;//��countΪ2ʱΪ������ͼ��
		FlushBatchDraw();
		Sleep(1);
	}


	/*�ұ��������ұ�����*/
	if (digrightbf == 0 && scene == 1)
	{
		if (count_4 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//����һ��ͼƬ�����治��ʱ���ԭ����
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//���뱳��������������ɫ
		}
		else if (count_4 == 2)//���ڴ�������ת��Ϊ������
		{
			clearrectangle(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, person.center_x - digrightperson_width / 2 + digrightperson_width, person.center_y - digrightperson_high / 2 + digrightperson_high);//��������״̬��ͼƬ
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, digrightperson_width + 1, digrightperson_high + 1, &img_1, person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2);//���ϱ���ͼ
		}
		right_i++;//������ͼ
		person.center_x = person.center_x + 15;//�������������x����
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, right_i * person_width, person_high, NOTSRCERASE);//���������ߵĺڰ�ͼƬ
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, right_i * person_width, person_high, SRCINVERT);//���������ߵĲ�ͼ
		FlushBatchDraw();
		count_4 = 1;
		Sleep(100);
		if (right_i == 3)
			right_i = 0;
	}
	else if (digrightbf == 1)
	{
		if (count_4 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//���ڴ�����ͼ��ת��Ϊ������ͼ��
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//����������ɫ
		}
		else if (count_4 == 2)
		{
			clearrectangle(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, person.center_x - digrightperson_width / 2 + digrightperson_width, person.center_y - digrightperson_high / 2 + digrightperson_high);//��������״̬��ͼƬ
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, digrightperson_width + 1, digrightperson_high + 1, &img_1, person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2);//���ϱ���ͼ
		}
		putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_1, NOTSRCERASE);//��������ڰ�
		putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_2, SRCINVERT);//���������
		count_4 = 2;//��countΪ2ʱΪ������ͼ��
		FlushBatchDraw();
		Sleep(1);
	}
	/*�ع�ԭֵ����*/
	shoes_a = 0;//�����ٶȹ�Ϊԭֵ����w�ı䣩
	digbf = 0;//�����ڻع�ԭֵ����s�ı䣩
	digleftbf = 3;//�����ڻع�ԭֵ����a�ı䣩
	digrightbf = 3;//�����ڻع�ԭֵ����d�ı䣩
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

	if (scene == 1)//��һ��
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 0)//�������a�����ƶ�
		{
			digleftbf = 0;//��ʾ������
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 1)//�������a�����ƶ�
		{
			digleftbf = 1;//��ʾ����
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 0)//d
		{
			digrightbf = 0;//��ʾ������
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 1)//d
		{
			digrightbf = 1;//��ʾ����
		}
		if (GetAsyncKeyState(0x57) & 0x8000)//��w	
		{
			shoes_a = -2;
		}
		if (GetAsyncKeyState(0x53) & 0x8000)//��s
		{
			digbf = 1;//��ʾ������
		}
	}
	/*�ع�ԭֵ���� �ع������ƶ��жϵ�ֵ*/
	exist_leftstone = 0;
	exist_rightstone = 0;
}


void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

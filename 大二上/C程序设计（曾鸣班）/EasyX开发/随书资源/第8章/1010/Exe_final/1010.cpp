#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")
#define width 400
#define high 650//���廭����С

//����ȫ�ֱ���

int diamonds[width][high] = { 0 };//���������������Ķ�ά����

int step_r, step, step1;//����߳�һ�뼰�߳�

int i, j;//ѭ������

int t;//�����жϱ���
int rt;//�ص�����λ�õ��жϱ���
int isselect1, isselect2;//ѡ���жϱ���
int t1, t2;//�ж��Ƿ��������������

int score;
char scoreString[10];//������ʾ
TCHAR scoreText[10];   //��vs��ʱȡ�����ע��

int kinds;

MOUSEMSG msg;//�����Ϣ
IMAGE img_bk;	//������Ϸ����
IMAGE img_bg;	// �����ʼ���汳��


struct diamond
{
	int x;
	int y;
};

struct center
{
	int x;
	int y;
};

diamond d[3];
center c[2];

void back1()//ʹ�������Ļص����ַ��������
{
	d[1].x = c[0].x;
	d[1].y = c[0].y;
}

void back2()
{
	d[2].x = c[1].x;
	d[2].y = c[1].y;
}

void mouse1()
{
	d[1].x = msg.x;
	d[1].y = msg.y;
}

void mouse2()
{
	d[2].x = msg.x;
	d[2].y = msg.y;
}

void judge()//�ж�������ķ������ͣ���ʹ�������������Ӧ
{
	for (i = 1; i < 3; i++)
	{
		if (diamonds[d[i].x][d[i].y] == 3)
		{
			diamonds[d[i].x - step - 2][d[i].y] = 3;
			diamonds[d[i].x + step + 2][d[i].y] = 3;
		}
		if (diamonds[d[i].x][d[i].y] == 4)
		{
			diamonds[d[i].x][d[i].y - step - 2] = 4;
			diamonds[d[i].x][d[i].y + step + 2] = 4;
		}
		if (diamonds[d[i].x][d[i].y] == 5)
		{
			diamonds[d[i].x][d[i].y - step - 2] = 5;
		}
		if (diamonds[d[i].x][d[i].y] == 6)
		{
			diamonds[d[i].x - step - 2][d[i].y] = 6;
		}
		if (diamonds[d[i].x][d[i].y] == 7)
		{
			diamonds[d[i].x - step - 2][d[i].y] = 7;
			diamonds[d[i].x][d[i].y - step - 2] = 7;
		}
		if (diamonds[d[i].x][d[i].y] == 8)
		{
			diamonds[d[i].x - step - 2][d[i].y] = 8;
			diamonds[d[i].x][d[i].y + step + 2] = 8;
		}
		if (diamonds[d[i].x][d[i].y] == 9)
		{
			diamonds[d[i].x + step + 2][d[i].y] = 9;
			diamonds[d[i].x][d[i].y + step + 2] = 9;
		}
		if (diamonds[d[i].x][d[i].y] == 10)
		{
			diamonds[d[i].x + step + 2][d[i].y] = 10;
			diamonds[d[i].x][d[i].y - step - 2] = 10;
		}
	}
}

void startup()
{

	c[0].x = 125; c[0].y = 500;//����������������
	c[1].x = 275; c[1].y = 500;

	d[0].x = 40;//��ɫ�����ʼλ��
	d[0].y = 100;

	d[1].x = c[0].x; d[1].y = c[0].y;//������������
	d[2].x = c[1].x; d[2].y = c[1].y;

	step = 30;//����߳�
	step_r = 15;
	step1 = 32;//����һ������

	isselect1 = 0;
	isselect2 = 0;
	t = 0;
	rt = 0;//�趨�жϳ�ʼֵΪ0

	kinds = 9;

	score = 0;

	for (i = 1; i < 3; i++)
	{
		diamonds[d[i].x][d[i].y] = rand() % kinds + 2;//�������
	}
	judge();//�Գ�����������ж�

	loadimage(&img_bk, _T(".\\background.jpg"));	// ��ȡͼƬ�� img ������

	for (i = 0; i < 10; i++)//��ʼ����ɫ����ײ�
	{
		for (j = 0; j < 10; j++)
		{
			diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 1;
		}
	} 
}

void press()	//��ʼ����
{
	initgraph(width, high);		// ��ʼ����ͼ����

	loadimage(&img_bg, _T(".\\begin.jpg"));	// ��ȡ��ʼ���浽 img ������
	putimage(0, 0, &img_bg);	// ������ (0, 0) λ����ʾ��ʼ����
}

void showbk()	//��ʾ����ģ��
{
	setbkcolor(RGB(242, 255, 248));	// ���ñ���ɫ

	putimage(0, 0, &img_bk);	// ������ (0, 0) λ����ʾ IMAGE ����

	for (i = 0; i < 400; i++)//���Ƶײ�
	{
		for (j = 50; j < 500; j++)
		{
			if (diamonds[i][j] == 1)
			{
				setfillcolor(RGB(224, 224, 224));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
		}
	}
}
void showdiamond()
{
	for (i = 0; i < 400; i++)//������������ѭ��
	{
		for (j = 0; j < 650; j++)
		{
			if (diamonds[i][j] == 2)//������Ϊ2ʱ��ʾ�����ͷ���
			{
				setfillcolor(RGB(124, 136, 194));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 3)//������������
			{
				setfillcolor(RGB(237, 149, 75));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 4)//������������
			{
				setfillcolor(RGB(237, 149, 75));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 5)//������������
			{
				setfillcolor(RGB(255, 198, 62));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 6)//������������
			{
				setfillcolor(RGB(255, 198, 62));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 7)//234����
			{
				setfillcolor(RGB(89, 203, 134));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 8)//124����
			{
				setfillcolor(RGB(89, 203, 134));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 9)//123����
			{
				setfillcolor(RGB(105, 197, 231));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 10)//134����
			{
				setfillcolor(RGB(105, 197, 231));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
		}
	}

	//vc������ʾ
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	itoa(score, scoreString, 10);
	outtextxy(130, 40, _T(scoreString));
	//vs������ʾ
	/*settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	_itoa_s(score, scoreString, 10);
	MultiByteToWideChar(CP_ACP, 0, scoreString, -1, scoreText, 10);
	outtextxy(130, 40, scoreText);*/
}

void updateWithInput()	//���û������йصĸ���
{
	while (1)
	{
		msg = GetMouseMsg();
		if (isselect2 == 0 && (msg.y < d[1].y + step1 + step_r) && (msg.y > d[1].y - step1 - step_r) && (msg.x < d[1].x + step1 + step_r) && (msg.x > d[1].x - step1 - step_r))
		{
			if (msg.mkLButton)
			{
				isselect1 = 1;//��ѡ��
			}
			if (isselect1 == 1)
			{
				if (diamonds[d[1].x][d[1].y] == 2)//���ѡ�����2����
				{
					if (msg.mkLButton&& diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 2;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 2;

										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										back1();
										t1=1;

										score = score + 1;//һ���������ȥ������һ
										rt++;
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							back1();
							diamonds[d[1].x][d[1].y] = 2;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 3)//������Ϊ3�ͷ���
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//��ѡ��
					{
						diamonds[d[1].x][d[1].y] = 0;//��������Ϊ0
						diamonds[d[1].x - step - 2][d[1].y] = 0;
						diamonds[d[1].x + step + 2][d[1].y] = 0;//����������ҲΪ0

						mouse1();//������ƶ�
						diamonds[d[1].x][d[1].y] = 3;
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�ĺ����ҷ��������Ƿ�Ϊ1�����Ƿ�ɷţ�
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;//ʹ����ĵװ巽�����ı�����ʵ������

										diamonds[d[1].x][d[1].y] = 0;
										diamonds[d[1].x - step - 2][d[1].y] = 0;
										diamonds[d[1].x + step + 2][d[1].y] = 0;//���λ�ü����ҷ�������Ϊ0

										back1();

										t1=1;//����·���
										score = score + 3;
										rt++;
									}
								}
							}
						if (rt == 0)
						{
							diamonds[d[1].x][d[1].y] = 0;
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							diamonds[d[1].x + step + 2][d[1].y] = 0;
							back1();
							diamonds[d[1].x][d[1].y] = 3;

							isselect1 = 0;
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 4)//������Ϊ4�ͷ���
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//��ѡ��
					{
						diamonds[d[1].x][d[1].y] = 0;//��������Ϊ0
						diamonds[d[1].x][d[1].y - step - 2] = 0;
						diamonds[d[1].x][d[1].y + step + 2] = 0;//����������ҲΪ0

						mouse1();//������ƶ�
						diamonds[d[1].x][d[1].y] = 4;//���ķ�������·���Ϊ4
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�ĺ����·��������Ƿ�Ϊ1�����Ƿ�ɷţ�
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 4;//ʹ����ĵװ巽�����ı�����ʵ������

										diamonds[d[1].x][d[1].y] = 0;
										diamonds[d[1].x][d[1].y - step - 2] = 0;
										diamonds[d[1].x][d[1].y + step + 2] = 0;//���λ�ü����·�������Ϊ0

										back1();//ʹ�����������»ص����ַ��������
										
										t1=1;

										score = score + 3;
										rt++;
									}
								}
							}
						if (rt == 0)
						{
							diamonds[d[1].x][d[1].y] = 0;
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							diamonds[d[1].x][d[1].y + step + 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 4;
							isselect1 = 0;
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 5)//���ѡ�����5����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0
						diamonds[d[1].x][d[1].y - step - 2] = 0;

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 5;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 5;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 5;
										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										diamonds[d[1].x][d[1].y - step - 2] = 0;

										back1();//ʹ�������Ļص����ַ��������
										
										t1=1;

										score = score + 2;
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 5;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 6)//���ѡ�����6����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0
						diamonds[d[1].x - step - 2][d[1].y] = 0;

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 6;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										diamonds[d[1].x - step - 2][d[1].y] = 0;

										back1();//ʹ�������Ļص����ַ��������
										
										t1=1;
										score = score + 2;
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 6;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 7)//���ѡ�����7����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0
						diamonds[d[1].x - step - 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y - step - 2] = 0;

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 7;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 7;

										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										diamonds[d[1].x - step - 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y - step - 2] = 0;

										back1();//ʹ�������Ļص����ַ��������
										
										t1=1;

										score = score + 3;
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 7;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 8)//���ѡ�����8����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0
						diamonds[d[1].x - step - 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y + step + 2] = 0;

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 8;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 8;

										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										diamonds[d[1].x - step - 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y + step + 2] = 0;

										back1();//ʹ�������Ļص����ַ��������
										
										t1=1;

										score = score + 3;//�������ȥ��������
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y + step + 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 8;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 9)//���ѡ�����9����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0
						diamonds[d[1].x + step + 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y + step + 2] = 0;

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 9;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 9;

										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										diamonds[d[1].x + step + 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y + step + 2] = 0;

										back1();//ʹ�������Ļص����ַ��������
										
										t1=1;

										score = score + 3;//�������ȥ��������
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							diamonds[d[1].x + step + 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y + step + 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 9;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 10)//���ѡ�����10����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//ԭλ������Ϊ0
						diamonds[d[1].x + step + 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y - step - 2] = 0;

						mouse1();//����λ�ú����λ����ͬ
						diamonds[d[1].x][d[1].y] = 10;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 10;

										diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
										diamonds[d[1].x + step + 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y - step - 2] = 0;

										back1();//ʹ�������Ļص����ַ��������
										
										t1=1;

										score = score + 3;//�������ȥ��������
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[1].x][d[1].y] = 0;//ԭλ��Ϊ0
							diamonds[d[1].x + step + 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 10;//�ڳ��ַ�����������ʹ�������
							isselect1 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect1 = 0;//ѡ�����
							break;
						}
					}
					break;
				}
			}
		}
		else if (isselect1 == 0 && (msg.y < d[2].y + step1 + step_r) && (msg.y > d[2].y - step1 - step_r) && (msg.x < d[2].x + step1 + step_r) && (msg.x > d[2].x - step1 - step_r))
		{
			if (msg.mkLButton)
			{
				isselect2 = 1;//��ѡ��
			}
			if (isselect2 == 1)
			{
				if (diamonds[d[2].x][d[2].y] == 2)//���ѡ�����2����
				{
					if (msg.mkLButton&& diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						mouse2();//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 2;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 2;

										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										back2();
										t2=1;

										score = score + 1;//�������ȥ������һ
										rt++;
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							back2();
							diamonds[d[2].x][d[2].y] = 2;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 3)//������Ϊ3�ͷ���
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//��ѡ��
					{
						diamonds[d[2].x][d[2].y] = 0;//��������Ϊ0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						diamonds[d[2].x + step + 2][d[2].y] = 0;//����������ҲΪ0
						mouse2();//������ƶ�
						diamonds[d[2].x][d[2].y] = 3;
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�ĺ����ҷ��������Ƿ�Ϊ1�����Ƿ�ɷţ�
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;//ʹ����ĵװ巽�����ı�����ʵ������

										diamonds[d[2].x][d[2].y] = 0;
										diamonds[d[2].x - step - 2][d[2].y] = 0;
										diamonds[d[2].x + step + 2][d[2].y] = 0;//���λ�ü����ҷ�������Ϊ0

										back2();

										t2=1;
										score = score + 3;
										rt++;
									}
								}
							}
						if (rt == 0)
						{
							diamonds[d[2].x][d[2].y] = 0;
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							diamonds[d[2].x + step + 2][d[2].y] = 0;
							back2();
							diamonds[d[2].x][d[2].y] = 3;

							isselect2 = 0;
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 4)//������Ϊ4�ͷ���
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//��ѡ��
					{
						diamonds[d[2].x][d[2].y] = 0;//��������Ϊ0
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						diamonds[d[2].x][d[2].y + step + 2] = 0;//����������ҲΪ0
						mouse2();
						//������ƶ�
						diamonds[d[2].x][d[2].y] = 4;//���ķ�������·���Ϊ4
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�ĺ����·��������Ƿ�Ϊ1�����Ƿ�ɷţ�
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 4;//ʹ����ĵװ巽�����ı�����ʵ������

										diamonds[d[2].x][d[2].y] = 0;
										diamonds[d[2].x][d[2].y - step - 2] = 0;
										diamonds[d[2].x][d[2].y + step + 2] = 0;//���λ�ü����·�������Ϊ0

										back2();//ʹ�����������»ص����ַ��������
										t2=1;

										score = score + 3;
										rt++;
									}
								}
							}
						if (rt == 0)
						{
							diamonds[d[2].x][d[2].y] = 0;
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							diamonds[d[2].x][d[2].y + step + 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 4;
							isselect2 = 0;
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 5)//���ѡ�����5����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						mouse2();
						//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 5;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 5;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 5;
										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										diamonds[d[2].x][d[2].y - step - 2] = 0;

										back2();//ʹ�������Ļص����ַ��������
										
										t2=1;

										score = score + 2;
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 5;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 6)//���ѡ�����6����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						mouse2();
						//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 6;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										diamonds[d[2].x - step - 2][d[2].y] = 0;

										back2();//ʹ�������Ļص����ַ��������
										
										t2=1;
										score = score + 2;
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 6;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 7)//���ѡ�����7����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						mouse2();
						//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 7;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 7;

										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										diamonds[d[2].x - step - 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y - step - 2] = 0;

										back2();
										//ʹ�������Ļص����ַ��������
										t2=1;

										score = score + 3;//һ���������ȥ������һ
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 7;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 8)//���ѡ�����8����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y + step + 2] = 0;
						mouse2();
						//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 8;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 8;

										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										diamonds[d[2].x - step - 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y + step + 2] = 0;

										back2();//ʹ�������Ļص����ַ��������
										
										t2=1;

										score = score + 3;//һ���������ȥ��������
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y + step + 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 8;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 9)//���ѡ�����9����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						diamonds[d[2].x + step + 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y + step + 2] = 0;
						mouse2();
						//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 9;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 9;

										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										diamonds[d[2].x + step + 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y + step + 2] = 0;

										back2();//ʹ�������Ļص����ַ��������
										
										t2=1;

										score = score + 3;//�������ȥ��������
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							diamonds[d[2].x + step + 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y + step + 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 9;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 10)//���ѡ�����10����
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//ԭλ������Ϊ0
						diamonds[d[2].x + step + 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						mouse2();
						//����λ�ú����λ����ͬ
						diamonds[d[2].x][d[2].y] = 10;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 10;

										diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
										diamonds[d[2].x + step + 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y - step - 2] = 0;

										back2();//ʹ�������Ļص����ַ��������
										
										t2=1;

										score = score + 3;//�������ȥ��������
										rt++;//�ж��Ƿ��з��鱻����ȥ
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[d[2].x][d[2].y] = 0;//ԭλ��Ϊ0
							diamonds[d[2].x + step + 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 10;//�ڳ��ַ�����������ʹ�������
							isselect2 = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							isselect2 = 0;
							break;
						}
					}
					break;
				}
			}
		}
	}
}

void updateWithoutInput()	//���û������޹صĸ���
{
	if (t1 == 1 && t2 == 1)
	{
		diamonds[d[1].x][d[1].y] = rand() % kinds + 2;//1λ���������һ������
		diamonds[d[2].x][d[2].y] = rand() % kinds + 2;//2λ���������һ������
		t1 = 0;
		t2 = 0;
	}
	judge();//��������ķ����ж�
			//��������������ж�����
	if ((isselect1 == 0) && (isselect2 == 0))
	{
		//�Ӻ����ж�����
		for (j = 0; j < 10; j++)
		{
			t = 0;
			for (i = 0; i < 10; i++)
			{
				if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] != 1)//getpixel(d[0].x + i*step1 + 10, d[0].y + j*step1 + 10) != RGB(224, 224, 224)
					t++;
			}
			if (t == 10)
			{
				for (i = 0; i < 10; i++)
				{
					diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 1;
				}
				score += 10;
				mciSendString(_T("stop jpmusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
				mciSendString(_T("close jpmusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
				mciSendString(_T("open D:\\popmusic.WAV alias jpmusic"), NULL, 0, NULL); // ����������
				mciSendString(_T("play jpmusic"), NULL, 0, NULL); // ������һ��
			}
			t = 0;
		}
		//�������ж�����
		for (i = 0; i < 10; i++)
		{
			t = 0;
			for (j = 0; j < 10; j++)
			{

				if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] != 1)
					t++;
			}
			if (t == 10)
			{
				for (j = 0; j < 10; j++)
				{
					diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 1;
				}
				score += 10;
				mciSendString(_T("stop jpmusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
				mciSendString(_T("close jpmusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
				mciSendString(_T("open .\\popmusic.WAV alias jpmusic"), NULL, 0, NULL); // ����������
				mciSendString(_T("play jpmusic"), NULL, 0, NULL); // ������һ��
			}
			t = 0;
		}
	}
}

void main()
{
	startup();
	press();	//��ʼ����	

	while (1)
	{
		msg = GetMouseMsg();//��ȡ�����Ϣ
		if (msg.mkLButton&&msg.y < 317 && msg.y >233 && msg.x < 296 && msg.x > 99)
		{
			mciSendString(_T("open .\\putmusic.WAV alias jpmusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("play jpmusic"), NULL, 0, NULL); // ������һ��
			break;
		}
	}

	BeginBatchDraw();//��ʼ��������

	while (1)
	{
		showbk();
		showdiamond();
		FlushBatchDraw();
		updateWithInput();
		updateWithoutInput();
	}
	EndBatchDraw();//������������
	_getch();
	closegraph();
}

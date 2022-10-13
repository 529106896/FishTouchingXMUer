#include <graphics.h>
#include <conio.h>
#define width 400
#define high 650//���廭����С

//����ȫ�ֱ���

int diamond_x1, diamond_y1;////��������λ������
int diamond_x0, diamond_y0;//��ɫ�ײ���������
int diamonds[width][high] = { 0 };///���������������Ķ�ά����
int center_x1, center_y1;//���ַ��������

int step_r, step, step1;//����߳�һ�뼰�߳�

int i, j;//ѭ������

int t;//�����жϱ���
int rt;//�ص�����λ�õ��жϱ���
int isselect;//ѡ���жϱ���

int score;
char scoreString[10];//������ʾ
TCHAR scoreText[10];   //��vs��ʱȡ�����ע��

MOUSEMSG msg;//�����Ϣ
IMAGE img_bk;	//������Ϸ����
IMAGE img_bg;	// �����ʼ���汳��

void startup()
{
	center_x1 = 200;//����������������
	center_y1 = 500;

	diamond_x1 = center_x1;//������������
	diamond_y1 = center_y1;

	diamond_x0 = 40;
	diamond_y0 = 90;

	step = 30;
	step_r = 15;

	isselect = 0;
	t = 0;
	rt = 0;//�趨�жϳ�ʼֵΪ0

	step1 = 32;

	score = 0;

	diamonds[diamond_x1][diamond_y1] = rand() % 2 + 2;//�ȴ�һ�����鿪ʼд

	if (diamonds[diamond_x1][diamond_y1] == 3)
	{
		diamonds[diamond_x1 - step - 2][diamond_y1] = 3;
		diamonds[diamond_x1 + step + 2][diamond_y1] = 3;
	}

	loadimage(&img_bk, _T(".\\background.jpg"));	// ��ȡͼƬ�� img ������

	for (i = 0; i < 10; i++)//��ʼ����ɫ����ײ�
	{
		for (j = 0; j < 10; j++)
		{
			diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 1;
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
		}
	}
	/*
	//vc������ʾ
	/*settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	itoa(score, scoreString, 10);
	outtextxy(130, 40, _T(scoreString));*/


	//vs������ʾ
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	_itoa_s(score, scoreString, 10);
	MultiByteToWideChar(CP_ACP, 0, scoreString, -1, scoreText, 10);

	outtextxy(130, 40, scoreText);
}

void updateWithInput()	//���û������йصĸ���
{
	while (1)
	{
		msg = GetMouseMsg();
		if ((msg.y < diamond_y1 + step1 + step_r) && (msg.y > diamond_y1 - step1 - step_r) && (msg.x < diamond_x1 + step1 + step_r) && (msg.x > diamond_x1 - step1 - step_r))
		{
			if (msg.mkLButton)
			{
				isselect = 1;//��ѡ��
			}
			if (isselect == 1)
			{
				if (diamonds[diamond_x1][diamond_y1] == 2)//���ѡ�����2����
				{
					if (msg.mkLButton&& diamonds[msg.x][msg.y] != 1)
					{
						diamonds[diamond_x1][diamond_y1] = 0;//ԭλ������Ϊ0
						diamond_x1 = msg.x;
						diamond_y1 = msg.y;//����λ�ú����λ����ͬ
						diamonds[diamond_x1][diamond_y1] = 2;//����λ����ʾ����
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((diamond_x1 - (diamond_x0 + i*step1 + step_r))*(diamond_x1 - (diamond_x0 + i*step1 + step_r)) + (diamond_y1 - (diamond_y0 + j*step1 + step_r))*(diamond_y1 - (diamond_y0 + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�������Ƿ�Ϊ1
									if (diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] == 1)
									{
										diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 2;

										diamonds[diamond_x1][diamond_y1] = 0;//ԭλ��Ϊ0
										diamond_x1 = center_x1;
										diamond_y1 = center_y1;//ʹ�������Ļص����ַ��������
										diamonds[diamond_x1][diamond_y1] = rand() % 2 + 2;//�������һ������
										if (diamonds[diamond_x1][diamond_y1] == 3)
										{
											diamonds[diamond_x1 - step - 2][diamond_y1] = 3;
											diamonds[diamond_x1 + step + 2][diamond_y1] = 3;
										}
										score = score + 1;//һ���������ȥ������һ
										rt++;
									}
								}
							}
						if (rt == 0)//Ϊ0ʱ˵������δ������ȥ
						{
							diamonds[diamond_x1][diamond_y1] = 0;//ԭλ��Ϊ0
							diamond_x1 = center_x1;
							diamond_y1 = center_y1;
							diamonds[diamond_x1][diamond_y1] = 2;//�ڳ��ַ�����������ʹ�������
							isselect = 0;//ѡ�����
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
							break;
						}
					}
					break;
				}
				else if (diamonds[diamond_x1][diamond_y1] == 3)//������Ϊ3�ͷ���
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//��ѡ��
					{
						diamonds[diamond_x1][diamond_y1] = 0;//��������Ϊ0
						diamonds[diamond_x1 - step - 2][diamond_y1] = 0;
						diamonds[diamond_x1 + step + 2][diamond_y1] = 0;//����������ҲΪ0
						diamond_x1 = msg.x;
						diamond_y1 = msg.y;//������ƶ�
						diamonds[diamond_x1][diamond_y1] = 3;
						diamonds[diamond_x1 - step - 2][diamond_y1] = 3;
						diamonds[diamond_x1 + step + 2][diamond_y1] = 3;
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//�жϷ����Ƿ�����10*10�װ��ĳ����������Ϊԭ�㷽���ܳ�һ��Ϊ�뾶��Բ��
								if ((diamond_x1 - (diamond_x0 + i*step1 + step_r))*(diamond_x1 - (diamond_x0 + i*step1 + step_r)) + (diamond_y1 - (diamond_y0 + j*step1 + step_r))*(diamond_y1 - (diamond_y0 + j*step1 + step_r)) <= 15 * 15)
								{
									//�жϸ�Բ�ĺ����ҷ��������Ƿ�Ϊ1�����Ƿ�ɷţ�
									if (diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] == 1 &&
										diamonds[diamond_x0 + (i - 1)*step1 + step_r][diamond_y0 + j*step1 + step_r] == 1 &&
										diamonds[diamond_x0 + (i + 1)*step1 + step_r][diamond_y0 + j*step1 + step_r] == 1)
									{
										diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 3;
										diamonds[diamond_x0 + (i - 1)*step1 + step_r][diamond_y0 + j*step1 + step_r] = 3;
										diamonds[diamond_x0 + (i + 1)*step1 + step_r][diamond_y0 + j*step1 + step_r] = 3;//ʹ����ĵװ巽�����ı�����ʵ������

										diamonds[diamond_x1][diamond_y1] = 0;
										diamonds[diamond_x1 - step - 2][diamond_y1] = 0;
										diamonds[diamond_x1 + step + 2][diamond_y1] = 0;//���λ�ü����ҷ�������Ϊ0

										diamond_x1 = center_x1;
										diamond_y1 = center_y1;

										diamonds[diamond_x1][diamond_y1] = rand() % 2 + 2;//����·���

										if (diamonds[diamond_x1][diamond_y1] == 3)
										{
											diamonds[diamond_x1 - step - 2][diamond_y1] = 3;
											diamonds[diamond_x1 + step + 2][diamond_y1] = 3;
										}
										score = score + 3;
										rt++;
									}
								}
							}
						if (rt == 0)
						{
							diamonds[diamond_x1][diamond_y1] = 0;
							diamonds[diamond_x1 - step - 2][diamond_y1] = 0;
							diamonds[diamond_x1 + step + 2][diamond_y1] = 0;
							diamond_x1 = center_x1;
							diamond_y1 = center_y1;
							diamonds[diamond_x1][diamond_y1] = 3;
							diamonds[diamond_x1 - step - 2][diamond_y1] = 3;
							diamonds[diamond_x1 + step + 2][diamond_y1] = 3;

							isselect = 0;
							break;
						}
						else
						{
							rt = 0;//���¶Իص�����λ�ø��жϸ�ֵ
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
	//��������������ж�����
	if (isselect == 0)
	{
		//�������ж�����
		for (i = 0; i < 10; i++)
		{
			t = 0;
			for (j = 0; j < 10; j++)
			{

				if (getpixel(diamond_x0 + i*step1 + 10, diamond_y0 + j*step1 + 10) != RGB(224, 224, 224))
					t++;
			}
			if (t == 10)
			{
				for (j = 0; j < 10; j++)
				{
					diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 1;
				}
				score += 10;
			}
			t = 0;
		}
		//�Ӻ����ж�����
		for (j = 0; j < 10; j++)
		{
			t = 0;
			for (i = 0; i < 10; i++)
			{
				if (getpixel(diamond_x0 + i*step1 + 10, diamond_y0 + j*step1 + 10) != RGB(224, 224, 224))
					t++;
			}
			if (t == 10)
			{
				for (i = 0; i < 10; i++)
				{
					diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 1;
				}
				score += 10;
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

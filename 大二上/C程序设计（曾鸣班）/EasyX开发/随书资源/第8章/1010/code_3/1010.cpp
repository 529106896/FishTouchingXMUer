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

	step1 = 32;

	t = 0;
	score = 0;

	diamonds[diamond_x1][diamond_y1] = rand() % 1 + 2;//�ȴ�һ�����鿪ʼд

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
		}
	}
	/*else if (diamonds[diamond_x1][diamond_y1] = 2)//������������
	{
	setfillcolor(RGB(255, 198, 62));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 - step_r, diamond_x1 - 1, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 - step_r, diamond_x1 + step + 1, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 3)//������������
	{
	setfillcolor(RGB(255, 198, 62));
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step - 1, diamond_x1 + step_r, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 + 1, diamond_x1 + step_r, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 4)//������������
	{
	setfillcolor(RGB(237, 149, 75));
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 5)//������������
	{
	setfillcolor(RGB(237, 149, 75));
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 6)//�Ŀ�������
	{
	setfillcolor(RGB(152, 220, 85));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 7)//234����
	{
	setfillcolor(RGB(89, 203, 134));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 8)//124����
	{
	setfillcolor(RGB(89, 203, 134));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 9)//134����
	{
	setfillcolor(RGB(89, 203, 134));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 10)//123����
	{
	setfillcolor(RGB(89, 203, 134));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 11)//�����ĸ�����
	{
	setfillcolor(RGB(255, 198, 62));
	solidroundrect(diamond_x1 - step - 1, diamond_y1 - step_r, diamond_x1 - 1, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 + 1, diamond_y1 - step_r, diamond_x1 + step + 1, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 - 2 * step - 3, diamond_y1 - step_r, diamond_x1 - step - 3, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 + step + 3, diamond_y1 - step_r, diamond_x1 + 2 * step + 3, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 12)//�����ĸ�����
	{
	setfillcolor(RGB(255, 198, 62));
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step - 1, diamond_x1 + step_r, diamond_y1 - 1, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 + 1, diamond_x1 + step_r, diamond_y1 + step + 1, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 - 2 * step - 3, diamond_x1 + step_r, diamond_y1 - step - 3, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 + step + 3, diamond_x1 + step_r, diamond_y1 + 2 * step + 3, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 13)//�����������
	{
	setfillcolor(RGB(221, 101, 85));
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 - 2 * step - step_r - 4, diamond_y1 - step_r, diamond_x1 - step - step_r - 4, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 + step + step_r + 4, diamond_y1 - step_r, diamond_x1 + 2 * step + step_r + 4, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 14)//�����������
	{
	setfillcolor(RGB(221, 101, 85));
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 - 2 * step - step_r - 4, diamond_x1 + step_r, diamond_y1 - step - step_r - 4, 5, 5);
	solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + step + 4, diamond_x1 + step_r, diamond_y1 + 2 * step + step_r + 4, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 15)//�Ź��񷽿�
	{
	setfillcolor(RGB(77, 213, 175));

	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);//����
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);//����
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);//����

	solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 16)//12369�������
	{
	setfillcolor(RGB(92, 190, 229));

	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);

	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 17)//36789�������
	{
	setfillcolor(RGB(92, 190, 229));

	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);

	solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 18)//12347�������
	{
	setfillcolor(RGB(92, 190, 229));

	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);

	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);

	solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 19)//14789�������
	{
	setfillcolor(RGB(92, 190, 229));

	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);

	solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);
	solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

	solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
	}*/



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
					if (msg.mkLButton)
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
										diamonds[diamond_x1][diamond_y1] = rand() % 1 + 2;//�������һ������
										score = score + 1;//һ���������ȥ������һ
										isselect = 0;
									}
								}
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
				setfillcolor(RGB(224, 224, 224));
				solidroundrect(diamond_x0 + i*step1, diamond_y0 + j*step1, diamond_x0 + i*step1 + step, diamond_y0 + j*step1 + step, 5, 5);
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
				setfillcolor(RGB(224, 224, 224));
				solidroundrect(diamond_x0 + i*step1, diamond_y0 + j*step1, diamond_x0 + i*step1 + step, diamond_y0 + j*step1 + step, 5, 5);
				diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 1;
			}
			score += 10;
		}
		t = 0;
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

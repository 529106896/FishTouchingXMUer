#include <graphics.h>
#include <conio.h>
#define width 400
#define high 650//���廭����С

//����ȫ�ֱ���

int diamond_x1, diamond_y1;////��������λ������
int diamond_x0, diamond_y0;//��ɫ�ײ���������
int diamonds[width][high] = { 0 };///���������������Ķ�ά����

int step_r, step, step1;//����߳�һ�뼰�߳�

int i, j;//ѭ������
int t;//�����жϱ���

int score;
char scoreString[10];//������ʾ
TCHAR scoreText[10];   //��vs��ʱȡ�����ע��

MOUSEMSG msg;//�����Ϣ
IMAGE img_bk;	//������Ϸ����
IMAGE img_bg;	// �����ʼ���汳��

void startup()
{
	diamond_x1 = 200;
	diamond_y1 = 500;
	diamond_x0 = 40;
	diamond_y0 = 90;
	step = 30;
	step_r = 15;
	step1 = 32;
	t = 0;
	score = 0;
	diamonds[diamond_x1][diamond_y1] = rand() % 1 + 1;//�ȴ�һ�����鿪ʼд

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
	if (diamonds[diamond_x1][diamond_y1] == 1)//һ������
	{
		setfillcolor(RGB(124, 136, 194));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
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

	
	/*
	//vc������ʾ
	settextcolor(RGB(0, 0, 0));
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

}

void updateWithoutInput()	//���û������޹صĸ���
{
	//�������ж�����
	for (i = 50; i < 360; i += 32)
	{
		t = 0;
		for (j = 110; j < 410; j += 32)
		{
			if (getpixel(i, j) != RGB(224, 224, 224))
				t++;
		}
		i = i - 10;
		if (t == 10)
		{
			for (j = 100; j < 400; j += 32)
			{
				setfillcolor(RGB(224, 224, 224));
				solidroundrect(i, j, i + step, j + step, 5, 5);
			}
		}
		i = i + 10;
	}
	//�Ӻ����ж�����
	for (j = 110; j < 400; j += 32)
	{
		t = 0;
		for (i = 50; i < 350; i += 32)
		{
			if (getpixel(i, j) != RGB(224, 224, 224))
				t++;
		}
		j = j - 10;
		if (t == 10)
		{
			for (i = 40; i < 350; i += 32)
			{

				setfillcolor(RGB(224, 224, 224));
				solidroundrect(i, j, i + step, j + step, 5, 5);
			}
			score += 10;
		}
		j = j + 10;
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

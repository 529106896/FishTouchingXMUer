#include <graphics.h>
#include <conio.h>
#define width 400
#define high 650

int diamond_x1, diamond_y1;
int diamond_x0, diamond_y0;
int diamonds[high][width] = { 0 };
int step_r, step;

int i, j;

void startup()
{
	diamond_x1 = 200;
	diamond_y1 = 555;
	diamond_x0 = 40;
	diamond_y0 = 90;
	step = 30;
	step_r = 15;
	diamonds[diamond_x1][diamond_y1] = rand() % 19 + 1;
}


/*void press()	//��ʼ����
{
	initgraph(width, high);		// ��ʼ����ͼ����

	IMAGE img_bg;	// ���� IMAGE ����
	loadimage(&img_bg, _T(".\\begin.jpg"));	// ��ȡ��ʼ���浽 img ������
	putimage(0, 0, &img_bg);	// ������ (0, 0) λ����ʾ��ʼ����

	MOUSEMSG m;
	if (MouseHit())
	{
		m = GetMouseMsg();
	}
	_getch();
	closegraph();

}*/

void showbk()	//��ʾ����ģ��
{
	initgraph(width, high);		// ��ʼ����ͼ����
	setbkcolor(RGB(242, 255, 248));	// ���ñ���ɫ

	IMAGE img_bk;	// ���� IMAGE ����
	loadimage(&img_bk, _T(".\\background.jpg"));	// ��ȡͼƬ�� img ������
	putimage(0, 0, &img_bk);	// ������ (0, 0) λ����ʾ IMAGE ����

	for (i = 40; i < 350; i += 32)
	{
		for (j = 100; j < 400; j += 32)
		{
			setfillcolor(RGB(224, 224, 224));
			solidroundrect(i, j, i + step, j + step, 5, 5);
		}
	}
}
void showdiamond()
{
	if (diamonds[diamond_x1][diamond_y1] = 1)//һ������
	{
		setfillcolor(RGB(124, 136, 194));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 2)//������������
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
	}
}

void updateWithInput()	//���û������йصĸ���
{

}

void updateWithoutInput()	//���û������޹صĸ���
{

}

void main()
{
	startup();
//	press();	//��ʼ����
	showbk();
	while (1)
	{
		showdiamond();
		updateWithInput();
		updateWithoutInput();
	}
	closegraph();
	_getch();
}

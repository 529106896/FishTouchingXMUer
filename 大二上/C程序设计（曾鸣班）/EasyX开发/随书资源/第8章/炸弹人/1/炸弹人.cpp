#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

#define high 200
#define width  300 //������ʼ��
#define distence 11 //����������ʵ�ʱ߽�ľ���

int x_man, y_man;

IMAGE img_bk, img_people1, img_people2,img_zhangai; //ͼƬ��ַ

void startup()
{
	initgraph(width, high);
	loadimage(&img_bk, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\map020_01_02.jpg"));
	loadimage(&img_zhangai, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\�ϰ���.jpg"));
	loadimage(&img_people1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\����\\����1.jpg"));
	loadimage(&img_people2, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\����\\����2.jpg"));
	x_man = 20+distence;
	y_man = 20+distence;
}

void show()
{
	
	int i=0;
	for (i = 0; i < 3; i++)
	{
		putimage(0, 0, &img_bk);
		putimage(x_man, y_man, 2 * distence, 2 * distence, &img_people1, 2 * i*distence, 0, NOTSRCERASE);
		putimage(x_man, y_man, 2 * distence, 2 * distence, &img_people2, 2 * i*distence, 0, SRCINVERT);
		Sleep(10);
	}
	
}

void updateWithoutInput()
{
	if (_kbhit())
	{
		char ch;
		ch = _getch();
		if (ch == 'w')
		{
			y_man = y_man - 5;
		}
		if (ch == 's')
		{
			y_man = y_man + 5;
		}
		if (ch == 'a')
		{
			x_man = x_man - 5;
		}
		if (ch == 'd')
		{
			x_man = x_man + 5;
		}
	}
}

void gameover()
{
	_getch();
	closegraph();
}

void main()
{
	startup();  // ���ݳ�ʼ��	
	while (1)  //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		//updateWithInput();     // ���û������йصĸ���
	}
	gameover();     // ��Ϸ��������������
}

#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

#define high 200
#define width  300 //画布初始化
#define distence 11 //人物中心与实际边界的距离

int x_man, y_man;

IMAGE img_bk, img_people1, img_people2,img_zhangai; //图片地址

void startup()
{
	initgraph(width, high);
	loadimage(&img_bk, _T("D:\\猿\\期末大作业\\素材\\地图\\map020_01_02.jpg"));
	loadimage(&img_zhangai, _T("D:\\猿\\期末大作业\\素材\\地图\\障碍改.jpg"));
	loadimage(&img_people1, _T("D:\\猿\\期末大作业\\素材\\人物\\人物1.jpg"));
	loadimage(&img_people2, _T("D:\\猿\\期末大作业\\素材\\人物\\人物2.jpg"));
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
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		//updateWithInput();     // 与用户输入有关的更新
	}
	gameover();     // 游戏结束、后续处理
}

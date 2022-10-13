#include <graphics.h>
#include <conio.h>
#define width 400
#define high 650//定义画布大小

//定义全局变量

int diamond_x1, diamond_y1;////方块所在位置中心
int diamond_x0, diamond_y0;//灰色底布方块中心
int diamonds[width][high] = { 0 };///定义在整个画布的二维数组

int step_r, step, step1;//方块边长一半及边长

int i, j;//循环变量
int t;//消除判断变量

int score;
char scoreString[10];//分数显示
TCHAR scoreText[10];   //用vs打开时取消这个注释

MOUSEMSG msg;//鼠标消息
IMAGE img_bk;	//定义游戏背景
IMAGE img_bg;	// 定义初始界面背景

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
	diamonds[diamond_x1][diamond_y1] = rand() % 1 + 1;//先从一个方块开始写

	loadimage(&img_bk, _T(".\\background.jpg"));	// 读取图片到 img 对象中

	for (i = 0; i < 10; i++)//初始化灰色方块底布
	{
		for (j = 0; j < 10; j++)
		{
			diamonds[diamond_x0 + i*step1 + step_r][diamond_y0 + j*step1 + step_r] = 1;
		}
	}
}

void press()	//初始窗口
{
	initgraph(width, high);		// 初始化绘图窗口

	loadimage(&img_bg, _T(".\\begin.jpg"));	// 读取初始界面到 img 对象中
	putimage(0, 0, &img_bg);	// 在坐标 (0, 0) 位置显示初始界面
}

void showbk()	//显示背景模板
{
	setbkcolor(RGB(242, 255, 248));	// 设置背景色

	putimage(0, 0, &img_bk);	// 在坐标 (0, 0) 位置显示 IMAGE 对象

	for (i = 0; i < 400; i++)//绘制底布
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
	if (diamonds[diamond_x1][diamond_y1] == 1)//一个方块
	{
		setfillcolor(RGB(124, 136, 194));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	}
	/*else if (diamonds[diamond_x1][diamond_y1] = 2)//横向两个方块
	{
		setfillcolor(RGB(255, 198, 62));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 - step_r, diamond_x1 - 1, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 - step_r, diamond_x1 + step + 1, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 3)//竖向两个方块
	{
		setfillcolor(RGB(255, 198, 62));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step - 1, diamond_x1 + step_r, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 + 1, diamond_x1 + step_r, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 4)//横向三个方块
	{
		setfillcolor(RGB(237, 149, 75));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 5)//竖向三个方块
	{
		setfillcolor(RGB(237, 149, 75));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 6)//四块正方形
	{
		setfillcolor(RGB(152, 220, 85));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 7)//234三块
	{
		setfillcolor(RGB(89, 203, 134));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 8)//124三块
	{
		setfillcolor(RGB(89, 203, 134));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 9)//134三块
	{
		setfillcolor(RGB(89, 203, 134));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 + 1, diamond_x1 + step + 1, diamond_y1 + step + 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 10)//123三块
	{
		setfillcolor(RGB(89, 203, 134));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 - step - 1, diamond_x1 - 1, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 - step - 1, diamond_y1 + 1, diamond_x1 - 1, diamond_y1 + step + 1, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 - step - 1, diamond_x1 + step + 1, diamond_y1 - 1, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 11)//横向四个方块
	{
		setfillcolor(RGB(255, 198, 62));
		solidroundrect(diamond_x1 - step - 1, diamond_y1 - step_r, diamond_x1 - 1, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 + 1, diamond_y1 - step_r, diamond_x1 + step + 1, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 - 2 * step - 3, diamond_y1 - step_r, diamond_x1 - step - 3, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 + step + 3, diamond_y1 - step_r, diamond_x1 + 2 * step + 3, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 12)//竖向四个方块
	{
		setfillcolor(RGB(255, 198, 62));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step - 1, diamond_x1 + step_r, diamond_y1 - 1, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 + 1, diamond_x1 + step_r, diamond_y1 + step + 1, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 - 2 * step - 3, diamond_x1 + step_r, diamond_y1 - step - 3, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 + step + 3, diamond_x1 + step_r, diamond_y1 + 2 * step + 3, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 13)//横向五个方块
	{
		setfillcolor(RGB(221, 101, 85));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 - 2 * step - step_r - 4, diamond_y1 - step_r, diamond_x1 - step - step_r - 4, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 + step + step_r + 4, diamond_y1 - step_r, diamond_x1 + 2 * step + step_r + 4, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 14)//竖向五个方块
	{
		setfillcolor(RGB(221, 101, 85));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 - 2 * step - step_r - 4, diamond_x1 + step_r, diamond_y1 - step - step_r - 4, 5, 5);
		solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + step + 4, diamond_x1 + step_r, diamond_y1 + 2 * step + step_r + 4, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 15)//九宫格方块
	{
		setfillcolor(RGB(77, 213, 175));

		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);//中中
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);//中左
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);//中右

		solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 16)//12369五个方块
	{
		setfillcolor(RGB(92, 190, 229));

		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);

		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 17)//36789五个方块
	{
		setfillcolor(RGB(92, 190, 229));

		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r, diamond_x1 + step_r + step + 2, diamond_y1 + step_r, 5, 5);

		solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 18)//12347五个方块
	{
		setfillcolor(RGB(92, 190, 229));

		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);

		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);

		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r - step - 2, diamond_x1 + step_r, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 - step_r - step - 2, diamond_x1 + step_r + step + 2, diamond_y1 - 2 - step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 19)//14789五个方块
	{
		setfillcolor(RGB(92, 190, 229));

		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r, diamond_x1 - step_r - 2, diamond_y1 + step_r, 5, 5);

		solidroundrect(diamond_x1 - step_r, diamond_y1 + step_r + 2, diamond_x1 + step_r, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 + step_r + 2, diamond_x1 - step_r - 2, diamond_y1 + step_r + step + 2, 5, 5);
		solidroundrect(diamond_x1 + step_r + 2, diamond_y1 + step_r + 2, diamond_x1 + step_r + step + 2, diamond_y1 + step_r + step + 2, 5, 5);

		solidroundrect(diamond_x1 - step_r - step - 2, diamond_y1 - step_r - step - 2, diamond_x1 - step_r - 2, diamond_y1 - 2 - step_r, 5, 5);
	}*/

	
	/*
	//vc分数显示
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	itoa(score, scoreString, 10);
	outtextxy(130, 40, _T(scoreString));*/

	
	//vs分数显示
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	_itoa_s(score, scoreString, 10);
	MultiByteToWideChar(CP_ACP, 0, scoreString, -1, scoreText, 10);

	outtextxy(130, 40, scoreText);
}

void updateWithInput()	//与用户输入有关的更新
{

}

void updateWithoutInput()	//与用户输入无关的更新
{
	//从竖排判断消除
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
	//从横排判断消除
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
	press();	//初始界面	

	while (1)
	{
		msg = GetMouseMsg();//获取鼠标信息
		if (msg.mkLButton&&msg.y < 317 && msg.y >233 && msg.x < 296 && msg.x > 99)
		{
			break;
		}
	}

	BeginBatchDraw();//开始批量绘制

	while (1)
	{
		showbk();
		showdiamond();
		FlushBatchDraw();
		updateWithInput();
		updateWithoutInput();
	}
	EndBatchDraw();//结束批量绘制
	_getch();
	closegraph();
}

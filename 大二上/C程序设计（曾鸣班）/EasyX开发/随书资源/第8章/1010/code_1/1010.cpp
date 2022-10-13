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


/*void press()	//初始窗口
{
	initgraph(width, high);		// 初始化绘图窗口

	IMAGE img_bg;	// 定义 IMAGE 对象
	loadimage(&img_bg, _T(".\\begin.jpg"));	// 读取初始界面到 img 对象中
	putimage(0, 0, &img_bg);	// 在坐标 (0, 0) 位置显示初始界面

	MOUSEMSG m;
	if (MouseHit())
	{
		m = GetMouseMsg();
	}
	_getch();
	closegraph();

}*/

void showbk()	//显示背景模板
{
	initgraph(width, high);		// 初始化绘图窗口
	setbkcolor(RGB(242, 255, 248));	// 设置背景色

	IMAGE img_bk;	// 定义 IMAGE 对象
	loadimage(&img_bk, _T(".\\background.jpg"));	// 读取图片到 img 对象中
	putimage(0, 0, &img_bk);	// 在坐标 (0, 0) 位置显示 IMAGE 对象

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
	if (diamonds[diamond_x1][diamond_y1] = 1)//一个方块
	{
		setfillcolor(RGB(124, 136, 194));
		solidroundrect(diamond_x1 - step_r, diamond_y1 - step_r, diamond_x1 + step_r, diamond_y1 + step_r, 5, 5);
	}
	else if (diamonds[diamond_x1][diamond_y1] = 2)//横向两个方块
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
	}
}

void updateWithInput()	//与用户输入有关的更新
{

}

void updateWithoutInput()	//与用户输入无关的更新
{

}

void main()
{
	startup();
//	press();	//初始界面
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

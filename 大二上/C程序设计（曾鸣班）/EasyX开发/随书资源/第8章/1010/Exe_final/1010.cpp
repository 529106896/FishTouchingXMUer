#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")
#define width 400
#define high 650//定义画布大小

//定义全局变量

int diamonds[width][high] = { 0 };//定义在整个画布的二维数组

int step_r, step, step1;//方块边长一半及边长

int i, j;//循环变量

int t;//消除判断变量
int rt;//回到中心位置的判断变量
int isselect1, isselect2;//选择判断变量
int t1, t2;//判断是否新随机两个方块

int score;
char scoreString[10];//分数显示
TCHAR scoreText[10];   //用vs打开时取消这个注释

int kinds;

MOUSEMSG msg;//鼠标消息
IMAGE img_bk;	//定义游戏背景
IMAGE img_bg;	// 定义初始界面背景


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

void back1()//使方块中心回到出现方块的中心
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

void judge()//判断新随机的方块类型，并使方块中心数组对应
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

	c[0].x = 125; c[0].y = 500;//出现随机方块的中心
	c[1].x = 275; c[1].y = 500;

	d[0].x = 40;//灰色方块初始位置
	d[0].y = 100;

	d[1].x = c[0].x; d[1].y = c[0].y;//随机方块的中心
	d[2].x = c[1].x; d[2].y = c[1].y;

	step = 30;//方块边长
	step_r = 15;
	step1 = 32;//与下一方块间隔

	isselect1 = 0;
	isselect2 = 0;
	t = 0;
	rt = 0;//设定判断初始值为0

	kinds = 9;

	score = 0;

	for (i = 1; i < 3; i++)
	{
		diamonds[d[i].x][d[i].y] = rand() % kinds + 2;//随机方块
	}
	judge();//对初次随机方块判断

	loadimage(&img_bk, _T(".\\background.jpg"));	// 读取图片到 img 对象中

	for (i = 0; i < 10; i++)//初始化灰色方块底布
	{
		for (j = 0; j < 10; j++)
		{
			diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 1;
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
	for (i = 0; i < 400; i++)//在整个画面内循环
	{
		for (j = 0; j < 650; j++)
		{
			if (diamonds[i][j] == 2)//当数组为2时显示该类型方块
			{
				setfillcolor(RGB(124, 136, 194));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 3)//横向三个方块
			{
				setfillcolor(RGB(237, 149, 75));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 4)//竖向三个方块
			{
				setfillcolor(RGB(237, 149, 75));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 5)//横向两个方块
			{
				setfillcolor(RGB(255, 198, 62));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 6)//竖向两个方块
			{
				setfillcolor(RGB(255, 198, 62));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 7)//234三块
			{
				setfillcolor(RGB(89, 203, 134));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 8)//124三块
			{
				setfillcolor(RGB(89, 203, 134));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 9)//123三块
			{
				setfillcolor(RGB(105, 197, 231));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
			else if (diamonds[i][j] == 10)//134三块
			{
				setfillcolor(RGB(105, 197, 231));
				solidroundrect(i - step_r, j - step_r, i + step_r, j + step_r, 5, 5);
			}
		}
	}

	//vc分数显示
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	itoa(score, scoreString, 10);
	outtextxy(130, 40, _T(scoreString));
	//vs分数显示
	/*settextcolor(RGB(0, 0, 0));
	settextstyle(30, 15, _T("Arial"));
	_itoa_s(score, scoreString, 10);
	MultiByteToWideChar(CP_ACP, 0, scoreString, -1, scoreText, 10);
	outtextxy(130, 40, scoreText);*/
}

void updateWithInput()	//与用户输入有关的更新
{
	while (1)
	{
		msg = GetMouseMsg();
		if (isselect2 == 0 && (msg.y < d[1].y + step1 + step_r) && (msg.y > d[1].y - step1 - step_r) && (msg.x < d[1].x + step1 + step_r) && (msg.x > d[1].x - step1 - step_r))
		{
			if (msg.mkLButton)
			{
				isselect1 = 1;//被选择
			}
			if (isselect1 == 1)
			{
				if (diamonds[d[1].x][d[1].y] == 2)//如果选择的是2方块
				{
					if (msg.mkLButton&& diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 2;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 2;

										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										back1();
										t1=1;

										score = score + 1;//一个方块放上去分数加一
										rt++;
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							back1();
							diamonds[d[1].x][d[1].y] = 2;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 3)//当方块为3型方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//被选择
					{
						diamonds[d[1].x][d[1].y] = 0;//方块中心为0
						diamonds[d[1].x - step - 2][d[1].y] = 0;
						diamonds[d[1].x + step + 2][d[1].y] = 0;//左右两方块也为0

						mouse1();//随鼠标移动
						diamonds[d[1].x][d[1].y] = 3;
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心和左右方块中心是否为1（即是否可放）
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;//使最近的底板方块中心变量以实现吸附

										diamonds[d[1].x][d[1].y] = 0;
										diamonds[d[1].x - step - 2][d[1].y] = 0;
										diamonds[d[1].x + step + 2][d[1].y] = 0;//鼠标位置及左右方块中心为0

										back1();

										t1=1;//随机新方块
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
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 4)//当方块为4型方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//被选择
					{
						diamonds[d[1].x][d[1].y] = 0;//方块中心为0
						diamonds[d[1].x][d[1].y - step - 2] = 0;
						diamonds[d[1].x][d[1].y + step + 2] = 0;//上下两方块也为0

						mouse1();//随鼠标移动
						diamonds[d[1].x][d[1].y] = 4;//中心方块和上下方块为4
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心和上下方块中心是否为1（即是否可放）
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 4;//使最近的底板方块中心变量以实现吸附

										diamonds[d[1].x][d[1].y] = 0;
										diamonds[d[1].x][d[1].y - step - 2] = 0;
										diamonds[d[1].x][d[1].y + step + 2] = 0;//鼠标位置及上下方块中心为0

										back1();//使方块中心重新回到出现方块的中心
										
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
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 5)//如果选择的是5方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0
						diamonds[d[1].x][d[1].y - step - 2] = 0;

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 5;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 5;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 5;
										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										diamonds[d[1].x][d[1].y - step - 2] = 0;

										back1();//使方块中心回到出现方块的中心
										
										t1=1;

										score = score + 2;
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 5;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 6)//如果选择的是6方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0
						diamonds[d[1].x - step - 2][d[1].y] = 0;

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 6;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										diamonds[d[1].x - step - 2][d[1].y] = 0;

										back1();//使方块中心回到出现方块的中心
										
										t1=1;
										score = score + 2;
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 6;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 7)//如果选择的是7方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0
						diamonds[d[1].x - step - 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y - step - 2] = 0;

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 7;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 7;

										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										diamonds[d[1].x - step - 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y - step - 2] = 0;

										back1();//使方块中心回到出现方块的中心
										
										t1=1;

										score = score + 3;
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 7;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 8)//如果选择的是8方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0
						diamonds[d[1].x - step - 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y + step + 2] = 0;

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 8;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 8;

										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										diamonds[d[1].x - step - 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y + step + 2] = 0;

										back1();//使方块中心回到出现方块的中心
										
										t1=1;

										score = score + 3;//方块放上去分数增加
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							diamonds[d[1].x - step - 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y + step + 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 8;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 9)//如果选择的是9方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0
						diamonds[d[1].x + step + 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y + step + 2] = 0;

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 9;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 9;

										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										diamonds[d[1].x + step + 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y + step + 2] = 0;

										back1();//使方块中心回到出现方块的中心
										
										t1=1;

										score = score + 3;//方块放上去分数增加
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							diamonds[d[1].x + step + 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y + step + 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 9;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
							break;
						}
					}
					break;
				}
				else if (diamonds[d[1].x][d[1].y] == 10)//如果选择的是10方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[1].x][d[1].y] = 0;//原位置数组为0
						diamonds[d[1].x + step + 2][d[1].y] = 0;
						diamonds[d[1].x][d[1].y - step - 2] = 0;

						mouse1();//方块位置和鼠标位置相同
						diamonds[d[1].x][d[1].y] = 10;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[1].x - (d[0].x + i*step1 + step_r))*(d[1].x - (d[0].x + i*step1 + step_r)) + (d[1].y - (d[0].y + j*step1 + step_r))*(d[1].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 10;

										diamonds[d[1].x][d[1].y] = 0;//原位置为0
										diamonds[d[1].x + step + 2][d[1].y] = 0;
										diamonds[d[1].x][d[1].y - step - 2] = 0;

										back1();//使方块中心回到出现方块的中心
										
										t1=1;

										score = score + 3;//方块放上去分数增加
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[1].x][d[1].y] = 0;//原位置为0
							diamonds[d[1].x + step + 2][d[1].y] = 0;
							diamonds[d[1].x][d[1].y - step - 2] = 0;
							back1();

							diamonds[d[1].x][d[1].y] = 10;//在出现方块中心重新使方块出现
							isselect1 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect1 = 0;//选择结束
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
				isselect2 = 1;//被选择
			}
			if (isselect2 == 1)
			{
				if (diamonds[d[2].x][d[2].y] == 2)//如果选择的是2方块
				{
					if (msg.mkLButton&& diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						mouse2();//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 2;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 2;

										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										back2();
										t2=1;

										score = score + 1;//方块放上去分数加一
										rt++;
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							back2();
							diamonds[d[2].x][d[2].y] = 2;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 3)//当方块为3型方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//被选择
					{
						diamonds[d[2].x][d[2].y] = 0;//方块中心为0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						diamonds[d[2].x + step + 2][d[2].y] = 0;//左右两方块也为0
						mouse2();//随鼠标移动
						diamonds[d[2].x][d[2].y] = 3;
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心和左右方块中心是否为1（即是否可放）
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 3;//使最近的底板方块中心变量以实现吸附

										diamonds[d[2].x][d[2].y] = 0;
										diamonds[d[2].x - step - 2][d[2].y] = 0;
										diamonds[d[2].x + step + 2][d[2].y] = 0;//鼠标位置及左右方块中心为0

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
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 4)//当方块为4型方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)//被选择
					{
						diamonds[d[2].x][d[2].y] = 0;//方块中心为0
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						diamonds[d[2].x][d[2].y + step + 2] = 0;//上下两方块也为0
						mouse2();
						//随鼠标移动
						diamonds[d[2].x][d[2].y] = 4;//中心方块和上下方块为4
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心和上下方块中心是否为1（即是否可放）
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1 &&
										diamonds[d[0].x + i *step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 4;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 4;//使最近的底板方块中心变量以实现吸附

										diamonds[d[2].x][d[2].y] = 0;
										diamonds[d[2].x][d[2].y - step - 2] = 0;
										diamonds[d[2].x][d[2].y + step + 2] = 0;//鼠标位置及上下方块中心为0

										back2();//使方块中心重新回到出现方块的中心
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
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 5)//如果选择的是5方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						mouse2();
						//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 5;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 5;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 5;
										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										diamonds[d[2].x][d[2].y - step - 2] = 0;

										back2();//使方块中心回到出现方块的中心
										
										t2=1;

										score = score + 2;
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 5;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 6)//如果选择的是6方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						mouse2();
						//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 6;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 6;
										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										diamonds[d[2].x - step - 2][d[2].y] = 0;

										back2();//使方块中心回到出现方块的中心
										
										t2=1;
										score = score + 2;
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 6;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 7)//如果选择的是7方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						mouse2();
						//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 7;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 7;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 7;

										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										diamonds[d[2].x - step - 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y - step - 2] = 0;

										back2();
										//使方块中心回到出现方块的中心
										t2=1;

										score = score + 3;//一个方块放上去分数加一
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 7;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 8)//如果选择的是8方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						diamonds[d[2].x - step - 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y + step + 2] = 0;
						mouse2();
						//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 8;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + (i - 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 8;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 8;

										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										diamonds[d[2].x - step - 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y + step + 2] = 0;

										back2();//使方块中心回到出现方块的中心
										
										t2=1;

										score = score + 3;//一个方块放上去分数增加
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							diamonds[d[2].x - step - 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y + step + 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 8;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 9)//如果选择的是9方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						diamonds[d[2].x + step + 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y + step + 2] = 0;
						mouse2();
						//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 9;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 9;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j + 1)*step1 + step_r] = 9;

										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										diamonds[d[2].x + step + 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y + step + 2] = 0;

										back2();//使方块中心回到出现方块的中心
										
										t2=1;

										score = score + 3;//方块放上去分数增加
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							diamonds[d[2].x + step + 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y + step + 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 9;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
							isselect2 = 0;
							break;
						}
					}
					break;
				}
				else if (diamonds[d[2].x][d[2].y] == 10)//如果选择的是10方块
				{
					if (msg.mkLButton && diamonds[msg.x][msg.y] != 1)
					{
						diamonds[d[2].x][d[2].y] = 0;//原位置数组为0
						diamonds[d[2].x + step + 2][d[2].y] = 0;
						diamonds[d[2].x][d[2].y - step - 2] = 0;
						mouse2();
						//方块位置和鼠标位置相同
						diamonds[d[2].x][d[2].y] = 10;//在新位置显示方块
					}
					else
					{
						for (i = 0; i < 10; i++)
							for (j = 0; j < 10; j++)
							{
								//判断方块是否在以10*10底板的某个方块中心为原点方块周长一半为半径的圆内
								if ((d[2].x - (d[0].x + i*step1 + step_r))*(d[2].x - (d[0].x + i*step1 + step_r)) + (d[2].y - (d[0].y + j*step1 + step_r))*(d[2].y - (d[0].y + j*step1 + step_r)) <= 15 * 15)
								{
									//判断该圆心数组是否为1
									if (diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] == 1 &&
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] == 1)
									{
										diamonds[d[0].x + i*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + (i + 1)*step1 + step_r][d[0].y + j*step1 + step_r] = 10;
										diamonds[d[0].x + i*step1 + step_r][d[0].y + (j - 1)*step1 + step_r] = 10;

										diamonds[d[2].x][d[2].y] = 0;//原位置为0
										diamonds[d[2].x + step + 2][d[2].y] = 0;
										diamonds[d[2].x][d[2].y - step - 2] = 0;

										back2();//使方块中心回到出现方块的中心
										
										t2=1;

										score = score + 3;//方块放上去分数增加
										rt++;//判断是否有方块被放上去
									}
								}
							}
						if (rt == 0)//为0时说明方块未被放上去
						{
							diamonds[d[2].x][d[2].y] = 0;//原位置为0
							diamonds[d[2].x + step + 2][d[2].y] = 0;
							diamonds[d[2].x][d[2].y - step - 2] = 0;
							back2();

							diamonds[d[2].x][d[2].y] = 10;//在出现方块中心重新使方块出现
							isselect2 = 0;//选择结束
							break;
						}
						else
						{
							rt = 0;//重新对回到中心位置附判断赋值
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

void updateWithoutInput()	//与用户输入无关的更新
{
	if (t1 == 1 && t2 == 1)
	{
		diamonds[d[1].x][d[1].y] = rand() % kinds + 2;//1位置重新随机一个方块
		diamonds[d[2].x][d[2].y] = rand() % kinds + 2;//2位置重新随机一个方块
		t1 = 0;
		t2 = 0;
	}
	judge();//对新随机的方块判断
			//当点击结束后再判断消除
	if ((isselect1 == 0) && (isselect2 == 0))
	{
		//从横排判断消除
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
				mciSendString(_T("stop jpmusic"), NULL, 0, NULL);   // 先把前面一次的音乐停止
				mciSendString(_T("close jpmusic"), NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString(_T("open D:\\popmusic.WAV alias jpmusic"), NULL, 0, NULL); // 打开跳动音乐
				mciSendString(_T("play jpmusic"), NULL, 0, NULL); // 仅播放一次
			}
			t = 0;
		}
		//从竖排判断消除
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
				mciSendString(_T("stop jpmusic"), NULL, 0, NULL);   // 先把前面一次的音乐停止
				mciSendString(_T("close jpmusic"), NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString(_T("open .\\popmusic.WAV alias jpmusic"), NULL, 0, NULL); // 打开跳动音乐
				mciSendString(_T("play jpmusic"), NULL, 0, NULL); // 仅播放一次
			}
			t = 0;
		}
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
			mciSendString(_T("open .\\putmusic.WAV alias jpmusic"), NULL, 0, NULL); // 打开跳动音乐
			mciSendString(_T("play jpmusic"), NULL, 0, NULL); // 仅播放一次
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

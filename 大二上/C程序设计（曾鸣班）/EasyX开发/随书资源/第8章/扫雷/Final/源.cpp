#include<stdlib.h>
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<windows.h> 
#include<math.h>
#include<conio.h>
#define sm_len 20
#define NBomb 10
#pragma comment(lib,"Winmm.lib")


int map[20][20];//主要地图 10表示地雷，2表示标记，3表示翻开
int mask[20][20];//地图掩码  -1表示未翻开且为空格子(init) 3表示已经翻开 1表示问号 2表示标记
int Mx, My;//鼠标位置
int mark = 0;//强制结束 0表示可以继续；1表示退出循环，游戏结束
int jud = 0;//胜利判断 0表示初始状态，未胜利；1表示胜利
SYSTEMTIME start;//计时模块



IMAGE  num_2[9];//对显示给用户的周围雷的图片进行预载入
IMAGE  bomb_2_1;//底色为灰色的地雷，用于爆炸后显示给用户看
IMAGE  bomb_2_2;//底色为红色的地雷，用于显示最后用户点击的雷的位置
IMAGE  flag_2_1;//用于表示小旗帜
IMAGE  flag_2_2;//用于标志问号的图片预载入
IMAGE  StateSetUp;//用于预载入初始化的右边状态
IMAGE  StateVictory;//用于定义胜利后右边的状态
IMAGE  StateFailure;//用于定义失败后右边的状态
IMAGE masks_2[10];//定义右边的计时器所用到的数字
IMAGE Background;//定义背景图片
IMAGE dot;//定义显示在右侧状态区域的点
IMAGE Score;//定义显示排除的地雷


//下面这里的函数是用于预载入图片
void drawinit()
{
	loadimage(&num_2[0], "./images/pg1.bmp");//用于显示已经翻开的空格
	loadimage(&num_2[1], "./images/p1.bmp");
	loadimage(&num_2[2], "./images/p2.bmp");
	loadimage(&num_2[3], "./images/p3.bmp");
	loadimage(&num_2[4], "./images/p4.bmp");
	loadimage(&num_2[5], "./images/p5.bmp");
	loadimage(&num_2[6], "./images/p6.bmp");
	loadimage(&num_2[7], "./images/p7.bmp");
	loadimage(&num_2[8], "./images/p8.bmp");
	//以上的为载入的显示周围雷的个数
	loadimage(&bomb_2_1, "./images/bomb.bmp");
	loadimage(&bomb_2_2, "./images/redbomb.bmp");
	loadimage(&Score, "./images/r1.bmp");
	//以上为点击爆炸后显示的雷及相关的图片
	loadimage(&flag_2_1, "./images/flag.bmp");
	loadimage(&flag_2_2, "./images/flag2.bmp");
	//以上为右击的问号以及旗帜标识
	loadimage(&masks_2[0], "./images/t0.bmp");
	loadimage(&masks_2[1], "./images/t1.bmp");
	loadimage(&masks_2[2], "./images/t2.bmp");
	loadimage(&masks_2[3], "./images/t3.bmp");
	loadimage(&masks_2[4], "./images/t4.bmp");
	loadimage(&masks_2[5], "./images/t5.bmp");
	loadimage(&masks_2[6], "./images/t6.bmp");
	loadimage(&masks_2[7], "./images/t7.bmp");
	loadimage(&masks_2[8], "./images/t8.bmp");
	loadimage(&masks_2[9], "./images/t9.bmp");
	loadimage(&dot, "./images/dot.bmp");
	//以上为时钟的显示
	loadimage(&StateSetUp, "./images/r2.bmp");
	loadimage(&StateVictory, "./images/r3.bmp");
	loadimage(&StateFailure, "./images/r4.bmp");
	//以上为状态栏的图片
	loadimage(&Background, "./images/bg.bmp");//背景图
	return;
}

void Setup()//数据的初始化
{
	int i, j, k;
	int x, y;//地雷的临时坐标
	srand((int)time(0));//随机布雷准备
	//以下为对地雷层以及显示层的初始化
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			mask[j][i] = -1;
		}
	}
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			map[j][i] = 0;
		}
	}
	//以下为分4个区域的分别布雷
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10 + 10;
		y = rand() % 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10;
		y = rand() % 10 + 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10 + 10;
		y = rand() % 10 + 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	//对右侧状态以及计时区的初始化
	putimage(736, 460, &dot);
	putimage(736, 481, &dot);
	putimage(640, 80, &StateSetUp);
}


void Show()//每次都会重新绘制
{
	int i, j;
	BeginBatchDraw();//开始批量绘图
	putimage(0, 0, &Background);//对背景图的初始化
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (mask[j][i] == 2 )
			{
				putimage(i * 32, j * 32, &flag_2_1);//搜索全局并且标记出旗帜
			}
			if (mask[j][i] == 1)
			{
				putimage(i * 32, j * 32, &flag_2_2);//搜索全局并且标记问号
			}
			if (map[j][i] == 3 && mask[j][i] == 0)
			{
				putimage(i * 32+1, j * 32+1, &num_2[0]);//搜索全局并且显示出翻开的格子
			}
			//搜索全局并且显示出周围雷的数量1-8
			if (map[j][i] == 11 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[1]);
			}
			if (map[j][i] == 22 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[2]);
			}
			if (map[j][i] == 33 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[3]);
			}
			if (map[j][i] == 44 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[4]);
			}
			if (map[j][i] == 55 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[5]);
			}
			if (map[j][i] == 66 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[6]);
			}
			if (map[j][i] == 77 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[7]);
			}
			if (map[j][i] == 88 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[8]);
			}
		}
	}
	EndBatchDraw();//结束绘图
}








int poi_sum(int x, int y, int size)//统计周围8个格子中雷的数量
{
	int sum;
	int nx, ny;
	int lei;
	lei = 10;
	sum = 0;

	nx = x - 1, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x - 1, ny = y;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x - 1, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}

	return sum;
}

void do_null(int x, int y)//附近空点处理，如果是空格子，则显示翻开的样子
{

	map[y][x] = 3;
	return;
}

void not_null(int x, int y, int nums)//附近非空处理，如果周围有雷，则显示周围雷的个数
{
	if (nums == 1)
	{
		map[y][x] = 11;
	}
	if (nums == 2)
	{
		map[y][x] = 22;
	}
	if (nums == 3)
	{
		map[y][x] = 33;
	}
	if (nums == 4)
	{
		map[y][x] = 44;
	}
	if (nums == 5)
	{
		map[y][x] = 55;
	}
	if (nums == 6)
	{
		map[y][x] = 66;
	}
	if (nums == 7)
	{
		map[y][x] = 77;
	}
	if (nums == 8)
	{
		map[y][x] = 88;
	}
	return;
}

void duires(int n_x, int n_y, int size)
{
	typedef struct dui {
		int x;
		int y;
	}*duis;

	duis du;
	int head, tail, leis, tx, ty, i;
	du = (duis)malloc(sizeof(dui)*size*size);

	//初始化
	head = 0;
	tail = 1;

	du[head].x = n_x;
	du[head].y = n_y;


	leis = poi_sum(n_x, n_y, size);
	if (leis > 0)//判断周围是否有雷
	{
		free(du);
		not_null(n_x, n_y, leis);
		return;
	}

	mask[n_y][n_x] = 0;

	while (head != tail)//在头尾序号不相等时，循环执行以下步骤
	{
		n_x = du[head].x;//读取头序号所指的数据
		n_y = du[head].y;//读取头序号所指的数据
		leis = poi_sum(n_x, n_y, size);
		if (leis > 0)
		{
			not_null(n_x, n_y, leis);
		}
		else
		{
			for (i = 0; i < 9; i++)//序号循环
			{

				tx = n_x + i % 3 - 1; ty = n_y + i / 3 - 1;//当前点附近的9个点
				if (tx == n_x && ty == n_y)//排除本身
				{
					continue;
				}
				if (tx >= 0 && ty >= 0 && tx <size && ty < size && mask[ty][tx] == -1)//在满足判定条件时
				{
					leis = poi_sum(tx, ty, size);//计算临时点周围的数目
					mask[ty][tx] = 0;
					if (leis > 0)
					{
						not_null(tx, ty, leis);
					}
					else
					{
						do_null(tx, ty);
						du[tail].x = tx;
						du[tail].y = ty;
						tail++;//尾指针加一
					}
				}
			}
		}
		head++;//头指针后移一位
	}
	free(du);//对应malloc
}




void Control()
{
	int x, y;
	int i, j;
	MOUSEMSG m;
	m = GetMouseMsg();//对鼠标位置的获取及处理
	if (m.uMsg == WM_MOUSEMOVE)//对鼠标的位置的跟踪，出现选中框
	{
		x = m.x / 32;
		y = m.y / 32;
		if (x < 20 && y < 20)
		{
			setlinestyle(PS_SOLID, 4);
			setlinecolor(0x58d827);
			rectangle(32 * x, 32 * y, 32 * x + 32, 32 * y + 32);
		}
	}
	if (m.uMsg == WM_LBUTTONDOWN)//左击鼠标判断
	{
		x = m.x / 32;
		y = m.y / 32;
		if (mask[y][x] != 2)//在允许显示的情况下进行操作
		{
			if (map[y][x] == 0)//在点击点没有雷的情况下
			{
				map[y][x] = 3;
				duires(x, y, 20);//传递给核心程序
			}
			for (i = 1; i < 9; i++)
			{
				if (map[y][x] == 11 * i)//如果周围有数字，则停止其再次被点击
				{
					mask[y][x] = 0;
				}
			}
			if (map[y][x] == 10)//如果点中雷判断
			{
				for (i = 0; i < 20; i++)
				{
					for (j = 0; j < 20; j++)
					{
						if (map[j][i] == 10)//对点中雷后的图形显示
						{
							if (j == y&&i == x)
							{
								putimage(i * 32 + 1, j * 32 + 1, &bomb_2_2);
							}
							else if(mask[j][i]==2)
							{
								putimage(i * 32 + 1, j * 32 + 1, &Score);
							}
							else
							{
								putimage(i * 32 + 1, j * 32 + 1, &bomb_2_1);
							}
						}
					}
				}
				mark = 1;//强制结束
				//以下为爆炸后的声音
				mciSendString("stop fmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
				mciSendString("close fmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open .\\audio\\fail.mp3 alias fmusic", NULL, 0, NULL); // 打开失败音乐
				mciSendString("play fmusic", NULL, 0, NULL); // 仅播放一次
			}
		}
		//以下为点击鼠标的声音播放
		mciSendString("stop cmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
		mciSendString("close cmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open .\\audio\\click.wav alias cmusic", NULL, 0, NULL); // 打开跳动音乐
		mciSendString("play cmusic", NULL, 0, NULL); // 仅播放一次
	}
	if (m.uMsg == WM_RBUTTONDOWN)//右击用于标记问号以及旗帜
	{
		x = m.x / 32;
		y = m.y / 32;
		if (mask[y][x] != 2 && mask[y][x] != 1 && mask[y][x] != 0)
		{
			mask[y][x] = 2;
		}
		else if (mask[y][x] == 1)//标记旗帜
		{
			mask[y][x] = -1;
		}
		else if (mask[y][x] == 2)//标记问号
		{
			mask[y][x] = 1;
		}
	}
}



void Time()
{
	int t1, t2;
	int i, j;
	int a, b;
	int sum;
	SYSTEMTIME ti;
	sum = 0;
	GetLocalTime(&ti);		// 获取当前时间
	sum += ti.wHour - start.wHour;
	sum *= 60;
	sum += ti.wMinute - start.wMinute;
	sum *= 60;
	sum += ti.wSecond - start.wSecond;
	i = 0;
	j = 0;
	t1 = sum;
	t2 = sum / 60;//对时间分钟和秒数的换算
	while (i != 2)
	{
		if (i == 0)
		{
			t1 = sum % 60;
		}
		a = t1 % 10;
		putimage(780 - 32 * i, 450, &masks_2[a]);//显示秒数
		t1 = t1 / 10;
		i++;
	}
	while (j != 2)
	{
		b = t2 % 10;
		putimage(700 - 32 * j, 450, &masks_2[b]);//显示分钟
		t2 = t2 / 10;
		j++;
	}
}


void Judge()
{
	int i, j;
	int cnt;
	cnt = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (mask[i][j] == 2 && map[i][j] == 10)//胜利判断
			{
				cnt++;
			}
		}
	}
	if (cnt == 4 * NBomb)//胜利结束游戏，并播放音乐
	{
		mark = 1;
		jud = 1;
		mciSendString("stop wmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
		mciSendString("close wmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open .\\audio\\win.mp3 alias wmusic", NULL, 0, NULL); // 打开胜利音乐
		mciSendString("play wmusic", NULL, 0, NULL); // 仅播放一次
	}
}

int main()
{
	int op = 1;
	char input;
	initgraph(840, 640);//初始化画图
	GetLocalTime(&start);//获取系统时间
	drawinit();//预载入图片
	Setup();//初始化程序
	do//用于重新启动程序
	{
		while (1)
		{
			Judge();
			Show();
			Time();
			Control();	
			Sleep(5);
			if (mark == 1)//强制结束
			{
				if (jud == 1)
				{
					putimage(640, 80, &StateVictory);//显示胜利图片
				}
				else
				{
					putimage(640, 80, &StateFailure);//显示失败图片
				}
				input = _getch();//接受用户的判断，是否重新开始游戏
				if (input == 'y')
				{
					op = 1;
					mark = 0;
					jud = 0;
					initgraph(840, 640);
					GetLocalTime(&start);
					drawinit();
					Setup();
				}
				if (input == 'n')
				{
					op = 0;
					break;
				}
			}
		}
	} while (op==1);//结束游戏
	closegraph();//关闭绘图
	return 0;
}
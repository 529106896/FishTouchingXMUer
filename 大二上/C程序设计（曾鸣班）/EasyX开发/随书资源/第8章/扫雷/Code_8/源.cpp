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


int map[20][20];//主要地图 10表示地雷，2表示标记，3表示翻开
int mask[20][20];//地图掩码  -1表示未翻开且为空格子(init) 3表示已经翻开 1表示问号 2表示标记
int bombx, bomby;
int Mx, My;//鼠标位置
int mark = 0;//强制结束
int jud = 0;//胜利判断
SYSTEMTIME start;//计时模块



IMAGE  num_2[9];//0_==un_indented ++
IMAGE  bomb_2_1;//grey
IMAGE  bomb_2_2;//red
IMAGE  bomb_2_3;//big
IMAGE  flag_2_1;//warn
IMAGE  flag_2_2;//?
IMAGE  soved_2;
IMAGE  win_2;
IMAGE  main_2;//center pic
IMAGE  r2;
IMAGE  r3;
IMAGE  r4;

IMAGE masks_2[10];
IMAGE mask_poi;
IMAGE mask_bigbomb;
IMAGE mask_2;// mask pic
IMAGE bg;
IMAGE dot;
IMAGE Score;


void drawinit(/*int size*/)
{
	loadimage(&num_2[0], "./images/pg1.bmp");
	loadimage(&num_2[1], "./images/p1.bmp");
	loadimage(&num_2[2], "./images/p2.bmp");
	loadimage(&num_2[3], "./images/p3.bmp");
	loadimage(&num_2[4], "./images/p4.bmp");
	loadimage(&num_2[5], "./images/p5.bmp");
	loadimage(&num_2[6], "./images/p6.bmp");
	loadimage(&num_2[7], "./images/p7.bmp");
	loadimage(&num_2[8], "./images/p8.bmp");

	loadimage(&bomb_2_1, "./images/bomb.bmp");
	loadimage(&bomb_2_2, "./images/redbomb.bmp");
	loadimage(&bomb_2_3, "./images/icon.jpg");


	loadimage(&flag_2_1, "./images/flag.bmp");
	loadimage(&flag_2_2, "./images/flag2.bmp");


	loadimage(&soved_2, "./images/grey.bmp");
	loadimage(&win_2, "./images/wins.bmp");


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

	loadimage(&mask_poi, "./images/m0.bmp");
	loadimage(&mask_bigbomb, "./m_bomb.bmp");
	loadimage(&dot, "./images/dot.bmp");
	loadimage(&Score, "./images/r1.bmp");
	loadimage(&r2, "./images/r2.bmp");
	loadimage(&r3, "./images/r3.bmp");
	loadimage(&r4, "./images/r4.bmp");

	loadimage(&main_2, "./images/wins.bmp");
	loadimage(&mask_2, "./images/wins.bmp");
	loadimage(&bg, "./images/bg.bmp");
	return;
}

void Setup()
{
	int i, j, k;
	int x, y;//地雷的临时坐标
	srand((int)time(0));
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
	putimage(736, 460, &dot);
	putimage(736, 481, &dot);
	putimage(640, 80, &r2);
}


void Show()
{
	int i, j;
	BeginBatchDraw();
	putimage(0, 0, &bg);
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (mask[j][i] == 2 )
			{
				putimage(i * 32, j * 32, &flag_2_1);//标记
			}
			if (mask[j][i] == 1)
			{
				putimage(i * 32, j * 32, &flag_2_2);//标记?
			}
			if (map[j][i] == 3 && mask[j][i] == 0)
			{
				putimage(i * 32+1, j * 32+1, &num_2[0]);//翻开的样子
			}
			if (map[j][i] == 11 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[1]);//标记1
			}
			if (map[j][i] == 22 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[2]);//标记2
			}
			if (map[j][i] == 33 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[3]);//标记3
			}
			if (map[j][i] == 44 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[4]);//标记4
			}
			if (map[j][i] == 55 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[5]);//标记5
			}
			if (map[j][i] == 66 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[6]);//标记6
			}
			if (map[j][i] == 77 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[7]);//标记7
			}
			if (map[j][i] == 88 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[8]);//标记8
			}
		}
	}
	EndBatchDraw();
}







//zhang
int poi_sum(int x, int y, int size)
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

void do_null(int x, int y)//附近空点处理
{

	map[y][x] = 3;
	return;
}

void not_null(int x, int y, int nums)//附近非空处理
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

	//init
	head = 0;
	tail = 1;

	du[head].x = n_x;
	du[head].y = n_y;


	leis = poi_sum(n_x, n_y, size);
	if (leis > 0)
	{
		free(du);
		not_null(n_x, n_y, leis);
		return;
	}

	mask[n_y][n_x] = 0;

	while (head != tail)
	{
		n_x = du[head].x;
		n_y = du[head].y;
		leis = poi_sum(n_x, n_y, size);
		if (leis > 0)
		{
			not_null(n_x, n_y, leis);
		}
		else
		{
			for (i = 0; i < 9; i++)
			{

				tx = n_x + i % 3 - 1; ty = n_y + i / 3 - 1;
				if (tx == n_x && ty == n_y)
				{
					continue;
				}
				if (tx >= 0 && ty >= 0 && tx <size && ty < size && mask[ty][tx] == -1)
				{
					leis = poi_sum(tx, ty, size);
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
						tail++;
					}
				}

			}

		}
		head++;
	}
	free(du);
}




void Control()
{
	int x, y;
	int i, j;
	MOUSEMSG m;
	m = GetMouseMsg();
	if (m.uMsg == WM_MOUSEMOVE)
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
	if (m.uMsg == WM_LBUTTONDOWN)
	{
		x = m.x / 32;
		y = m.y / 32;
		if (mask[y][x] != 2)
		{
			if (map[y][x] == 0)
			{
				map[y][x] = 3;
				duires(x, y, 20);
			}
			for (i = 1; i < 9; i++)
			{
				if (map[y][x] == 11 * i)
				{
					mask[y][x] = 0;
				}
			}
			if (map[y][x] == 10)
			{
				for (i = 0; i < 20; i++)
				{
					for (j = 0; j < 20; j++)
					{
						if (map[j][i] == 10)
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
				mark = 1;
			}
		}
	}
	if (m.uMsg == WM_RBUTTONDOWN)
	{
		x = m.x / 32;
		y = m.y / 32;
		if (mask[y][x] != 2 && mask[y][x] != 1 && mask[y][x] != 0)
		{
			mask[y][x] = 2;
		}
		else if (mask[y][x] == 1)
		{
			mask[y][x] = -1;
		}
		else if (mask[y][x] == 2)
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
	t2 = sum / 60;
	while (i != 2)
	{
		if (i == 0)
		{
			t1 = sum % 60;
		}
		a = t1 % 10;
		putimage(780 - 32 * i, 450, &masks_2[a]);
		t1 = t1 / 10;
		i++;
	}
	while (j != 2)
	{
		b = t2 % 10;
		putimage(700 - 32 * j, 450, &masks_2[b]);
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
			if (mask[i][j] == 2)
			{
				cnt++;
			}
		}
	}
	if (cnt == 4 * NBomb)
	{
		mark = 1;
		jud = 1;
	}
}

int main()
{
	int op = 1;
	initgraph(840, 640);
	GetLocalTime(&start);
	drawinit(/*int size*/);
	Setup();
	do
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
					putimage(640, 80, &r3);
				}
				else
				{
					putimage(640, 80, &r4);
				}
				char input;
				input = _getch();
				if (input == 'y')
				{
					op = 1;
					mark = 0;
					initgraph(840, 640);
					GetLocalTime(&start);
					drawinit(/*int size*/);
					Setup();
				}
				if (input == 'n')
				{
					op = 0;
					break;
				}
			}
		}
	} while (op==1);
	closegraph();
	return 0;
}
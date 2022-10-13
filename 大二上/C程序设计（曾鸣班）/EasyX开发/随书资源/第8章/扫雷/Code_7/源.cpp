#include<stdlib.h>
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<windows.h> 
#include<math.h>
#include<conio.h>
#define sm_len 20


int map[20][20];//主要地图 10表示地雷，2表示标记，3表示翻开
int mask[20][20];//地图掩码  -1表示未翻开且为空格子(init) 3表示已经翻开 1表示问号 2表示标记
int bombx, bomby;
int Mx, My;//鼠标位置
int mark = 0;//强制结束
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

IMAGE masks_2[9];
IMAGE mask_poi;
IMAGE mask_bigbomb;
IMAGE mask_2;// mask pic
IMAGE bg;


void drawinit(/*int size*/)
{
	loadimage(&num_2[0], "./images/0.bmp");
	loadimage(&num_2[1], "./images/1.bmp");
	loadimage(&num_2[2], "./images/2.bmp");
	loadimage(&num_2[3], "./images/3.bmp");
	loadimage(&num_2[4], "./images/4.bmp");
	loadimage(&num_2[5], "./images/5.bmp");
	loadimage(&num_2[6], "./images/6.bmp");
	loadimage(&num_2[7], "./images/7.bmp");
	loadimage(&num_2[8], "./images/8.bmp");

	loadimage(&bomb_2_1, "./images/bomb.bmp");
	loadimage(&bomb_2_2, "./images/redbomb.bmp");
	loadimage(&bomb_2_3, "./images/icon.jpg");


	loadimage(&flag_2_1, "./images/flag.bmp");
	loadimage(&flag_2_2, "./images/flag2.bmp");


	loadimage(&soved_2, "./images/grey.bmp");
	loadimage(&win_2, "./images/wins.bmp");


	loadimage(&masks_2[0], "./images/m0.bmp");
	loadimage(&masks_2[1], "./images/m1.bmp");
	loadimage(&masks_2[2], "./images/m2.bmp");
	loadimage(&masks_2[3], "./images/m3.bmp");
	loadimage(&masks_2[4], "./images/m4.bmp");
	loadimage(&masks_2[5], "./images/m5.bmp");
	loadimage(&masks_2[6], "./images/m6.bmp");
	loadimage(&masks_2[7], "./images/m7.bmp");
	loadimage(&masks_2[8], "./images/m8.bmp");

	loadimage(&mask_poi, "./images/m0.bmp");
	loadimage(&mask_bigbomb, "./m_bomb.bmp");




	loadimage(&main_2, "./images/wins.bmp");
	loadimage(&mask_2, "./images/wins.bmp");
	loadimage(&bg, "./images/bg.bmp");
	return;
}

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	return;
}

void Setup()
{
	int i, j, k;
	int x, y;//地雷的临时坐标
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
	for (k = 0; k < 3; k++)
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
	for (k = 0; k < 3; k++)
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
	for (k = 0; k < 3; k++)
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
	for (k = 0; k < 3; k++)
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
}


void Show()
{
	int i, j;
	gotoxy(0, 0);
	BeginBatchDraw();
	//for (i = 0; i < 640; i = i + 32)
	//{
	//	for (j = 0; j < 640; j = j + 32)
	//	{
	//		putimage(j, i, &soved_2);
	//	}
	//}
	//for (i = 0; i < 640; i = i + 32)
	//{
	//	for (j = 0; j < 640; j = j + 32)
	//	{
	//		setlinestyle(PS_SOLID, 1);
	//		setcolor(BLACK);
	//		rectangle(j, i, j + 32, i + 32);
	//	}
	//}
	putimage(0, 0, &bg);
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (map[j][i] == 2 && mask[j][i] == 0)
			{
				putimage(i * 32, j * 32, &flag_2_1);//标记
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
			if (map[j][i] == 10 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &bomb_2_2);//bomb
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
	int i;
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
			mask[y][x] = 0;
			mark = 1;
		}
	}
	if (m.uMsg == WM_RBUTTONDOWN)
	{
		x = m.x / 32;
		y = m.y / 32;		
		map[y][x] = 2;
		mask[y][x] = 0;
	}
}



void Judge()
{

}




int main()
{
	initgraph(840, 640);
	drawinit(/*int size*/);
	Setup();
	while (1)
	{
		Show();
		Control();
		//Auto();
		Judge();
		Sleep(5);
		if (mark == 1)//强制结束
		{
			break;
		}
	}
	system("pause");
	return 0;
}
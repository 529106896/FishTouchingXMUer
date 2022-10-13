#include<stdlib.h>
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<windows.h> 
#include<math.h>
#define sm_len 20


int map[20][20];//主要地图
int mask[20][20];//地图掩码  -1表示未翻开且为空格子 0表示已经翻开 1表示问号 2表示地雷区
int a[640][640] = { 0 };//储存地雷的有关信息,1为有地雷但不显示，2为标记，3为有翻开，0为正常
int bombx, bomby;
int Mx, My;//鼠标位置



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
IMAGE	mask_2;// mask pic


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
	//SetWorkingImage(&main_2);
	//setbkcolor(BLACK);
	//clearcliprgn();
	//SetWorkingImage(&mask_2);
	//setbkcolor(BLACK);
	//	clearcliprgn();
	//SetWorkingImage(NULL);
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
	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			mask[j][i] = -1;
		}
	}
	for (i = 0; i < 641; i = i + 32)
	{
		for (j = 0; j < 641; j = j + 32)
		{
			putimage(i, j, &soved_2);
		}
	}
	gotoxy(0, 0);
	for (i = 0; i < 641; i = i + 32)
	{
		for (j = 0; j < 641; j = j + 32)
		{
			setcolor(BLACK);
			rectangle(i, j, i + 32, j + 32);
		}
	}
}

//void draw2_main(int xs, int ys)
//{
//	int i, j;
//	putimage(0, 0, &mask_2);
//	SetWorkingImage(&mask_2);
//
//	ys -= 12;
//	xs -= 12;
//
//	for (j = 0; j < ys; j++)
//	{
//		for (i = 0; i < xs; i++)
//		{
//
//			if (map[j][i]<9)
//			{
//				putimage(i * sm_len, j * sm_len, &masks_2[map[j][i]]);
//			}
//			else
//			{
//				putimage(i * sm_len, j * sm_len, &mask_poi);
//			}
//
//		}
//	}
//	SetWorkingImage(&main_2);
//	for (j = 0; j < ys; j++)
//	{
//		for (i = 0; i < xs; i++)
//		{
//
//			if (map[j][i]<9)
//			{
//				putimage(i * sm_len, j * sm_len, &num_2[map[j][i]]);
//			}
//			else
//			{
//				switch (map[j][i])
//				{
//				case 10:
//					putimage(i * sm_len, j * sm_len, &flag_2_1);
//					break;
//				case 11:
//					putimage(i * sm_len, j * sm_len, &flag_2_2);
//					break;
//				case 12:
//					putimage(i * sm_len, j * sm_len, &bomb_2_1);
//					break;
//				case 13:
//					putimage(i * sm_len, j * sm_len, &bomb_2_2);
//					break;
//				}
//			}
//
//		}
//	}
//	SetWorkingImage(NULL);
//	setaspectratio(1.6, 1.6);
//	putimage(0, 0, &mask_2, NOTSRCERASE);
//	putimage(0, 0, &main_2, SRCERASE);
//	setaspectratio(1, 1);
//	return;
//}


//void Setup()
//{
//	int i, j;
//	int bombtemp;//地雷的随机位置
//	initgraph(640, 640);
//	for (i = 0; i < 32; i++)
//	{
//		for (j = 0; j < 32; j++)
//		{
//
//			map[i][j] = (i + j) % 8 + 1;
//		}
//	}
//	draw2_init(32);
//	draw2_main(32, 32);
//	a[350][350] = 1;
//	bombtemp = rand() % 20;
//	bombx = bombtemp * 32;
//	bombtemp = rand() % 20;
//	bomby = bombtemp * 32;
//	a[bombx][bomby] = 1;
//}




void Show()
{
	int i, j;
	for (i = 0; i <= 608; i = i + 32)
	{
		for (j = 0; j <= 608; j = j + 32)
		{
			if (a[i][j] == 0)
			{
				rectangle(i, j, i + 32, j + 32);//初始化的样子
			}
			if (a[i][j] == 1)
			{
				rectangle(i, j, i + 32, j + 32);//有地雷但不显示
			}
			if (a[i][j] == 2)
			{
				rectangle(i, j, i+10,j+10);//标记
			}
			if (a[i][j] == 3)
			{
				putimage(i , j , &num_2[0]);//翻开的样子
			}
		}
	}
}







//zhang
void duires(int n_x, int n_y, int size);//循环判断队列
int poi_sum(int x, int y, int size);//探测周围地雷数
void do_null(int x, int y);
void not_null(int x, int y, int nums);



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
	x = x * 32;
	y = y * 32;
	a[x][y] = 3;
	return;
}

void not_null(int x, int y, int nums)//附近非空处理
{
	return;
}

void duires(int n_x, int n_y, int size)
{
	typedef struct dui {
		int x;
		int y;
	}*duis;

	dui du[1000];
	int head, tail, leis, tx, ty;

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

			tx = n_x - 1; ty = n_y - 1;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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

			tx = n_x - 1; ty = n_y;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
			tx = n_x - 1; ty = n_y + 1;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
			tx = n_x; ty = n_y + 1;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
			tx = n_x + 1; ty = n_y + 1;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
			tx = n_x + 1; ty = n_y;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
			tx = n_x + 1; ty = n_y - 1;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
			tx = n_x; ty = n_y - 1;
			if (mask[ty][tx] == -1 && tx >= 0 && ty >= 0 && tx <size && ty < size)
			{
				leis = poi_sum(tx, ty, size);
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
		head++;
	}
}




void Control()
{
	int x, y;
	int tempx, tempy;
	MOUSEMSG m;
	m = GetMouseMsg();
	if (m.uMsg == WM_MOUSEMOVE)
	{
		putpixel(m.x, m.y, WHITE);
	}
	if (m.uMsg == WM_LBUTTONDOWN)
	{
		/*tempx = m.x / 32;
		x = tempx * 32;
		tempy = m.y / 32;
		y = tempy * 32;
		a[x][y] = 3;*/
		x = m.x / 32;
		y = m.y / 32;
		duires(x, y, 20);
	}
	/*Mx = m.x;
	My = m.y;*/
}


void Auto()
{
	int x, y;
	x = Mx/32, y = My/32;
	duires(x, y, 20);
}







void Judge()
{

}




int main()
{
	initgraph(640, 640);
	drawinit(/*int size*/);
	Setup();
	while (1)
	{
		Show();
		Control();
		//Auto();
		Judge();
	}
	system("pause");
	return 0;
}
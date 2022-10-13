#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#define sm_len 20

int map[32][32];//主要地图
int mask[32][32] = { 0 };//地图掩码



void draw2_main(int xs, int ys);
void draw2_init(int size);
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
int p2_size;


int main()
{
	int i, j;
	initgraph(640, 640);
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 32; j++)
		{
			
				map[i][j] = (i + j)%8+1;
		}
	}
	draw2_init(32);
	draw2_main(32,32);
	while (1);
	return 0;
}

void draw2_init(int size)
{
	p2_size = size;
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




	loadimage(&main_2, "./images/wins.bmp");//! big/small defined here  !
	loadimage(&mask_2, "./images/bak.bmp");
	SetWorkingImage(&main_2);
	setbkcolor(BLACK);
	clearcliprgn();
	SetWorkingImage(&mask_2);
	setbkcolor(BLACK);
//	clearcliprgn();
	SetWorkingImage(NULL);
	return;
}

void draw2_main(int xs, int ys)
{
	int i, j;
	putimage(0, 0, &mask_2);
	SetWorkingImage(&mask_2);
	
	ys -= 12;
	xs -= 12;

	for (j = 0; j < ys; j++)
	{
		for (i = 0; i < xs; i++)
		{

			if(map[j][i]<9)
			{
				putimage(i * sm_len, j * sm_len, &masks_2[map[j][i]]);
			}
			else
			{
				putimage(i * sm_len, j * sm_len, &mask_poi);
			}
			
		}
	}
	SetWorkingImage(&main_2);
	for (j = 0; j < ys; j++)
	{
		for (i = 0; i < xs; i++)
		{

			if(map[j][i]<9)
			{
				putimage(i * sm_len, j * sm_len, &num_2[map[j][i]]);
			}
			else
			{
				switch (map[j][i])
				{
				case 10: 
					putimage(i * sm_len, j * sm_len, &flag_2_1); 
					break;
				case 11: 
					putimage(i * sm_len, j * sm_len, &flag_2_2); 
					break;
				case 12: 
					putimage(i * sm_len, j * sm_len, &bomb_2_1);
					break;
				case 13: 
					putimage(i * sm_len, j * sm_len, &bomb_2_2); 
					break;
				}
			}
			
		}
	}
	SetWorkingImage(NULL); 
	setaspectratio(1.6, 1.6);
	putimage(0, 0, &mask_2, NOTSRCERASE);
	putimage(0, 0, &main_2, SRCERASE);
	setaspectratio(1, 1);
	return;
}
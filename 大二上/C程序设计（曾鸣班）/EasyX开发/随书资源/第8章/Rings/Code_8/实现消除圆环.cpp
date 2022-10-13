#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tlhelp32.h>
#pragma comment(lib,"Winmm.lib")

//123分别代表红黄蓝，
int z;//测试数据
int high,wedith;
int x,y;	//坐标
int gap;	//点与点之间的间距
int i,j,smallC,middleC,largeC;		//循环使用的变量
int size;	//点到能拖动边界的距离
int num=0;
int color_size;
MOUSEMSG m;
COLORREF Defcolor[4];


struct Circle
{
	int x;
	int y;
	int get;
	int exist;
	int type[3];
	int color[3];
};

struct point
{
	int x;
	int y;
	int getcircle[3];
	int getcolor[3];
};

point p[10];
Circle c[4];



void back1()	//圆环1回到初始位置
{
	c[1].x=p[1].x;
	c[1].y=p[9].y+gap;	
}

void back2()	//圆环2回到初始位置
{
	c[2].x=p[2].x;
	c[2].y=p[9].y+gap;	
}

void back3()	//圆环3回到初始位置
{
	c[3].x=p[3].x;
	c[3].y=p[9].y+gap;	
}


void stay1()	//圆环1在鼠标弹起位置定位到临近点
{
	c[1].x=p[i].x;
	c[1].y=p[i].y;
}

void stay2()	//圆环2在鼠标弹起位置定位到临近点
{
	c[2].x=p[i].x;
	c[2].y=p[i].y;
}

void stay3()	//圆环3在鼠标弹起位置定位到临近点
{
	c[3].x=p[i].x;
	c[3].y=p[i].y;
}

void out(int n)
{
	c[n].x=-100;
	c[n].y=-100;
}

void CleanDouble_type_one(int clean_color)	//消除第一行和第一列
{
	for(i=1;i<=4;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[7].getcolor[j]==clean_color)
		{
			p[7].getcolor[j]=0;
			p[7].getcircle[j]=0;
		}
	}
	mciSendString("stop music1", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music1", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music1", NULL, 0, NULL);
	mciSendString("play music1", NULL, 0, NULL); // 仅播放一次

}
void CleanDouble_type_two(int clean_color)	//消除第一行和第二列
{
	for(i=1;i<=3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[5].getcolor[j]==clean_color)
		{
			p[5].getcolor[j]=0;
			p[5].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[8].getcolor[j]==clean_color)
		{
			p[8].getcolor[j]=0;
			p[8].getcircle[j]=0;
		}
	}
	mciSendString("stop music2", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music2", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music2", NULL, 0, NULL);
	mciSendString("play music2", NULL, 0, NULL); // 仅播放一次
}
void CleanDouble_type_three(int clean_color)	//消除第一行和第三列
{
	for(i=1;i<=3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[6].getcolor[j]==clean_color)
		{
			p[6].getcolor[j]=0;
			p[6].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[9].getcolor[j]==clean_color)
		{
			p[9].getcolor[j]=0;
			p[9].getcircle[j]=0;
		}
	}
	mciSendString("stop music3", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music3", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music3", NULL, 0, NULL);
	mciSendString("play music3", NULL, 0, NULL); // 仅播放一次
}

void CleanDouble_type_four(int clean_color)	//消除第二行和第一列
{
	for(i=1;i<=7;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[5].getcolor[j]==clean_color)
		{
			p[5].getcolor[j]=0;
			p[5].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[6].getcolor[j]==clean_color)
		{
			p[6].getcolor[j]=0;
			p[6].getcircle[j]=0;
		}
	}
	mciSendString("stop music4", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music4", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music4", NULL, 0, NULL);
	mciSendString("play music4", NULL, 0, NULL); // 仅播放一次
}

void CleanDouble_type_five(int clean_color)	//消除第二行和第二列
{
	for(i=2;i<=8;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[4].getcolor[j]==clean_color)
		{
			p[4].getcolor[j]=0;
			p[4].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[6].getcolor[j]==clean_color)
		{
			p[6].getcolor[j]=0;
			p[6].getcircle[j]=0;
		}
	}
	mciSendString("stop music5", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music5", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music5", NULL, 0, NULL);
	mciSendString("play music5", NULL, 0, NULL); // 仅播放一次
}

void CleanDouble_type_six(int clean_color)	//消除第二行和第三列
{
	for(i=3;i<=9;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[4].getcolor[j]==clean_color)
		{
			p[4].getcolor[j]=0;
			p[4].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[5].getcolor[j]==clean_color)
		{
			p[5].getcolor[j]=0;
			p[5].getcircle[j]=0;
		}
	}
	mciSendString("stop music6", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music6", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music6", NULL, 0, NULL);
	mciSendString("play music6", NULL, 0, NULL); // 仅播放一次
}

void CleanDouble_type_seven(int clean_color)	//消除第三行和第一列
{
	for(i=1;i<=7;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[8].getcolor[j]==clean_color)
		{
			p[8].getcolor[j]=0;
			p[8].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[9].getcolor[j]==clean_color)
		{
			p[9].getcolor[j]=0;
			p[9].getcircle[j]=0;
		}
	}
	mciSendString("stop music7", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music7", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music7", NULL, 0, NULL);
	mciSendString("play music7", NULL, 0, NULL); // 仅播放一次
}
void CleanDouble_type_eight(int clean_color)	//消除第三行和第二列
{
	for(i=7;i<=9;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[2].getcolor[j]==clean_color)
		{
			p[2].getcolor[j]=0;
			p[2].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[5].getcolor[j]==clean_color)
		{
			p[5].getcolor[j]=0;
			p[5].getcircle[j]=0;
		}
	}
	mciSendString("stop music8", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music8", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music8", NULL, 0, NULL);
	mciSendString("play music8", NULL, 0, NULL); // 仅播放一次
}
void CleanDouble_type_nine(int clean_color)	//消除第三行和第三列
{
	for(i=7;i<=9;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[3].getcolor[j]==clean_color)
		{
			p[3].getcolor[j]=0;
			p[3].getcircle[j]=0;
		}
	}
	for(j=0;j<3;j++)
	{
		if(p[6].getcolor[j]==clean_color)
		{
			p[6].getcolor[j]=0;
			p[6].getcircle[j]=0;
		}
	}
	mciSendString("stop music9", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close music9", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias music9", NULL, 0, NULL);
	mciSendString("play music9", NULL, 0, NULL); // 仅播放一次
}
void judgeclean_type_one(int judge_color)	//判断第一行第一列颜色是否相同
{
	num=0;
	for(i=1;i<=4;i++)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[7].getcircle[j]==1&&p[7].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_one(judge_color);
	}
}



void judgeclean_type_two(int judge_color)	//判断第一行第二列颜色是否相同

{
	num=0;
	for(i=1;i<=3;i++)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[5].getcircle[j]==1&&p[5].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[8].getcircle[j]==1&&p[8].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_two(judge_color);
	}
}


void judgeclean_type_three(int judge_color)	//判断第一行第三列颜色是否相同

{
	num=0;
	for(i=1;i<=3;i++)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[6].getcircle[j]==1&&p[6].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[9].getcircle[j]==1&&p[9].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_three(judge_color);
	}
}

void judgeclean_type_four(int judge_color)	//判断第二行第一列颜色是否相同

{
	num=0;
	for(i=1;i<=7;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[5].getcircle[j]==1&&p[5].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[6].getcircle[j]==1&&p[6].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_four(judge_color);
	}
}

void judgeclean_type_five(int judge_color)	//判断第二行第二列颜色是否相同

{
	num=0;
	for(i=2;i<=8;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[4].getcircle[j]==1&&p[4].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[6].getcircle[j]==1&&p[6].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_five(judge_color);
	}
}

void judgeclean_type_six(int judge_color)	//判断第二行第三列颜色是否相同

{
	num=0;
	for(i=3;i<=9;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[4].getcircle[j]==1&&p[4].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[5].getcircle[j]==1&&p[5].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_six(judge_color);
	}
}

void judgeclean_type_seven(int judge_color)	//判断第三行第一列颜色是否相同

{
	num=0;
	for(i=1;i<=7;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[8].getcircle[j]==1&&p[8].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[9].getcircle[j]==1&&p[9].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_seven(judge_color);
	}
}

void judgeclean_type_eight(int judge_color)	//判断第三行第二列颜色是否相同
{
	num=0;
	for(i=7;i<=9;i++)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[2].getcircle[j]==1&&p[2].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[5].getcircle[j]==1&&p[5].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_eight(judge_color);
	}
}

void judgeclean_type_nine(int judge_color)	//判断第三行第三列颜色是否相同

{
	num=0;
	for(i=7;i<=9;i++)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[3].getcircle[j]==1&&p[3].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	for(j=0;j<3;j++)
	{
		if( p[6].getcircle[j]==1&&p[6].getcolor[j]==judge_color)
		{
			num++;
			break;
		}
	}
	if(num==5)
	{
		CleanDouble_type_nine(judge_color);
	}
}



void Clear_FullPoint()	//消除同一点上三个圈颜色相同的环
{
	for (i=1;i<=9;i++)
	{
		if ((p[i].getcircle[0]==1 &&p[i].getcircle[1]==1 &&p[i].getcircle[2]==1) &&(p[i].getcolor[0]==1 &&p[i].getcolor[1]==1 &&p[i].getcolor[2]==1) )//同一点三个圆环颜色为红色
		{
			for (j=0;j<3;j++)
			{
				p[i].getcircle[j]=0;
				p[i].getcolor[j]=0;
			}
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open E:\\Rings\\xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

		if ((p[i].getcircle[0]==1 &&p[i].getcircle[1]==1 &&p[i].getcircle[2]==1) &&(p[i].getcolor[0]==2 &&p[i].getcolor[1]==2 &&p[i].getcolor[2]==2) )//同一点三个圆环颜色为蓝色
		{
			for (j=0;j<3;j++)
			{
				p[i].getcircle[j]=0;
				p[i].getcolor[j]=0;
			}
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open E:\\Rings\\xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

		if ((p[i].getcircle[0]==1 &&p[i].getcircle[1]==1 &&p[i].getcircle[2]==1) &&(p[i].getcolor[0]==3 &&p[i].getcolor[1]==3 &&p[i].getcolor[2]==3) )//同一点三个圆环颜色为黄色
		{
			for (j=0;j<3;j++)
			{
				p[i].getcircle[j]=0;
				p[i].getcolor[j]=0;
			}
			mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open E:\\Rings\\xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
			mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}

		if ((p[i].getcircle[0]==1 &&p[i].getcircle[1]==1 &&p[i].getcircle[2]==1) &&(p[i].getcolor[0]==4 &&p[i].getcolor[1]==4 &&p[i].getcolor[2]==4) )//同一点三个圆环颜色为绿色
		{
			for (j=0;j<3;j++)
			{
				p[i].getcircle[j]=0;
				p[i].getcolor[j]=0;
			}
		mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
		mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open E:\\Rings\\xtxiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
		mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
		}
	
	}
}
void CleanHeng_1(int clean_color)	//消除第一行
{
	for(i=1;i<=3;i++)
	{
		for(j=0;j<3;j++)
		{
		if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
mciSendString("stop xcmusic1", NULL, 0, NULL);   // 先把前面一次的音乐停止
mciSendString("close xcmusic1", NULL, 0, NULL); // 先把前面一次的音乐关闭
mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic1", NULL, 0, NULL);
mciSendString("play xcmusic1", NULL, 0, NULL); // 仅播放一次
}
void CleanHeng_2(int clean_color)	//消除第二行
{
	for(i=4;i<=6;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
mciSendString("stop xcmusic2", NULL, 0, NULL);   // 先把前面一次的音乐停止
mciSendString("close xcmusic2", NULL, 0, NULL); // 先把前面一次的音乐关闭
mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic2", NULL, 0, NULL);
mciSendString("play xcmusic2", NULL, 0, NULL); // 仅播放一次
}
void CleanHeng_3(int clean_color)	//消除第三行
{
	for(i=7;i<=9;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
mciSendString("stop xcmusic3", NULL, 0, NULL);   // 先把前面一次的音乐停止
mciSendString("close xcmusic3", NULL, 0, NULL); // 先把前面一次的音乐关闭
mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic3", NULL, 0, NULL);
mciSendString("play xcmusic3", NULL, 0, NULL); // 仅播放一次
}
void JudgeHeng_1(int judge_color)	//判断第一行三点是否有颜色相同的环
{
	num=0;
	for(i=1;i<=3;i++)
	{
		for(j=0;j<3;j++)
		{
			if( p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	if(num==3)
	{
		CleanHeng_1(judge_color);
	}
}


void JudgeHeng_2(int judge_color)	//判断第二行三点是否有颜色相同的环
{
	num=0;
	for(i=4;i<=6;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	if(num==3)
	{
		CleanHeng_2(judge_color);
	}
}

void JudgeHeng_3(int judge_color)	//判断第三行三点是否有颜色相同的环
{
	num=0;
	for(i=7;i<=9;i++)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1&&p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	if(num==3)
	{
		CleanHeng_3(judge_color);
	}
}


void CleanShu_1(int clean_color)	//消除第一列
{
	for(i=1;i<=7;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	mciSendString("stop xcmusic4", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic4", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic4", NULL, 0, NULL);
	mciSendString("play xcmusic4", NULL, 0, NULL); // 仅播放一次
}
void CleanShu_2(int clean_color)	//消除第二列
{
	for(i=2;i<=8;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	mciSendString("stop xcmusic5", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic5", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic5", NULL, 0, NULL);
	mciSendString("play xcmusic5", NULL, 0, NULL); // 仅播放一次
}
void CleanShu_3(int clean_color)	//消除第三列
{
	for(i=3;i<=9;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	mciSendString("stop xcmusic6", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic6", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic6", NULL, 0, NULL);
	mciSendString("play xcmusic6", NULL, 0, NULL); // 仅播放一次
}
void JudgeShu_1(int judge_color)	//判断第一列三点是否有颜色相同的环
{
	num=0;
	for (i=1;i<=7;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1 && p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	
	if(num==3)
	{
		CleanShu_1(judge_color);
	}
}

void JudgeShu_2(int judge_color)	//判断第二列三点是否有颜色相同的环
{
	num=0;
	for (i=2;i<=8;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1 && p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	
	if(num==3)
	{
		CleanShu_2(judge_color);
	}
}

void JudgeShu_3(int judge_color)	//判断第三列三点是否有颜色相同的环
{
	num=0;
	for (i=3;i<=9;i=i+3)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1 && p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	
	if(num==3)
	{
		CleanShu_3(judge_color);
	}
}

void CleanXie_left(int clean_color)	//消除左上到右下颜色相同的环
{
	for(i=1;i<=9;i=i+4)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	mciSendString("stop xcmusic7", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic7", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic7", NULL, 0, NULL);
	mciSendString("play xcmusic7", NULL, 0, NULL); // 仅播放一次
}
void CleanXie_right(int clean_color)	//消除左下到右上颜色相同的环

{
	for(i=3;i<=7;i=i+2)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcolor[j]==clean_color)
			{
				p[i].getcolor[j]=0;
				p[i].getcircle[j]=0;
			}
		}
	}
	mciSendString("stop xcmusic8", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close xcmusic8", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open E:\\Rings\\xiaochu.mp3 alias xcmusic8", NULL, 0, NULL);
	mciSendString("play xcmusic8", NULL, 0, NULL); // 仅播放一次
}
void JudgeXie_left(int judge_color)		//判断左上到右下是否有颜色相同的环
{
	num=0;
	for (i=1;i<=9;i=i+4)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1 && p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}
	
	if(num==3)
	{
		CleanXie_left(judge_color);
	}
}
void JudgeXie_right(int judge_color)	//判断左下到右上是否有颜色相同的环
{
	num=0;
	for (i=3;i<=7;i=i+2)
	{
		for(j=0;j<3;j++)
		{
			if(p[i].getcircle[j]==1 && p[i].getcolor[j]==judge_color)
			{
				num++;
				break;
			}
		}
	}	
	if(num==3)
	{
		CleanXie_right(judge_color);
	}
}



void starup()	//游戏初始化
{	
	high=390;
	wedith=550;
	initgraph(high,wedith);		//画布大小
	gap=95;		//点之间的间隔

	IMAGE img_bk;	// 定义 IMAGE 对象
	loadimage(&img_bk, "E:\\Rings\\封面hahaha.jpg");	// 读取图片到 img 对象中
	putimage(0, 0, &img_bk);	// 在坐标 (0, 0) 位置显示 IMAGE 对象
	getch();

	p[1].x=100;p[2].x=100+gap;p[3].x=100+gap*2;		//九个点的横坐标
	p[4].x=100;p[5].x=100+gap;p[6].x=100+gap*2;
	p[7].x=100;p[8].x=100+gap;p[9].x=100+gap*2;	

	p[1].y=180;p[4].y=180+gap;p[7].y=180+gap*2;		//九个点的纵坐标		
	p[2].y=180;p[5].y=180+gap;p[8].y=180+gap*2;
	p[3].y=180;p[6].y=180+gap;p[9].y=180+gap*2;	

	for(i=1;i<=3;i++)		//画出三个圆并定位
	{	
		c[i].x=p[i].x;
		c[i].y=p[9].y+gap;
		c[i].get=0;
		c[i].exist=0;
		c[i].color[0]=rand()%4+1;
		c[i].color[1]=rand()%4+1;
		c[i].color[2]=rand()%4+1;
	}
	
	for(i=1;i<=9;i++)//给点上的三个环全部初始化
	{
		for(j=0;j<3;j++)
		{
			p[i].getcircle[j]=0;
			p[i].getcolor[j]=0;
		}
	}

	//预设颜色
	Defcolor[0]=RGB(255,90,52);		//RED
	Defcolor[1]=RGB(25,147,233);	//BLUE
	Defcolor[2]=RGB(251,255,36);	//YELLOW
	Defcolor[3]=RGB(76,214,40);		//GREEN

	//判断环1是否存在并随机生成三个环是否存在
	if(c[1].exist==0)
	{
		for (i=0;i<3;i++)
			c[1].type[i]=rand()%2;
		c[1].exist=1;
	}

	//判断环2是否存在并随机生成三个环是否存在
	if(c[2].exist==0)
	{
		for (i=0;i<3;i++)
			c[2].type[i]=rand()%2;
		c[2].exist=1;
	}

	//判断环3是否存在并随机生成三个环是否存在
	if(c[3].exist==0)
	{
		for (i=0;i<3;i++)
			c[3].type[i]=rand()%2;
		c[3].exist=1;
	}
	//避免出现三个环都没有和三个环都没有的情况	
}
void Draw_ring(int c,Circle New_c[3])
{
	for(i=1;i<=3;i++)
	{
		if (New_c[i].type[0]==1&&New_c[i].color[0]==c)
			circle(New_c[i].x,New_c[i].y,10);
		if(New_c[i].type[1]==1&&New_c[i].color[1]==c)
			circle(New_c[i].x,New_c[i].y,17);
		if(New_c[i].type[2]==1&&New_c[i].color[2]==c)
			circle(New_c[i].x,New_c[i].y,24);
	}
}
void Draw_pointring(int c,point New_p[3])
{
	for(i=1;i<=9;i++)
	{
		if (New_p[i].getcircle[0]==1&&New_p[i].getcolor[0]==c)
			circle(New_p[i].x,New_p[i].y,10);
		if(New_p[i].getcircle[1]==1&&New_p[i].getcolor[1]==c)
			circle(New_p[i].x,New_p[i].y,17);
		if(New_p[i].getcircle[2]==1&&New_p[i].getcolor[2]==c)
			circle(New_p[i].x,New_p[i].y,24);
	}
}
void show()
{
	mciSendString("open E:\\Rings\\la.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
	BeginBatchDraw();	//这个函数用于开始批量绘图。
						//执行后，任何绘图操作都将暂时不输出到屏幕上
						//直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(31,78,121));//设置背景颜色
	solidrectangle(0,0,high,wedith);//画背景

	setwritemode(R2_MERGEPEN);//设置画图方式为OR

	for(j=1;j<=3;j++)
	{
	if(c[j].exist==0)
		{
		for (i=0;i<3;i++)
		{
			c[j].type[i]=rand()%2;
			c[j].color[i]=rand()%4+1;
		}
		c[j].exist=1;
		}
	}
	for(i=1;i<=3;i++)
	{
		if (c[i].type[0]==0 && c[i].type[1]==0 && c[i].type[2]==0)
			c[i].type[0]=1;
		if (c[i].type[0]==1&&c[i].type[1]==1)
			c[i].type[2]=0;
	}
		
	//画出三个圆环
	
		setlinestyle(PS_SOLID,5);//线条颜色为5
		setlinecolor(Defcolor[0]);//环的颜色为红
		Draw_ring(1,c);
		Draw_pointring(1,p);
		setlinecolor(Defcolor[1]);//环的颜色为蓝
		Draw_ring(2,c);	
		Draw_pointring(2,p);
		setlinecolor(Defcolor[2]);//环的颜色为黄色
		Draw_ring(3,c);
		Draw_pointring(3,p);
		setlinecolor(Defcolor[3]);//环的颜色为绿色
		Draw_ring(4,c);
		Draw_pointring(4,p);
	
	setwritemode(R2_COPYPEN);
	
	
	//画九个点
	setcolor(WHITE);
	setfillcolor(WHITE);
	for(x=p[1].x;x<=p[3].x;x+=gap)
		fillcircle(x,p[1].y,1);//第一排的点
	for(x=p[4].x;x<=p[6].x;x+=gap)
		fillcircle(x,p[4].y,1);//第二排的点
	for(x=p[7].x;x<=p[9].x;x+=gap)
		fillcircle(x,p[7].y,1);//第三排的点
	
	FlushBatchDraw();
	// 执行未完成的绘制任务
		
}


void withoutinput()
{
	//三个环都放出去后重新刷新
for (i=1;i<=3;i++)
{
	if(c[i].exist==2) 
	{
		c[i].exist=0;
		out(i);		
	}
}
if (c[1].x==-100 &&c[2].x==-100 &&c[3].x==-100 )
{
	back1();
	back2();
	back3();
}
for(color_size=1;color_size<=4;color_size++)
{
	judgeclean_type_one(color_size);
	judgeclean_type_two(color_size);
	judgeclean_type_three(color_size);
	judgeclean_type_four(color_size);
	judgeclean_type_five(color_size);
	judgeclean_type_six(color_size);
	judgeclean_type_seven(color_size);
	judgeclean_type_eight(color_size);
	judgeclean_type_nine(color_size);
	Clear_FullPoint();
	JudgeHeng_1(color_size);
	JudgeHeng_2(color_size);
	JudgeHeng_3(color_size);
	JudgeShu_1(color_size);
	JudgeShu_2(color_size);
	JudgeShu_3(color_size);	
	JudgeXie_left(color_size);	
	JudgeXie_right(color_size);	
}



}

void withinput()
{
	m=GetMouseMsg();
	size = 53;
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=314 && m.x>=266 && m.y>=441 && m.y<=489)	
	{
		c[3].get=1;		
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=124 && m.x>=76 && m.y>=441 && m.y<=489)	
	{
		c[1].get=1;	
	}
	if(m.uMsg == WM_LBUTTONDOWN && m.x<=219 && m.x>=171 && m.y>=441 && m.y<=489 )	
	{
		c[2].get=1;		
	}
	
	
	
	if(c[1].get==1)	//当鼠标按下后圆环跟着鼠标移动
	{
		c[1].x=m.x;
		c[1].y=m.y;
		for (i=1;i<=9;i++)
		{
			if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
			{
				for(j=0;j<3;j++)
				{
				if(c[1].type[j]==1&&p[i].getcircle[j]==1)
						z=1;
				}
				for(j=0;j<3;j++)
				{
					if(c[1].type[j]==1&&p[i].getcircle[j]==0&&z==0)
					{
						p[i].getcircle[j]=1;
						p[i].getcolor[j]=c[1].color[j];
					}
				}
				if(z==0)
				{
				stay1();	//在游戏边界内松开鼠标圆环1定位到临近点坐标
				c[1].get=0;
				c[1].exist=2;//存在过但是移走了
				}
				else
				{
				back1();
				c[1].get=0;
				z=0;
				}
			}			
			else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
			{	
				back1();	//游戏边界外松开鼠标圆环1回到原位
				c[1].get=0;		
			}
			else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
			{
				back1();	
				c[1].get=0;
			}
		}
	}
	if(c[2].get==1)//当鼠标按下后圆环2跟着鼠标移动
		{
			c[2].x=m.x;
			c[2].y=m.y;
			for (i=1;i<=9;i++)
			{
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
				{
					for(j=0;j<3;j++)
					{
					if(c[2].type[j]==1&&p[i].getcircle[j]==1)
							z=1;
					}
					for(j=0;j<3;j++)
					{
						if(c[2].type[j]==1&&p[i].getcircle[j]==0&&z==0)
						{
							p[i].getcircle[j]=1;
							p[i].getcolor[j]=c[2].color[j];
						}
					}
					if(z==0)
					{
					stay2();//在游戏边界内松开鼠标圆环2定位到临近点坐标
					c[2].get=0;  
					c[2].exist=2;//存在过但是移走了
					}
					else
					{
						back2();
						c[2].get=0;
						z=0;
					}
				}			
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
				{	
					back2();	//游戏边界外松开鼠标圆环2回到原位
					c[2].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
				{
					back2();
					c[2].get=0;
				}
			}
		}
	if(c[3].get==1)//当鼠标按下后圆环3跟着鼠标移动
		{
			c[3].x=m.x;
			c[3].y=m.y;
			for (i=1;i<=9;i++)
			{
				if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)//size/2会使得判断范围更好可是同时也会使得判断back失效
				{ 
					for(j=0;j<3;j++)
					{
					 if(c[3].type[j]==1&&p[i].getcircle[j]==1)
							z=1;
					}
					for(j=0;j<3;j++)
					{
						if(c[3].type[j]==1&&p[i].getcircle[j]==0&&z==0)
						{
							p[i].getcircle[j]=1;
							p[i].getcolor[j]=c[3].color[j];
						}
					}
					if(z==0)
					{
					stay3();	//在游戏边界内松开鼠标圆环3定位到临近点坐标
					c[3].get=0;
					c[3].exist=2;//存在过但是移走了
					}
					else
					{
						back3();
						c[3].get=0;
						z=0;
					}
				}	
				
				else if (m.uMsg == WM_LBUTTONUP && (m.x<=p[1].x-size || m.x>=p[3].x+size || m.y<=p[1].y-size || m.y>=p[7].y+size))
				{	
					back3();	//游戏边界外松开鼠标圆环3回到原位
					c[3].get=0;		
				}
				else if(m.uMsg == WM_LBUTTONUP && m.x>=p[i].x-size && m.x<=p[i].x+size && m.y>=p[i].y-size && m.y<=p[i].y+size)
				{
					back3();
					c[3].get=0;
				}
			}		
		}	
}


void main()
{
		starup();
		while(1)
		{
			mciSendString("open E:\\Rings\\la.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
			mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
			withinput();
			withoutinput();
			show();	
		}
		EndBatchDraw();
		getch();
		closegraph();	
}

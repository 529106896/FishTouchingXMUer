#include<graphics.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

void startup();
void show();
void updatewithoutinput();
void status_change();
void updatewithinput();
void gameover();

#define high 670//画布的高度
#define width 900//画布的宽度
#define person_high 72//定义挖地小子的高度
#define person_width 64//定义挖地小子的宽度
#define shoesperson_high 82//定义挖地小子飞升时的高度
#define shoesperson_width 64//定义挖地小子飞升时的宽度
#define digdownperson_high 80//定义挖地小子向下挖时的高度
#define digdownperson_width 64//定义挖地小子向下挖时的宽度
#define digleftperson_high 78//定义挖地小子向左挖时的高度
#define digleftperson_width 64//定义挖地小子向左挖时的宽度
#define digrightperson_high 78//定义挖地小子向左挖时的高度
#define digrightperson_width 64//定义挖地小子向左挖时的宽度
#define num_1_stonewidth 14//第一关中横向石块个数
#define num_1_stonehigh 4//第一关中纵向石块的个数
#define stone_high 64//砖块的高
#define stone_width 64//砖块的宽
#define apper_1stone 414//第一关中开始出现砖块的y位置


IMAGE img_bk;//定义背景图片
IMAGE img_1;//定义第一关的图片
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7;//定义石块的图片
IMAGE img_person_0, img_person_00;//定义挖地小子的正面图片 0表示黑白版 00表示彩版
IMAGE img_person_1, img_person_2;//定义挖地小子左右走的图片 1表示黑白版 2表示彩版
IMAGE img_shoes_1, img_shoes_2;//定义火箭鞋图片 1表示黑白版 2表示彩版
IMAGE img_digleftperson_1, img_digleftperson_2;//定义挖地小子向左挖的照片  1表示黑白版 2表示彩版
IMAGE img_digrightperson_1, img_digrightperson_2;//定义挖地小子向右挖的照片  1表示黑白版 2表示彩版
IMAGE img_digdownperson_1, img_digdownperson_2;//定义挖地小子向下挖的照片  1表示黑白版 2表示彩版
MOUSEMSG m;//定义一个鼠标变量

typedef struct thing//定义结构体用于人
{
	int left_x;//左端x坐标
	int left_y;//左端y坐标
	int right_x;//右端x坐标
	int right_y;//右端y坐标
	int top_x;//上端x坐标
	int top_y;//上端y坐标
	int bottom_x;//底部x坐标
	int bottom_y;//底部y坐标
	int center_x;//中心x坐标
	int center_y;//中心y坐标
	int v;//挖地小子竖直方向速度
}thing;
thing person;//定义人

struct stone//定义结构体用于土块
{
	int left_x;//左端x坐标
	int left_y;//左端y坐标
	int right_x;//右端x坐标
	int right_y;//右端y坐标
	int top_x;//上端x坐标
	int top_y;//上端y坐标
	int bottom_x;//底部x坐标
	int bottom_y;//底部y坐标
	int center_x;//中心x坐标
	int center_y;//中心y坐标
	int status;//表示砖块的状态 0表示无 1为原始 2破碎1 3破碎2 4破碎3 5破碎4 6破碎5 7破碎6
}stone[num_1_stonehigh][num_1_stonewidth];//土块的结构体一共56个砖块

int scene;//用于切换场景
int left_i;//记录向左移动的图片
int right_i;//记录向右移动的图片
int G;//重力加速度
int shoes_a;//火箭鞋加速度
int count_1;//用于记录飞行时上一张照片,从而选择消除图片大小为多少,初始值为正面图案（此为记录飞行）count_1==1表示人物正面 count_1==2表示人物向下挖
int count_2;//用于记录向下挖时上一张照片,从而选择消除图片大小为多少,初始值为正面图案（此为记录向下w挖）count_2==1表示人物正面 count_2==2表示人物向下挖
int count_3;//用于记录向左挖时上一张照片,从而选择消除图片大小为多少,初始值为正面图案（此为记录向左挖）count_3==1表示人物正面 count_3==2表示人物向左挖
int count_4;//用于记录向右挖时上一张照片,从而选择消除图片大小为多少,初始值为正面图案（此为记录向右挖）count_4==1表示人物正面 count_4==2表示人物向右挖
int digbf;//用于记录判断是否在向下挖 0表示没有 1表示有
int digleftbf;//用于记录判断是否在向左挖 0表示没有 1表示有
int digrightbf;//用于记录判断是否在向右挖 0表示没有 1表示有
int exist_leftstone;//用于记录判断是否左端有砖块 0表示没有 1表示有
int exist_rightstone;//用于记录判断是否右端有砖块 0表示没有 1表示有
void main()
{
	startup();
	while (1)
	{
		show();
		updatewithoutinput();
		status_change();
		updatewithinput();
	}
	gameover();
}
/*count 0 开始界面；1 第一关界面 */
void startup()
{
	initgraph(width, high);//画布
	loadimage(&img_bk, _T("background.jpg"));//导入游戏开始界面
	loadimage(&img_1, _T("level_1.jpg"));//导入第一关的图片
	loadimage(&img_person_0, _T("person_0.jpg"));//导入人物正面的图片黑白版
	loadimage(&img_person_00, _T("person_00.jpg"));//导入人物正面的图片彩版
	loadimage(&img_person_1, _T("person_1.jpg"));//导入人物左右走路的图片的黑白版
	loadimage(&img_person_2, _T("person_2.jpg"));//导入人物左右走路的图片彩版
	loadimage(&img_stone_0, _T("stone_0.jpg"));//导入空的图片
	loadimage(&img_stone_1, _T("stone_1.jpg"));//导入石块原图的图片
	loadimage(&img_stone_2, _T("stone_2.jpg"));//导入破碎1的图片
	loadimage(&img_stone_3, _T("stone_3.jpg"));//导入破碎2的图片
	loadimage(&img_stone_4, _T("stone_4.jpg"));//导入破碎3的图片
	loadimage(&img_stone_5, _T("stone_5.jpg"));//导入破碎4的图片
	loadimage(&img_stone_6, _T("stone_6.jpg"));//导入破碎5的图片
	loadimage(&img_stone_7, _T("stone_7.jpg"));//导入破碎6的图片
	loadimage(&img_shoes_1, _T("shoes_1.jpg"));//导入上升的图片黑白版
	loadimage(&img_shoes_2, _T("shoes_2.jpg"));//导入上升的图片彩版
	loadimage(&img_digleftperson_1, _T("digleftperson_1.jpg"));//导入向左挖的图片的黑白版
	loadimage(&img_digleftperson_2, _T("digleftperson_2.jpg"));//导入向左挖的图片的彩版
	loadimage(&img_digrightperson_1, _T("digrightperson_1.jpg"));//导入向右挖的图片的黑白版
	loadimage(&img_digrightperson_2, _T("digrightperson_2.jpg"));//导入向右挖的图片的彩版
	loadimage(&img_digdownperson_1, _T("digdownperson_1.jpg"));//导入向下挖的图片的黑白版
	loadimage(&img_digdownperson_2, _T("digdownperson_2.jpg"));//导入向下挖的图片的彩版
	mciSendString(_T("open bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);//导入背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环背景音乐

	scene = 0;//用于切换场景
	shoes_a = 0;//火箭鞋初速度
	count_1 = 1;//初始时人物正面 count_1==1表示人物正面 count_1==2表示人物向上飞
	count_2 = 1;//初始时人物正面 count_2==1表示人物正面 count_2==2表示人物向下挖
	count_3 = 1;//初始时人物正面 count_3==1表示人物正面 count_3==2表示人物向左挖
	count_4 = 1;//初始时人物正面 count_3==1表示人物正面 count_3==2表示人物向右挖
	exist_leftstone = 0;//初始时左边没有砖块 exist_leftstone==0表示左边没有砖块 exist_leftstone==1表示左边有砖块
	exist_rightstone = 0;//初始时右边没有砖块 exist_leftstone==0表示左边没有砖块 exist_leftstone==1表示左边有砖块
	digleftbf = 0;//判断是否向左开始挖
	digrightbf = 0;//判断是否向右开始挖
/*对每个砖块进行初始化*/
	int i, j;
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			stone[i][j].center_x = stone_width / 2 + j * stone_width;//初始化每个砖块的中心x坐标
			stone[i][j].center_y = apper_1stone + stone_high / 2 + i * stone_high;//初始化每个砖块的中心y坐标
			stone[i][j].left_x = j * stone_width;//初始化每个砖块的左端x坐标
			stone[i][j].left_y = apper_1stone + stone_high / 2 + i * stone_high;//初始化每个砖块的左端y坐标
			stone[i][j].right_x = stone_width + j * stone_width;//初始化每个砖块的右端x坐标
			stone[i][j].right_y = apper_1stone + stone_high / 2 + i * stone_high;//初始化每个砖块的右端y坐标
			stone[i][j].top_x = stone_width / 2 + j * stone_width;//初始化每个砖块的上端x坐标
			stone[i][j].top_y = apper_1stone + i * stone_high;//初始化每个砖块的上端y坐标
			stone[i][j].bottom_x = stone_width / 2 + j * stone_width;//初始化每个砖块的下端x坐标
			stone[i][j].bottom_y = apper_1stone + stone_high + i * stone_high;//初始化每个砖块的下端y坐标
			stone[i][j].status = 1;//原始状态
		}
	/*挖地小子赋初始位置值 */
	person.center_x = width / 2;
	person.center_y = apper_1stone - person_high / 2;

	/*移动变量赋值*/
	left_i = 0;
	right_i = 0;
	person.v = 0;
	BeginBatchDraw();
}
void show()
{
	int i, j;//循环变量
	if (scene == 0)//切换背景
	{
		putimage(0, 0, &img_bk);//导出背景图片
		FlushBatchDraw();
	}

	else if (scene == 1)//切换到场景1
	{
		putimage(0, 0, &img_1);//导出第一关的图片

  /*0表示无 1为原始 2破碎1 3破碎2 4破碎3 5破碎4 6破碎5 7破碎6*/
		for (i = 0; i < num_1_stonehigh; i++)
			for (j = 0; j < num_1_stonewidth; j++)
			{
				if (stone[i][j].status == 1)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_1);//砖块初始化
				else if (stone[i][j].status == 2)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_2);////破碎1的图片
				else if (stone[i][j].status == 3)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_3);////破碎2的图片
				else if (stone[i][j].status == 4)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_4);////破碎3的图片
				else if (stone[i][j].status == 5)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_5);////破碎4的图片
				else if (stone[i][j].status == 6)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_6);////破碎5的图片
				else if (stone[i][j].status == 7)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_7);////破碎6的图片
				else if (stone[i][j].status == 0)
					putimage(stone_width * j, apper_1stone + stone_high * i, &img_stone_0);////完全破碎的图片
			}

	}


	/*人物坐标关联 每个值都与人物坐标中心相关 增强坐标的相关性*/
	person.left_x = person.center_x - person_width / 2;
	person.left_y = person.center_y;
	person.right_x = person.center_x + person_width / 2;
	person.right_y = person.center_y;
	person.top_x = person.center_x;
	person.top_y = person.center_y - person_high / 2;
	person.bottom_x = person.center_x;
	person.bottom_y = person.center_y + person_high / 2;


}
void updatewithoutinput()
{
	int i, j;
	/*判定人物是否站在砖块上*/
	G = 1;//重力加速度初值
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (stone[i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
				person.center_x <= stone[i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
				person.center_x >= stone[i][j].center_x - person_width / 2 - stone_width / 2 + 10 &&//判断人物与砖块之间横坐标之间的关系
				stone[i][j].status != 0)//判断是否踩在砖块上（通过判断人物与砖块之间纵坐标距离,判断人物与砖块之间横坐标之间的关系,砖块的状态）
			{
				G = 0;//重力加速度变为0
				person.v = 0;//踩到砖块是人物不下落
				person.center_y = stone[i][j].center_y - person_high / 2 - stone_high / 2;//保持人物与砖块的间距
				break;
			}

		}
	/*判断人物飞行时是否上方有砖块*/
	if (shoes_a == -2)//当人物上升时，若上方头顶存在砖块，则不能向上飞
	{
		for (i = 0; i < num_1_stonehigh; i++)
			for (j = 0; j < num_1_stonewidth; j++)
			{
				if (person.center_y - stone[i][j].center_y <= stone_high - person_high / 2 + stone_high / 2 &&
					person.center_y - stone[i][j].center_y >= (stone_high - person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
					person.center_x <= stone[i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
					person.center_x >= stone[i][j].center_x - person_width / 2 - stone_width / 2 + 10 &&//判断人物与砖块之间横坐标之间的关系
					stone[i][j].status != 0)
				{
					person.v = 0;//速度为零
					shoes_a = -1;//与重力加速度抵消，人物合外力为零，好处（1.可以时图片继续为向上升的图片 2.松手后可以落下）
					break;
				}
			}
	}
	/*判断是否在向下挖*/
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (stone[i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
				person.center_x <= stone[i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
				person.center_x >= stone[i][j].center_x - person_width / 2 - stone_width / 2 + 10 //判断人物与砖块之间横坐标之间的关系
				 )//判断是否踩在砖块上（通过判断人物与砖块之间纵坐标距离,判断人物与砖块之间横坐标之间的关系,砖块的状态）
			{
				if (digbf == 1 && stone[i][j].status != 0)//若可以挖且下方有砖块
				{
					person.center_x = stone[i][j].center_x;//保持人物与砖块d的横坐标相等
					static int speed_2 = 0;//用于限制向下挖的速度
					if (speed_2 < 100)
						speed_2++;
					else if (speed_2 == 100)
					{
						stone[i][j].status++;//状态加1
						speed_2 = 0;
					}
					if (stone[i][j].status == 8)
						stone[i][j].status = 0;//砖块消失
				}
			}
		}

	/*判断人物左边是否有砖块*/
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (person.center_x - stone[i][j].center_x <= stone_width / 2 + person_width / 2 &&
				person.center_x - stone[i][j].center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[i][j].status != 0)
			{
				exist_leftstone = 1;//左端存在砖块
				if (digleftbf == 1)//开始向左挖
				{
					person.center_x = stone[i][j].center_x + stone_width / 2 + person_width / 2;//左边挖归位
					static int speed_3 = 0;//用于限制向下挖的速度
					if (speed_3 < 100)
						speed_3++;
					else if (speed_3 == 100)
					{
						stone[i][j].status++;//状态加1
						speed_3 = 0;
					}
					if (stone[i][j].status == 8)
						stone[i][j].status = 0;//砖块消失
				}
			}
			
		}
	/*判断人物右边是否有砖块*/
	for (i = 0; i < num_1_stonehigh; i++)
		for (j = 0; j < num_1_stonewidth; j++)
		{
			if (stone[i][j].center_x - person.center_x <= stone_width / 2 + person_width / 2 &&
				stone[i][j].center_x - person.center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[i][j].status != 0)
			{
				exist_rightstone = 1;//左端存在砖块
				if (digrightbf == 1)//开始向左挖
				{
					person.center_x = stone[i][j].center_x - stone_width / 2 - person_width / 2;//左边挖归位
					static int speed_3 = 0;//用于限制向下挖的速度
					if (speed_3 < 100)
						speed_3++;
					else if (speed_3 == 100)
					{
						stone[i][j].status++;//状态加1
						speed_3 = 0;
					}
					if (stone[i][j].status == 8)
						stone[i][j].status = 0;//砖块消失
				}
			}
		}
   /*人物控制中枢*/
	static int speed_1 = 0;//用于限制下落的速度
	if (speed_1 < 10)
		speed_1++;
	else if (speed_1 == 10)
	{
		person.v = person.v + G + shoes_a;//速度的变化量
		if (person.v >= 25)//限速设定
			person.v = 25;
		if (person.v <= -15)//限速设定
			person.v = -15;
		person.center_y = person.center_y + person.v;//人物竖直方向位置变化
		speed_1 = 0;
	}
}
void status_change()
{
	int i, j;
	/*当人物不动时转向正面 */
	if (scene == 1)
	{
		if (shoes_a == 0 && digbf == 0 && digleftbf == 3 && digrightbf == 3)//digbf==0避免向下挖的时候显示正面图片
		{
			if (count_1 == 1)//用于判断消除什么大小
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//当上一张图片是正面不动时清除原人物
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//加入背景，用于消除黑色
			}
			else if (count_1 == 2)//用于从飞行状态转变为正面
			{
				clearrectangle(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, person.center_x - shoesperson_width / 2 + shoesperson_width, person.center_y - shoesperson_high / 2 + shoesperson_high);//消除飞行状态的图片
				putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, shoesperson_width + 1, shoesperson_high + 1, &img_1, person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2);//加上背景图
			}
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//人物正面黑白版
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//人物正面彩版
			count_1 = 1;//当count为1时为正面图案
			FlushBatchDraw();
			Sleep(1);
		}
		/*当按w时人物向上飞*/
		else if (shoes_a < 0)
		{
			if (count_1 == 1)
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//用于从正面图案转变为飞行图案
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//用于消除黑色
			}
			else if (count_1 == 2)
			{
				clearrectangle(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, person.center_x - shoesperson_width / 2 + shoesperson_width, person.center_y - shoesperson_high / 2 + shoesperson_high);//保持飞行状态时，消除上次的团
				putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, shoesperson_width + 1, shoesperson_high + 1, &img_1, person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2);//加入新的图案
			}
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物正面黑白
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物正面彩
			count_1 = 2;//当count为2时为飞行图案
			FlushBatchDraw();
			Sleep(1);
		}



		/*没有挖时人物正面*/
		if (digbf == 0 && shoes_a == 0 && digleftbf == 3 && digrightbf == 3)//shoes==0避免人物向上飞的时候显示正面图片
		{
			if (count_2 == 1)
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//当上一张图片是正面不动时清除原人物
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//加入背景，用于消除黑色
			}
			else if (count_2 == 2)//用于从向下挖状态转变为正面
			{
				clearrectangle(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, person.center_x - digdownperson_width / 2 + digdownperson_width, person.center_y - digdownperson_high / 2 + digdownperson_high);//消除飞行状态的图片
				putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, digdownperson_width + 1, digdownperson_high + 1, &img_1, person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2);//加上背景图
			}
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//人物正面黑白版
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//人物正面彩版
			count_2 = 1;//当count为1时为正面图案
			FlushBatchDraw();
			Sleep(1);
		}
		/*人物转变为向下挖的图片*/
		else if (digbf == 1)
		{
			if (count_2 == 1)
			{
				clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//用于从正面图案转变为向下挖图案
				putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//用于消除黑色
			}
			else if (count_2 == 2)
			{
				clearrectangle(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, person.center_x - digdownperson_width / 2 + digdownperson_width, person.center_y - digdownperson_high / 2 + digdownperson_high);//保持向下挖状态时，消除上次的团
				putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, digdownperson_width + 1, digdownperson_high + 1, &img_1, person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2);//加入新的图案
			}
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_1, NOTSRCERASE);//人物正面黑白
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_2, SRCINVERT);//人物正面彩
			count_2 = 2;//当count为2时为向下挖图案
			FlushBatchDraw();
			Sleep(1);
		}

	}
	/*左边行走与左边挖土*/
	if (digleftbf == 0 && scene==1)
	{
		if (count_3 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//当上一张图片是正面不动时清除原人物
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//加入背景，用于消除黑色
		}
		else if (count_3 == 2)//用于从向左挖转变为向左走
		{
			clearrectangle(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, person.center_x - digleftperson_width / 2 + digleftperson_width, person.center_y - digleftperson_high / 2 + digleftperson_high);//消除飞行状态的图片
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, digleftperson_width + 1, digleftperson_high + 1, &img_1, person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2);//加上背景图
		}
		left_i++;
		person.center_x = person.center_x - 15;//人物的中心坐标x减少
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, left_i * person_width, 0, NOTSRCERASE);//放置向左走的黑白图片
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, left_i * person_width, 0, SRCINVERT);//放置向左走的彩图
		FlushBatchDraw();
		count_3 = 1;
		Sleep(100);
		if (left_i == 3)
			left_i = 0;
	}
	else if (digleftbf == 1)
	{
		if (count_3 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//用于从正面图案转变为向下挖图案
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//用于消除黑色
		}
		else if (count_3 == 2)
		{
			clearrectangle(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, person.center_x - digleftperson_width / 2 + digleftperson_width, person.center_y - digleftperson_high / 2 + digleftperson_high);//消除飞行状态的图片
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, digleftperson_width + 1, digleftperson_high + 1, &img_1, person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2);//加上背景图
		}
		putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_1, NOTSRCERASE);//人物正面黑白
		putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_2, SRCINVERT);//人物正面彩
		count_3 = 2;//当count为2时为向下挖图案
		FlushBatchDraw();
		Sleep(1);
	}


	/*右边行走与右边挖土*/
	if (digrightbf == 0 && scene == 1)
	{
		if (count_4 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//当上一张图片是正面不动时清除原人物
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//加入背景，用于消除黑色
		}
		else if (count_4 == 2)//用于从向左挖转变为向左走
		{
			clearrectangle(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, person.center_x - digrightperson_width / 2 + digrightperson_width, person.center_y - digrightperson_high / 2 + digrightperson_high);//消除飞行状态的图片
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, digrightperson_width + 1, digrightperson_high + 1, &img_1, person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2);//加上背景图
		}
		right_i++;//采用套图
		person.center_x = person.center_x + 15;//人物的中心坐标x减少
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, right_i * person_width, person_high, NOTSRCERASE);//放置向右走的黑白图片
		putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, right_i * person_width, person_high, SRCINVERT);//放置向右走的彩图
		FlushBatchDraw();
		count_4 = 1;
		Sleep(100);
		if (right_i == 3)
			right_i = 0;
	}
	else if (digrightbf == 1)
	{
		if (count_4 == 1)
		{
			clearrectangle(person.left_x, person.top_y, person.left_x + person_width, person.top_y + person_high);//用于从正面图案转变为向下挖图案
			putimage(person.left_x, person.top_y, person_width + 1, person_high + 1, &img_1, person.left_x, person.top_y);//用于消除黑色
		}
		else if (count_4 == 2)
		{
			clearrectangle(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, person.center_x - digrightperson_width / 2 + digrightperson_width, person.center_y - digrightperson_high / 2 + digrightperson_high);//消除飞行状态的图片
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, digrightperson_width + 1, digrightperson_high + 1, &img_1, person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2);//加上背景图
		}
		putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_1, NOTSRCERASE);//人物正面黑白
		putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_2, SRCINVERT);//人物正面彩
		count_4 = 2;//当count为2时为向下挖图案
		FlushBatchDraw();
		Sleep(1);
	}
	/*回归原值部分*/
	shoes_a = 0;//将加速度归为原值（按w改变）
	digbf = 0;//向下挖回归原值（按s改变）
	digleftbf = 3;//向左挖回归原值（按a改变）
	digrightbf = 3;//向右挖回归原值（按d改变）
}
void updatewithinput()
{
	/*当进入界面的时候点击‘按任意键进入’进入游戏*/
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONUP && scene == 0)
		{
			if (m.x <= 563 && m.x >= 316 && m.y <= 602 && m.y >= 570)//按键范围判断
			{
				scene = 1;//跳转为第一关
			}
		}
	}

	if (scene == 1)//第一关
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 0)//如果按下a，左移动
		{
			digleftbf = 0;//表示不开挖
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 1)//如果按下a，左移动
		{
			digleftbf = 1;//表示开挖
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 0)//d
		{
			digrightbf = 0;//表示不开挖
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 1)//d
		{
			digrightbf = 1;//表示开挖
		}
		if (GetAsyncKeyState(0x57) & 0x8000)//按w	
		{
			shoes_a = -2;
		}
		if (GetAsyncKeyState(0x53) & 0x8000)//按s
		{
			digbf = 1;//表示可以挖
		}
	}
	/*回归原值部分 回归左右移动判断的值*/
	exist_leftstone = 0;
	exist_rightstone = 0;
}


void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

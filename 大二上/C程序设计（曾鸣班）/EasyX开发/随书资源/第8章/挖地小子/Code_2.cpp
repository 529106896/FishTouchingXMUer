#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")

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
#define shoesperson_high 92//定义挖地小子飞升时的高度
#define shoesperson_width 64//定义挖地小子飞升时的宽度
#define digdownperson_high 80//定义挖地小子向下挖时的高度
#define digdownperson_width 64//定义挖地小子向下挖时的宽度
#define digleftperson_high 78//定义挖地小子向左挖时的高度
#define digleftperson_width 64//定义挖地小子向左挖时的宽度
#define digrightperson_high 78//定义挖地小子向左挖时的高度
#define digrightperson_width 64//定义挖地小子向左挖时的宽度
#define num_stonewidth 14//横向石块个数
#define num_stonehigh 11//纵向石块个数
#define num_scene 3//关卡个数
#define stone_high 64//砖块的高
#define stone_width 64//砖块的宽
#define apper_1stone 414//第一关中开始出现砖块的y位置
#define apper_2stone 0//第二关中开始出现砖块的y位置


IMAGE img_bk;//定义背景图片
IMAGE img_1;//定义第一关的图片
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7;//定义石块的图片
IMAGE img_coal_1, img_coal_2, img_coal_3, img_coal_4, img_coal_5, img_coal_0;//定义煤块的图片
IMAGE img_copper_1, img_copper_2, img_copper_3, img_copper_4, img_copper_5, img_copper_6, img_copper_0;//定义铜块的图片
IMAGE img_silver_1, img_silver_2, img_silver_3, img_silver_4, img_silver_5, img_silver_0;//定义银块的图片
IMAGE img_person_0, img_person_00;//定义挖地小子的正面图片 0表示黑白版 00表示彩版
IMAGE img_person_1, img_person_2;//定义挖地小子左右走的图片 1表示黑白版 2表示彩版
IMAGE img_shoes_1, img_shoes_2;//定义火箭鞋图片 1表示黑白版 2表示彩版
IMAGE img_digleftperson_1, img_digleftperson_2;//定义挖地小子向左挖的照片  1表示黑白版 2表示彩版
IMAGE img_digrightperson_1, img_digrightperson_2;//定义挖地小子向右挖的照片  1表示黑白版 2表示彩版
IMAGE img_digdownperson_1, img_digdownperson_2;//定义挖地小子向下挖的照片  1表示黑白版 2表示彩版
IMAGE img_shop;//商店
MOUSEMSG m;//定义一个鼠标变量

int scene;//用于切换场景
int left_i;//记录向左移动的图片
int right_i;//记录向右移动的图片
int G;//重力加速度
int shoes_a;//火箭鞋加速度
int digbf;//用于记录判断是否在向下挖 0表示没有 1表示有
int digleftbf;//用于记录判断是否在向左挖 0表示没有 1表示有
int digrightbf;//用于记录判断是否在向右挖 0表示没有 1表示有
int flyleftbf;//用于记录判断是否在向左飞 0表示没有 1表示有
int flyrightbf;//用于记录判断是否在向右飞 0表示没有 1表示有
int exist_leftstone;//用于记录判断是否左端有砖块 0表示没有 1表示有
int exist_rightstone;//用于记录判断是否右端有砖块 0表示没有 1表示有
int exist_downstone;//用于记录判断是否下端有砖块 0表示没有 1表示有
int exist_flyleftstone; //用于记录判断飞行时是否左端有砖块 0表示没有 1表示有
int exist_flyrightstone; //用于记录判断飞行时是否右端有砖块 0表示没有 1表示有
int score;//分数记录

typedef struct thing//定义结构体用于人
{
	float left_x;//左端x坐标
	float left_y;//左端y坐标
	float right_x;//右端x坐标
	float right_y;//右端y坐标
	float top_x;//上端x坐标
	float top_y;//上端y坐标
	float bottom_x;//底部x坐标
	float bottom_y;//底部y坐标
	float center_x;//中心x坐标
	float center_y;//中心y坐标
	float v;//挖地小子竖直方向速度
}thing;
thing person;//定义人

struct stone//定义结构体用于土块
{
	float left_x;//左端x坐标
	float left_y;//左端y坐标
	float right_x;//右端x坐标
	float right_y;//右端y坐标
	float top_x;//上端x坐标
	float top_y;//上端y坐标
	float bottom_x;//底部x坐标
	float bottom_y;//底部y坐标
	float center_x;//中心x坐标
	float center_y;//中心y坐标
	float status;//表示砖块的状态 0表示无 1为原始 2破碎1 3破碎2 4破碎3 5破碎4 6破碎5 7破碎6
}stone[num_scene][num_stonehigh][num_stonewidth];//土块的结构体一共56个砖块

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
	loadimage(&img_shop, _T("shop.jpg"));//导入商店的图片
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
	loadimage(&img_coal_1, _T("coal_1.jpg"));//导入完整煤
	loadimage(&img_coal_2, _T("coal_2.jpg"));//导入破碎1煤
	loadimage(&img_coal_3, _T("coal_3.jpg"));//导入破碎2,煤
	loadimage(&img_coal_4, _T("coal_4.jpg"));//导入破碎3煤
	loadimage(&img_coal_5, _T("coal_5.jpg"));//导入破碎4煤
	loadimage(&img_coal_0, _T("coal_0.jpg"));//完全破碎的煤
	loadimage(&img_copper_1, _T("Copper_1.jpg"));//导入完整铜
	loadimage(&img_copper_2, _T("Copper_2.jpg"));//导入破碎1铜
	loadimage(&img_copper_3, _T("Copper_3.jpg"));//导入破碎2铜
	loadimage(&img_copper_4, _T("Copper_4.jpg"));//导入破碎3铜
	loadimage(&img_copper_5, _T("Copper_5.jpg"));//导入破碎4铜
	loadimage(&img_copper_6, _T("Copper_6.jpg"));//导入破碎5铜
	loadimage(&img_copper_0, _T("Copper_0.jpg"));//完全破碎的铜
	loadimage(&img_silver_1, _T("silver_1.jpg"));//导入完整银
	loadimage(&img_silver_2, _T("silver_2.jpg"));//导入破碎1银
	loadimage(&img_silver_3, _T("silver_3.jpg"));//导入破碎2银
	loadimage(&img_silver_4, _T("silver_4.jpg"));//导入破碎3银
	loadimage(&img_silver_5, _T("silver_5.jpg"));//导入破碎4银
	loadimage(&img_silver_0, _T("silver_0.jpg"));//完全破碎的银
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
	exist_leftstone = 0;//初始时左边没有砖块 exist_leftstone==0表示左边没有砖块 exist_leftstone==1表示左边有砖块
	exist_rightstone = 0;//初始时右边没有砖块 exist_rightstone==0表示左边没有砖块 exist_leftrightstone==1表示左边有砖块
	exist_downstone = 0;//初始时下边没有砖块 exist_downstone==0表示左边没有砖块 exist_downstone==1表示左边有砖块
	exist_flyleftstone = 0;
	exist_flyrightstone = 0;
	digleftbf = 0;//判断是否向左开始挖
	digrightbf = 0;//判断是否向右开始挖
	flyleftbf = 0;//判断是否向左飞
	flyrightbf = 0;//判断是否向右飞

 /*对每个砖块进行初始化*/
	int i, j, k;
	for (k = 0; k < 3; k++)
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				stone[k][i][j].center_x = -1000;
				stone[k][i][j].center_y = -1000;
				stone[k][i][j].left_x = -1000;
				stone[k][i][j].left_y = -1000;
				stone[k][i][j].right_x = -1000;
				stone[k][i][j].right_y = -1000;
				stone[k][i][j].top_x = -1000;
				stone[k][i][j].top_y = -1000;
				stone[k][i][j].bottom_x = -1000;
				stone[k][i][j].bottom_y = -1000;
				stone[k][i][j].status = -1000;
			}
	for (i = 7; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)//第一关的石块位置
		{
			stone[1][i][j].center_x = stone_width / 2 + j * stone_width;//初始化每个砖块的中心x坐标
			stone[1][i][j].center_y = apper_1stone + stone_high / 2 + (i - 7) * stone_high;//初始化每个砖块的中心y坐标
			stone[1][i][j].left_x = j * stone_width;//初始化每个砖块的左端x坐标
			stone[1][i][j].left_y = apper_1stone + stone_high / 2 + (i - 7) * stone_high;//初始化每个砖块的左端y坐标
			stone[1][i][j].right_x = stone_width + j * stone_width;//初始化每个砖块的右端x坐标
			stone[1][i][j].right_y = apper_1stone + stone_high / 2 + (i - 7) * stone_high;//初始化每个砖块的右端y坐标
			stone[1][i][j].top_x = stone_width / 2 + j * stone_width;//初始化每个砖块的上端x坐标
			stone[1][i][j].top_y = apper_1stone + (i - 7) * stone_high;//初始化每个砖块的上端y坐标
			stone[1][i][j].bottom_x = stone_width / 2 + j * stone_width;//初始化每个砖块的下端x坐标
			stone[1][i][j].bottom_y = apper_1stone + stone_high + (i - 7) * stone_high;//初始化每个砖块的下端y坐标
			stone[1][i][j].status = 31;//原始状态
		}

	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)//第一关的石块位置
		{
			stone[2][i][j].center_x = stone_width / 2 + j * stone_width;//初始化每个砖块的中心x坐标
			stone[2][i][j].center_y = apper_2stone + stone_high / 2 + i * stone_high;//初始化每个砖块的中心y坐标
			stone[2][i][j].left_x = j * stone_width;//初始化每个砖块的左端x坐标
			stone[2][i][j].left_y = apper_2stone + stone_high / 2 + i * stone_high;//初始化每个砖块的左端y坐标
			stone[2][i][j].right_x = stone_width + j * stone_width;//初始化每个砖块的右端x坐标
			stone[2][i][j].right_y = apper_2stone + stone_high / 2 + i * stone_high;//初始化每个砖块的右端y坐标
			stone[2][i][j].top_x = stone_width / 2 + j * stone_width;//初始化每个砖块的上端x坐标
			stone[2][i][j].top_y = apper_2stone + i * stone_high;//初始化每个砖块的上端y坐标
			stone[2][i][j].bottom_x = stone_width / 2 + j * stone_width;//初始化每个砖块的下端x坐标
			stone[2][i][j].bottom_y = apper_2stone + stone_high + i * stone_high;//初始化每个砖块的下端y坐标
			stone[2][i][j].status = 31;//原始状态
		}
	/*挖地小子赋初始位置值 */
	person.center_x = width / 2;
	person.center_y = apper_1stone-person_high/2;
	/*移动变量赋值*/
	left_i = 0;
	right_i = 0;
	person.v = 0;
	/*分数初始*/
	score = 0;
	BeginBatchDraw();
}
void show()
{
	int i, j, k;//循环变量
	k = 0;
	if (scene == 0)//切换背景
	{
		putimage(0, 0, &img_bk);//导出背景图片
		FlushBatchDraw();
	}
	/* 土块 0表示无 1为原始 2破碎1 3破碎2 4破碎3 5破碎4 6破碎5 7破碎6*/
	/*煤块 11表示原始 12表示破碎1 13表示破碎2 14表示破碎3 15表示破碎4  16表示煤
	铜块  21表示原始  22表示破碎1 23表示破碎2 24表示破碎3  25表示破碎4 26表示破碎5 27表示铜块
	银块   31表示原始  32表示破碎1 33表示破碎2 34表示破碎3 35表示破碎4 36表示银块*/
	else if (scene == 1)//切换到场景1
	{
		putimage(0, 0, &img_1);//导出第一关的图
		k = 1;
	}
	else if (scene == 2)
	{
		putimage(0, 0, &img_1);//导出第一关的图
		k = 2;
	}
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			/*原始土块*/
			if (stone[k][i][j].status == 0)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_0);////完全破碎的图片
			else if (stone[k][i][j].status == 1)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_1);//砖块初始化
			else if (stone[k][i][j].status == 2)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_2);////破碎1的图片
			else if (stone[k][i][j].status == 3)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_3);////破碎2的图片
			else if (stone[k][i][j].status == 4)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_4);////破碎3的图片
			else if (stone[k][i][j].status == 5)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_5);////破碎4的图片
			else if (stone[k][i][j].status == 6)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_6);////破碎5的图片
			else if (stone[k][i][j].status == 7)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_7);////破碎6的图片
																					/*煤块*/
			else if (stone[k][i][j].status == 11)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_1);//完整煤的图片
			else if (stone[k][i][j].status == 12)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_2);//煤破碎1的图片
			else if (stone[k][i][j].status == 13)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_3);//煤破碎2的图片
			else if (stone[k][i][j].status == 14)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_4);//煤破碎3的图片
			else if (stone[k][i][j].status == 15)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_5);//煤破碎4的图片
			else if (stone[k][i][j].status == 16)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_coal_0);//完全煤破碎的图片
																				   /*铜块*/
			else if (stone[k][i][j].status == 21)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_1);//完整铜的图片
			else if (stone[k][i][j].status == 22)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_2);//铜破碎1的图片
			else if (stone[k][i][j].status == 23)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_3);//铜破碎2的图片
			else if (stone[k][i][j].status == 24)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_4);//铜破碎3的图片
			else if (stone[k][i][j].status == 25)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_5);//铜破碎4的图片
			else if (stone[k][i][j].status == 26)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_6);//铜破碎5的图片
			else if (stone[k][i][j].status == 27)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_copper_0);//铜
																					 /*银块*/
			else if (stone[k][i][j].status == 31)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_1);//完整煤的图片
			else if (stone[k][i][j].status == 32)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_2);//煤破碎1的图片
			else if (stone[k][i][j].status == 33)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_3);//煤破碎2的图片
			else if (stone[k][i][j].status == 34)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_4);//煤破碎3的图片
			else if (stone[k][i][j].status == 35)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_5);//煤破碎4的图片
			else if (stone[k][i][j].status == 36)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_silver_0);//完全煤破碎的图片
		}
	if (scene == -1)//切换到场景商店
	{
		putimage(0, 0, &img_shop);//导出背景图片
		FlushBatchDraw();
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
	int i, j, k;
	/*判定人物是否站在砖块上*/
	G = 1;//重力加速度初值
	if (scene == 1)
		k = 1;
	else if (scene == 2)
		k = 2;
	else
		k = 1;
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[k][i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
				person.center_x <= stone[k][i][j].center_x + stone_width / 2 + 1 &&
				person.center_x >= stone[k][i][j].center_x - stone_width / 2 - 1 &&//判断人物与砖块之间横坐标之间的关系
				stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36
				)//判断是否踩在砖块上（通过判断人物与砖块之间纵坐标距离,判断人物与砖块之间横坐标之间的关系,砖块的状态）
			{
				exist_downstone = 1;//下端存在砖块
				G = 0;//重力加速度变为0
				person.v = 0;//踩到砖块是人物不下落
				person.center_y = stone[k][i][j].center_y - person_high / 2 - stone_high / 2;//保持人物与砖块的间距
				break;
			}
		}
	/*判断人物飞行时是否上方有砖块*/
	if (shoes_a == -2)//当人物上升时，若上方头顶存在砖块，则不能向上飞
	{
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				if (person.center_y - stone[k][i][j].center_y <= stone_high - person_high / 2 + stone_high / 2 &&
					person.center_y - stone[k][i][j].center_y >= (stone_high - person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
					person.center_x <= stone[k][i][j].center_x + person_width / 2 + stone_width / 2 - 10 &&
					person.center_x >= stone[k][i][j].center_x - person_width / 2 - stone_width / 2 + 10 &&//判断人物与砖块之间横坐标之间的关系
					stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
				{
					person.v = 0;//速度为零
					shoes_a = -1;//与重力加速度抵消，人物合外力为零，好处（1.可以时图片继续为向上升的图片 2.松手后可以落下）
					break;
				}
			}
	}
	/*判断是否在向下挖*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[k][i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
				person.center_x <= stone[k][i][j].center_x + stone_width / 2 &&
				person.center_x >= stone[k][i][j].center_x - stone_width / 2  //判断人物与砖块之间横坐标之间的关系
				)//判断是否踩在砖块上（通过判断人物与砖块之间纵坐标距离,判断人物与砖块之间横坐标之间的关系,砖块的状态）
			{
				if (digbf == 1 && stone[k][i][j].status != 0 && exist_downstone == 1 && stone[k][i][j].status != 16
					&& stone[k][i][j].status != 27 && stone[k][i][j].status != 36)//若可以挖且下方有砖块
				{
					person.center_x = stone[k][i][j].center_x;//保持人物与砖块d的横坐标相等
					static int speed_2 = 0;//用于限制向下挖的速度
					if (speed_2 < 70)
						speed_2++;
					else if (speed_2 == 70)
					{
						stone[k][i][j].status++;//状态加1
						speed_2 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//砖块消失
				}
			}
		}
	/*判断人物左边是否有砖块*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.center_x - stone[k][i][j].center_x <= stone_width / 2 + person_width / 2 &&
				person.center_x - stone[k][i][j].center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[k][i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
			{
				exist_leftstone = 1;//左端存在砖块
				if (digleftbf == 1)//开始向左挖
				{
					person.center_x = stone[k][i][j].center_x + stone_width / 2 + person_width / 2;//左边挖归位
					static int speed_3 = 0;//用于限制向左挖的速度
					if (speed_3 < 70)
						speed_3++;
					else if (speed_3 == 70)
					{
						stone[k][i][j].status++;//状态加1
						speed_3 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//砖块消失
				}
			}
		}
	/*判断人物右边是否有砖块*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_x - person.center_x <= stone_width / 2 + person_width / 2 &&
				stone[k][i][j].center_x - person.center_x >= (stone_width / 2 + person_width / 2) / 2 &&
				stone[k][i][j].center_y - person.center_y == person_high / 2 - stone_high / 2 &&
				stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
			{
				exist_rightstone = 1;//右端存在砖块
				if (digrightbf == 1)//开始向右挖
				{
					person.center_x = stone[k][i][j].center_x - stone_width / 2 - person_width / 2;//右边挖归位
					static int speed_3 = 0;//用于限制向右挖的速度
					if (speed_3 < 70)
						speed_3++;
					else if (speed_3 == 70)
					{
						stone[k][i][j].status++;//状态加1
						speed_3 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//砖块消失
				}
			}
		}
	/*判断人物飞行时左边是否有砖块*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.left_x == stone[k][i][j].right_x && person.left_y - stone[k][i][j].right_y <= person_high / 2 + stone_high / 2
				&& person.left_y - stone[k][i][j].right_y >= -person_high / 2 - stone_high / 2
				&& stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36 && shoes_a < 0)
				exist_flyleftstone = 1;
		}
	/*判断人物飞行时右边是否有砖块*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.right_x == stone[k][i][j].left_x && person.right_y - stone[k][i][j].left_y <= person_high / 2 + stone_high / 2
				&& person.right_y - stone[k][i][j].left_y >= -person_high / 2 - stone_high / 2
				&& stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36 && shoes_a < 0)
				exist_flyrightstone = 1;
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
		if (person.v <= -12)//限速设定
			person.v = -12;
		person.center_y = person.center_y + person.v;//人物竖直方向位置变化
		speed_1 = 0;
	}
	/*拾取物品*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].status == 16 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10)//拾取煤块
			{
				stone[k][i][j].status = 0;
				score = score + 10;//一个煤块10分
			}
			if (stone[k][i][j].status == 27 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10)//拾取铜块
			{
				stone[k][i][j].status = 0;
				score = score + 20;//一个铜块20分
			}
			if (stone[k][i][j].status == 36 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10)//拾取银块
			{
				stone[k][i][j].status = 0;
				score = score + 50;//一个银块50分
			}
		}
	/*显示分数*/
	TCHAR s[5];
	_stprintf(s, _T("%d"), score);
	outtextxy(100, 15, s);
	settextcolor(WHITE);
	/*游戏限制边界*/
	if (scene == 1)
	{
		if (person.left_x < 0)//限制左边界
			person.center_x = person_width / 2;
		else if (person.right_x > 900)//限制右边界
			person.center_x = 900 - person_width / 2;
		else if (person.top_y < 0)//限制上边界
			person.center_y = person_high / 2;
	}
	/*关卡跳跃*/
	if (scene == 1 && person.bottom_y > high)//第一关到第二关
	{
		scene = 2;
		person.center_y = -person_width / 2;
	}
	else if (scene == 2 && person.bottom_y < 0)//从第二关返回第一关
	{
		scene = 1;
		person.center_y = high - person_high;
	}
}
void status_change()//状态改变放置图片
{
	int i, j;
	if (scene != 0 && scene != -1)
	{
		/*当人物不动时转向正面 */
		if (shoes_a == 0 && digbf == 0 && digleftbf == 3 && digrightbf == 3)//当值都为初始值时的时候显示正面图片
		{
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//人物正面黑白版
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//人物正面彩版
			FlushBatchDraw();
			Sleep(1);
		}
		/*当按w时人物向上飞*/
		else if (shoes_a < 0 && flyleftbf == 0 && flyrightbf == 0)
		{
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			FlushBatchDraw();
			Sleep(1);
		}
		/*空中向左飞行 按wa*/
		else if (shoes_a < 0 && flyleftbf == 1)
		{
			if (exist_flyleftstone == 0)
				person.center_x = person.center_x - 1;//人物的中心坐标x减少
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			FlushBatchDraw();
			Sleep(1);
		}
		/*空中向右飞行 按wd*/
		else if (shoes_a < 0 && flyrightbf == 1)
		{
			if (exist_flyrightstone == 0)
				person.center_x = person.center_x + 1;//人物的中心坐标x减少
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			FlushBatchDraw();
			Sleep(1);
		}
		/*人物转变为向下挖的图片*/
		else if (digbf == 1)
		{
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_1, NOTSRCERASE);//人物向下挖黑白
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_2, SRCINVERT);//人物向下挖彩
			FlushBatchDraw();
			Sleep(1);
		}
		/*左边行走*/
		else if (digleftbf == 0)
		{
			person.center_x = person.center_x - 15;//人物的中心坐标x减少
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, left_i * person_width, 0, NOTSRCERASE);//放置向左走的黑白图片
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, left_i * person_width, 0, SRCINVERT);//放置向左走的彩图
			FlushBatchDraw();
			left_i++;
			Sleep(100);
			if (left_i == 3)
				left_i = 0;
		}
		/*向左挖土*/
		else if (digleftbf == 1)
		{
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_1, NOTSRCERASE);//人物向左挖黑白
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_2, SRCINVERT);//人物向左挖彩
			FlushBatchDraw();
			Sleep(1);
		}
		/*右边行走*/
		else if (digrightbf == 0)
		{
			person.center_x = person.center_x + 15;//人物的中心坐标x减少
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, right_i * person_width, person_high, NOTSRCERASE);//放置向右走的黑白图片
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, right_i * person_width, person_high, SRCINVERT);//放置向右走的彩图
			FlushBatchDraw();
			right_i++;//采用套图
			Sleep(100);
			if (right_i == 3)
				right_i = 0;
		}
		/*向右挖土*/
		else if (digrightbf == 1)
		{
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_1, NOTSRCERASE);//人物向右挖黑白
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_2, SRCINVERT);//人物向右挖彩
			FlushBatchDraw();
			Sleep(1);
		}
	}
	/*回归原值部分 下方控制部分可以改变值*/
	shoes_a = 0;//将加速度归为原值（按w改变）
	digbf = 0;//向下挖回归原值（按s改变）
	digleftbf = 3;//向左挖回归原值（按a改变）
	digrightbf = 3;//向右挖回归原值（按d改变）
	flyleftbf = 0;//向左飞回归原值
	flyrightbf = 0;//向右飞回归原值
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
	if (scene == 1 || scene == 2)//第一关
	{
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 0 && exist_downstone == 1)//如果按下a，下方有石块，左移动
		{
			digleftbf = 0;//表示不开挖
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 1)//如果按下a，左挖
		{
			digleftbf = 1;//表示开挖
		}
		if ((GetAsyncKeyState(0x41) & 0x8000) && exist_leftstone == 0 && exist_downstone == 0)//如果按下a，下方没石块，左飞移动
		{
			flyleftbf = 1;
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 0 && exist_downstone == 1)//如果按下d，下方有石块，右移动
		{
			digrightbf = 0;//表示不开挖
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 1)//如果按下d，右挖
		{
			digrightbf = 1;//表示开挖
		}
		if ((GetAsyncKeyState(0x44) & 0x8000) && exist_rightstone == 0 && exist_downstone == 0)//如果按下d，下方没石块，右移动
		{
			flyrightbf = 1;
		}
		if (GetAsyncKeyState(0x57) & 0x8000)//按w	
		{
			shoes_a = -2;
		}
		if (GetAsyncKeyState(0x53) & 0x8000 && exist_downstone == 1)//按s
		{
			digbf = 1;//表示可以挖
		}
		if (GetAsyncKeyState(0x20) & 0x8000 && person.bottom_y == apper_1stone && person.center_x<570 && person.center_x>500)//按空格
		{
			scene = -1;//进入商店
		}
	}
	if (scene == -1)
	{
		char input;
		if (kbhit())
		{
			input = getch();
			if (input == 'q')
				scene = 1;//退出商店
		}
	}
	/*回归原值部分 回归左右移动判断的值*/
	exist_leftstone = 0;
	exist_rightstone = 0;
	exist_downstone = 0;
	exist_flyleftstone = 0;
	exist_flyrightstone = 0;
}
void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

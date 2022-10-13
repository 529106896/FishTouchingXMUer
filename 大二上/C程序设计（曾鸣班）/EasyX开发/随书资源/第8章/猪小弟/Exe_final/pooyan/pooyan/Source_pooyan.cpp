#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#pragma comment(lib,"Winmm.lib")
#define HEIGHT 600
#define WIDTH 640
#define POOYAN_SPEED 3 //初始化猪妈的速度为5
#define ARROW_NUM 1000  //骨箭支数
#define ARROW_SPEED 3 //初始化骨箭的速度为3
#define WOLF_NUM 18 //狼的只数
#define BONE_NUM 5 //肉骨棒的个数
#define WOLF_NUM_2 15//第二关狼的只数
# define WOLF_SPEED_2 20//第二关狼的速度
#define POOYAN_SPEED_2 3//第二关初始化猪妈速度为3
#define SCORE_1 15//第一关通关分数
#define SCORE_2 20//第二关通关分数

int act = 0;  //控制游戏关卡
int num = 0;  //控制过关
int num_2 = 0;

			  //level_0相关数据初始化
IMAGE level0_bk;	//背景图
IMAGE pooyan_blue_0, pooyan_blue_0_bk, pooyan_blue_1, pooyan_blue_1_bk;
IMAGE pooyan_pink_0, pooyan_pink_0_bk, pooyan_pink_1, pooyan_pink_1_bk;
IMAGE pooyan_red_0, pooyan_red_0_bk, pooyan_red_1, pooyan_red_1_bk;
IMAGE ball_0, ball_0_bk, ball_1, ball_1_bk;
IMAGE wolf_0, wolf_0_bk, wolf_1, wolf_1_bk;
int pooyan_blue_0_x = 640, pooyan_blue_0_y = 425;
int pooyan_pink_0_x = 640, pooyan_pink_0_y = 425;
int pooyan_red_0_x = 640, pooyan_red_0_y = 425;
int ball_0_x = 640, ball_0_y = 400;
int wolf_0_x = 640, wolf_0_y = 425;
int score = 0;	//分数

//动画1相关数据初始化
IMAGE bk;
IMAGE pooyan_pink_3_bk_next, pooyan_pink_3_next, pooyan_pink_4_bk_next, pooyan_pink_4_next;
IMAGE wolf_3_bk_right, wolf_3_right, wolf_4_bk_right, wolf_4_right;
IMAGE pooyan_pink_3, pooyan_pink_3_bk, pooyan_pink_4, pooyan_pink_4_bk;
IMAGE pooyan_red_3, pooyan_red_3_bk, pooyan_red_4, pooyan_red_4_bk;
IMAGE wolf_3, wolf_3_bk, wolf_4, wolf_4_bk;
int pooyan_pink_3_x = 640, pooyan_pink_3_y = 425;
int pooyan_red_3_x = 640, pooyan_red_3_y = 425;
int pooyan_pink_3_next_x = 240, pooyan_pink_3_next_y = 425;
int wolf_1_right_x = 0, wolf_1_right_y = 425;
int wolf_1_left_x = 325, wolf_1_left_y = 425;

//level_1
IMAGE level1_bk;	//背景图
IMAGE level1_pooyan_red_bk, level1_pooyan_red_front;	//猪妈的图
IMAGE pooyan_red_down_bk, pooyan_red_down_front;
IMAGE pooyan_red1_down_bk, pooyan_red1_down_front;//猪妈下坠
IMAGE arrow_bk, arrow_front;//骨箭的图
IMAGE arrow_down_front, arrow_down_bk;//骨箭下坠的图
IMAGE level_wolf_bk, level_wolf_front;//狼的图
IMAGE level1_ball_bk, level1_ball_front;//气球的图
IMAGE ball_red_exploded_bk, ball_red_exploded_front;//气球爆炸的图
IMAGE rope_bk, rope_front;//绳子的图
IMAGE wolf1_bk_right, wolf1_right, wolf2_bk_right, wolf2_right;//狼向右走的图
IMAGE wolf_stop_bk1, wolf_stop_front1, wolf_stop_bk2, wolf_stop_front2;//狼被击中的图
IMAGE wolf_dead_bk1, wolf_dead_front1, wolf_dead_bk2, wolf_dead_front2;//狼下坠的图
IMAGE bullet_bk, bullet_front;//子弹的图
IMAGE bone_bk, bone_front;//肉骨棒的图
IMAGE ball_rise_bk, ball_rise_front;//上升的气球

//动画2相关数据初始化
IMAGE pooyan_blue_5, pooyan_blue_5_bk, pooyan_blue_6, pooyan_blue_6_bk;
IMAGE pooyan_pink_5, pooyan_pink_5_bk, pooyan_pink_6, pooyan_pink_6_bk;
IMAGE pooyan_red_5, pooyan_red_5_bk, pooyan_red_6, pooyan_red_6_bk;
IMAGE ball_5, ball_5_bk, ball_6, ball_6_bk;
IMAGE wolf_5, wolf_5_bk, wolf_6, wolf_6_bk;
int pooyan_blue_4_x = 640, pooyan_blue_4_y = 425;
int pooyan_pink_4_x = 640, pooyan_pink_4_y = 425;
int pooyan_red_4_x = 640, pooyan_red_4_y = 425;
int ball_4_x = 640, ball_4_y = 400;
int wolf_4_x = 640, wolf_4_y = 425;

struct level1_pooyan
{
	int x;
	int y;
	int status;//猪妈的状态 1为存活状态，2为下坠状态，3为游戏结束
	int down_x;//猪妈下坠的横坐标
	int down_y;//猪妈下坠的纵坐标
};
level1_pooyan pooyan;

struct level1_arrow
{
	int x;
	int y;
	int shot;//箭的状态 -1是未发射或消失，1是发射，2是下坠
};
level1_arrow arrow[ARROW_NUM];//骨箭的坐标，放箭的数组，判断放箭，on_off用来实现屏幕中只存在两支箭
int const_shot = -1; int on_off = 0;//与骨箭相关的两个整型变量

int rand_interval;//控制狼与狼之间的随机间隔
struct level1_wolf//尝试结构体写法
{
	int x;
	int y;
	int sign;//狼的状态 -1是未出现，1是存活，2是死前挣扎，3是快速下坠
	int down_x;//狼下落的横坐标
	int interval;//狼之间的间隔
};
level1_wolf wolf[WOLF_NUM];//定义狼的只数
int wolf_cst;//狼的一只一只出现

struct level1_ball //气球的操作基本与狼类似
{
	int y;
	int down_x;//气球的下落坐标
	int sign;//气球的状态 -1是未出现或消失，1是存在，2是爆炸
	int interval;//气球之间的间隔
	int shot;//修复bug，肉骨棒射中狼后，箭射破对应气球再次死亡的问题
};
level1_ball ball[WOLF_NUM];
int ball_cst;

struct level1_rope
{
	int y;
};
level1_rope rope;

struct level1_bullet
{
	int x;
	int y;
	int sign;//随机一群发射子弹的狼 0就不发，1就发
	int rand_attack_y;//狼发射子弹的位置
	int status;//子弹的状态 -1是未发射或消失，1是发射
};
level1_bullet bullet[WOLF_NUM];

struct level1_bone
{
	float x;
	float y;
	float vx;
	float vy;
	int status;
	int on_off;
	int awake;
};
level1_bone bone;

//level_2

IMAGE level2_bk;	//背景图
IMAGE stone_bk, stone_front;//石头的图

//第二关的变量
int pooyan_red_x, pooyan_red_y;//定义猪妈的坐标
int ball_x[WOLF_NUM_2], ball_y[WOLF_NUM_2];//气球的坐标
int wolf_x[WOLF_NUM_2], wolf_y[WOLF_NUM_2];//狼的坐标
int arrow_x[ARROW_NUM], arrow_y[ARROW_NUM];//箭的坐标
int wolf_sign[WOLF_NUM_2];//标记屏幕上的每一只狼用于判断狼是否出现，-1表示没有出现，1表示出现
int wolf_count;//用于控制屏幕上每一只狼
int ball_count;//用于控制屏幕上每一只气球
int count_shoot;//统计射了几只箭并便于后续控制
int shoot[ARROW_NUM];//判断是否射射箭的数组，-1表示没有出现，1表示出现
int rand_space;//随机出现的狼之间的间隔距离，避免重合
int string_y;//绳子纵坐标
int wolf_up_x[WOLF_NUM_2];//狼上升的位置的横坐标
int ball_up_x[WOLF_NUM_2];//气球上升时的横坐标
int ball_sign[WOLF_NUM_2];//标记每一个气球，-1表示没有出现，1表示出现
int stone_x;//石头的横纵坐标
int stone_y;
int arrow_num;//统计屏幕上箭的个数，确保屏幕上存在箭的个数固定；
int ball_interval[WOLF_NUM_2];//用来给爆炸后的气球延时处理
int wolf_interval[WOLF_NUM_2];//给死后的狼延时处理
int pooyan_red_dead_x;
int pooyan_red_dead_y;//处理猪妈死亡后的坐标
int pooyan_exit;//判断猪妈是否存活，1表示存活，2表示中弹死亡
int put_wolf=0;//推石头的狼

void startup_0();
void show_0();
void update_without_input_0();
void update_with_input_0();

void startup_3();
void show_3();
void update_without_input_3();

void startup_4();
void show_4();
void update_without_input_4();

void startup_1();
void show_1();
void update_without_input_1();
void update_with_input_1();

void startup_2();
void show_2();
void update_without_input_2();
void update_with_input_2();
void gameover();

void main()
{
	initgraph(WIDTH, HEIGHT);//定义一张640*600的游戏画布

	srand(time(NULL));
	startup_0();
	while (act == 0)
	{
		show_0();
		update_without_input_0();
		update_with_input_0();
	}

	startup_3();
	while (act == 1)
	{
		show_3();
		update_without_input_3();
		if (pooyan_red_3_x <= 0)
			break;
	}

	startup_1();
	while (act == 1)
	{
		show_1();//画出一帧图
		update_without_input_1();//更新无关输入的变量
		update_with_input_1();//更新输入
		if (num >= 10)
			break;
	}

	startup_4();
	while (act == 1)
	{
		show_4();
		update_without_input_4();
		if (pooyan_red_4_x <= 0)
			break;
	}

	startup_2();
	while (act == 1)
	{
		show_2();//绘图
		update_without_input_2();//不需要输入的更新
		update_with_input_2();//需要输入的更新
	}
	gameover();
	getch();
	//EndBatchDraw();
	closegraph();
}

void startup_0()
{
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("猪小弟"));//获得窗口句柄
	loadimage(&level0_bk, L"pooyan.jpg");	//背景图
	loadimage(&pooyan_blue_0, L"pooyan_blue0.jpg");
	loadimage(&pooyan_blue_0_bk, L"pooyan_blue0_bk.jpg");
	loadimage(&pooyan_blue_1, L"pooyan_blue1.jpg");
	loadimage(&pooyan_blue_1_bk, L"pooyan_blue1_bk.jpg");
	loadimage(&pooyan_pink_0, L"pooyan_pink0.jpg");
	loadimage(&pooyan_pink_0_bk, L"pooyan_pink0_bk.jpg");
	loadimage(&pooyan_pink_1, L"pooyan_pink1.jpg");
	loadimage(&pooyan_pink_1_bk, L"pooyan_pink1_bk.jpg");
	loadimage(&pooyan_red_0, L"pooyan_red0.jpg");
	loadimage(&pooyan_red_0_bk, L"pooyan_red0_bk.jpg");
	loadimage(&pooyan_red_1, L"pooyan_red1.jpg");
	loadimage(&pooyan_red_1_bk, L"pooyan_red1_bk.jpg");
	loadimage(&ball_0, L"ball0.jpg");
	loadimage(&ball_0_bk, L"ball0_bk.jpg");
	loadimage(&ball_1, L"ball1.jpg");
	loadimage(&ball_1_bk, L"ball1_bk.jpg");
	loadimage(&wolf_0, L"wolf0.jpg");
	loadimage(&wolf_0_bk, L"wolf0_bk.jpg");
	loadimage(&wolf_1, L"wolf1.jpg");
	loadimage(&wolf_1_bk, L"wolf1_bk.jpg");

	mciSendString(_T("open bk0.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	BeginBatchDraw();
}

void show_0()
{
	putimage(0, 0, &level0_bk);  //背景
	int i, j;
	for (j = 0; j < HEIGHT; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			if (i == wolf_0_x && j == wolf_0_y && wolf_0_x > 0)
			{
				Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(wolf_0_x, wolf_0_y, &wolf_0_bk, NOTSRCERASE);
					putimage(wolf_0_x, wolf_0_y, &wolf_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(wolf_0_x, wolf_0_y, &wolf_1_bk, NOTSRCERASE);
					putimage(wolf_0_x, wolf_0_y, &wolf_1, SRCINVERT);
				}
			}
			if (i == pooyan_blue_0_x && j == pooyan_blue_0_y && pooyan_blue_0_x > 0)
			{
				if (wolf_0_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_0_bk, NOTSRCERASE);
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_1_bk, NOTSRCERASE);
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_1, SRCINVERT);
				}
			}
			if (i == pooyan_pink_0_x && j == pooyan_pink_0_y && pooyan_pink_0_x > 0)
			{
				if (pooyan_blue_0_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_pink_0_x, pooyan_pink_0_y, &pooyan_pink_0_bk, NOTSRCERASE);
					putimage(pooyan_pink_0_x, pooyan_blue_0_y, &pooyan_pink_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_pink_0_x, pooyan_pink_0_y, &pooyan_pink_1_bk, NOTSRCERASE);
					putimage(pooyan_pink_0_x, pooyan_blue_0_y, &pooyan_pink_1, SRCINVERT);
				}
			}
			if (i == ball_0_x && j == ball_0_y && wolf_0_x <= 428)
			{
				if (ball_0_y > 380)
				{
					if (i / 10 % 2 == 0)
					{
						putimage(ball_0_x, ball_0_y, &ball_0_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_0, SRCINVERT);
					}
					if (i / 10 % 2 == 1)
					{
						putimage(ball_0_x, ball_0_y, &ball_1_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_1, SRCINVERT);
					}
				}
				if (ball_0_y <= 380)
				{
					if (j / 10 % 2 == 0)
					{
						putimage(ball_0_x, ball_0_y, &ball_0_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_0, SRCINVERT);
					}
					if (j / 10 % 2 == 1)
					{
						putimage(ball_0_x, ball_0_y, &ball_1_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_1, SRCINVERT);
					}
				}
			}
			if (i == pooyan_red_0_x && j == pooyan_red_0_y && pooyan_red_0_x > 0)
			{
				if (pooyan_pink_0_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_0_bk, NOTSRCERASE);
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_1_bk, NOTSRCERASE);
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_1, SRCINVERT);
				}
			}
		}
		
	}
	FlushBatchDraw();
}

void update_without_input_0()
{

	if (wolf_0_x > 0)
		wolf_0_x = wolf_0_x - 10;
	if (wolf_0_x <= 540 && pooyan_blue_0_x > 0)
		pooyan_blue_0_x = pooyan_blue_0_x - 10;
	if (wolf_0_x <= 440 && pooyan_pink_0_x > 0)
		pooyan_pink_0_x = pooyan_pink_0_x - 10;
	if (wolf_0_x <= 428)
	{
		if (ball_0_x > 175)
			ball_0_x = ball_0_x - 10;
		else if (ball_0_y > 280 && pooyan_red_0_x > 130)
			ball_0_y = ball_0_y - 10;
	}
	if (wolf_0_x <= 340 && pooyan_red_0_x > 0)
		pooyan_red_0_x = pooyan_red_0_x - 10;
}

void update_with_input_0()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == 's' && ball_0_y == 280)
			ball_0_y = 340;
		if (input == 'w' && ball_0_y == 340)
			ball_0_y = 280;
		if (input == 13 && ball_0_y == 280)
			act = 1;
	}
}

void startup_3()
{
	loadimage(&bk, L"bk.jpg");
	loadimage(&pooyan_pink_3, L"pooyan_pink0.jpg");
	loadimage(&pooyan_pink_3_bk, L"pooyan_pink0_bk.jpg");
	loadimage(&pooyan_pink_4, L"pooyan_pink1.jpg");
	loadimage(&pooyan_pink_4_bk, L"pooyan_pink1_bk.jpg");
	loadimage(&pooyan_red_3, L"pooyan_red0.jpg");
	loadimage(&pooyan_red_3_bk, L"pooyan_red0_bk.jpg");
	loadimage(&pooyan_red_4, L"pooyan_red1.jpg");
	loadimage(&pooyan_red_4_bk, L"pooyan_red1_bk.jpg");
	loadimage(&wolf_3, L"wolf0.jpg");
	loadimage(&wolf_3_bk, L"wolf0_bk.jpg");
	loadimage(&wolf_4, L"wolf1.jpg");
	loadimage(&wolf_4_bk, L"wolf1_bk.jpg");
	loadimage(&pooyan_pink_3_bk_next, L"pooyan_pink0_bk_next.jpg");
	loadimage(&pooyan_pink_3_next, L"pooyan_pink0_next.jpg");
	loadimage(&pooyan_pink_4_bk_next, L"pooyan_pink1_bk_next.jpg");
	loadimage(&pooyan_pink_4_next, L"pooyan_pink1_next.jpg");
	loadimage(&wolf_3_bk_right, L"wolf1_bk_right.jpg");
	loadimage(&wolf_3_right, L"wolf1_right.jpg");
	loadimage(&wolf_4_bk_right, L"wolf2_bk_right.jpg");
	loadimage(&wolf_4_right, L"wolf2_right.jpg");

	BeginBatchDraw();
}

void show_3()
{
	putimage(0, 0, &bk);
	int j;
	for (j = 0; j < WIDTH; j++)
	{
		if (j == pooyan_pink_0_x && pooyan_pink_0_x >= 240)
		{
			Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_3_bk, NOTSRCERASE);
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_3, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_4_bk, NOTSRCERASE);
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_4, SRCINVERT);
			}
		}
		if (j == pooyan_pink_3_next_x && pooyan_pink_3_x <= 230 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		{
			if (wolf_1_right_x <= 0)
				Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_3_bk_next, NOTSRCERASE);
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_3_next, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_4_bk_next, NOTSRCERASE);
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_4_next, SRCINVERT);
			}
		}
		if (j == wolf_1_right_x && pooyan_pink_3_x <= 230 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		{
			Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_3_bk_right, NOTSRCERASE);
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_3_right, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_4_bk_right, NOTSRCERASE);
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_4_right, SRCINVERT);
			}
		}
		if (j == wolf_1_left_x && pooyan_pink_3_next_x - wolf_1_right_x < 5)
		{
			Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4, SRCINVERT);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_4_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_4, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4, SRCINVERT);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_3_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_3, SRCINVERT);
			}
		}
		if (j == pooyan_red_3_x && wolf_1_left_x <= 320)
		{
			if (wolf_1_left_x < 0)
				Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_3_bk, NOTSRCERASE);
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_3, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_4_bk, NOTSRCERASE);
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_4, SRCINVERT);
			}
		}
	}
	FlushBatchDraw();
}

void update_without_input_3()
{
	if (pooyan_pink_3_x >= 240 && wolf_1_right_x < pooyan_pink_3_next_x)
		pooyan_pink_3_x = pooyan_pink_3_x - 10;
	if (pooyan_pink_3_x <= 240 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		pooyan_pink_3_next_x = pooyan_pink_3_next_x + 10;
	if (pooyan_pink_3_x <= 240 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		wolf_1_right_x = wolf_1_right_x + 30;
	if (wolf_1_left_x >= 0 && pooyan_pink_3_next_x - wolf_1_right_x < 5)
		wolf_1_left_x = wolf_1_left_x - 30;
	if (pooyan_red_3_x >= 0 && wolf_1_left_x <= 320)
		pooyan_red_3_x = pooyan_red_3_x - 30;
}

void startup_4()
{
	loadimage(&bk, L"bk.jpg");
	loadimage(&pooyan_blue_5, L"pooyan_blue0.jpg");
	loadimage(&pooyan_blue_5_bk, L"pooyan_blue0_bk.jpg");
	loadimage(&pooyan_blue_6, L"pooyan_blue1.jpg");
	loadimage(&pooyan_blue_6_bk, L"pooyan_blue1_bk.jpg");
	loadimage(&pooyan_pink_5, L"pooyan_pink0.jpg");
	loadimage(&pooyan_pink_5_bk, L"pooyan_pink0_bk.jpg");
	loadimage(&pooyan_pink_6, L"pooyan_pink1.jpg");
	loadimage(&pooyan_pink_6_bk, L"pooyan_pink1_bk.jpg");
	loadimage(&pooyan_red_5, L"pooyan_red0.jpg");
	loadimage(&pooyan_red_5_bk, L"pooyan_red0_bk.jpg");
	loadimage(&pooyan_red_6, L"pooyan_red1.jpg");
	loadimage(&pooyan_red_6_bk, L"pooyan_red1_bk.jpg");
	loadimage(&wolf_5, L"wolf0.jpg");
	loadimage(&wolf_5_bk, L"wolf0_bk.jpg");
	loadimage(&wolf_6, L"wolf1.jpg");
	loadimage(&wolf_6_bk, L"wolf1_bk.jpg");

	BeginBatchDraw();
}

void show_4()
{
	putimage(0, 0, &bk);  //背景
	int i, j;
	for (j = 0; j < HEIGHT; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			if (i == wolf_4_x && j == wolf_4_y && wolf_4_x > 0)
			{
				Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(wolf_4_x, wolf_4_y, &wolf_5_bk, NOTSRCERASE);
					putimage(wolf_4_x, wolf_4_y, &wolf_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(wolf_4_x, wolf_4_y, &wolf_6_bk, NOTSRCERASE);
					putimage(wolf_4_x, wolf_4_y, &wolf_6, SRCINVERT);
				}
			}
			if (i == pooyan_blue_4_x && j == pooyan_blue_4_y && pooyan_blue_4_x > 0)
			{
				if (wolf_4_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_5_bk, NOTSRCERASE);
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_6_bk, NOTSRCERASE);
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_6, SRCINVERT);
				}
			}
			if (i == pooyan_pink_4_x && j == pooyan_pink_4_y && pooyan_pink_4_x > 0)
			{
				if (pooyan_blue_4_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_pink_4_x, pooyan_pink_4_y, &pooyan_pink_5_bk, NOTSRCERASE);
					putimage(pooyan_pink_4_x, pooyan_blue_4_y, &pooyan_pink_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_pink_4_x, pooyan_pink_4_y, &pooyan_pink_6_bk, NOTSRCERASE);
					putimage(pooyan_pink_4_x, pooyan_blue_4_y, &pooyan_pink_6, SRCINVERT);
				}
			}
			if (i == pooyan_red_4_x && j == pooyan_red_4_y && pooyan_red_4_x > 0)
			{
				if (pooyan_pink_4_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_5_bk, NOTSRCERASE);
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_6_bk, NOTSRCERASE);
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_6, SRCINVERT);
				}
			}
		}
	}
	FlushBatchDraw();
}

void update_without_input_4()
{
	if (wolf_4_x > 0)
		wolf_4_x = wolf_4_x - 10;
	if (wolf_4_x <= 540 && pooyan_blue_4_x > 0)
		pooyan_blue_4_x = pooyan_blue_4_x - 10;
	if (wolf_4_x <= 440 && pooyan_pink_4_x > 0)
		pooyan_pink_4_x = pooyan_pink_4_x - 10;
	if (wolf_4_x <= 340 && pooyan_red_4_x > 0)
		pooyan_red_4_x = pooyan_red_4_x - 10;
}

void startup_1()
{

	mciSendString(L"close bkmusic", NULL, 0, NULL);

	mciSendString(L"open bk1.mp3 alias bkm", NULL, 0, NULL);
	mciSendString(L"play bkm repeat", NULL, 0, NULL);
	loadimage(&level1_bk, L"level1_bk.jpg");	//背景图
	loadimage(&level1_pooyan_red_bk, L"level1_pooyan_red_bk.jpg");
	loadimage(&level1_pooyan_red_front, L"level1_pooyan_red_front.jpg");//猪妈的图
	loadimage(&pooyan_red_down_bk, L"pooyan_red_down_bk.jpg");
	loadimage(&pooyan_red_down_front, L"pooyan_red_down_front.jpg");
	loadimage(&pooyan_red1_down_bk, L"pooyan_red1_down_bk.jpg");
	loadimage(&pooyan_red1_down_front, L"pooyan_red1_down_front.jpg");//猪妈下坠的图
	loadimage(&arrow_bk, L"arrow_bk.jpg");
	loadimage(&arrow_front, L"arrow_front.jpg");//骨箭的图
	loadimage(&arrow_down_bk, L"arrow_down_bk.jpg");
	loadimage(&arrow_down_front, L"arrow_down_front.jpg");//骨箭下坠的图
	loadimage(&level1_ball_bk, L"level1_ball_bk.jpg");//气球的图
	loadimage(&level1_ball_front, L"level1_ball_front.jpg");
	//神奇！！！气球的图要是放在狼的图下面会出bug，show的时候明明没有show球，它也会产生影响，效果类似于x光透视
	loadimage(&ball_red_exploded_bk, L"ball_red_exploded_bk.jpg");
	loadimage(&ball_red_exploded_front, L"ball_red_exploded_front.jpg");//气球爆炸的图
	loadimage(&ball_rise_bk, L"ball_rise_bk.jpg");
	loadimage(&ball_rise_front, L"ball_rise_front.jpg");//气球上升的图
	loadimage(&level_wolf_bk, L"level_wolf_bk.jpg");
	loadimage(&level_wolf_front, L"level_wolf_front.jpg");//狼的图
	loadimage(&rope_bk, L"rope_bk.jpg");
	loadimage(&rope_front, L"rope_front.jpg");//绳子的图
	loadimage(&wolf1_bk_right, L"wolf1_bk_right.jpg");
	loadimage(&wolf1_right, L"wolf1_right.jpg");
	loadimage(&wolf2_bk_right, L"wolf2_bk_right.jpg");
	loadimage(&wolf2_right, L"wolf2_right.jpg");//狼向右行走的图
	loadimage(&wolf_stop_bk1, L"wolf_stop_bk1.jpg");
	loadimage(&wolf_stop_front1, L"wolf_stop_front1.jpg");
	loadimage(&wolf_stop_bk2, L"wolf_stop_bk2.jpg");
	loadimage(&wolf_stop_front2, L"wolf_stop_front2.jpg");//狼被击中的图
	loadimage(&wolf_dead_bk1, L"wolf_dead_bk1.jpg");
	loadimage(&wolf_dead_front1, L"wolf_dead_front1.jpg");
	loadimage(&wolf_dead_bk2, L"wolf_dead_bk2.jpg");
	loadimage(&wolf_dead_front2, L"wolf_dead_front2.jpg");//狼下坠的图
	loadimage(&bullet_bk, L"bullet_bk.jpg");
	loadimage(&bullet_front, L"bullet_front.jpg");//子弹的图
	loadimage(&bone_bk, L"level1_bone_bk.jpg");
	loadimage(&bone_front, L"level1_bone_front.jpg");//肉骨棒的图

	pooyan.x = 500, pooyan.y = 140;//猪妈的初始坐标
	pooyan.status = 1;
	int i;
	for (i = 0; i < ARROW_NUM; i++)
	{
		arrow[i].shot = -1;
		arrow[i].x = pooyan.x - 25; //25保证了箭从箭头射出
	}//初始化
	rand_interval = rand() % 2500 + 1000;//控制狼与狼之间的随机间隔
	wolf_cst = -1;//初始一只狼都没有
	ball_cst = -1;//初始一只气球都没有

				  //思路，先实现狼一个一个出现，然后用随机函数来控制狼的出现时间 类似于static 静态变量的方法
	for (i = 0; i < WOLF_NUM; i++)
	{
		wolf[i].interval = { 0 };
		ball[i].interval = { 0 };
		wolf[i].x = 0;
		wolf[i].y = 7;//保证开始时狼的纵坐标和上面的悬崖平台相贴
		ball[i].y = 7;
		wolf[i].sign = -1;
		ball[i].sign = -1;
		wolf[i].down_x = rand() % 300 + 90;//随机一下所有的狼的下落横坐标
		ball[i].down_x = wolf[i].down_x;
		bullet[i].sign = rand() % 2;//随机一群发射子弹的狼
		ball[i].shot = 0;
	}
	for (i = 0; i < WOLF_NUM; i++)
	{
		if (bullet[i].sign == 1)//0不发射，1发射
			bullet[i].rand_attack_y = rand() % 100 + 90;//随机狼发着子弹的位置
		bullet[i].x = wolf[i].down_x;
		bullet[i].y = bullet[i].rand_attack_y;
		bullet[i].status = -1;
	}
	//肉骨棒的初始化
	bone.x = 516;
	bone.y = 120;
	bone.vx = 1.8;
	bone.vy = 0.2;
	bone.status = 1;
	bone.on_off = 0;
	bone.awake = 0;
	BeginBatchDraw();//开始绘画
}

void show_1()
{
	int i;
	putimage(0, 0, &level1_bk);//背景图

	putimage(530, 113, 20, rope.y - 100, &rope_bk, 530, 120, NOTSRCERASE);
	putimage(530, 113, 20, rope.y - 100, &rope_front, 530, 120, SRCINVERT);//绳子的图

	if (pooyan.status == 1)
	{
		putimage(pooyan.x, pooyan.y, &level1_pooyan_red_bk, NOTSRCERASE);
		putimage(pooyan.x, pooyan.y, &level1_pooyan_red_front, SRCINVERT);//猪妈的图
	}
	if (pooyan.status == 2)
	{
		putimage(pooyan.down_x, pooyan.down_y + 30, &pooyan_red1_down_bk, NOTSRCERASE);
		putimage(pooyan.down_x, pooyan.down_y + 30, &pooyan_red1_down_front, SRCINVERT);
		putimage(pooyan.x, pooyan.y, &pooyan_red_down_bk, NOTSRCERASE);
		putimage(pooyan.x, pooyan.y, &pooyan_red_down_front, SRCINVERT);//猪妈下坠的图

	}
	for (i = 0; i < ARROW_NUM; i++)
	{
		if (arrow[i].shot == 1)//if (shot[i])与	if (shot[i]==1)的运行速度天差地别，这是一个非常奇妙的事
		{
			putimage(arrow[i].x, arrow[i].y, &arrow_bk, NOTSRCERASE);
			putimage(arrow[i].x, arrow[i].y, &arrow_front, SRCINVERT);//骨箭的图
		}
		if (arrow[i].shot == 2)
		{
			putimage(arrow[i].x, arrow[i].y, &arrow_down_bk, NOTSRCERASE);
			putimage(arrow[i].x, arrow[i].y, &arrow_down_front, SRCINVERT);//骨箭下坠的图
		}
	}
	for (i = 0; i < WOLF_NUM; i++)
	{
		if (wolf[i].sign == 1)
		{
			if (wolf[i].x < wolf[i].down_x)
			{
				if (wolf[i].x % 10 <= 5)//负责减速本来写的是wolf[i].x % 2 ==0，跑起来像飞毛腿一样
				{
					putimage(wolf[i].x, wolf[i].y + 20, &wolf1_bk_right, NOTSRCERASE);
					putimage(wolf[i].x, wolf[i].y + 20, &wolf1_right, SRCINVERT);
				}
				else if (wolf[i].x % 10>5)
				{
					putimage(wolf[i].x, wolf[i].y + 20, &wolf2_bk_right, NOTSRCERASE);
					putimage(wolf[i].x, wolf[i].y + 20, &wolf2_right, SRCINVERT);
				}
			}
			else if (wolf[i].x >= wolf[i].down_x)//下落
			{
				putimage(wolf[i].x, wolf[i].y, &level_wolf_bk, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y, &level_wolf_front, SRCINVERT);
			}
		}
		if (wolf[i].sign == 2)//狼被击中
		{
			if (wolf[i].interval % 30 <= 15)
			{
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_stop_bk1, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_stop_front1, SRCINVERT);
			}
			else if (wolf[i].interval % 30 > 15)
			{
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_stop_bk2, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_stop_front2, SRCINVERT);
			}
		}
		if (wolf[i].sign == 3)
		{
			//快速下坠
			if (wolf[i].y % 100 <= 50)
			{
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_dead_bk1, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_dead_front1, SRCINVERT);
			}
			else if (wolf[i].y % 100 > 50)
			{
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_dead_bk2, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y + 50, &wolf_dead_front2, SRCINVERT);
			}
		}
		if (wolf[i].sign == 4)
		{
			if (wolf[i].x % 10 <= 5)
			{
				putimage(wolf[i].x, wolf[i].y + 20, &wolf1_bk_right, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y + 20, &wolf1_right, SRCINVERT);
			}
			else if (wolf[i].x % 10 > 5)
			{
				putimage(wolf[i].x, wolf[i].y + 20, &wolf2_bk_right, NOTSRCERASE);
				putimage(wolf[i].x, wolf[i].y + 20, &wolf2_right, SRCINVERT);
			}
		}
	}

	for (i = 0; i < WOLF_NUM; i++)
	{
		//气球正常下落
		if (ball[i].sign == 1 && wolf[i].x >= wolf[i].down_x)
		{
			putimage(ball[i].down_x, ball[i].y, &level1_ball_bk, NOTSRCERASE);
			putimage(ball[i].down_x, ball[i].y, &level1_ball_front, SRCINVERT);
		}
		//气球爆炸
		if (ball[i].sign == 2)
		{
			putimage(ball[i].down_x + 25, ball[i].y + 5, &ball_red_exploded_bk, NOTSRCERASE);
			putimage(ball[i].down_x + 25, ball[i].y + 5, &ball_red_exploded_front, SRCINVERT);
		}
		//气球上升
		if (ball[i].sign == 3)
		{
			putimage(ball[i].down_x + 25, ball[i].y + 5, &ball_rise_bk, NOTSRCERASE);
			putimage(ball[i].down_x + 25, ball[i].y + 5, &ball_rise_front, SRCINVERT);
		}
	}
	for (i = 0; i < WOLF_NUM; i++)
	{
		if (bullet[i].sign == 1)
		{
			if (bullet[i].status == 1)
			{
				putimage(bullet[i].x + 20, bullet[i].y + 30, &bullet_bk, NOTSRCERASE);
				putimage(bullet[i].x + 20, bullet[i].y + 30, &bullet_front, SRCINVERT);
			}
		}
	}
	if (bone.status == 1 || bone.status == 2)
	{
		putimage(bone.x, bone.y, &bone_bk, NOTSRCERASE);
		putimage(bone.x, bone.y, &bone_front, SRCINVERT);
	}
	TCHAR s[80];
	_stprintf_s(s, _T("%06d"), score);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(2, 5, _T("分数:"));
	outtextxy(55, 5, s);
	FlushBatchDraw();//结束当前帧的绘画
}

void update_without_input_1()
{
	int i, j;
	rope.y = pooyan.y;

	//骨箭的模块
	static int arrow_speed = 0;//定义静态变量arrow_speed来控制箭的速度
	if (arrow_speed < ARROW_SPEED)
		arrow_speed++;
	if (arrow_speed == ARROW_SPEED)
	{
		for (i = 0; i < ARROW_NUM; i++)
		{
			if (arrow[i].shot == 1)
			{
				if (arrow[i].x >-80)//扫描所有的箭，如果箭接受了发箭指令，那只箭就开始进行自减，进行向左移动，由于箭图的put是从箭头开始的，所以-80是为了隐藏箭身
					arrow[i].x--;//为了接下来箭和其他元素进行交互，这种箭的速度定为1，从而使箭的移动更细腻一点
				if (arrow[i].x == -80)
					arrow[i].shot = -1;
			}
			if (arrow[i].shot == 2)
			{
				if (arrow[i].y < HEIGHT + 50)
					arrow[i].y++;
				if (arrow[i].y == HEIGHT + 50)
					arrow[i].shot = -1;
			}
		}
		arrow_speed = 0;
	}
	on_off = 0;//负责刷新
	for (i = 0; i < ARROW_NUM; i++)
	{
		if (arrow[i].shot>0)//如果有箭的状态是在屏幕上移动的，那么开始计数
			on_off++;
	}


	//狼的模块

	static int rand_wolf = 0;//用于狼的延迟出现
	if (rand_wolf < rand_interval)
		rand_wolf++;
	if (rand_wolf == rand_interval&&wolf_cst < WOLF_NUM - 1)
		//wolf_cst<WOLF_NUM-1修复结尾bug，毕竟wolf[wolf_cst].sign是数组，不能越界
		//定义wolf[].sign只能存WOLF_NUM个数据，wolf_cst < WOLF_NUM-1，（-1<WOLF_NUM-1，即0<WOLF_NUM，即WOLF_NUM只狼），所以WOLF_NUM-1这个数再大一点，wolf[].sign就越界，
		//如果单独显示，sign越界没问题，但是在一个复杂的界面上，就不行，数据必须精确，如果WOLF_NUM-1再大一点，结尾就变成了狼和箭不能同时正常运行的尴尬局面	
	{
		wolf_cst++;//一只一只狼的赋值，体现变化

		ball_cst++;//气球
		if (wolf_cst >= 0)
			wolf[wolf_cst].sign = 1;//狼的赋值

		if (ball_cst >= 0)
			ball[ball_cst].sign = 1;//气球的赋值
									//普天同庆，修复最后一只狼的bug，自加后，立刻赋值，最为合理和安全，放外面，就是错，就是不对！
		rand_interval = rand() % 2500 + 1000;//rand()%m+n  m为随机变化幅度   n为固定变化幅度
		rand_wolf = 0;
	}
	//遍历，找到落到地面的狼，之后向右跑
	for (i = 0; i < WOLF_NUM; i++)
		if (wolf[i].y >= 490 && wolf[i].sign == 1)
		{
			wolf[i].sign = 4;
			ball[i].sign = -1;
		}
	//狼的移动速度
	static int wolf_speed = 0;
	if (wolf_speed < 20)
		wolf_speed++;
	if (wolf_speed == 20)
	{
		for (i = 0; i < WOLF_NUM; i++)
		{
			//开始时的向右跑
			if (wolf[i].sign == 1 && wolf[i].x < wolf[i].down_x)
				wolf[i].x++;
			//下落
			if (wolf[i].sign == 1 && wolf[i].x == wolf[i].down_x)
			{
				wolf[i].y++; ball[i].y++;
			}
			//快速下落
			if (wolf[i].sign == 3)
				wolf[i].y += 5;
			//狼下落到地面向右行走
			if (wolf[i].sign == 4)
				wolf[i].x++;
			if (ball[i].sign == 3)
				ball[i].y--;
		}
		wolf_speed = 0;
	}

	for (j = 0; j < WOLF_NUM; j++)
	{
		if ((bone.x >= wolf[j].down_x - 8) && (bone.x <= wolf[j].down_x + 40) && (bone.y > ball[j].y + 30) && (bone.y <= ball[j].y + 65))
		{
			wolf[j].sign = 2;//狼死前挣扎
			ball[j].sign = 3;//上升
			ball[j].shot = 1;
		}
	}
	//箭射中气球的判断
	for (i = 0; i < ARROW_NUM; i++)
	{
		for (j = 0; j < WOLF_NUM; j++)
		{
			//删除if (arrow[i].shot == 1)，实现下坠的箭可以扎破下方的气球
			if ((arrow[i].x >= ball[j].down_x - 8) && (arrow[i].x <= ball[j].down_x + 40) && (arrow[i].y >= ball[j].y - 3) && (arrow[i].y <= ball[j].y + 30))
			{
				//骨箭下坠
				ball[j].sign = 2;//气球爆炸
				if (ball[j].shot == 0)
				{
					wolf[j].sign = 2;//狼死前挣扎
				}
				arrow[i].x = -50;//箭消失，刷新下一支
				score += 700;//分数
			}
			if ((arrow[i].x >= wolf[j].down_x - 8) && (arrow[i].x <= wolf[j].down_x + 40) && (arrow[i].y > ball[j].y + 30) && (arrow[i].y <= ball[j].y + 65))
			{
				if (wolf[j].sign == 1)
					arrow[i].shot = 2;//骨箭射中狼，骨箭下坠（ps:之后加射中狼两次，狼就死）
				if (ball[j].sign == 4)
				{
					ball[j].sign = 2;
					ball[i].y = -1;
					arrow[i].x = -50;//箭消失，刷新下一支
					score += 200;
				}
			}
			if ((bone.x >= wolf[j].down_x - 8) && (bone.x <= wolf[j].down_x + 40) && (bone.y > ball[j].y + 30) && (bone.y <= ball[j].y + 65))
			{
				wolf[j].sign = 2;//狼死前挣扎
				ball[j].sign = 3;//上升	
			}
		}
	}
	//狼挣扎状态变化的延迟
	for (j = 0; j < WOLF_NUM; j++)
	{
		if (wolf[j].sign == 2)
			wolf[j].interval++;
		if (wolf[j].interval == 600)
		{
			score += 500;
			wolf[j].sign = 3;
			wolf[j].down_x = -1;
			wolf[j].interval = 0;
			num++;
		}
	}
	//气球爆炸状态变化的延迟
	for (j = 0; j < WOLF_NUM; j++)
	{
		if (ball[j].sign == 2)
			ball[j].interval++;
		if (ball[j].interval == 100)//将ball的interval的值定为100，修复了紧接着射出的第二支箭也消失的bug
		{
			ball[j].y = -1;//修复bug，将被射中的气球去掉，否则当箭再次出现在下坠的狼的上方的时候，下坠的狼还会暂停一下，也就是又被射死了一次
			ball[j].sign = -1;
			ball[j].down_x = -1;
			ball[j].interval = 0;
		}
	}
	//子弹的模块
	//子弹的发射与移动
	for (i = 0; i < WOLF_NUM; i++)
	{
		if (wolf[i].y == bullet[i].rand_attack_y&& wolf[i].sign == 1)//当狼走到该发子弹的位置时，子弹状态变位1，即发射状态
			bullet[i].status = 1;
	}
	static int bullet_speed = 0;//子弹的移动速度
	if (bullet_speed < 10)
		bullet_speed++;
	if (bullet_speed == 10)
	{
		for (i = 0; i < WOLF_NUM; i++)
		{
			if (bullet[i].status == 1)
			{
				bullet[i].x += 2;
				bullet[i].y++;
			}
		}
		bullet_speed = 0;
	}
	//子弹状态的变化
	for (i = 0; i < WOLF_NUM; i++)
	{
		//猪妈中弹
		if ((bullet[i].x >= pooyan.x) && (bullet[i].x < pooyan.x + 5) && (bullet[i].y >= pooyan.y - 5) && (bullet[i].y <= pooyan.y + 45))
		{
			pooyan.status = 2;
			pooyan.down_x = pooyan.x;
			pooyan.down_y = pooyan.y;
		}
		//猪妈用吊篮的顶部挡掉子弹
		if ((bullet[i].x >= pooyan.x - 5) && (bullet[i].x <= pooyan.x + 50) && (bullet[i].y >= pooyan.y - 20) && (bullet[i].y < pooyan.y))
		{
			bullet[i].status = -1;
			bullet[i].x = -1;
			bullet[i].y = -1;
		}
		//猪妈用吊篮的底部挡掉子弹
		if ((bullet[i].x >= pooyan.x - 15) && (bullet[i].x <= pooyan.x + 50) && (bullet[i].y >= pooyan.y + 35))
		{
			bullet[i].status = -1;
			bullet[i].x = -1;
			bullet[i].y = -1;
		}
	}
	//子弹击中猪妈后，猪妈的快速下坠
	static int speed_pooyan_red = 0;//控制猪妈下坠的速度
	if (speed_pooyan_red < 2)
		speed_pooyan_red++;
	if (speed_pooyan_red == 2)
	{
		if (pooyan.status == 2)
			pooyan.down_y++;
		speed_pooyan_red = 0;
	}
	//猪妈死亡，游戏结束
	if (pooyan.down_y >= HEIGHT)
		act = 3;
	//肉骨棒模块
	if (pooyan.y == 120 && bone.status == 1)
	{
		bone.status = 2;
	}
	if (bone.status == 2 && bone.on_off == 0)
	{
		bone.x = pooyan.x - 10;
		bone.y = pooyan.y + 45;
	}
	static int l = 0;

	if (bone.status == 2 && bone.on_off == 1)
	{
		if (l < 4)
			l++;
		if (l == 4)
		{
			bone.x -= bone.vx;
			bone.y += bone.vy;
			if (bone.x <= 300)
				bone.vy += 0.01;
			l = 0;
		}
	}

	if (bone.x <= 40 || bone.y > 500)
	{
		bone.on_off = 0;
		bone.status = -1;
		bone.x = 516;
		bone.y = 120;
		bone.awake = 1;
		bone.vx = 1.8,
			bone.vy = 0.2;
	}
	static int x = 0;
	if (bone.awake == 1)
	{
		if (x < 3000)
			x++;
		if (x == 3000)
		{
			bone.status = 1;
			x = 0;
			bone.awake = 0;
		}
	}

}

void update_with_input_1()
{
	int i;
	static int speed_pooyan = 0;//定义静态变量speed_pooyan来控制猪的速度
	if (GetAsyncKeyState(0x57) & 0x8000 && pooyan.y >= 113 && pooyan.status == 1)//w，猪妈向上移动
	{
		if (speed_pooyan < POOYAN_SPEED)
			speed_pooyan++;
		if (speed_pooyan == POOYAN_SPEED)
		{
			pooyan.y -= 1;//写1用来细腻的移动
			speed_pooyan = 0;
		}
	}
	if (GetAsyncKeyState(0x53) & 0x8000 && pooyan.y <= 400 && pooyan.status == 1)//s，猪妈向下移动
	{
		if (speed_pooyan < POOYAN_SPEED)
			speed_pooyan++;
		if (speed_pooyan == POOYAN_SPEED)
		{
			pooyan.y += 1;//写1用来细腻的移动
			speed_pooyan = 0;
		}
	}
	char input;
	int judge;/*直接用无冲突按键的函数，会出现问题(问题为GetAsyncKeyState函数判断太灵敏，你感觉是按了一下'j'，
			  但是const_shot的自加进行了很多次，所以无法实现按一次射一只箭，但是无冲突按键又对游戏性有极大的提高），所以用judge跳转一下*/
	judge = 0;//初始化judge，并刷新judge以保证正常情况下，能随时接受按键'j'的指令
	if (kbhit())
	{
		input = getch();
		if (input == 'j')
			judge = 1;
	}
	if (GetAsyncKeyState(0x4A) & 0x8000 && (on_off < 2))//j  (on_off<2)用来控制屏幕中只能存在两支箭，否则输入无效
	{
		/*如果按一次j，第一支箭会一直向左射，如果第二次按j，数组的1启动，第二支箭会一直向左射，从举例到一般的思考中得出骨箭元素的写法*/
		if (judge == 1)
		{
			if (bone.status == 2)
			{
				bone.on_off = 1;
				mciSendString(L"close py", NULL, 0, NULL);
				mciSendString(L"open py.mp3 alias py", NULL, 0, NULL);
				mciSendString(L"play py", NULL, 0, NULL);
			}
			else
			{
				const_shot++;//计算按了多少次j
				arrow[const_shot].shot = 1;//如果按下了'j'键，就把一支箭从-1状态变为1；按一次'j'，const_shot就自加一次，相当于换箭的开关
				arrow[const_shot].y = pooyan.y + 43;//跟踪按下'j'时，那只箭的Y坐标，该语句不能放在update_without_input之中，因为箭一旦射出，就无需更新

				mciSendString(L"close shot", NULL, 0, NULL);
				mciSendString(L"open shot.mp3 alias shot", NULL, 0, NULL);
				mciSendString(L"play shot", NULL, 0, NULL);
			}
		}
	}
}

void startup_2()
{
	int i;
//	put_wolf = 0;//初始化推石头的狼为0；
	stone_x = 450;
	stone_y = 20;//石头的初始坐标
	pooyan_red_x = 500;
	pooyan_red_y = 120;//猪妈的初始坐标
	pooyan_exit = 1;//初始化猪妈存活
	for (i = 0; i < ARROW_NUM; i++)
	{
		shoot[i] = -1;//没有箭射出
		arrow_x[i] = pooyan_red_x - 25;
		arrow_y[i] = pooyan_red_y + 43;//初始化箭的坐标
	}
	count_shoot = -1;
	arrow_num = 0;//初始化屏幕上没有箭时计数为0；
	for (i = 0; i < WOLF_NUM_2; i++)//初始化狼的坐标
	{
		wolf_x[i] = 0;
		wolf_y[i] = 505;
		wolf_sign[i] = -1;//初始化将所有狼标记为-1表示没有狼出现
		wolf_up_x[i] = rand() % 250 + 90;//初始化狼和气球上升时的坐标
		wolf_interval[i] = { 0 };
	}
	wolf_count = -1;//初始化屏幕上没有狼,也没有气球；
	ball_count = -1;
	rand_space = rand() % 2500 + 1000;//控制狼与狼之间的随机间隔
	for (i = 0; i < WOLF_NUM_2; i++)//初始化气球坐标
	{
		ball_x[i] = wolf_x[i];
		ball_y[i] = wolf_y[i];//通过图层遮盖让气球和狼完美衔接
		ball_sign[i] = -1;
		ball_up_x[i] = wolf_up_x[i];
		ball_interval[i] = { 0 };
	}
	loadimage(&level2_bk, L"level2_bk.jpg");	//背景图
	loadimage(&stone_bk, L"stone_bk.jpg");
	loadimage(&stone_front, L"stone_front.jpg");//石头的图
	loadimage(&level1_pooyan_red_bk, L"level1_pooyan_red_bk.jpg");
	loadimage(&level1_pooyan_red_front, L"level1_pooyan_red_front.jpg");//猪妈的图
	loadimage(&pooyan_red_down_bk, L"pooyan_red_down_bk.jpg");
	loadimage(&pooyan_red_down_front, L"pooyan_red_down_front.jpg");
	loadimage(&pooyan_red1_down_bk, L"pooyan_red1_down_bk.jpg");
	loadimage(&pooyan_red1_down_front, L"pooyan_red1_down_front.jpg");//猪妈下坠的图
	loadimage(&arrow_bk, L"arrow_bk.jpg");
	loadimage(&arrow_front, L"arrow_front.jpg");//骨箭的图
	loadimage(&arrow_down_bk, L"arrow_down_bk.jpg");
	loadimage(&arrow_down_front, L"arrow_down_front.jpg");//骨箭下坠的图
	loadimage(&level1_ball_bk, L"level1_ball_bk.jpg");//气球的图
	loadimage(&level1_ball_front, L"level1_ball_front.jpg");
	loadimage(&ball_red_exploded_bk, L"ball_red_exploded_bk.jpg");
	loadimage(&ball_red_exploded_front, L"ball_red_exploded_front.jpg");//气球爆炸的图
	loadimage(&level_wolf_bk, L"level_wolf_bk.jpg");
	loadimage(&level_wolf_front, L"level_wolf_front.jpg");//狼的图
	loadimage(&rope_bk, L"rope_bk.jpg");
	loadimage(&rope_front, L"rope_front.jpg");//绳子的图
	loadimage(&wolf1_bk_right, L"wolf1_bk_right.jpg");
	loadimage(&wolf1_right, L"wolf1_right.jpg");
	loadimage(&wolf2_bk_right, L"wolf2_bk_right.jpg");
	loadimage(&wolf2_right, L"wolf2_right.jpg");//狼向右行走的图
	loadimage(&wolf_stop_bk1, L"wolf_stop_bk1.jpg");
	loadimage(&wolf_stop_front1, L"wolf_stop_front1.jpg");
	loadimage(&wolf_stop_bk2, L"wolf_stop_bk2.jpg");
	loadimage(&wolf_stop_front2, L"wolf_stop_front2.jpg");//狼被击中的图
	loadimage(&wolf_dead_bk1, L"wolf_dead_bk1.jpg");
	loadimage(&wolf_dead_front1, L"wolf_dead_front1.jpg");
	loadimage(&wolf_dead_bk2, L"wolf_dead_bk2.jpg");
	loadimage(&wolf_dead_front2, L"wolf_dead_front2.jpg");//狼下坠的图
	loadimage(&bullet_bk, L"bullet_bk.jpg");
	loadimage(&bullet_front, L"bullet_front.jpg");//子弹的图
	loadimage(&rope_bk, L"rope_bk.jpg");
	loadimage(&rope_front, L"rope_front.jpg");//绳子的图
	loadimage(&bone_bk, L"level1_bone_bk.jpg");
	loadimage(&bone_front, L"level1_bone_front.jpg");//肉骨棒的图
	HWND hWnd = GetHWnd();
	mciSendString(L"close bkmusic", NULL, 0, NULL);

	SetWindowText(hWnd, _T("猪小弟"));//获得窗口句柄

	mciSendString(L"open bk1.mp3 alias bkm", NULL, 0, NULL);
	mciSendString(L"play bkm repeat", NULL, 0, NULL);
	BeginBatchDraw();
}

void show_2()
{
	int i;
	putimage(0, 0, &level2_bk);//背景图
							   //箭的模块
	for (i = 0; i < ARROW_NUM; i++)
	{
		if (shoot[i] == 1)
		{
			putimage(arrow_x[i], arrow_y[i], &arrow_bk, NOTSRCERASE);
			putimage(arrow_x[i], arrow_y[i], &arrow_front, SRCINVERT);//箭的图
		}
		if (shoot[i] == 2)
		{
			putimage(arrow_x[i], arrow_y[i], &arrow_down_bk, NOTSRCERASE);
			putimage(arrow_x[i], arrow_y[i], &arrow_down_front, SRCINVERT);//骨箭下坠的图
		}
	}
	putimage(stone_x, stone_y, &stone_bk, NOTSRCERASE);
	putimage(stone_x, stone_y, &stone_front, SRCINVERT);//石头的图
	if (pooyan_exit == 1)
	{
		putimage(pooyan_red_x, pooyan_red_y, &level1_pooyan_red_bk, NOTSRCERASE);
		putimage(pooyan_red_x, pooyan_red_y, &level1_pooyan_red_front, SRCINVERT);//猪妈的图
	}
	if (pooyan_exit == 2)
	{
		putimage(pooyan_red_dead_x, pooyan_red_dead_y + 30, &pooyan_red1_down_bk, NOTSRCERASE);
		putimage(pooyan_red_dead_x, pooyan_red_dead_y + 30, &pooyan_red1_down_front, SRCINVERT);
		putimage(pooyan_red_x, pooyan_red_y, &pooyan_red_down_bk, NOTSRCERASE);
		putimage(pooyan_red_x, pooyan_red_y, &pooyan_red_down_front, SRCINVERT);//猪妈下坠的图
	}
	putimage(530, 113, 20, pooyan_red_y - 110, &rope_bk, 530, 120, NOTSRCERASE);
	putimage(530, 113, 20, pooyan_red_y - 110, &rope_front, 530, 120, SRCINVERT);//绳子的图
																				 //狼的模块
	for (i = 0; i < WOLF_NUM_2; i++)
	{
		if (wolf_sign[i] == 1)
		{
			//实现狼向右移动的动画
			if (wolf_x[i] < wolf_up_x[i])
			{
				if (wolf_x[i] % 10 >= 5)//这里没有采用%2的奇偶数切换，那样会让狼跑的太快。
				{
					putimage(wolf_x[i], wolf_y[i], &wolf1_bk_right, NOTSRCERASE);
					putimage(wolf_x[i], wolf_y[i], &wolf1_right, SRCINVERT);//狼向右移动的图1
				}
				else if (wolf_x[i] % 10 < 5)
				{
					putimage(wolf_x[i], wolf_y[i], &wolf2_bk_right, NOTSRCERASE);
					putimage(wolf_x[i], wolf_y[i], &wolf2_right, SRCINVERT);//狼向右移动的图2
				}
			}
			//狼开始上升
			else if (wolf_x[i] >= wolf_up_x[i])
			{
				putimage(wolf_x[i], wolf_y[i], &level_wolf_bk, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i], &level_wolf_front, SRCINVERT);//狼的图
			}
		}
		if (wolf_sign[i] == 2)//如果狼被击中,先进行延时
		{
			if (wolf_interval[i] % 20 <= 10)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_bk1, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_front1, SRCINVERT);
			}
			else if (wolf_interval[i] % 20 > 10)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_bk2, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_front2, SRCINVERT);
			}
		}
		if (wolf_sign[i] == 3)//延时后进入快速下落状态
		{
			if (wolf_y[i] % 80 <= 40)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_bk1, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_front1, SRCINVERT);
			}
			else if (wolf_y[i] % 80 > 40)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_bk2, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_front2, SRCINVERT);
			}
		}
		if (wolf_sign[i] == 4)
		{
			if (wolf_x[i] % 10 <= 5)
			{
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf1_bk_right, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf1_right, SRCINVERT);
			}
			else if (wolf_x[i] % 10 > 5)
			{
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf2_bk_right, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf2_right, SRCINVERT);
			}
		}
	}
	//气球的模块
	for (i = 0; i < WOLF_NUM_2; i++)
	{
		if ((ball_sign[i] == 1) && (wolf_x[i] >= wolf_up_x[i]))//狼到达指定位置气球也可以登场了
		{
			putimage(ball_x[i], ball_y[i], &level1_ball_bk, NOTSRCERASE);
			putimage(ball_x[i], ball_y[i], &level1_ball_front, SRCINVERT);//气球的图
		}
		if (ball_sign[i] == 2)
		{
			putimage(ball_x[i], ball_y[i], &ball_red_exploded_bk, NOTSRCERASE);
			putimage(ball_x[i], ball_y[i], &ball_red_exploded_front, SRCINVERT);//气球爆炸的图
		}
	}
	//用来记录分数
	TCHAR s[80];
	_stprintf_s(s, _T("%06d"), score);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(2, 5, _T("分数:"));
	outtextxy(55, 5, s);
	FlushBatchDraw();
}

void update_without_input_2()
{
	//箭移动的模块,箭移动的模块要放在狼的模块上面，不然会出现最后一只狼的气球射不死的bug。。。不知道什么鬼
	if (count_shoot >= 0)
	{
		shoot[count_shoot] = 1;
	}
	static int arrow_speed = 0;//定义静态变量控制定义箭的速度
	if (arrow_speed < ARROW_SPEED)
	{
		arrow_speed++;
	}
	if (arrow_speed == ARROW_SPEED)
	{
		for (int i = 0; i < ARROW_NUM; i++)
		{
			if (shoot[i] == 1)//箭的左移
			{
				if (arrow_x[i] > -50)
				{
					arrow_x[i] = arrow_x[i] - 1;//箭自动左移
				}
				else if (arrow_x[i] <= -50)//箭飞出屏幕后显示关闭，这一步必须要关闭，否则后面还会计数，导致猪妈只能发出3只箭的bug，难道飞出屏幕还算在屏幕里么？
				{
					shoot[i] = -1;
				}
			}
			if (shoot[i] == 2)//箭的下落
			{
				if (arrow_y[i] <= HEIGHT + 50)
				{
					arrow_y[i]++;
				}
				if (arrow_y[i] > HEIGHT + 50)
				{
					shoot[i] = -1;
				}
			}
		}
		arrow_speed = 0;
	}
	arrow_num = 0;
	for (int i = 0; i < ARROW_NUM; i++)
	{
		if ((shoot[i] == 1)||(shoot[i]==2))
		{
			arrow_num++;//给屏幕上的箭计数
		}
	}
	//狼的自主移动的模块
	static int sj = 0;//用于狼的延迟出现
	if (sj < rand_space)
	{
		sj++;
	}
	if ((sj == rand_space) && (wolf_count < WOLF_NUM_2 - 1))
	{
		rand_space = rand() % 2500 + 1800;//rand()%m+n  m为随机变化幅度   n为固定变化幅度；
										  //在这里比初始化加大了间隔，为了更好地防止出现狼和气球图片重合；
		sj = 0;
		wolf_count++;
		ball_count++;
		if (wolf_count >= 0)//两个赋值也得放在里面，不然还是会在结尾出现bug
		{
			wolf_sign[wolf_count] = 1;//给每一只狼依次赋值为1，让它出现；
		}
		if (ball_count >= 0)
		{
			ball_sign[ball_count] = 1;//给每一只气球依次赋值为1，让它出现；
		}
	}
	for (int i = 0; i < WOLF_NUM_2; i++)
	{
		if (wolf_y[i] == 8 && wolf_sign[i] == 1)
		{
			wolf_sign[i] = 4;
		}
	}
	static int wolf_speed = 0;//定义静态变量控制狼的速度
	if (wolf_speed < WOLF_SPEED_2)
	{
		wolf_speed++;
	}
	if (wolf_speed == WOLF_SPEED_2)
	{
		int i;
		for (i = 0; i < WOLF_NUM_2; i++)
		{
			if ((wolf_x[i] < wolf_up_x[i]) && (wolf_sign[i] == 1))
			{
				wolf_x[i]++;//狼向右移动
				ball_x[i] = wolf_x[i];
			}
			if ((wolf_y[i] > 8) && (wolf_sign[i] == 1) && (wolf_x[i] >= wolf_up_x[i]))//狼自动上移
			{
				wolf_y[i]--;
			}
			if (wolf_sign[i] == 3)//被击中后快速下落
			{
				wolf_y[i] = wolf_y[i] + 5;
			}
			//狼向石头行走
			if ((wolf_sign[i] == 4) && (wolf_x[i] < stone_x - 35))
			{
				wolf_x[i]++;
			}
			else if ((wolf_sign[i] == 4) && (wolf_x[i] >= stone_x - 35))
			{
				wolf_x[i]--;
			}
		}
		//气球的移动模块；由于气球和狼是一起的，所以原理差不多;
		for (int i = 0; i < WOLF_NUM_2; i++)
		{
			if (/*ball_y[i] > 8 &&*/ (ball_sign[i] == 1) && (wolf_x[i] >= wolf_up_x[i]))//气球自动上移
			{
				ball_y[i]--;
			}
		}
		wolf_speed = 0;
	}
	string_y = pooyan_red_y;//控制绳子跟着猪妈移动增长缩短；
							//Sleep(5);//延时，用sleep的延时会让画面变卡,影响画面的所有内容；这个问题通过静态变量控制速度解决；
							//得分的判定
	int i, j;
	for (i = 0; i < ARROW_NUM; i++)
	{
		for (j = 0; j < WOLF_NUM; j++)
		{
			//箭射中气球的判定
			if ((arrow_x[i] >= ball_up_x[j] - 8) && (arrow_x[i] <= ball_up_x[j] + 40) && (arrow_y[i] >= ball_y[j] - 3) && (arrow_y[i] <= ball_y[j] + 30))
			{
				ball_sign[j] = 2;//气球爆炸
				wolf_sign[j] = 2;//狼死前挣扎
				arrow_x[i] = -50;//箭消失，刷新下一支
				score += 200;
			}
			//箭射中狼的判定
			if ((arrow_x[i] >= wolf_up_x[j] - 8) && (arrow_x[i] <= wolf_up_x[j] + 40) && (arrow_y[i] > ball_y[j] + 30) && (arrow_y[i] <= ball_y[j] + 65))
			{
				if (wolf_sign[j] == 1)
				{
					shoot[i] = 2;//骨箭射中狼，骨箭下坠
				}
			}
		}
	}
	//对爆炸后的气球进行处理
	for (j = 0; j < WOLF_NUM; j++)
	{
		if (ball_sign[j] == 2)
		{
			ball_interval[j]++;
		}
		if (ball_interval[j] == 100)
		{
			ball_y[j] = -1;
			ball_up_x[j] = -1;
			ball_sign[j] = -1;
			ball_interval[j] = 0;
		}
	}
	//对死后的狼的处理
	for (j = 0; j < WOLF_NUM; j++)
	{
		if (wolf_sign[j] == 2)
			wolf_interval[j]++;
		if (wolf_interval[j] == 500)
		{
			wolf_up_x[j] =-1;
			wolf_sign[j] = 3;
			wolf_interval[j] = 0;
			num_2++;
		}
	}
	//到达山崖上的狼推石头
	put_wolf = 0;
	for (i = 0; i < WOLF_NUM_2; i++)
	{
		if ((wolf_sign[i] == 4) && (wolf_x[i] == stone_x - 35))
		{
			put_wolf=put_wolf+1;
		}
		if (put_wolf >= 3)
		{
			stone_x = pooyan_red_x;
			stone_y++;
		}
	}
		//猪妈被石头砸中
	if ((stone_y >= pooyan_red_y) && (stone_y >= pooyan_red_y - 5) && (stone_y <= pooyan_red_y + 45))
	{
		pooyan_red_dead_x = pooyan_red_x;
		pooyan_red_dead_y = pooyan_red_y;
		pooyan_exit = 2;
	}
	
	//对死后的猪妈的处理
	static int pooyan_red_speeed = 0;
	if (pooyan_red_speeed < 2)
		pooyan_red_speeed++;
	if (pooyan_red_speeed == 2)
	{
		if (pooyan_exit == 2)
			pooyan_red_dead_y++;
		pooyan_red_speeed = 0;
	}
	//猪妈死亡，游戏结束
	if (pooyan_red_dead_y >= HEIGHT)
		act = 3;
	//过关与失败的判定
	if (num_2 >= 15)
	{
		act = 0;
	}
}

void update_with_input_2()
{
	//用input=getch()会产生严重的键位冲突；影响可玩性；
	//所以改用GetAsyncKeyState函数来解决键位冲突
	static int pooyan_red_speed = 0;//静态变量控制猪妈的速度，增加流畅性
	if (GetAsyncKeyState(0x57) & 0x8000 && (pooyan_red_y >= 120))//用w键控制猪妈上移
	{
		if (pooyan_red_speed < POOYAN_SPEED_2)
		{
			pooyan_red_speed++;
		}
		else if (pooyan_red_speed == POOYAN_SPEED_2)
		{
			pooyan_red_y = pooyan_red_y--;
			pooyan_red_speed = 0;
		}
	}
	if (GetAsyncKeyState(0x53) & 0x8000 && pooyan_red_y <= 350)//用s键控制猪妈向下移动
	{
		if (pooyan_red_speed < POOYAN_SPEED_2)
		{
			pooyan_red_speed++;
		}
		else if (pooyan_red_speed == POOYAN_SPEED_2)
		{
			pooyan_red_y = pooyan_red_y++;
			pooyan_red_speed = 0;
		}
	}
	char input;
	int judge = 0;//用来解决GetAsyncKeyState过于灵敏的问题，如果不加，就会出现按一次‘j’出现很多只箭；
	if (kbhit())
	{
		input = getch();
		if (input = 'j')
		{
			judge = 1;
		}
	}
	if (GetAsyncKeyState(0x4A) && 0x8000 && (arrow_num < 3))//按j键放箭同时控制屏幕上只能存在3只箭
	{
		if (judge == 1)
		{
			count_shoot++;//每加一次，数组中的箭就释放一次；
			arrow_y[count_shoot] = pooyan_red_y + 43;//让每一只箭发出后都待在正确位置 ，而不是跟着猪妈漂移；
			mciSendString(L"close shot", NULL, 0, NULL);
			mciSendString(L"open shot.mp3 alias shot", NULL, 0, NULL);
			mciSendString(L"play shot", NULL, 0, NULL);

		}
	}
}

void gameover()
{
	if (act == 3)
	{
		Sleep(1000);
		getch();
		exit(0);
	}
}

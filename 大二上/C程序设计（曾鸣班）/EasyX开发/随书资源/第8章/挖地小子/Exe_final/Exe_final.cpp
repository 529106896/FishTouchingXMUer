/*游戏背景*/
    /*挖地小子的小女友被地底的魔兽帝王抓住了，他必须要去地底救出他的女友。为了找到魔兽帝王，他苦心寻
找，终于有一天他发现了一点魔兽帝王的踪迹，然而三只恶霸挡在他寻找女友的路上。*/

/*控制键位*/
/*‘w’向若上飞行  
  ‘s’若人物下方有砖块向下挖地 
  ‘a’若左方无砖块左移动，若有则左挖
  ‘d’若右端无砖块右移动，若有则右挖 
  ‘j’放置炸弹 ‘k’使用能量包增加能量 
  ‘l’使用氧气包增加氧气*/

/*进入商店*/
/* 按‘1’购买炸弹500 score 
   按‘2’是升级能量等级
   按‘3’是升级氧气等级
   按‘4’购买氧气包
   按‘5’购买能量包*/

/*游戏目标*/
// 不停地开采矿物，把销售矿物所得的钱用来升级道具，打败三只恶霸。

/*挖地小子
1.初始经济500 score
2.score会自动增加
3.利用score可以升级和购买装备
4.向上飞行需要消耗能量
5.在地下需要消耗氧气
6.人在地下跑动会加速氧气消耗
7.人在地上跑动会加速能量和氧气的恢复
8.在第二关时人物的各种动作会变慢
7.人碰到怪兽会使氧气下降
9.炸弹会炸死怪物也会炸伤人物*/

/*隐藏福利*/
//煤块有着复生能力只要你不破坏他的的本源（拾取煤块后在它没复生之前不去挖它几秒后会自动恢复）

#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"Winmm.lib")

void startup(); // 数据初始化
void mapstartup(); // 地图初始化
void show(); // 画面显示
void associated(); // 用于串联人物结构体中的变量
void updatewithoutinput(); // 与用户输入无关的变量
void status_change(); // 状态的变化
void updatewithinput(); // 与用户输入有关的变量
void startMenu(); // 初始菜单界面
void pauseMenu(); // 游戏暂停后菜单界面，一般按ESC键后启动该界面
void readRecordFile(); // 读取游戏数据文件存档
void writeRecordFile(); // 存储游戏数据文件存档
void gameover(); // 游戏结束

#define high 670//画布的高度
#define width 900//画布的宽度
#define person_high 72//定义挖地小子的高度
#define person_width 64//定义挖地小子的宽度
#define monster_high 60//定义怪物的高度
#define monster_width 56//定义怪物的宽度
#define monster_num 3//怪物的故事
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
#define bomb_money 50//炸弹的价格
#define bomb_high 64//炸弹以及爆炸画面的高度
#define bomb_width 64//炸弹以及爆炸画面的宽度

IMAGE img_bk;//定义背景图片
IMAGE img_ebg;//游戏结束图片
IMAGE img_success;//游戏成功时的图片
IMAGE img_1;//定义第一关的图片
IMAGE img_stone_0, img_stone_1, img_stone_2, img_stone_3, img_stone_4, img_stone_5, img_stone_6, img_stone_7, img_stone_1314;//定义石块的图片
IMAGE img_coal_1, img_coal_2, img_coal_3, img_coal_4, img_coal_5, img_coal_0;//定义煤块的图片
IMAGE img_copper_1, img_copper_2, img_copper_3, img_copper_4, img_copper_5, img_copper_6, img_copper_0;//定义铜块的图片
IMAGE img_silver_1, img_silver_2, img_silver_3, img_silver_4, img_silver_5, img_silver_0;//定义银块的图片
IMAGE img_stone_99;//石块
IMAGE img_person_0, img_person_00;//定义挖地小子的正面图片 0表示黑白版 00表示彩版
IMAGE img_monsterrun_0, img_monsterrun_00;//定义怪物走路的图片  0表示黑白版  00表示彩版
IMAGE img_person_1, img_person_2;//定义挖地小子左右走的图片 1表示黑白版 2表示彩版
IMAGE img_shoes_1, img_shoes_2;//定义火箭鞋图片 1表示黑白版 2表示彩版
IMAGE img_digleftperson_1, img_digleftperson_2;//定义挖地小子向左挖的照片  1表示黑白版 2表示彩版
IMAGE img_digrightperson_1, img_digrightperson_2;//定义挖地小子向右挖的照片  1表示黑白版 2表示彩版
IMAGE img_digdownperson_1, img_digdownperson_2;//定义挖地小子向下挖的照片  1表示黑白版 2表示彩版
IMAGE img_bomb_1, img_bomb_boom, img_bwbomb_boom;//炸弹
IMAGE img_bwbomb_1;//炸弹黑白
IMAGE img_energy;//能量图片
IMAGE img_oxygen;//氧气图片
IMAGE img_ener_oxy1;//能氧黑白
IMAGE img_ener_oxy2;//能氧
IMAGE img_shop;//商店
MOUSEMSG m;//定义一个鼠标变量

int scene;//scene  -5游戏成功 -4游戏结束 -3游戏暂停 -2 游戏初始菜单 -1商店 0游戏进入画面 1游戏第一关 2游戏第二关
int left_i;//记录人向左移动的图片
int right_i;//记录人向右移动的图片
int mleft_i[monster_num];//记录怪物向左移动的图片
int mright_i[monster_num];//记录怪物向右移动的图片
int boom_i;//记录人炸弹爆炸时的图片
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
float energy_i;//能量图片变化横坐标
float energy_j;//能量图片变化纵坐标
float oxygen_i;//氧气图片变化的横坐标
float oxygen_j;//氧气图片变化的纵坐标
int put_bomb;//放置炸弹
int score;//分数记录
int k;//关卡变量

typedef struct thing//定义结构体用于人
{
	/*怪兽和人共有*/
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
	 /*用于人*/
	float v;//挖地小子竖直方向速度
	int bomb;//挖地小子携带炸弹的个数
	int oxygen;//人物携带能量包的个数
	int energy;//人物携带氧气包的个数
	int scene;//定义人物在的关卡位置
	int oxygen_level;//氧气等级
	int energy_level;//能量等级
	/*用于怪兽*/
	int direction;//定义走路的方向 0代表向右走 1表示向左走
	int status;//定义怪物的状态  1表示存活 0表示死亡
}thing;
thing person;//定义人
thing monster[monster_num];//定义怪物

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
	int scene;//石头关卡的状态
}stone[num_scene][num_stonehigh][num_stonewidth];//土块的结构体一共56个砖块
struct stone bomb;//存储炸弹的结构体

void main()
{
	startup();
	mapstartup();
	while (1)
	{
		show();
		associated();
		updatewithoutinput();
		status_change();
		updatewithinput();
	}
	gameover();
}

void startup()
{
	int i, j, k;
	initgraph(width, high);//画布
	loadimage(&img_bk, _T("background.jpg"));//导入游戏开始界面
	loadimage(&img_ebg, _T("endbackground.jpg"));//导入游戏结束界面
	loadimage(&img_success, _T("success.jpg"));//导入游戏胜利界面
	loadimage(&img_1, _T("level_1.jpg"));//导入第一关的图片
	loadimage(&img_energy, _T("energy.jpg"));//导入能量的图片
	loadimage(&img_oxygen, _T("oxygen.jpg"));//导入能量的图片
	loadimage(&img_ener_oxy1, _T("ener_oxy1.jpg"));//导入能氧黑白照
	loadimage(&img_ener_oxy2, _T("ener_oxy2.jpg"));//导入能氧
	loadimage(&img_shop, _T("shop.jpg"));//导入商店的图片
	loadimage(&img_person_0, _T("person_0.jpg"));//导入人物正面的图片黑白版
	loadimage(&img_person_00, _T("person_00.jpg"));//导入人物正面的图片彩版
	loadimage(&img_monsterrun_0, _T("monsterrun_0.jpg"));//导入怪物走路图片的彩版
	loadimage(&img_monsterrun_00, _T("monsterrun_00.jpg"));//导入怪物走路图片的黑白版
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
	loadimage(&img_stone_99, _T("stone_99.jpg"));//导入石头
	loadimage(&img_stone_1314, _T("stone_1314.jpg"));//回复
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
	loadimage(&img_bomb_1, _T("bomb_1.jpg"));//炸弹原始
	loadimage(&img_bwbomb_1, _T("bwbomb_1.jpg"));//炸弹原始黑白
	loadimage(&img_bomb_boom, _T("bomb_boom.jpg"));//炸弹爆炸过程中过程图片
	loadimage(&img_bwbomb_boom, _T("bwbomb_boom.jpg"));//炸弹爆炸过程中过程黑白图片
	mciSendString(_T("open bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);//导入背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环背景音乐

	scene = 0;//导入初始场景
	shoes_a = 0;//火箭鞋初速度
	exist_leftstone = 0;//初始时左边没有砖块 exist_leftstone==0表示左边没有砖块 exist_leftstone==1表示左边有砖块
	exist_rightstone = 0;//初始时右边没有砖块 exist_rightstone==0表示左边没有砖块 exist_leftrightstone==1表示左边有砖块
	exist_downstone = 0;//初始时下边没有砖块 exist_downstone==0表示左边没有砖块 exist_downstone==1表示左边有砖块
	exist_flyleftstone = 0;
	exist_flyrightstone = 0;
	digleftbf = 0;//判断是否向左开始挖·、
	digrightbf = 0;//判断是否向右开始挖
	flyleftbf = 0;//判断是否向左飞
	flyrightbf = 0;//判断是否向右飞
	put_bomb = 0;
	/*对炸弹进行初始化*/
	bomb.center_x = -1000;
	bomb.center_y = -1000;
	bomb.left_x = -1000;
	bomb.left_y = -1000;
	bomb.right_x = -1000;
	bomb.right_y = -1000;
	bomb.top_x = -1000;
	bomb.top_y = -1000;
	bomb.bottom_x = -1000;
	bomb.bottom_y = -1000;
	bomb.status = 0;
	bomb.scene = 100;
	/*对每个砖块进行初始化*/
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
	/*定义每个石块的固定位置*/
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
			stone[1][i][j].status = 1;
		}
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)//第二关的石块位置
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
			stone[2][i][j].status = 1;
		}
	/*挖地小子赋初始值 */
	person.center_x = width / 2;
	person.center_y = apper_1stone - person_high / 2;
	person.bomb = 0;//初始没有炸弹
	person.status = 1;//初始挖地小子活着
	person.oxygen_level = 1;//氧气等级
	person.energy_level = 1;//能量等级
	person.oxygen = 1;//氧气包
	person.energy = 1;//能量包
	/*对怪物进行初始化*/
	for (i = 0; i < monster_num; i++)
	{
		monster[0].center_x = stone_width;
		monster[0].center_y = stone_high * 9 - monster_high / 2;
		monster[1].center_x = stone_width * 6;
		monster[1].center_y = stone_high * 4 - monster_high / 2;
		monster[2].center_x = stone_width * 10;
		monster[2].center_y = stone_high * 7 - monster_high / 2;
		monster[i].direction = 0;
		monster[i].status = 1;//表示存活
	}
	/*移动变量赋值*/
	left_i = 0;
	right_i = 0;
	energy_i = 120;//能量柱的长度
	energy_j = 19;//能量柱的宽度
	oxygen_i = 107;//氧气柱的长度
	oxygen_j = 54;//氧气柱的宽度
	boom_i = 0;
	person.v = 0;//人向下方向的速度   向下为正  向上为负
	/*分数初始*/
	score = 500;
	BeginBatchDraw();
}
void mapstartup()
{
	int i, j;
	for (i = 7; i<11; i++)
		for (j = 0; j<2; j++)
		{
			stone[1][i][j].status = 99;
		}
	for (i = 7; i<8; i++)
		for (j = 8; j<14; j++)
		{
			stone[1][i][j].status = 99;
		}
	for (i = 9; i<10; i++)
		for (j = 4; j<6; j++)
		{
			stone[1][i][j].status = 11;
		}
	for (i = 10; i<11; i++)
		for (j = 2; j<7; j++)
		{
			stone[1][i][j].status = 11;
		}
	for (i = 10; i<11; i++)
		for (j = 9; j<14; j++)
		{
			stone[1][i][j].status = 11;
		}
	for (i = 8; i<9; i++)
		for (j = 1; j<5; j++)//怪物
		{
			stone[2][i][j].status = 0;
		}
	for (i = 3; i<4; i++)
		for (j = 5; j<9; j++)//怪物
		{
			stone[2][i][j].status = 0;
		}
	for (i = 6; i<7; i++)
		for (j = 9; j<13; j++)//怪物
		{
			stone[2][i][j].status = 0;
		}
	for (i = 2; i<6; i++)
		for (j = 3; j<5; j++)
		{
			stone[2][i][j].status = 31;
		}
	for (i = 1; i<5; i++)
		for (j = 12; j<13; j++)
		{
			stone[2][i][j].status = 11;
		}
	for (i = 9; i<10; i++)
		for (j = 1; j<5; j++)
		{
			stone[2][i][j].status = 21;
		}
	for (i = 7; i<8; i++)
		for (j = 7; j<14; j++)
		{
			stone[2][i][j].status = 21;
		}
	for (i = 6; i<7; i++)
		for (j = 5; j<9; j++)
		{
			stone[2][i][j].status == 31;
		}
}
/* 土块 0表示无 1为原始 2破碎1 3破碎2 4破碎3 5破碎4 6破碎5 7破碎6*/
/*煤块 11表示原始 12表示破碎1 13表示破碎2 14表示破碎3 15表示破碎4  16表示煤
= 铜块  21表示原始  22表示破碎1 23表示破碎2 24表示破碎3  25表示破碎4 26表示破碎5 27表示铜块
银块   31表示原始  32表示破碎1 33表示破碎2 34表示破碎3 35表示破碎4 36表示银块*/
void show()
{
	int i, j;//循环变量
	k = 0;
	if (scene == 0)//切换背景
	{
		putimage(0, 0, &img_bk);//导出背景图片
		FlushBatchDraw();
	}
	while (scene == -2)
		startMenu(); // 初始菜单界面
	while (scene == -3)
		pauseMenu(); // 游戏暂停后菜单界面，一般按ESC键后启动该界面
	if (scene == 1)//切换到场景1
	{
		putimage(0, 0, &img_1);//导出第一关的图
		k = 1;
	}
	else if (scene == 2)
	{
		putimage(0, 0, &img_1);//导出第一关的图   不过进入了第二关的设定
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
			else if (stone[k][i][j].status == 99)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_99);//砖块初始化
			else if (stone[k][i][j].status == -1)
				putimage(stone[k][i][j].left_x, stone[k][i][j].top_y, &img_stone_1314);//砖块初始化
		}
	if (scene == 2)
	{
		putimage(width - 610, 0, &img_ener_oxy1, NOTSRCERASE);//放置氧气柱与能量柱结合的图片的黑白版
		putimage(width - 610, 0, &img_ener_oxy2, SRCINVERT);//放置氧气柱与能量柱结合的图片的彩版
	}
	/*人物能量槽与氧气槽*/
	if (scene == 1 || scene == 2)
	{
		putimage(735, 213, energy_i, energy_j, &img_energy, 0, 0);//放置能量柱
		putimage(740, 248, oxygen_i, oxygen_j, &img_oxygen, 0, 0);//放置氧气柱
	}
	/*商店*/
	if (scene == -1)//切换到场景商店
	{
		putimage(0, 0, &img_shop);//导出背景图片
	}
}
void associated()//用于串联人物结构体中的变量
{
	int i;
	/*人物坐标关联 每个值都与人物坐标中心相关 增强坐标的相关性*/
	person.left_x = person.center_x - person_width / 2;
	person.left_y = person.center_y;
	person.right_x = person.center_x + person_width / 2;
	person.right_y = person.center_y;
	person.top_x = person.center_x;
	person.top_y = person.center_y - person_high / 2;
	person.bottom_x = person.center_x;
	person.bottom_y = person.center_y + person_high / 2;
	/*怪物坐标关联 每个值都与怪物坐标中心相关 增强坐标的相关性*/
	for (i = 0; i < monster_num; i++)
	{
		monster[i].left_x = monster[i].center_x - monster_width / 2;
		monster[i].left_y = monster[i].center_y;
		monster[i].right_x = monster[i].center_x + monster_width / 2;
		monster[i].right_y = monster[i].center_y;
		monster[i].top_x = monster[i].center_x;
		monster[i].top_y = monster[i].center_y - monster_high / 2;
		monster[i].bottom_x = monster[i].center_x;
		monster[i].bottom_y = monster[i].center_y - monster_high / 2;
	}
}
void updatewithoutinput()
{
	int i, j;
	G = 1;//重力加速度初值
	/*关卡同步*/
	if (scene != -3 && scene != -2 && scene != 0)//只有都不是这些关卡时，才执行。用||不能实现这个效果。
		person.scene = scene;//人物存在的关卡同步
    /*能量消耗完不能飞*/
	if (energy_i <= 0)
		shoes_a = 0;
	/*关卡与三维数组同步*/
	if (scene == 1)
		k = 1;
	else if (scene == 2)
		k = 2;
	else
		k = 1;
	/*判定人物是否站在砖块上*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].center_y - person.center_y <= person_high / 2 + stone_high / 2 &&
				stone[k][i][j].center_y - person.center_y >= (person_high / 2 + stone_high / 2) / 2 &&//通过判断人物与砖块之间纵坐标距离
				person.center_x <= stone[k][i][j].center_x + stone_width / 2 + person_width / 2 - 15 &&
				person.center_x >= stone[k][i][j].center_x - stone_width / 2 - person_width / 2 + 15 &&//判断人物与砖块之间横坐标之间的关系
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
					stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)//状态不为空
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
					static int speed_2 = 0;//用于限制向下挖的速度  控制状态变化快慢
					if (speed_2 < 60)
						speed_2++;
					else if (speed_2 == 60)
					{
						stone[k][i][j].status++;//状态加1
						speed_2 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//砖块消失
					if (stone[k][i][j].status == 100)
						stone[k][i][j].status = 99;//状态变回99 还是石头
				}
			}
		}
	/*判断人物左边是否有砖块  向左挖*/
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
					if (speed_3 < 60)
						speed_3++;
					else if (speed_3 == 60)
					{
						stone[k][i][j].status++;//状态加1
						speed_3 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//砖块消失
					if (stone[k][i][j].status == 100)
						stone[k][i][j].status = 99;//石头挖不动
				}
			}
		}
	/*判断人物右边是否有砖块 向右挖*/
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
					if (speed_3 < 60)
						speed_3++;
					else if (speed_3 == 60)
					{
						stone[k][i][j].status++;//状态加1
						speed_3 = 0;
					}
					if (stone[k][i][j].status == 8)
						stone[k][i][j].status = 0;//砖块消失
					if (stone[k][i][j].status == 100)
						stone[k][i][j].status = 99;//石头挖不动
				}
			}
		}
	/*判断人物飞行时左边是否有砖块*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.left_x == stone[k][i][j].right_x && person.left_y - stone[k][i][j].right_y <= person_high / 2 + stone_high / 2 - 12
				&& person.left_y - stone[k][i][j].right_y >= -person_high / 2 - stone_high / 2 + 12
				&& stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36 && shoes_a < 0)
			{
					exist_flyleftstone = 1;
			}
		}
	/*判断人物飞行时右边是否有砖块*/
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (person.right_x == stone[k][i][j].left_x && person.right_y - stone[k][i][j].left_y <= person_high / 2 + stone_high / 2 - 12
				&& person.right_y - stone[k][i][j].left_y >= -person_high / 2 - stone_high / 2 + 12
				&& stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36 && shoes_a < 0)
			{
					exist_flyrightstone = 1;
			}
		}
	/*判断怪物的运动*/
	int m;
	/*右走*/
	for (m = 0; m < monster_num; m++)
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				if (monster[m].center_x - stone[k][i][j].center_x <= stone_width / 2 + monster_width / 2 &&
					monster[m].center_x - stone[k][i][j].center_x >= (stone_width / 2 + monster_width / 2) / 2 &&
					monster[m].center_y - stone[k][i][j].center_y == stone_high / 2 - monster_high / 2 &&
					stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
				{
					monster[m].direction = 0;//左端存在砖块向右走  
				}
			}
	/*左走*/
	for (m = 0; m < monster_num; m++)
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				if (stone[k][i][j].center_x - monster[m].center_x <= stone_width / 2 + monster_width / 2 &&
					stone[k][i][j].center_x - monster[m].center_x >= (stone_width / 2 + monster_width / 2) / 2 &&
					monster[m].center_y - stone[k][i][j].center_y == stone_high / 2 - monster_high / 2 &&
					stone[k][i][j].status != 0 && stone[k][i][j].status != 16 && stone[k][i][j].status != 27 && stone[k][i][j].status != 36)
				{
					monster[m].direction = 1;//右端存在砖块向左走   
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
				&& person.center_x > stone[k][i][j].center_x - 10 && person.center_y<stone[k][i][j].center_y + 40
				&& person.center_y>stone[k][i][j].center_y -40)//拾取煤块
			{
				stone[k][i][j].status = -1;
				score = score + 100;//一个煤块100分
			}
			if (stone[k][i][j].status == 27 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10 && person.center_y<stone[k][i][j].center_y + 40
				&& person.center_y>stone[k][i][j].center_y -40)//拾取铜块
			{
				stone[k][i][j].status = 0;
				score = score + 500;//一个金块500分
			}
			if (stone[k][i][j].status == 36 && person.center_x <stone[k][i][j].center_x + 10
				&& person.center_x > stone[k][i][j].center_x - 10 && person.center_y<stone[k][i][j].center_y + 40
				&& person.center_y>stone[k][i][j].center_y -40)//拾取银块
			{
				stone[k][i][j].status = 0;
				score = score + 300;//一个银块300分
			}
		}
	/*煤块的恢复*/
	static int speed_10[num_scene][num_stonehigh][num_stonewidth] = { 0 };
	for (i = 0; i < num_stonehigh; i++)
		for (j = 0; j < num_stonewidth; j++)
		{
			if (stone[k][i][j].status == -1)//砖块的状态变为完全破碎的
			{
				speed_10[k][i][j]++;
				if (speed_10[k][i][j] == 4000)//砖块恢复的速度
				{
					stone[k][i][j].status = 11;//只能恢复一次
					speed_10[k][i][j] = 0;
				}
			}
		}
	/*放置炸弹并控制炸弹的变化*/
	if (put_bomb == 1)
	{
		bomb.center_x = person.center_x;
		bomb.center_y = person.center_y + 10;
		bomb.scene = scene;//炸弹要和关卡一致
	}
	if (bomb.center_x < 900 && bomb.center_x>0 && bomb.center_y < 670 && bomb.center_y>0)
	{
		static int speed_4 = 0;
		if (speed_4 < 200)//炸弹变化的快慢
			speed_4++;
		else if (speed_4 == 200)
		{
			bomb.status++;//状态加1
			speed_4 = 0;
		}
	}
	/*炸弹炸死怪物的判定*/
	for (i = 0; i < monster_num; i++)
	{
		if (bomb.status >= 6 && bomb.center_x - monster[i].center_x <= bomb_width / 2 + monster_width / 2
			&& bomb.center_x - monster[i].center_x >= -bomb_width / 2 - monster_width / 2 && bomb.center_y - monster[i].center_y <= bomb_high - monster_high + 4
			&& bomb.center_y - monster[i].center_y >= -bomb_high + monster_high - 4)//炸弹位置与人物的位置范围的判断
		{
			score = (score + 3000 * monster[i].status);//打死怪物增加500分
			monster[i].status = 0;//怪物死亡
		}
	}
	/*人物碰到怪物掉血*/
	for (i = 0; i < monster_num; i++)
	{
		if (person.center_x - monster[i].center_x <= person_width / 2 + monster_width / 2
			&& person.center_x - monster[i].center_x >= -person_width / 2 - monster_width / 2 && person.center_y - monster[i].center_y <= person_high - monster_high + 4
			&& person.center_y - monster[i].center_y >= -person_high + monster_high - 4)
		{
			oxygen_i = oxygen_i - 0.1;//氧气柱的变化
		}
	}
	/*炸弹炸人物的判定*/
	if (bomb.status >= 6 && bomb.center_x - person.center_x <= bomb_width / 2 + person_width / 2 - 4
		&& bomb.center_x - person.center_x >= -bomb_width / 2 - person_width / 2 + 4 && bomb.center_y - person.center_y <= bomb_high / 2 + person_high / 2 - 4
		&& bomb.center_y - person.center_y >= -bomb_high / 2 - person_high / 2 + 4)
	{
		oxygen_i = oxygen_i - 4;//氧气柱的变化
	}
	/*能量消耗与恢复*/
	if (shoes_a < 0)
	{
		if (energy_i > 0)
			energy_i = energy_i - 0.08*(5 - person.energy_level);//能量柱的变化
	}
	else if (shoes_a == 0)
	{
		energy_i = energy_i + 0.04;//能量柱的变化
	}
	if (energy_i >= 120)
		energy_i = 120;
	/*氧气消耗与恢复*/
	if (scene == 1 && person.top_y <= apper_1stone)
	{
			oxygen_i = oxygen_i + 0.04;//氧气柱的变化
	}
	if ((scene == 1 && person.top_y > apper_1stone) || scene == 2)
	{
		oxygen_i = oxygen_i - 0.008*(5 - person.oxygen_level);//氧气柱的变化
	}
	if (oxygen_i >= 107)
		oxygen_i = 107;
	/*人物死亡判定*/
	if (oxygen_i < 0)
	{
		person.status = 0;
		scene = -4; //-4游戏结束
		putimage(0, 0, &img_ebg);//游戏失败
	}
	/*人物胜利判定*/
	for (i = 0; i < monster_num; i++)
	{
		if (monster[i].status != 0)
			break;
		scene = -5; //-5游戏成功 
		putimage(0, 0, &img_success);//游戏成功
	}

	/*显示分数*/
	if (scene == 1 || scene == 2 || scene == -1)
	{
		TCHAR s[10], s1[10], s2[10], s3[10], s4[10], s5[10];
		setbkmode(TRANSPARENT);//背景透明
		_stprintf(s, _T("%d"), score);
		_stprintf(s1, _T("%d"), person.bomb);
		_stprintf(s2, _T("%d"), person.energy_level);
		_stprintf(s3, _T("%d"), person.oxygen_level);
		_stprintf(s4, _T("%d"), person.energy);
		_stprintf(s5, _T("%d"), person.oxygen);
		outtextxy(90, 12, s);
		outtextxy(150, 40, s1);
		outtextxy(150, 65, s2);
		outtextxy(130, 90, s3);
		outtextxy(100, 115, s4);
		outtextxy(100, 140, s5);
		outtextxy(10, 40, _T("炸弹个数："));
		outtextxy(10, 65, _T("喷火器等级："));
		outtextxy(10, 90, _T("体力等级："));
		outtextxy(10, 115, _T("能量包："));
		outtextxy(10, 140, _T("氧气包："));
		settextstyle(25, 0, _T("楷体"));
		settextcolor(BLACK);
	}
	/*分数自动增加*/
	{
		static int speed_9 = 0;
		if (speed_9 < 180)
			speed_9++;
		else if (speed_9 == 180)
		{
			speed_9 = 0;
			score = score + 1;
		}
	}
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
		person.center_y = -person_width / 2;//关卡变化时，人物坐标随之变化
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
	if (scene == 1 || scene == 2)
	{
		/*当人物不动时转向正面 */
		if (shoes_a == 0 && digbf == 0 && digleftbf == 3 && digrightbf == 3)//当值都为初始值时的时候显示正面图片
		{
			putimage(person.left_x, person.top_y, &img_person_0, NOTSRCERASE);//人物正面黑白版
			putimage(person.left_x, person.top_y, &img_person_00, SRCINVERT);//人物正面彩版
			Sleep(1);
		}
		/*当按w时人物向上飞*/
		else if (shoes_a < 0 && flyleftbf == 0 && flyrightbf == 0)
		{
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			Sleep(1);
		}
		/*空中向左飞行 按wa*/
		else if (shoes_a < 0 && flyleftbf == 1)
		{
			if (exist_flyleftstone == 0)//左边不存在石块
				person.center_x = person.center_x - 1;//人物的中心坐标x减少
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			Sleep(1);
		}
		/*空中向右飞行 按wd*/
		else if (shoes_a < 0 && flyrightbf == 1)
		{
			if (exist_flyrightstone == 0)
				person.center_x = person.center_x + 1;//人物的中心坐标x增加
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_1, NOTSRCERASE);//人物向上飞黑白版
			putimage(person.center_x - shoesperson_width / 2, person.center_y - shoesperson_high / 2, &img_shoes_2, SRCINVERT);//人物向上飞彩版
			Sleep(1);
		}
		/*人物转变为向下挖的图片*/
		else if (digbf == 1)
		{
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_1, NOTSRCERASE);//人物向下挖黑白
			putimage(person.center_x - digdownperson_width / 2, person.center_y - digdownperson_high / 2, &img_digdownperson_2, SRCINVERT);//人物向下挖彩
			Sleep(1);
		}
		/*左边行走*/
		static int speed_8;
		if (speed_8 < 50)
			speed_8++;
		if (digleftbf == 0)
		{
			if (speed_8 == 50)
			{
				left_i++;
				person.center_x = person.center_x - 15;//人物的中心坐标x减少
				speed_8 = 0;
			}
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, left_i * person_width, 0, NOTSRCERASE);//放置向左走的黑白图片
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, left_i * person_width, 0, SRCINVERT);//放置向左走的彩图
			if (left_i == 3)
				left_i = 0;
		}
		/*向左挖土*/
		else if (digleftbf == 1)
		{
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_1, NOTSRCERASE);//人物向左挖黑白
			putimage(person.center_x - digleftperson_width / 2, person.center_y - digleftperson_high / 2, &img_digleftperson_2, SRCINVERT);//人物向左挖彩
			Sleep(1);
		}
		/*右边行走*/
		static int speed_7;
		if (speed_7 < 50)
			speed_7++;
		if (digrightbf == 0)
		{
			if (speed_7 == 50)
			{
				person.center_x = person.center_x + 15;//人物的中心坐标x减少
				right_i++;//采用套图
				speed_7 = 0;
			}
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_1, right_i * person_width, person_high, NOTSRCERASE);//放置向右走的黑白图片
			putimage(person.left_x, person.top_y, person_width, person_high, &img_person_2, right_i * person_width, person_high, SRCINVERT);//放置向右走的彩图
			if (right_i == 3)
				right_i = 0;
		}
		/*向右挖土*/
		else if (digrightbf == 1)
		{
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_1, NOTSRCERASE);//人物向右挖黑白
			putimage(person.center_x - digrightperson_width / 2, person.center_y - digrightperson_high / 2, &img_digrightperson_2, SRCINVERT);//人物向右挖彩
			Sleep(1);
		}
	}
	/*炸弹变化*/
	if (bomb.status <= 5 && scene == bomb.scene)
	{

		putimage(bomb.center_x - 32, bomb.center_y - 32, &img_bwbomb_1, NOTSRCERASE);//放置炸弹黑白图片
		putimage(bomb.center_x - 32, bomb.center_y - 32, &img_bomb_1, SRCINVERT);//放置炸弹彩图
	}
	else if (bomb.status >= 6)
	{
		if (scene == bomb.scene)
		{
			putimage(bomb.center_x - 32, bomb.center_y - 32, bomb_width, bomb_high, &img_bwbomb_boom, boom_i * bomb_width, 0, NOTSRCERASE);//放置炸弹的黑白图片
			putimage(bomb.center_x - 32, bomb.center_y - 32, bomb_width, bomb_high, &img_bomb_boom, boom_i * bomb_width, 0, SRCINVERT);//放置炸弹的彩图
		}
		boom_i++;
		Sleep(100);
		if (boom_i == 8)
		{
			bomb.status = 0;
			bomb.center_x = -1000;
			bomb.center_y = -1000;
			boom_i = 0;
			person.bomb--;//少一个炸弹
		}
	}
	/*怪物行走*/
	static int speed_5[monster_num] = { 0 }, speed_6[monster_num] = { 0 };
	if (scene == 2)
	{
		for (i = 0; i < monster_num; i++)
		{
			if (speed_5[i] < 60)//怪物行走的速度
				speed_5[i]++;
			if (speed_6[i] < 60)
				speed_6[i]++;
			if (monster[i].direction == 1 && monster[i].status == 1)
			{
				if (speed_5[i] == 60)
				{
					monster[i].center_x = monster[i].center_x - 10;//怪物的中心坐标x减少
					mleft_i[i]++;
					speed_5[i] = 0;
				}
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_00, mleft_i[i] * monster_width, monster_high, NOTSRCERASE);//放置怪物走路的黑白图片
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_0, mleft_i[i] * monster_width, monster_high, SRCINVERT);//放置怪物走路的彩图

				if (mleft_i[i] == 3)
					mleft_i[i] = 0;
			}
			else if (monster[i].direction == 0 && monster[i].status == 1)
			{
				if (speed_6[i] == 60)
				{
					monster[i].center_x = monster[i].center_x + 10;//怪物的中心坐标x增加
					mright_i[i]++;
					speed_6[i] = 0;
				}
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_00, mright_i[i] * monster_width, 0, NOTSRCERASE);//放置怪物走路的黑白图片
				putimage(monster[i].left_x, monster[i].top_y, monster_width, monster_high, &img_monsterrun_0, mright_i[i] * monster_width, 0, SRCINVERT);//放置怪物走路的彩图

				if (mright_i[i] == 3)
					mright_i[i] = 0;
			}
		}
	}
	FlushBatchDraw();
	/*回归原值部分 下方控制部分可以改变值*/
	shoes_a = 0;//将加速度归为原值（按w改变）
	digbf = 0;//向下挖回归原值（按s改变）
	digleftbf = 3;//向左挖回归原值（按a改变）
	digrightbf = 3;//向右挖回归原值（按d改变）
	flyleftbf = 0;//向左飞回归原值
	flyrightbf = 0;//向右飞回归原值
	put_bomb = 0;//不放置炸弹
}
void updatewithinput()
{
	/*当进入界面的时候点击 "按任意键进入" 进入游戏*/
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONUP && scene == 0)
		{
			if (m.x <= 563 && m.x >= 316 && m.y <= 602 && m.y >= 570)//按键范围判断
			{
				scene = -2;
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
		if (GetAsyncKeyState(0x4A) & 0x8000 && person.bomb > 0)//按j放置炸弹
		{
			put_bomb = 1;
		}
		if (GetAsyncKeyState(0x4B) & 0x8000 && person.energy > 0)//按k使用能量包
		{
			if (energy_i < 120)
			{
				energy_i += 80;
				person.energy--;
			}
		}
		if (GetAsyncKeyState(0x4C) & 0x8000 && person.oxygen > 0)//按l使用氧气包
		{
			if (oxygen_i < 107)
			{
				person.oxygen--;
				oxygen_i += 60;
			}
		}
	}
	if (GetAsyncKeyState(0x1B) & 0x8000 && (scene == 1 || scene == 2 || scene == -1))//游戏暂停按esc键
	{
		scene = -3;//游戏暂停界面
	}
	if (scene == -1)
	{
		char input;
		if (kbhit())
		{
			input = getch();
			if (input == 'q')
				scene = 1;//退出商店
			if (input == '1' && score >= 500)//购买炸弹
			{
				person.bomb++;
				score = score - 500;
			}
			if (input == '2' && score >= 500)//购买能量等级
			{
				score = score - 500 * person.energy_level;
				person.energy_level++;
			}
			if (input == '3' && score >= 500)//购买氧气等级
			{
				score = score - 500 * person.oxygen_level;
				person.oxygen_level++;
			}
			if (input == '4' && score >= 200)//购买氧气包
			{
				score = score - 200;
				person.oxygen += 1;
			}
			if (input == '5' && score >= 200)//购买能量包
			{
				score = score - 200;
				person.energy += 1;
			}
		}
	}
	/*回归原值部分 回归左右移动判断的值*/
	exist_leftstone = 0;
	exist_rightstone = 0;
	exist_downstone = 0;
	exist_flyleftstone = 0;
	exist_flyrightstone = 0;
}
void startMenu() // 初始菜单界面
{
	setfillcolor(BLACK);//背景为黑色
	fillrectangle(0, 0, 900, 670);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(width*0.3, high*0.2, _T("1 新游戏"));
	outtextxy(width*0.3, high*0.3, _T("2 读取游戏存档"));
	outtextxy(width*0.3, high*0.4, _T("3 退出"));
	FlushBatchDraw();
	Sleep(2);
	char input;
	if (kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == '1')
			scene = 1;
		else if (input == '2')
		{
			readRecordFile();
		}
		else if (input == '3')
		{
			exit(0);
		}
	}
}
void pauseMenu() // 游戏暂停后菜单界面，一般按ESC键后启动该界面
{
	setfillcolor(BLACK);//背景为黑色
	fillrectangle(0, 0, 900, 670);
	settextcolor(WHITE);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(width*0.3, high*0.2, _T("1 继续游戏"));
	outtextxy(width*0.3, high*0.3, _T("2 保存档案"));
	outtextxy(width*0.3, high*0.4, _T("3 退出"));
	FlushBatchDraw();
	Sleep(2);
	char input;
	if (kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == '1')
			scene = person.scene;
		else if (input == '2')
		{
			writeRecordFile();
		}
		else if (input == '3')
		{
			exit(0);
		}
	}
}
void readRecordFile()
{
	FILE *fp;
	int i, j, k;
	fp = fopen(".\\gameRecord.dat", "r");
	fscanf(fp, "%f %f %d %d %d", &person.center_x, &person.center_y, &person.scene, &score, &scene);
	for (k = 1; k < 3; k++)
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				fscanf(fp, " %d", &stone[k][i][j].status);
			}

	scene = person.scene;
	fclose(fp);
}
void writeRecordFile()
{
	FILE *fp;
	int i, j, k;
	fp = fopen(".\\gameRecord.dat", "w");
	fprintf(fp, "%f %f %d %d %d", person.center_x, person.center_y, person.scene, score, scene);
	for (k = 1; k < 3; k++)
		for (i = 0; i < num_stonehigh; i++)
			for (j = 0; j < num_stonewidth; j++)
			{
				fprintf(fp, " %d", stone[k][i][j].status);
			}
	scene = person.scene;
	fclose(fp);
}
void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

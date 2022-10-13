#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<windows.h>
#include<time.h>

#define width 600         //600*400的画布
#define high 400
#define X 60            //地图数组的横坐标
#define Y 40            //地图数组的纵坐标  
#define distence 30     //人物图像的长宽，截取的人物图像为正方形。。。。
#define speed 2          //人物移动的速度
#define control 10       //输入限速10
#define Boomwid 23       //炸弹宽
#define Boomhig 33        //炸弹高
#define armewid 17        //敌人宽
#define armehig 30       //敌人高

int x_man, y_man;         //炸弹人的坐标
int x_boom=-30, y_boom=-30;       //炸弹的坐标
int arme_x[3] = { 150,15 * 30,13 * 30 };           //敌人的横坐标
int arme_y[3] = { 30,30,9*30 };            //敌人的纵坐标

int map[X][Y] = { 0 };
/*初始化数组地图，0为可走黑块，1为不可炸毁障碍，
2为可炸毁障碍绘图点，22为障碍碰撞判断数值
3为炸弹人*/

int order = 0, turn = 0;
//炸弹人循环播放  order为横坐标，turn为纵坐标
//turn=0为向下，turn=1为向上，turn=2向左，turn=3胜利，turn=4死亡,turn=5向右
int boom_order = 0, boom_turn = 0;
//炸弹的循环播放，boom_order为横坐标,boom_turn为纵坐标
int arme_order[3] = { 0 }, arme_turn[3] = { 0 };
//敌人的循环播放，arme_order为横坐标，arme_turn为纵坐标
int armenum = 3;

int whether = 0;       //控制炸弹数量的变量
int boom = 0;          //判断炸弹是否爆炸的变量，0为没有爆炸，大于0为爆炸
int boom_up = 0, boom_down = 0, boom_left = 0, boom_right = 0;//上下左右的爆炸判定

int over = 1;       //游戏是否进行的判断常量  1为进行，0为死亡退出，2为胜利退出

clock_t begin, end;

IMAGE img_man, img_man1;
IMAGE img_stop, img_stop1;
IMAGE img_bk;
IMAGE img_boom, img_boom1;
IMAGE img_fail;
IMAGE img_arme,img_arme1;

//给障碍图片掩盖的部分全体赋值
void givedate(int x, int y)
{
	map[x][y + 1] = 22;
	map[x][y + 2] = 22;
	map[x + 1][y] = 22;
	map[x + 1][y + 1] = 22;
	map[x + 1][y + 2] = 22;
	map[x + 2][y] = 22;
	map[x + 2][y + 1] = 22;
	map[x + 2][y + 2] = 22;
}

//加载图片
void loadpicture()
{
	loadimage(&img_man, _T("D:\\猿\\期末大作业\\素材\\人物\\人物.jpg"));
	loadimage(&img_man1, _T("D:\\猿\\期末大作业\\素材\\人物\\人物1.jpg"));

	loadimage(&img_stop, _T("D:\\猿\\期末大作业\\素材\\地图\\障碍.jpg"));
	loadimage(&img_stop1, _T("D:\\猿\\期末大作业\\素材\\地图\\障碍1.jpg"));

	loadimage(&img_bk, _T("D:\\猿\\期末大作业\\素材\\地图\\地图.jpg"));

	loadimage(&img_boom, _T("D:\\猿\\期末大作业\\素材\\爆炸.jpg"));
	loadimage(&img_boom1, _T("D:\\猿\\期末大作业\\素材\\爆炸1.jpg"));

	loadimage(&img_fail, _T("D:\\猿\\期末大作业\\素材\\fail.jpg"));

	loadimage(&img_arme, _T("D:\\猿\\期末大作业\\素材\\怪物行走图.jpg"));
	loadimage(&img_arme1, _T("D:\\猿\\期末大作业\\素材\\怪物行走图1.jpg"));
}

/*数据初始化*/
void startup()
{
	x_man = 20;
	y_man = 20;

}


/*地图初始化*/
void datemap()
{
	initgraph(width, high);
	/*绘制地图障碍*/
	map[3][3 * 8] = 2;
	givedate(3, 3 * 8);
	//第一列
	map[2 * 3][2 * 3] = 2;
	givedate(2 * 3, 2 * 3);
	map[2 * 3][4 * 3] = 2;
	givedate(2 * 3, 4 * 3);
	map[2 * 3][5 * 3] = 2;
	givedate(2 * 3, 5 * 3);
	map[2 * 3][6 * 3] = 2;
	givedate(2 * 3, 6 * 3);
	map[2 * 3][8 * 3] = 2;
	givedate(2 * 3, 8 * 3);
	map[2 * 3][10 * 3] = 2;
	givedate(2 * 3, 10 * 3);
	//第二列
	map[3 * 3][4 * 3] = 2;
	givedate(3 * 3, 4 * 3);
	map[3 * 3][8 * 3] = 2;
	givedate(3 * 3, 8 * 3);
	//第三列
	map[4 * 3][3] = 2;
	givedate(4 * 3, 3);
	map[4 * 3][3 * 3] = 2;
	givedate(4 * 3, 3 * 3);
	map[4 * 3][4 * 3] = 2;
	givedate(4 * 3, 4 * 3);
	map[4 * 3][6 * 3] = 2;
	givedate(4 * 3, 6 * 3);
	map[4 * 3][8 * 3] = 2;
	givedate(4 * 3, 8 * 3);
	map[4 * 3][10 * 3] = 2;
	givedate(4 * 3, 10 * 3);
	//第四列
	map[6 * 3][2 * 3] = 2;
	givedate(6 * 3, 2 * 3);
	map[6 * 3][3 * 3] = 2;
	givedate(6 * 3, 3 * 3);
	map[6 * 3][4 * 3] = 2;
	givedate(6 * 3, 4 * 3);
	map[6 * 3][6 * 3] = 2;
	givedate(6 * 3, 6 * 3);
	map[6 * 3][8 * 3] = 2;
	givedate(6 * 3, 8 * 3);
	map[6 * 3][10 * 3] = 2;
	givedate(6 * 3, 10 * 3);
	//第六列
	map[7 * 3][10 * 3] = 2;
	givedate(7 * 3, 10 * 3);
	//第七列
	map[8 * 3][2 * 3] = 2;
	givedate(8 * 3, 2 * 3);
	map[8 * 3][4 * 3] = 2;
	givedate(8 * 3, 4 * 3);
	map[8 * 3][6 * 3] = 2;
	givedate(8 * 3, 6 * 3);
	map[8 * 3][8 * 3] = 2;
	givedate(8 * 3, 8 * 3);
	map[8 * 3][10 * 3] = 2;
	givedate(8 * 3, 10 * 3);
	//第八列
	map[10 * 3][2 * 3] = 2;
	givedate(10 * 3, 2 * 3);
	map[10 * 3][3 * 3] = 2;
	givedate(10 * 3, 3 * 3);
	map[10 * 3][4 * 3] = 2;
	givedate(10 * 3, 4 * 3);
	map[10 * 3][6 * 3] = 2;
	givedate(10 * 3, 6 * 3);
	map[10 * 3][8 * 3] = 2;
	givedate(10 * 3, 8 * 3);
	map[10 * 3][10 * 3] = 2;
	givedate(10 * 3, 10 * 3);
	//第十列
	map[12 * 3][2 * 3] = 2;
	givedate(12 * 3, 2 * 3);
	map[12 * 3][4 * 3] = 2;
	givedate(12 * 3, 4 * 3);
	map[12 * 3][6 * 3] = 2;
	givedate(12 * 3, 6 * 3);
	map[12 * 3][8 * 3] = 2;
	givedate(12 * 3, 8 * 3);
	map[12 * 3][9 * 3] = 2;
	givedate(12 * 3, 9 * 3);
	map[12 * 3][11 * 3] = 2;
	givedate(12 * 3, 11 * 3);
	//第十二列
	map[13 * 3][6 * 3] = 2;
	givedate(13 * 3, 6 * 3);
	map[13 * 3][8 * 3] = 2;
	givedate(13 * 3, 8 * 3);
	//第十三列
	map[14 * 3][3] = 2;
	givedate(14 * 3, 1 * 3);
	map[14 * 3][2 * 3] = 2;
	givedate(14 * 3, 2 * 3);
	map[14 * 3][4 * 3] = 2;
	givedate(14 * 3, 4 * 3);
	map[14 * 3][5 * 3] = 2;
	givedate(14 * 3, 5 * 3);
	map[14 * 3][6 * 3] = 2;
	givedate(14 * 3, 6 * 3);
	map[14 * 3][8 * 3] = 2;
	givedate(14 * 3, 8 * 3);
	map[14 * 3][10 * 3] = 2;
	givedate(14 * 3, 10 * 3);
	//第十四列
	map[16 * 3][2 * 3] = 2;
	givedate(16 * 3, 2 * 3);
	map[16 * 3][4 * 3] = 2;
	givedate(16 * 3, 4 * 3);
	map[16 * 3][6 * 3] = 2;
	givedate(16 * 3, 6 * 3);
	map[16 * 3][8 * 3] = 2;
	givedate(16 * 3, 8 * 3);
	map[16 * 3][10 * 3] = 2;
	givedate(16 * 3, 10 * 3);
	//第十六列
	map[17 * 3][8 * 3] = 2;
	givedate(17 * 3, 8 * 3);
	//第十七列
	map[18 * 3][2 * 3] = 2;
	givedate(18 * 3, 2 * 3);
	map[18 * 3][4 * 3] = 2;
	givedate(18 * 3, 4 * 3);
	map[18 * 3][6 * 3] = 2;
	givedate(18 * 3, 6 * 3);
	map[18 * 3][7 * 3] = 2;
	givedate(18 * 3, 7 * 3);
	map[18 * 3][8 * 3] = 2;
	givedate(18 * 3, 8 * 3);
	map[18 * 3][10 * 3] = 2;
	givedate(18 * 3, 10 * 3);


	BeginBatchDraw();
}

//显示函数
void show()
{
	int i, j;
	putimage(0, 0, &img_bk);

	if (whether > 0)
	{
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		//显示炸弹
	}
	if (boom > 0)
	{
		boom_turn = 1;
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		if (boom_up > 0)
		{
			boom_turn = 4;
			putimage(x_boom, y_boom - Boomhig, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom, y_boom - Boomhig, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		if (boom_down > 0)
		{
			boom_turn = 5;
			putimage(x_boom, y_boom + Boomhig, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom, y_boom + Boomhig, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		if (boom_left > 0)
		{
			boom_turn = 2;
			putimage(x_boom - Boomwid, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom - Boomwid, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		if (boom_right > 0)
		{
			boom_turn = 3;
			putimage(x_boom + Boomwid, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom + Boomwid, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		boom_turn = 0;
	}


	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{

			if (map[i][j] == 2)
			{
				putimage(i * 10, j * 10, &img_stop1, NOTSRCERASE);
				putimage(i * 10, j * 10, &img_stop, SRCINVERT);
			}


		}
	}

	putimage(x_man, y_man, distence, distence, &img_man1, order*distence, turn*distence, NOTSRCERASE);
	putimage(x_man, y_man, distence, distence, &img_man, order*distence, turn*distence, SRCINVERT);   
	//显示炸弹人
	
	for (i = 0; i < 3; i++)
	{
		putimage(arme_x[i], arme_y[i], armewid, armehig, &img_arme1, arme_order[i]*armewid, arme_turn[i]*armehig, NOTSRCERASE);
		putimage(arme_x[i], arme_y[i], armewid, armehig, &img_arme, arme_order[i]*armewid, arme_turn[i]*armehig, SRCINVERT);
	}

	FlushBatchDraw();
	if (over == 0)
	{
		putimage(0, 0, &img_fail);
		FlushBatchDraw();
		Sleep(100);
		exit(0);
	}
	if (armenum == 0)
	{
		Sleep(100);
		exit(0);
	}
	
}

//与用户输入无关的更新
void updateWithoutInput()
{
	static int x = 0;              //炸弹爆炸时间判断
	if (whether>0)
	{
		if (x < 5)
			x++;
		if (x == 5)
		{
			boom_order++;
			if (boom_order == 3)
				boom_order = 0;
		}
		end = clock();
		if (((double)end - begin) / CLK_TCK >2)
		{
			begin = clock();
			boom = 1;
			
		}
	}
	if (boom > 0)                   //炸弹爆炸后时间判断
	{
		if (x < 5)
			x++;
		if (x == 5)
		{
			boom_order++;
			if (boom_order == 3)
				boom_order = 0;
		}
		end = clock();
		if (((double)end - begin) / CLK_TCK >0.5)
		{
			boom = 0;
			whether = 0;
		}
		if (map[(x_boom + 5) / 10 - Boomhig/10][(y_boom + 5) / 10 + 1] == 0)       //炸弹上方的爆炸判定   y+1为了保持在中间判定
			boom_up++;
		if (map[(x_boom + 5) / 10 + Boomhig / 10][(y_boom + 5) / 10 + 1] == 0)      //炸弹下方的爆炸判定   
			boom_down++;
		if (map[(x_boom + 5) / 10 + 1][(y_boom + 5) / 10 - Boomwid / 10] == 0)     //炸弹左侧的爆炸判定
			boom_left++;
		if (map[(x_boom+5) / 10 + 1][(y_boom +5)/ 10 + Boomwid / 10] == 0)      //炸弹右侧的爆炸判定
			boom_right++;
		
		//炸弹伤害判断
		if (x_man <= x_boom + 2*Boomwid&&x_man >= x_boom - Boomwid)
		{
			if (y_man <= y_boom + Boomhig&&y_man >= y_boom)
			{
				over = 0;
			}
		}
		if (y_man <= y_boom + 2 * Boomhig&&y_man >= y_boom - Boomhig)
		{
			if (x_man <= x_boom + Boomwid&&x_man >= x_boom)
			{
				over = 0;
			}
		}
	}
	
	//敌人移动更新模块
	static int armespeed[3] = { 0 };  //怪物移动限速
	//怪物1
	if (arme_x[0] == 150 && arme_y[0] == 30)  //向下转
	{
		arme_turn[0] = 1;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	}
	else if (arme_x[0] == 150 && arme_y[0] == 150)       //向右转
	{
		arme_turn[0] = 2;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	} 
	else if (arme_x[0] == 13 * 30 && arme_y[0] == 150)   //向上转
	{
		arme_turn[0] = 3;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	}
	else if (arme_x[0] == 13 * 30 && arme_y[0] == 30)     //向左转
	{
		arme_turn[0] = 0;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	}
	//怪物1移动
	if (arme_x[0] == 150 && arme_y[0] < 150)           //向下移动
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_y[0]++;
		}
	}		
	else if (arme_x[0] == 13 * 30 && arme_y[0] > 30)    //向上移动
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_y[0]--;
		}
	}		
	else if (arme_y[0] == 150 && arme_x[0] < 13 * 30)   //向右移动
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_x[0]++;
		}
	}		
	else if (arme_y[0] == 30 && arme_x[0] > 150)       //向左移动
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_x[0]--;
		}
	}		

	//怪物2
	if (arme_x[1] == 15*30 && arme_y[1] == 30)  //向下转
	{
		arme_turn[1] = 1;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	else if (arme_x[1] == 15 * 30 && arme_y[1] == 7 * 30)   //向右转
	{
		arme_turn[1] = 2;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	else if (arme_y[1] == 7 * 30 && arme_x[1] == 17 * 30)   //向上转
	{
		arme_turn[1] = 3;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	else if (arme_x[1] == 17 * 30 && arme_y[1] == 30)       //向左转
	{
		arme_turn[1] = 0;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	//怪物2移动
	if (arme_x[1] == 15 * 30 && arme_y[1] < 7 * 30)     //向下移动
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_y[1]++;
		}
	}
	else if (arme_y[1] == 7 * 30 && arme_x[1] < 17 * 30)    //向右移动
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_x[1]++;
		}
	}
	else if (arme_x[1] == 17 * 30 && arme_y[1] > 30)      //向上移动
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_y[1]--;
		}
	}
	else if (arme_y[1] == 30 && arme_x[1] > 15 * 30)       //向左移动
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_x[1]--;
		}
	}

	//怪物3
	if(arme_x[2] == 13*30 && arme_y[2] == 9*30)  //向下转
	{
		arme_turn[2] = 1;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	if (arme_x[2] == 13 * 30 && arme_y[2] == 11 * 30)       //向右转
	{
		arme_turn[2] = 2;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	if (arme_x[2] == 17 * 30 && arme_y[2] == 11 * 30)        //向上转
	{
		arme_turn[2] = 3;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	if (arme_x[2] == 17 * 30 && arme_y[2] == 9 * 30)         //向左转
	{
		arme_turn[2] = 0;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	//怪物3移动
	if (arme_x[2] == 13 * 30 && arme_y[2] < 11 * 30)         //向下移动
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_y[2]++;
		}
	}
	else if (arme_y[2] == 11 * 30 && arme_x[2] < 17 * 30)            //向右移动
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_x[2]++;
		}
	}
	else if (arme_x[2] == 17 * 30 && arme_y[2] > 9 * 30)          //向上移动
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_y[2]--;
		}
	}
	else if (arme_y[2] == 9 * 30 && arme_x[2] > 13 * 30)         //向左移动
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_x[2]--;
		}
	}
}

//与用户输入有关的更新
void updateWithInput()
{
	static int num = 0;
	if ((GetAsyncKeyState(0x57) & 0x8000))//w 
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (y_man>30)
			{

				order++;
				turn = 1;

				if (map[(x_man + distence / 2) / 10][y_man / 10] != 2 && map[(x_man + distence / 2) / 10][y_man / 10] != 22)
				{
					y_man = y_man - speed;
				}


				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(0x53) & 0x8000))//s
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (y_man + distence <high-30)
			{

				order++;
				turn = 0;

				if (map[(x_man + distence / 2) / 10][(y_man + distence) / 10] != 2 && map[(x_man + distence / 2) / 10][(y_man + distence) / 10] != 22)
				{
					y_man = y_man + speed;
				}


				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(0x41) & 0x8000))//a 
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (x_man>30)
			{
				order++;
				turn = 2;
				if (map[x_man / 10][(y_man + distence / 2) / 10] != 22 && map[x_man / 10][(y_man + distence / 2) / 10] != 2)
				{
					x_man = x_man - speed;
				}
				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(0x44) & 0x8000))//d
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (x_man + distence  <width-30)
			{
				order++;
				turn = 5;
				if (map[(x_man + distence) / 10][(y_man + distence / 2) / 10] != 22 && map[(x_man + distence) / 10][(y_man + distence / 2) / 10] != 2)
				{
					x_man = x_man + speed;
				}

				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(VK_SPACE)))
	{
		if (whether == 0)
		{
			begin = clock();
			x_boom = x_man;
			y_boom = y_man;
			whether++;
		}	
	}
}

//游戏结束
void gameover()
{
	_getch();
	closegraph();
	EndBatchDraw();

}

void main()
{
	loadpicture();//加载图片
	startup();  // 数据初始化
	datemap();  //地图初始化

	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithInput();     // 与用户输入有关的更新
		updateWithoutInput();  // 与用户输入无关的更新
	}
	gameover();     // 游戏结束、后续处理
}

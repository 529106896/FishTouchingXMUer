#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<windows.h>


#define width 600         //600*400的画布
#define high 400
#define X 60            //地图数组的横坐标
#define Y 40            //地图数组的纵坐标  
#define distence 30     //人物图像的长宽，截取的人物图像为正方形。。。。
#define speed 2          //人物移动的速度
#define control 10       //输入限速10

int x_man, y_man;         //炸弹人的坐标

int map[X][Y] = { 0 };     
/*初始化数组地图，0为可走黑块，1为不可炸毁障碍，
2为可炸毁障碍绘图点，22为障碍碰撞判断数值
3为炸弹人*/

int order = 0, turn = 0;        
//炸弹人循环播放  order为横坐标，j为纵坐标
//turn=0为向下，turn=1为向上，turn=2向左，turn=3胜利，turn=4死亡,turn=5向右


IMAGE img_man, img_man1;
IMAGE img_stop, img_stop1;
IMAGE img_bk;

//给障碍图片掩盖的部分全体赋值
void givedate(int x,int y)         
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
	loadimage(&img_stop, _T("D:\\猿\\期末大作业\\素材\\地图\\障碍.jpg"));
	loadimage(&img_stop1, _T("D:\\猿\\期末大作业\\素材\\地图\\障碍1.jpg"));
	loadimage(&img_man1, _T("D:\\猿\\期末大作业\\素材\\人物\\人物1.jpg"));
	loadimage(&img_bk, _T("D:\\猿\\期末大作业\\素材\\地图\\地图.jpg"));
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
	map[3][3*8] = 2;
	givedate(3, 3 * 8);
	//第一列
	map[2 * 3][2 * 3] = 2;
	givedate(2 * 3, 2 * 3);
	map[2 * 3][4 * 3] = 2;
	givedate(2 * 3,4 * 3);
	map[2 * 3][5 * 3] = 2;
	givedate(2 * 3,5 * 3);
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
	FlushBatchDraw();
}

// 与用户输入无关的更新
/*void updateWithoutInput()      
{

}*/

//与用户输入有关的更新
void updateWithInput()          
{
	static int num = 0;
	if ((GetAsyncKeyState(0x57) & 0x8000))//w 
	{
		if (num < control)
			num++;
		else if(num== control)
		{
			if (y_man>0)
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
			if (y_man + distence <high)
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
			if (x_man>0)
			{
				order++;
				turn = 2;	
				if (map[x_man/10][(y_man + distence / 2)/10] != 22 && map[x_man / 10][(y_man + distence / 2) / 10] != 2)
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
			if (x_man + distence  <width)
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
		//updateWithoutInput();  // 与用户输入无关的更新
		
	}
	gameover();     // 游戏结束、后续处理
}

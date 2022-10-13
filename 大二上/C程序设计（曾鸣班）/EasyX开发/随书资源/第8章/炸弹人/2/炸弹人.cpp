#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

#define width 600
#define high 400
#define X 120
#define Y 80
#define distence 33

int x_man, y_man;         //炸弹人的坐标
int speed;                //炸弹人移动的速度
int map[X][Y] = { 0 };     
/*初始化数组地图，0为可走黑块，1为不可炸毁障碍，
2为可炸毁障碍绘图点，22为实际障碍
3为炸弹人*/

int i = 0, turn = 0;        //炸弹人循环播放  i为横坐标，j为纵坐标
//turn=0为向下，turn=1为向上，turn=2向左，turn=3胜利，turn=4死亡,turn=5向右


IMAGE img_man,img_stop;

//给障碍图片掩盖的部分全体赋值
void givedate(int x,int y)         
{
	int i, j;
	for (i = x; i < x + 3; i++)
	{
		for (j = y; j < y + 3; j++)
		{
			map[i][j] = 22;
		}
	}
	map[x][y] = 2;
}

//加载图片
void loadpicture()     
{
	loadimage(&img_man, _T("D:\\猿\\期末大作业\\素材\\人物\\人物.jpg"));
	loadimage(&img_stop, _T("D:\\猿\\期末大作业\\素材\\地图\\大障碍.jpg"));
}

/*数据初始化*/ 
void startup()        
{
	x_man = 2;
	y_man = 2;
	putimage(x_man*10, y_man*10,distence, distence, &img_man, 0, 0);
}


/*地图初始化*/
void datemap()         
{
	initgraph(width, high);
	int i, j;
	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			if (i  == x_man&&j == y_man)
				map[i][j] = 3;
		}
	}
	/*绘制地图障碍*/
	map[3][3*8] = 2;
	//givedate(3, 3 * 8);
	//第一列
	map[2 * 3][2 * 3] = 2;
	//givedate(2 * 3, 2 * 3);
	map[2 * 3][4 * 3] = 2;
	//givedate(2 * 3,4 * 3);
	map[2 * 3][5 * 3] = 2;
	//givedate(2 * 3,5 * 3);
	map[2 * 3][6 * 3] = 2;
	map[2 * 3][8 * 3] = 2;
	map[2 * 3][10 * 3] = 2;
	//第二列
	map[3 * 3][4 * 3] = 2;
	map[3 * 3][8 * 3] = 2;
	//第三列
	map[4 * 3][3] = 2;
	map[4 * 3][3 * 3] = 2;
	map[4 * 3][4 * 3] = 2;
	map[4 * 3][6 * 3] = 2;
	map[4 * 3][8 * 3] = 2;
	map[4 * 3][10 * 3] = 2;
	//第四列
	map[6 * 3][2 * 3] = 2;
	map[6 * 3][3 * 3] = 2;
	map[6 * 3][4 * 3] = 2;
	map[6 * 3][6 * 3] = 2;
	map[6 * 3][8 * 3] = 2;
	map[6 * 3][10 * 3] = 2;
	//第六列
	map[7 * 3][10 * 3] = 2;
	//第七列
	map[8 * 3][2 * 3] = 2;
	map[8 * 3][4 * 3] = 2;
	map[8 * 3][6 * 3] = 2;
	map[8 * 3][8 * 3] = 2;
	map[8 * 3][10 * 3] = 2;
	//第八列
	map[10 * 3][2 * 3] = 2;
	map[10 * 3][3 * 3] = 2;
	map[10 * 3][4 * 3] = 2;
	map[10 * 3][6 * 3] = 2;
	map[10 * 3][8 * 3] = 2;
	map[10 * 3][10 * 3] = 2;
	//第十列
	map[12 * 3][2 * 3] = 2;
	map[12 * 3][4 * 3] = 2;
	map[12 * 3][6 * 3] = 2;
	map[12 * 3][8 * 3] = 2;
	map[12 * 3][9 * 3] = 2;
	map[12 * 3][11 * 3] = 2;
	//第十二列
	map[13 * 3][6 * 3] = 2;
	map[13 * 3][8 * 3] = 2;
	//第十三列
	map[14 * 3][3] = 2;
	map[14 * 3][2 * 3] = 2;
	map[14 * 3][4 * 3] = 2;
	map[14 * 3][5 * 3] = 2;
	map[14 * 3][6 * 3] = 2;
	map[14 * 3][8 * 3] = 2;
	map[14 * 3][10 * 3] = 2;
	//第十四列
	map[16 * 3][2 * 3] = 2;
	map[16 * 3][4 * 3] = 2;
	map[16 * 3][6 * 3] = 2;
	map[16 * 3][8 * 3] = 2;
	map[16 * 3][10 * 3] = 2;
	//第十六列
	map[17 * 3][8 * 3] = 2;
	//第十七列
	map[18 * 3][2 * 3] = 2;
	map[18 * 3][4 * 3] = 2;
	map[18 * 3][6 * 3] = 2;
	map[18 * 3][7 * 3] = 2;
	map[18 * 3][8 * 3] = 2;
	map[18 * 3][10 * 3] = 2;
		
	
	BeginBatchDraw();
}

//显示函数
void show()
{
	int i, j;
	//cleardevice();

	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			if (map[i][j] == 2)
				putimage(i * 10, j * 10, &img_stop);
			//if (map[i][j] == 3)
				//putimage(x_man * 10, y_man * 10, distence, distence, &img_man, 0, 0);
		
		}
	}
	FlushBatchDraw();
}

// 与用户输入无关的更新
/*void updateWithoutInput()      
{

}*/

//与用户输入有关的更新
void updateWithInput()          
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		if (ch == 'w'&&y_man>0)
		{
			cleardevice();
			i++;
			turn = 1;
			//if(map[x_man][y_man]!=22&& map[x_man][y_man] != 2)    //与障碍碰撞的判断
				y_man--;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}

		if (ch == 's'&&y_man+ distence / 10 + 1<Y)
		{
			cleardevice();
			i++;
			turn = 0;
			//if(map[x_man][y_man+ distence / 10]!=22&& map[x_man][y_man + distence / 10] != 2)
				y_man++;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}
		if (ch == 'a'&&x_man>0)
		{
			cleardevice();
			i++;
			turn = 2;
			//if(map[x_man][y_man]!=22&& map[x_man][y_man] != 2)
				x_man--;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}
		if (ch == 'd'&&x_man+ distence / 10 + 1<X)
		{
			cleardevice();
			i++;
			turn = 5;
			//if(map[x_man+ distence / 10][y_man]!=22&& map[x_man + distence / 10][y_man] != 2)
				x_man++;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
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
		updateWithInput();     // 与用户输入有关的更新
		show();  // 显示画面
		//updateWithoutInput();  // 与用户输入无关的更新
		
	}
	gameover();     // 游戏结束、后续处理
}

#include <conio.h>
#include <graphics.h>
#include <stdio.h>
int man_x;				//定义人物的横坐标
int man_y;				//定义人物的纵坐标
int man_vy_begin;		//定义人物的垂直起跳初速度
int man_vx;				//定义人物的水平速度
int man_vy;				//定义人物的实时垂直速度
int a_vy;				//定义垂直速度方向的重力加速度
int a[560][560];		//定义画布大小
int jump_if;			//这个变量用于记载人物状态 空中状态为1 非空中状态为0 只有当非空中状态时才可以按‘w’起跳
//int speed_control;	//用于控制速度
//int speed;			//用于控制速度
IMAGE img_bk;			// 定义 IMAGE 对象 背景
IMAGE img_man;			//定义 IMAGE 对象 人物
void begining()						//游戏初始化模块
{
	man_x=100;
	man_y=509;
	man_vx=2;
	man_vy_begin=13;
	man_vy=man_vy_begin;
	a_vy=1;
	//speed_control=5;
	//speed=0;
	jump_if=0;
	loadimage(&img_bk, ".//蓝色药水1关.jpg",560,560);			// 读取背景图片到 img_bk 对象中
	loadimage(&img_man,".//向右1.jpg",30,30);			//读取人物图片到ima_man 对象中			

}
int map_y_down(int man_x,int man_y)						//定义地图函数 地图函数判断人物是否踩到地面 踩到返回1 否则返回0
{
	int judge;
	return judge;
}
int map_y_up(int man_x,int man_y)						//定义地图函数 判断人物的头顶是否有墙 有则返回1 否则返回0
{
	int judge;
	return judge;

}
int map_x_left(int man_x,int man_y)						//定义地图函数 判断人物的左边是否有墙 有则返回1 否则返回0
{
	int judge;
	return judge;
}
int map_x_right(int man_x,int man_y)					//定义地图函数 判断人物的右边是否有墙 有则返回1 否则返回0
{
	int judge;
	return judge;
}
void show()				//游戏显示模块
{
	putimage(0, 0, &img_bk);				// 在坐标 (0, 0) 位置显示 IMAGE 对象
	putimage(man_x, man_y, &img_man);		//显示出人物
}

void without_input()			//与用户输入无关的更新
{
	if(jump_if==1)				//当记载人物上升状态为1的时候 人物起跳
	{
		man_y=man_y-man_vy;
		man_vy=man_vy-a_vy;		//速度因存在重力加速度而改变
		/*if(map_y_up(int man_x,int man_y))					//调用地图函数 地图函数判断人物头顶是否有墙 有则返回1 否则返回0
		{
			man_vy=0;										//人物头顶撞到墙 垂直速度变为0	
		}
		*/
		if(man_y==509/*map_y_down(man_x,man_y)*/)			//调用地图函数 地图函数判断人物是否踩到地面 踩到返回1 否则返回0
		{
			man_vy=0;
			jump_if=0;										//人物踩到地面 变为非空中状态 0
			man_vy=man_vy_begin;							//人物踩到地面 重置起跳速度等于垂直速度
		}
	}
}

void user_input()				//与用户输入有关的更新
{
		if(GetAsyncKeyState('A')&0x8000)  
		{
			//if(/*!map_x_left(man_x,man_y)*/)			//调用地图函数 判断人物的左边是否有墙 有则返回1 否则返回0（前面有一个‘!’符号 没有墙返回0 ‘!0’则为真） 
			//{
				man_x-=2;  // 位置左移
			//}
		}
		if(GetAsyncKeyState('D')&0x8000)
		{
			//if(/*!!map_x_left(man_x,man_y)*/)			//调用地图函数 判断人物右边是否有墙 有则返回1 否则返回0 (前面加了一个‘!’ 没有墙返回0 ‘!0’为真)
			//{
				man_x+=2;  // 位置右移
			//}		
		}
		if(jump_if==0)			//当人物踩到地面时 ‘w’键才能有效输入
		{
			if(GetAsyncKeyState('W')&0x8000)
			{
				jump_if=1;			//‘w’键有效输入之后 上升状态变为1
			}
		}
	
}
void main()				//主函数
{
	initgraph(560,560);
	begining();
	BeginBatchDraw();
	while(1)
	{
		show();
		FlushBatchDraw();
		without_input();
		Sleep(15);
		user_input();
	}
	EndBatchDraw();
	getch();
	closegraph();
}


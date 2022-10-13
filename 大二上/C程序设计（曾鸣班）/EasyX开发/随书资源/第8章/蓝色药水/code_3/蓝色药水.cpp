#include <conio.h>
#include <graphics.h>
#include <stdio.h>
float man_x;				//定义人物的横坐标
float man_y;				//定义人物的纵坐标
float man_vy_begin;			//定义人物的垂直起跳初速度
float man_vx;				//定义人物的水平速度
float man_vy;				//定义人物的实时垂直速度
float a_vy;					//定义垂直速度方向的重力加速度
int sky_if;					//这个变量用于记载人物状态 空中状态为1 非空中状态为0 只有当非空中状态时才可以按‘w’起跳 空中状态人物受重力
float bullet_x[4],bullet_y[4];		//定义地图自动发射的子弹的坐标
float bullet_vx[4],bullet_vy[4];		//定义地图自动发射的子弹的速度
float bullet_v1,bullet_v0;			//定义两种速度情况
IMAGE img_bk;				//定义 IMAGE 对象 背景
IMAGE img_man;				//定义 IMAGE 对象 人物
IMAGE img_bullet;			//定义 IMAGE 对象 地图自动发射子弹
void begining()						//游戏初始化模块
{
	man_x=100;
	man_y=633;
	man_vx=2;
	man_vy_begin=-6.5;
	man_vy=0;

	bullet_v1=5;
	bullet_v0=0;
	int i;
	for(i=0;i<4;i++)
	{
		bullet_x[i]=bullet_y[i]=50;
		bullet_vx[i]=bullet_v1;
		bullet_vy[i]=bullet_v0;
	}
	
	a_vy=0.25;
	sky_if=0;
	loadimage(&img_bk, ".\\蓝色药水第8关.jpg",696,696);			// 读取背景图片到 img_bk 对象中
	loadimage(&img_man,".\\蓝色药水素材\\向右移动\\向右1.jpg",37,37);			//读取人物图片到img_man 对象中
	loadimage(&img_bullet,".\\子弹.jpg",30,30);					//读取子弹图片到 img_bullet 对象中

}
int map_y_down(int x1,int y1)						//定义地图函数 地图函数判断人物是否踩到地面 踩到返回1 否则返回0
{
	int judge;
	if(y1>633)
		judge=633;
	else if(y1>=573&&y1<=580&&x1>393&&x1<527)//1
		judge=573;
	else if(y1>=533&&y1<=540&&x1>533&&x1<629)//2
		judge=533;
	else if(y1>=472&&y1<=479&&x1>413&x1<508)//3
		judge=472;	
	else if(y1>=472&&y1<=479&&x1>250&&x1<346)//4
		judge=472;
	else if(y1>=472&&y1<=479&&x1>90&&x1<185)//6
		judge=472;
	else if(y1>=533&&y1<=540&&x1<185)//5
		judge=533;
	else if(y1>=411&&y1<=418&&x1<65)//7
		judge=411;
	else if(y1>=350&&y1<=357&&x1>90&&x1<185)//8
		judge=350;
	else if(y1>=290&&y1<=297&&x1<65)//9
		judge=290;
	else if(y1>=230&&y1<=237&&x1>90&&x1<185)//10
		judge=230;
	else if(y1>=169&&y1<=176&&x1<65)//11
		judge=169;
	else if(y1>=330&&y1<=337&&x1>213&&x1<260)//穿屏豆1
		judge=330;
	else if(y1>=252&&y1<=259&&x1>311&&x1<547)//12
		judge=252;
	else if(y1>=252&&y1<=259&&x1>550&&x1<632)//13
		judge=252;
	else if(y1>=330&&y1<=337&&x1>620)//14
		judge=330;
	else if(y1>=370&&y1<=377&&x1>524&&x1<629)//15
		judge=370;
	else if(y1>=330&&y1<=337&&x1>505&&x1<547)//穿屏豆2
		judge=330;
	else if(y1>=330&&y1<=337&&x1>470&&x1<490)//穿屏豆3
		judge=330;
	else if(y1>=88&&y1<=95&&x1<632)//16
		judge=88;
	else 
		judge=0;
	return judge;

}
int map_y_up(int x2,int y2)						//定义地图函数 判断人物的头顶是否有墙 有则返回1 否则返回0
{
	int judge;
	return judge;
}
int map_x_left(int x3,int y3)						//定义地图函数 判断人物的左边是否有墙 有则返回1 否则返回0
{
	int judge;
	return judge;
}
int map_x_right(int x4,int y4)					//定义地图函数 判断人物的右边是否有墙 有则返回1 否则返回0
{
	int judge;
	return judge;
}
void show()				//游戏显示模块
{
	putimage(0, 0, &img_bk);				// 在坐标 (0, 0) 位置显示 IMAGE 对象
	putimage(man_x, man_y, &img_man);		//显示出人物
	
	int i=0;
	putimage(bullet_x[i],bullet_y[i],&img_bullet);
}

void without_input()				//与用户输入无关的更新
{
	man_y=man_y+man_vy;				//人物的垂直速度man_y初始化是0，所以虽然有这段表达式，但人物并不会起跳
	
	int i=0;
	//for(i=0;i<4;i++)
	//{
		bullet_x[i]=bullet_x[i]+bullet_vx[i];
		bullet_y[i]=bullet_y[i]+bullet_vy[i];
		if(bullet_x[i]==630&&bullet_y[i]==50)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==630&&bullet_y[i]==625)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==545&&bullet_y[i]==625)
		{
			bullet_vy[i]=-bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==545&&bullet_y[i]==180)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==80&&bullet_y[i]==180)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==80&&bullet_y[i]==525)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==0&&bullet_y[i]==525)
		{
			bullet_x[i]=695;
		}
		if(bullet_x[i]==385&&bullet_y[i]==525)
		{
			bullet_vy[i]=-bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==385&&bullet_y[i]==325)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==210&&bullet_y[i]==325)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_y[i]==650)
		{
			bullet_vx[i]=bullet_v1;
			bullet_vy[i]=bullet_v0;
			bullet_x[i]=50;
			bullet_y[i]=50;
		}
	//}

	

	if(!map_y_down(man_x,man_y))					//调用地图函数，判断人物是否处于空中状态
	{
		sky_if=1;					//如果人物处于空中状态，则sky_if变为1；
	}
	if(sky_if==1)				//当人物空中状态为1的时候 启动在空中应该有的自动更新 
	{
	
		if(man_vy>=man_vy_begin)			//限制最大速度为起跳初速度
		{
			man_vy=man_vy+a_vy;		//在空中的时候速度因重力加速度而改变;	
		}
		
		/*if(map_y_up(int man_x,int man_y))					//调用地图函数 地图函数判断人物头顶是否有墙 有则返回1 否则返回0
		{
			man_vy=0;										//人物头顶撞到墙 垂直速度变为0	
		}*/
		if(map_y_down(man_x,man_y))			//调用地图函数 地图函数判断人物是否踩到地面 踩到返回1 否则返回0
		{
			man_vy=0;
			sky_if=0;						//人物踩到地面 变为非空中状态 0
			man_y=map_y_down(man_x,man_y);
		}
	}
}

void user_input()				//与用户输入有关的更新
{
		if(GetAsyncKeyState('A')&0x8000)  
		{
			//if(!map_x_left(man_x,man_y))			//调用地图函数 判断人物的左边是否有墙 有则返回1 否则返回0（前面有一个‘!’符号 没有墙返回0 ‘!0’则为真） 
			//{
				man_x-=2.2;  // 位置左移
			//}
		}
		if(GetAsyncKeyState('D')&0x8000)
		{
			//if(!map_x_right(man_x,man_y))			//调用地图函数 判断人物右边是否有墙 有则返回1 否则返回0 (前面加了一个‘!’ 没有墙返回0 ‘!0’为真)
			//{
				man_x+=2.2;  // 位置右移
			//}		
		}
		if(sky_if==0)			//当人物踩到地面为非空中状态时 ‘w’键才能有效输入
		{
			if(GetAsyncKeyState('W')&0x8000)
			{
				man_vy=man_vy_begin;			//‘w’键有效输入之后 人物立即拥有一个竖直方向上的初速度
			}
		}	
}
void main()				//主函数
{
	initgraph(696,696);
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

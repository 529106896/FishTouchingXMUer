//显示进入游戏菜单

//存在问题：在鱼随机移动过程中可能出现相互粘合在一块的情况。
//存在问题：食物鱼部分 过多重复代码



#include<graphics.h>
#include<conio.h>
#include<time.h>


#define length 1000//游戏画面宽度
#define high 640//游戏画面高度


struct yu
{
	double position_x;//横坐标
	double position_y;//纵坐标
	double v_x;//水平速度
	double v_y;//竖直速度
};
yu player;//玩家
yu timer;//闹钟
yu zhadan;//
yu food1;//1号鱼
yu food2;//2号鱼
yu food3;//3号鱼
yu food4;//4号鱼
yu food5;//5号鱼

IMAGE img_p1;//玩家图片
IMAGE img_p1bei;
IMAGE img_bk;//背景图片
IMAGE img_bk0;//进入界面图
IMAGE img_time;
IMAGE img_timebei;//闹钟图片
IMAGE img_zha;
IMAGE img_zhabei;//图片
IMAGE img_f1;
IMAGE img_f1bei;//1号鱼图片
IMAGE img_f2;
IMAGE img_f2bei;//2号鱼图片
IMAGE img_f3;
IMAGE img_f3bei;//3号鱼图片
IMAGE img_f4;
IMAGE img_f4bei;//4号鱼图片
IMAGE img_f5;
IMAGE img_f5bei;//5号鱼图片
char input;
double  p1size;//定义一个变量来储存玩家鱼的尺寸；
double  start_p1size;//定义一个变量来储存玩家的初始大小；
int score_p1;//分数
int gameStatus=0; // 游戏状态，0为选择界面，1为开始界面，2为结束游戏



void startMenu()
{
	putimage(0, 0, &img_bk0);//显示背景
	settextcolor(RGB(123,90,254));
	settextstyle(70,0, _T("华文琥珀"));
	outtextxy(length*0.36, high*0.19, _T("大鱼吃小鱼"));

	setbkmode(TRANSPARENT);
	settextcolor(RGB(106,0,0));
	settextstyle(37,0, _T("幼圆"));
	outtextxy(length*0.35, high*0.36, _T("1 新游戏"));
	outtextxy(length*0.35, high*0.44, _T("2 退出游戏"));


	settextcolor(RGB(64,0,128));
	settextstyle(25,0, _T("微软雅黑"));
	outtextxy(length*0.36, high*0.6, _T("方向键控制移动吃掉小鱼"));
	outtextxy(length*0.36, high*0.65, _T("在限时内达到目标分"));
	outtextxy(length*0.36, high*0.7, _T("闹钟增加时间 炸弹减少时间"));
	outtextxy(length*0.36, high*0.75, _T("三条生命 撞大鱼失去一条"));
	FlushBatchDraw();
	Sleep(2);

	char input;
	if(kbhit())//判断是否有输入
	{
		input=getch();//根据用户的不同输入来移动
		if (input=='1') 
			gameStatus=1;
		else if(input=='2')
		{
			gameStatus=2;
			exit(0);
		}
	}
}



void startup()
{
	score_p1=0;
	p1size=60;//玩家初始大小为60
	start_p1size=p1size;
	srand((unsigned) time(NULL));//随机数

	//是否调整 IMAGE 的大小以适应图片
	loadimage(&img_bk0, _T("D:\\enter.jpg"),1000,640,true);//进入界面
	loadimage(&img_bk, _T("D:\\background.jpg"),1000,640,true);//背景

	loadimage(&img_time, _T("D:\\time.jpg"),50,50,true);
	loadimage(&img_timebei, _T("D:\\timebei.jpg"),50,50,true);//闹钟

	loadimage(&img_zha, _T("D:\\zhadan1.jpg"),50,50,true);
	loadimage(&img_zhabei, _T("D:\\zhadan1bei.jpg"),50,50,true);//炸弹

	loadimage(&img_f1, _T("D:\\food1.jpg"),45,45,true);
	loadimage(&img_f1bei, _T("D:\\food1bei.jpg"),45,45,true);//1号鱼

	loadimage(&img_f2, _T("D:\\food2.jpg"),80,80,true);
	loadimage(&img_f2bei, _T("D:\\food2bei.jpg"),80,80,true);//2号鱼

	loadimage(&img_f3, _T("D:\\food3.jpg"),110,110,true);
	loadimage(&img_f3bei, _T("D:\\food3bei.jpg"),110,110,true);//3号鱼

	loadimage(&img_f4, _T("D:\\food4.jpg"),130,130,true);
	loadimage(&img_f4bei, _T("D:\\food4bei.jpg"),130,130,true);//4号鱼

	loadimage(&img_f5, _T("D:\\food5.jpg"),200,160,true);
	loadimage(&img_f5bei, _T("D:\\food5bei.jpg"),200,160,true);//5号鱼


	player.position_x=length/2.0;//玩家横坐标
	player.position_y=high/2.0;//玩家纵坐标
	player.v_x=0.4;//玩家水平速度
	player.v_y=0.4;//玩家竖直速度

	timer.position_x=-2000;//闹钟横坐标
	timer.position_y=rand()%500;//闹钟纵坐标随机设定
	timer.v_x=0.6;//闹钟速度

	zhadan.position_x=length+500;//横坐标
	zhadan.position_y=rand()%500;//纵坐标随机设定
	zhadan.v_x=0.6;//速度

	food1.position_x=0;//1号鱼横坐标
	food1.position_y=rand()%400;//1号鱼纵坐标随机设定
	food1.v_x=0.45;//1号鱼速度

	food2.position_x=-200;//2号鱼横坐标
	food2.position_y=rand()%400;//2号鱼纵坐标随机设定
	food2.v_x=0.45;//2号鱼速度

	food3.position_x=-500;//3号鱼横坐标
	food3.position_y=rand()%400;//3号鱼纵坐标随机设定
	food3.v_x=0.5;//3号鱼速度

	food4.position_x=-800;//4号鱼横坐标
	food4.position_y=rand()%400;//4号鱼纵坐标随机设定
	food4.v_x=0.5;//4号鱼速度

	food5.position_x=-1000;//5号鱼横坐标
	food5.position_y=rand()%400;//5号鱼纵坐标随机设定
	food5.v_x=0.4;//5号鱼速度

	initgraph(length,high);//画面大小
	BeginBatchDraw();

	while (gameStatus==0)
		startMenu();//初始菜单界面

}


void show()
{
	putimage(0, 0, &img_bk);//显示背景

	loadimage(&img_p1, _T("D:\\player.jpg"),p1size,p1size,true);
	loadimage(&img_p1bei, _T("D:\\playerbei.jpg"),p1size,p1size,true);//玩家

	putimage(timer.position_x, timer.position_y, &img_timebei,NOTSRCERASE);//显示闹钟
	putimage(timer.position_x, timer.position_y, &img_time,SRCINVERT);

	putimage(zhadan.position_x, zhadan.position_y, &img_zhabei,NOTSRCERASE);//显示炸弹
	putimage(zhadan.position_x, zhadan.position_y, &img_zha,SRCINVERT);

	putimage(food1.position_x, food1.position_y, &img_f1bei,NOTSRCERASE);//显示1号鱼
	putimage(food1.position_x, food1.position_y, &img_f1,SRCINVERT);

	putimage(food2.position_x, food2.position_y, &img_f2bei,NOTSRCERASE);//显示2号鱼
	putimage(food2.position_x, food2.position_y, &img_f2,SRCINVERT);

	putimage(food3.position_x, food3.position_y, &img_f3bei,NOTSRCERASE);//显示3号鱼
	putimage(food3.position_x, food3.position_y, &img_f3,SRCINVERT);

	putimage(food4.position_x, food4.position_y, &img_f4bei,NOTSRCERASE);//显示4号鱼
	putimage(food4.position_x, food4.position_y, &img_f4,SRCINVERT);

	putimage(food5.position_x, food5.position_y, &img_f5bei,NOTSRCERASE);//显示5号鱼
	putimage(food5.position_x, food5.position_y, &img_f5,SRCINVERT);

	putimage(player.position_x, player.position_y, &img_p1bei,NOTSRCERASE);//显示玩家
	putimage(player.position_x, player.position_y, &img_p1,SRCINVERT);//将玩家放到最后显示为了使其吃小鱼时看起来更真实


	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	settextstyle(20,0, _T("黑体"));
	TCHAR a[] = _T("玩家一:score");
	outtextxy(length*0.15,high*0.02, a);
	TCHAR m[20];
	_stprintf(m, _T("%d"),score_p1);        // 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(length*0.15,high*0.02+30,m);

	FlushBatchDraw();
}



void updateWithoutInput()
{

	timer.position_x = timer.position_x + timer.v_x;//闹钟向右移动
	zhadan.position_x = zhadan.position_x - zhadan.v_x;//向左移动
	food1.position_x = food1.position_x + food1.v_x;//1号鱼向右移动
	food2.position_x = food2.position_x + food2.v_x;//2号鱼向右移动
	food3.position_x = food3.position_x + food3.v_x;//3号鱼向右移动
	food4.position_x = food4.position_x + food4.v_x;//4号鱼向右移动
	food5.position_x = food5.position_x + food5.v_x;//5号鱼向右移动

	if(timer.position_x>=length)
	{
		timer.position_x=-8000;
		timer.position_y=rand()%500;//闹钟重复出现
	}
	if(zhadan.position_x<=0)
	{
		zhadan.position_x=5000;
		zhadan.position_y=rand()%500;//重复出现
	}
	if(food1.position_x>=length)
	{
		food1.position_x=-400;
		food1.position_y=rand()%400;//1号鱼重复出现
	}
	if(food2.position_x>=length)
	{
		food2.position_x=-900;
		food2.position_y=rand()%400;//2号鱼重复出现
	}
	if(food3.position_x>=length)
	{
		food3.position_x=-1500;
		food3.position_y=rand()%400;//3号鱼重复出现
	}
	if(food4.position_x>=length)
	{
		food4.position_x=-1800;
		food4.position_y=rand()%400;//4号鱼重复出现
	}
	if(food5.position_x>=length)
	{
		food5.position_x=-2500;
		food5.position_y=rand()%400;//5号鱼重复出现
	}

	if( (timer.position_x+25>=player.position_x+20 && timer.position_x+25<=player.position_x+p1size ) && (timer.position_y+25>=player.position_y+20 && timer.position_y+25<=player.position_y+p1size))
	{
		timer.position_x=-5000;
		timer.position_y=rand()%500;//玩家吃掉闹钟
	}
	if( (zhadan.position_x+25>=player.position_x+20 && zhadan.position_x+25<=player.position_x+p1size ) && (zhadan.position_y+25>=player.position_y+20 && zhadan.position_y+25<=player.position_y+p1size))
	{
		zhadan.position_x=4000;
		zhadan.position_y=rand()%500;//玩家吃掉炸弹
	}

	if(food1.position_x+25.5>player.position_x && food1.position_x+25.5<player.position_x+p1size && food1.position_y+25.5>player.position_y && food1.position_y+25.5<player.position_y+p1size)
		//判断一号鱼是否被吃。判断条件为一号鱼的中心坐标在玩家一内部即被吃
	{
		p1size+=0.5;
		score_p1++;
		food1.position_x=-400;
		food1.position_y=rand()%(high-45);//小鱼被吃，重新随机生成
	}
	if(p1size>80)
	{
		if(food2.position_x+40>player.position_x && food2.position_x+40<player.position_x+p1size && food2.position_y+40>player.position_y && food2.position_y+40<player.position_y+p1size)
		{
			p1size+=1;
			score_p1+=2;
			food2.position_x=-900;
			food2.position_y=rand()%(high-80);
		}

	}
	else
	{
		if(player.position_x+p1size/2.0>food2.position_x && player.position_x+p1size/2.0<food2.position_x+80 && player.position_y+p1size/2.0>food2.position_y && player.position_y+p1size/2.0<food2.position_y+80 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//出现在随机位置
			player.position_y=rand()%(high-60);
		}
	}
	//玩家与比自身大的鱼相撞，大小回到初始状态；并随机在其他地方生成；

	if(p1size>110)
	{
		if(food3.position_x+55.5>player.position_x && food3.position_x+55.5<player.position_x+p1size && food3.position_y+55.5>player.position_y && food3.position_y+55.5<player.position_y+p1size)
		{
			p1size+=1.5;
			score_p1+=3;
			food3.position_x=-1500;
			food3.position_y=rand()%(high-110);
		}

	}
	else
	{
		if(player.position_x+p1size/2.0>food3.position_x && player.position_x+p1size/2.0<food3.position_x+110 && player.position_y+p1size/2.0>food3.position_y && player.position_y+p1size/2.0<food3.position_y+110 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//出现在随机位置
			player.position_y=rand()%(high-60);
		}
	}
	if(p1size>130)
	{
		if(food4.position_x+65>player.position_x && food4.position_x+65<player.position_x+p1size && food4.position_y+65>player.position_y && food4.position_y+65<player.position_y+p1size)
		{
			p1size+=2;
			score_p1+=4;
			food4.position_x=-1800;
			food4.position_y=rand()%(high-130);
		}

	}
	else
	{
		if(player.position_x+p1size/2.0>food4.position_x && player.position_x+p1size/2.0<food4.position_x+130 && player.position_y+p1size/2.0>food4.position_y && player.position_y+p1size/2.0<food4.position_y+130 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//出现在随机位置
			player.position_y=rand()%(high-60);
		}
	}
	if(p1size>200)
	{
		if(food5.position_x+100>player.position_x&&food5.position_x+100<player.position_x+p1size&&food5.position_y+80>player.position_y&&food5.position_y+80<player.position_y+p1size)
		{
			p1size+=2.5;
			score_p1+=5;
			food5.position_x =-2500;
			food5.position_y =rand()%(high-160);
		}
	}
	else
	{
		if(player.position_x+p1size/2.0>food5.position_x && player.position_x+p1size/2.0<food5.position_x+200 && player.position_y+p1size/2.0>food5.position_y && player.position_y+p1size/2.0<food5.position_y+160 )
		{
			p1size=start_p1size;
			player.position_x=rand()%(length-60);//出现在随机位置
			player.position_y=rand()%(high-60);
		}
	}
}


void updateWithInput()
{

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (player.position_x>0))
		player.position_x=player.position_x-player.v_x;  //左移
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (player.position_x<length-80))
		player.position_x=player.position_x+player.v_x;  //右移
	if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  player.position_y>0)
		player.position_y=player.position_y-player.v_y;  //上移
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  player.position_y<high-80)
		player.position_y=player.position_y+player.v_y;  //下移

}



void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}


void main()
{
	startup();
	while(1)
	{
		show();
		updateWithoutInput() ;
		updateWithInput(); 
	}
	gameover();
}
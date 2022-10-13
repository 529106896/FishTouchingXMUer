
//显示玩家 方向键控制移动

//问题1：存在玩家移动时会有停滞
//GetAsyncKeyState解决
//问题2：背景图与玩家的大小比例不对
//loadimage后添加
//问题3：玩家跑出边界
//玩家控制移动中设限制


#include<graphics.h>
#include<conio.h>


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

IMAGE img_p1;//玩家图片
IMAGE img_p1bei;
IMAGE img_bk;//背景图片
char input;


void startup()
{
	loadimage(&img_bk, _T("D:\\background.jpg"),1000,640,true);
	loadimage(&img_p1, _T("D:\\player.jpg"),80,80,true);
	loadimage(&img_p1bei, _T("D:\\playerbei.jpg"),80,80,true);//是否调整 IMAGE 的大小以适应图片

	player.position_x=length/2.0;//玩家横坐标
	player.position_y=high/2.0;//玩家纵坐标
	player.v_x=0.4;//玩家水平速度
	player.v_y=0.4;//玩家竖直速度

	initgraph(length,high);//画面大小
	BeginBatchDraw();
}


void show()
{
	putimage(0, 0, &img_bk);//显示背景
	putimage(player.position_x, player.position_y, &img_p1bei,NOTSRCERASE);//显示玩家
	putimage(player.position_x, player.position_y, &img_p1,SRCINVERT);

	FlushBatchDraw();
}


void updateWithoutInput()
{

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

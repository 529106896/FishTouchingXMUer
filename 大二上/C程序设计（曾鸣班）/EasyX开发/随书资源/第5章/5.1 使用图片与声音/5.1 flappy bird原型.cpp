#include <graphics.h>
#include <conio.h>

// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

IMAGE img_bk,img_bd1,img_bd2,img_bar_up1,img_bar_up2,img_bar_down1,img_bar_down2;int bird_x;
int bird_y;

void startup()
{
	initgraph(350, 600);
	loadimage(&img_bk, "D:\\background.jpg");	
	loadimage(&img_bd1, "D:\\bird1.jpg");
	loadimage(&img_bd2, "D:\\bird2.jpg");	
	loadimage(&img_bar_up1, "D:\\bar_up1.gif");
	loadimage(&img_bar_up2, "D:\\bar_up2.gif");
	loadimage(&img_bar_down1, "D:\\bar_down1.gif");
	loadimage(&img_bar_down2, "D:\\bar_down2.gif");
	bird_x = 50;
	bird_y = 200;
	BeginBatchDraw();
	
	mciSendString("open D:\\background.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
}

void show()
{
	putimage(0, 0, &img_bk);	// 显示背景	
	putimage(150, -300, &img_bar_up1,NOTSRCERASE); // 显示上一半的障碍物
	putimage(150, -300, &img_bar_up2,SRCINVERT);
	putimage(150, 400, &img_bar_down1,NOTSRCERASE); // 显示下一半的障碍物
	putimage(150, 400, &img_bar_down2,SRCINVERT);
	putimage(bird_x, bird_y, &img_bd1,NOTSRCERASE); // 显示小鸟	
	putimage(bird_x, bird_y, &img_bd2,SRCINVERT);
	FlushBatchDraw();
	Sleep(50);
}

void updateWithoutInput()
{
	if (bird_y<500)
		bird_y = bird_y+3;
}

void updateWithInput()
{
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  
		if (input == ' ' && bird_y>20)  
		{
			bird_y = bird_y - 60;
			mciSendString("close jpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open D:\\Jump.mp3 alias jpmusic", NULL, 0, NULL); // 打开跳动音乐
            mciSendString("play jpmusic", NULL, 0, NULL); // 仅播放一次
		}
	}
}

void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}

int main()
{
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	gameover();     // 游戏结束、后续处理
	return 0;
}

#include<graphics.h>
#include <conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment (lib,"Winmm.lib")
#define WIDTH 200//游戏区宽度
#define HEIGHT 400//高度
#define UNIT 20//每个游戏区单位的实际像素

//全局变量
int g_arrBackGround[20][10]={0};//背景分割
int g_arrSqare[2][4]={0};
int n;
int t;//输入密码次数


//函数声明
void startup();
void show();
void CreateRandonSqare();
void CopySqareToBack();
void SqareDown();
void updateWithInput();
void updateWithoutInput();


//清屏
void gotoxy(int x,int y)
{

	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;

	pos.X=x;

	pos.Y=y;

	SetConsoleCursorPosition(handle,pos);
}

//图形
void CreateRandonSqare()
{
	n=rand()%7;
	switch (n)
	{
	case 0://田
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			break;
		}
	case 1://--
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[0][2]=1;
			g_arrSqare[0][3]=1;
			break;
		}
	case 2:
		// |
		//___
		{
			g_arrSqare[0][1]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			break;
		}
	case 3:
		//L
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			break;
		}
	case 4://z
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			break;
		}
	case 5://反z
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][0]=1;
			break;
		}
	case 6://反L
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			break;
		}
	}

}

//在背景里显示
void CopySqareToBack()
{
	int i,j;
	for(i=0;i<2;i++)
	{
		for (j=0;j<4;j++)
		{
			g_arrBackGround[i][j+3]=g_arrSqare[i][j];
		}
	}

}
 
//图形下降
void SqareDown()
{
	int i,j;
	for(i=19;i>=0;i--)
	{
		for(j=0;j<10;j++)
		{
			if(g_arrBackGround[i][j]==1)
			{
				g_arrBackGround[i+1][j]=g_arrBackGround[i][j];
				g_arrBackGround[i][j]=0;
			}
		}
	}
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{	
				rectangle(j*UNIT,i*UNIT,j*UNIT+UNIT,i*UNIT+UNIT);
			}
		}
	}
	Sleep(200);
	gotoxy(0,0);
}

//密码
/*void beforegame()
{
	int password;//密码123
	while(t<3)
	{
		printf("请输入密码:");
		scanf(" %d",&password);
		if(password!=123)
		{
			printf("密码错误");
			t++;
		}	
		else
			break;
	}
	if(t==3)
	{
		printf("该用户已被锁住!!!");
		system("pause");
		exit(0);
	}
}
*/
//初始化
void startup()
{
	initgraph(640,480);
	IMAGE img_bk;//定义IMAGE对象
	loadimage(&img_bk,_T("E:\\background.jpg"));//读取图片到img对象中
	putimage(0,0,&img_bk);//在坐标（0,0）位置显示IMAGE对象

	rectangle(0,0,WIDTH,HEIGHT);
	rectangle(WIDTH+10,1,WIDTH+80,HEIGHT-320);
	settextstyle(14, 0, _T("宋体"));
	outtextxy(215, 330, _T("操作说明"));
	outtextxy(215, 350, _T("上：旋转"));
	outtextxy(215, 370, _T("左：左移"));
	outtextxy(215, 390, _T("右：右移"));
	outtextxy(215, 410, _T("下：下移"));
	outtextxy(215, 430, _T("空格：沉底"));
	outtextxy(215, 450, _T("ESC：退出"));
	//mciSendString("open 俄罗斯方块\background.mp3 alias bkmusic", NULL, 0, NULL);//背景音乐
	//mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
	CreateRandonSqare();
	CopySqareToBack();
}

//画面显示
void show()
{
	clearrectangle(1,1,WIDTH-1,HEIGHT-1);
	
}
void updateWithInput()
{

}
void updateWithoutInput()
{
	srand((unsigned)time(NULL));
	SqareDown();
	

}
int main()
{
	//beforegame();
	startup();
	while(1)
	{	
		show();
		updateWithInput();
		updateWithoutInput();
	}
	getch();
	closegraph();
	return 0;
}

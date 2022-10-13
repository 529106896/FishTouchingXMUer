#include<graphics.h>
#include <conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#pragma comment (lib,"Winmm.lib")
#define WIDTH 200//游戏区宽度
#define HEIGHT 400//高度
#define UNIT 20//每个游戏区单位的实际像素

//全局变量
int g_arrBackGround[20][10]={0};//背景分割
int g_arrSqare[2][4]={0};
int n;
int t;//输入密码次数
COLORREF c;//方块颜色
int g_nSqareID;
int g_nLine,g_nList;
int arrSqare[3][3]={0};
int a;


//函数声明
void gotoxy(int x,int y);//清屏
void startup();//初始化
void show();//显示函数，清全屏
void UpdateWithoutInput();//与用户无关的输入
void UpdateWithInput();//与用户有关的输入
void CreateRandonSqare();//随机显示图形
void CopySqareToBack();//把图形写入背景数组
void SqareDown();//下降
void SqareLeft();//左移
void SqareRight();//右移
void OnChangeSqare();//变形
void ChangeSqare();//除长条和正方形外的变形
void ChangeLineSqare();//长条变形
int CanSqareChangeShape();//解决变形bug
int CanLineSqareChange();//解决长条变形bug

int CanSqareDown();//若返回0继续下降，返回1则代表到底，不下降
int CanSqareDown2();//若返回0继续下降，返回1则代表到底，不下降,与方块相遇
int CanSqareLeft();//若返回0继续左移，返回1则代表到最左边，不再左移
int CanSqareLeft2();//若返回0继续左移，返回1则代表到最左边，不再左移，与方块相遇
int CanSqareRight();//若返回0继续右移，返回1则代表到最右边，不再右移
int CanSqareRight2();//若返回0继续右移，返回1则代表到最右边，不再右移，与方块相遇
void PaintSqare();//画方块
void Change1TO2();//到底之后数组由1变2
void ShowSqare2();//2的时候也画方块到背景



int CanSqareChangeShape()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(g_arrBackGround[g_nLine+i][g_nList+j]==2)
			{
				return 0;
			}
		}
	}
	if(g_nList<0)
	{
		g_nList=0;
	}
	else if(g_nList+2>9)
	{
		g_nList=7;
	}
	return 1;
}
int CanLineSqareChange()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		if(g_arrBackGround[g_nLine][g_nList+i]==2||g_nList+i>9)//右边界
		{
			break;
			
		}

	}
	for(j=1;j<4;j++)
	{
		if(g_arrBackGround[g_nLine][g_nList-j]==2||g_nList-j<0)//左边界
		{
			break;
		}
	}
	if(i-1+j-1<3)
	{
		return 0;
	}
	return 1;
}

void ChangeLineSqare()
{
	if (g_arrBackGround[g_nLine][g_nList-1]==1)//横着
	{
		//清零
		g_arrBackGround[g_nLine][g_nList-1]=0;
		g_arrBackGround[g_nLine][g_nList+1]=0;
		g_arrBackGround[g_nLine][g_nList+2]=0;

		if(g_arrBackGround[g_nLine+1][g_nList]==2)
		{
			//赋值
			g_arrBackGround[g_nLine-1][g_nList]=1;
			g_arrBackGround[g_nLine-2][g_nList]=1;
			g_arrBackGround[g_nLine-3][g_nList]=1;
		}
		else if(g_arrBackGround[g_nLine+2][g_nList]==2)
		{
			//赋值
			g_arrBackGround[g_nLine-1][g_nList]=1;
			g_arrBackGround[g_nLine-2][g_nList]=1;
			g_arrBackGround[g_nLine+1][g_nList]=1;
		}
		else
		{
			//元素赋值
			g_arrBackGround[g_nLine-1][g_nList]=1;
			g_arrBackGround[g_nLine+1][g_nList]=1;
			g_arrBackGround[g_nLine+2][g_nList]=1;
		}
		

	}
	else
	{
		//清零
		g_arrBackGround[g_nLine-1][g_nList]=0;
		g_arrBackGround[g_nLine+1][g_nList]=0;
		g_arrBackGround[g_nLine+2][g_nList]=0;
		if(g_arrBackGround[g_nLine][g_nList+1]==2||g_nList==9)
		{
			//元素赋值
			g_arrBackGround[g_nLine][g_nList-1]=1;
			g_arrBackGround[g_nLine][g_nList-2]=1;
			g_arrBackGround[g_nLine][g_nList-3]=1;
			//标记改变
			g_nList-=2;

		}
		else if(g_arrBackGround[g_nLine][g_nList+2]==2||g_nList==8)
		{
			//元素赋值
			g_arrBackGround[g_nLine][g_nList-1]=1;
			g_arrBackGround[g_nLine][g_nList+1]=1;
			g_arrBackGround[g_nLine][g_nList-2]=1;
			//标记改变
			g_nList-=1;

		}
		else if(g_arrBackGround[g_nLine][g_nList-1]==2||g_nList==0)
		{
			//元素赋值
			g_arrBackGround[g_nLine][g_nList+3]=1;
			g_arrBackGround[g_nLine][g_nList+1]=1;
			g_arrBackGround[g_nLine][g_nList+2]=1;
			//标记改变
			g_nList+=1;
		}
		else 
		{
			g_arrBackGround[g_nLine][g_nList-1]=1;
			g_arrBackGround[g_nLine][g_nList+1]=1;
			g_arrBackGround[g_nLine][g_nList+2]=1;
			

		}
	}
}
void ChangeSqare()
{
	int i,j;
	int ntemp=2;
	//把背景复制出来
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			arrSqare[i][j]=g_arrBackGround[g_nLine+i][g_nList+j];
		}
	}
	//变形后复制回去
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			g_arrBackGround[g_nLine+i][g_nList+j]=arrSqare[ntemp][i];
			ntemp--;
		}
		ntemp=2;
	}

}
void OnChangeSqare()
{
	switch(g_nSqareID)
	{
	case 0://正方形
		return ;
	case 1://长条
		if (CanLineSqareChange()==1)
		{
			ChangeLineSqare();
			
		}
		else
		{
			return;
		}
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		//普通变形
		if(CanSqareChangeShape()==1)
		{
			ChangeSqare();
		}
		else
		{
			return ;
		}
		
		break;
	
	}
}
void UpdateWithInput()
{
	char input;
	while(kbhit())//判断是否有输入
	{
		input = getch();//根据用户的不同输入来移动
		if(input==75)//左移
		{
			if(CanSqareLeft()==1&&CanSqareLeft2()==1)
			{
				SqareLeft();
				g_nList--;
			}
		}
		if (input==77)//右移
		{
			if(CanSqareRight()==1&&CanSqareRight2()==1)
			{
				SqareRight();
				g_nList++;
			}
			
		}
		if(input==80)//下移
		{
			if(CanSqareDown()==1&&CanSqareDown2()==1)
			{
				SqareDown();
				g_nLine++;
			}
		}
		if(input==72)//变形
		{
			OnChangeSqare();
			
		}
	}

}

int CanSqareDown()
{
	int j;
	for (j=0;j<10;j++)
	{
		if(g_arrBackGround[19][j]==1)
		{
			a=19;
			return 0;
		}
	}
	return 1;
}

int CanSqareDown2()
{
	int i,j;
	for(i=19;i>=0;i--)
	{
		for (j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{
				if (g_arrBackGround[i+1][j]==2)
				{
					a=i+1;
					return 0;
				}
			}
		}
	}
	return 1;

}

int CanSqareLeft()
{
	int i;
	for(i=0;i<20;i++)
	{
		if(g_arrBackGround[i][0]==1)
			return 0;
	}
	return 1;
}

int CanSqareLeft2()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{
				if(g_arrBackGround[i][j-1]==2)
					return 0;
			}
		}
	}
	return 1;
}
int CanSqareRight()
{
	int i;
	for(i=0;i<20;i++)
	{
		if(g_arrBackGround[i][19]==1)
			return 0;
	}
	return 1;
}

int CanSqareRight2()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=9;j>=0;j--)
		{
			if (g_arrBackGround[i][j]==1)
			{
				if(g_arrBackGround[i][j+1]==2)
					return 0;	
			}
		}
	}
	return 1;
}
void UpdateWithoutInput()
{
	if (CanSqareDown()==1&&CanSqareDown2()==1)
	{
		SqareDown();
		g_nLine++;
		PaintSqare();
	}

	else 
	{
		Change1TO2();
		CreateRandonSqare();
		CopySqareToBack();
		PaintSqare();
	}
	ShowSqare2();
	
}

void ShowSqare2()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			if(g_arrBackGround[i][j]==2)
			{
				setfillcolor(DARKGRAY);
				setlinecolor(WHITE);
				fillrectangle(j*UNIT,i*UNIT,j*UNIT+UNIT,i*UNIT+UNIT);
			}
				
		}
	}
	Sleep(200);


}
void PaintSqare()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{	
				setfillcolor(c);
				setlinecolor(WHITE);
				fillrectangle(j*UNIT,i*UNIT,j*UNIT+UNIT,i*UNIT+UNIT);
			}
		}
	}
	Sleep(200);
	//gotoxy(0,0);
}

void Change1TO2()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			if(g_arrBackGround[i][j]==1)
				g_arrBackGround[i][j]=2;
		}
	}
}


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
	memset(g_arrSqare,0,sizeof(g_arrSqare));
	n=rand()%7;
	switch (n)
	{
	case 0://田
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			c=LIGHTRED;
			g_nLine=0;
			g_nList=4;
			break;
		}
	case 1://--
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[0][2]=1;
			g_arrSqare[0][3]=1;
			c=YELLOW;
			g_nLine=0;
			g_nList=4;
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
			c=LIGHTBLUE;
			g_nLine=0;
			g_nList=3;
			
			break;
		}
	case 3:
		//L
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			c=LIGHTGREEN;
			g_nLine=0;
			g_nList=3;
			
			break;
		}
	case 4://z
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			c=LIGHTCYAN;
			g_nLine=0;
			g_nList=3;
		
			break;
		}
	case 5://反z
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][0]=1;	
			c=LIGHTMAGENTA;
			g_nLine=0;
			g_nList=3;
			break;
		}
	case 6://反L
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			c=GREEN;
			g_nLine=0;
			g_nList=3;
			break;
		}
	}
	g_nSqareID=n;

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
	

}
void SqareLeft()
{
	int i,j;
	for(i=19;i>=0;i--)
	{
		for(j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{
				g_arrBackGround[i][j-1]=g_arrBackGround[i][j];
				g_arrBackGround[i][j]=0;
			}
		}
	}
}
void SqareRight()
{
	int i,j;
	for(i=19;i>=0;i--)
	{
		for(j=9;j>=0;j--)
		{
			if (g_arrBackGround[i][j]==1)
			{
				g_arrBackGround[i][j+1]=g_arrBackGround[i][j];
				g_arrBackGround[i][j]=0;
			}
		}
	}
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
	srand((unsigned)time(NULL));
	initgraph(640,480);
	IMAGE img_bk;//定义IMAGE对象
	loadimage(&img_bk,_T("E:\\background.jpg"));//读取图片到img对象中
	putimage(0,0,&img_bk);//在坐标（0,0）位置显示IMAGE对象

	rectangle(-1,0,WIDTH+1,HEIGHT+1);
	rectangle(WIDTH+10,1,WIDTH+150,HEIGHT-280);
	{
		settextstyle(14, 0, _T("宋体"));
		outtextxy(WIDTH+60, 5, _T("预览"));
	}
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
}

//画面显示
void show()
{
	int i,j;
	for (i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{
				clearrectangle(j*UNIT,i*UNIT,j*UNIT+UNIT,i*UNIT+UNIT);
			}
		}
	}
	
}	
	
int main()
{
	//beforegame();
	startup();

	CreateRandonSqare();
	CopySqareToBack();
	
	while(1)
	{	
		
		show();
		UpdateWithInput();
		UpdateWithoutInput();
		
	}
	getch();
	closegraph();
	return 0;
}

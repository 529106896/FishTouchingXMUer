#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define high 30
#define wide 40

//1为人，2为板，3为边界，4为上边界的锯齿//
void starup();
void show();
void updateWithoutinput();
void updateWithinput();
void gotoxy(int a, int b);               //清屏//

int frame[high][wide];
int i,j;
int radius;
int interval_static;
int interval_1,interval_2;                           //首先是可以用于调控新板生成的频率，其次可以让小球下落与整个画面的上升产生频率的落差感，造成重力的假象// 
int board_1,board_2,board_3;
int ball;
int judge=0;                                         //用于跳出两层循环的变量// 
char ch;

int main()
{
    starup();
	while(1)
	{
		gotoxy(0,0);
    	show();
    	updateWithoutinput();
    	updateWithinput();
	}
}

void starup()
{
	srand(time(NULL));
	radius=2;
	interval_static=20;
	interval_1=0;
	interval_2=0;
	ball=wide/2;
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
			if (j==wide-1)
			{
				frame[i][j]=3;
			}
			if (j==0)
			{
				frame[i][j]=3;
			}
			if (i==0&&j!=0&&j!=wide-1)
			{
				frame[i][j]=4;
			}
			if (i==high-1&&j>(wide/2-3)&&j<(wide/2+3))
			{
                frame[i][j]=2;
			}
			if (i==high-2&&j==ball)
			{
				frame[i][j]=1;
			}
		}
	}
}

void show()
{
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
			if (frame[i][j]==2)
			{
				printf ("_");
			}
			else if (frame[i][j]==3)
			{
				printf ("|");
			}
			else if (frame[i][j]==4)
			{
				printf ("T");
			}
			else if (frame[i][j]==0)
			{
				printf (" ");
			}
			else if (frame[i][j]==1)
			{
                printf ("O");
			}
		}
		printf ("\n");
	}
}


void updateWithoutinput()
{
	judge=0;
	srand(time(NULL));
   	if (interval_2==interval_static)           //只要板球上升，和出现新板，小球下落的刷新频率不同，就能实现重力的落差感// 
	{
	interval_2=0;                            //计时清零// 
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
            if (frame[i][j]==1&&frame[i+1][j]==2)
			{
				frame[i][j]=0;
				frame[i-1][j]=1;
			}
			else if (frame[i][j]==2&&i>1)
			{
				frame[i-1][j]=2;
				frame[i][j]=0;
			}
			else if (frame[i][j]==2&&i==1)
			{
                frame[i][j]=0;
			}
		}
	}
    }
    else
    {
    	interval_2=interval_2+4;
	}
    
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
		   if (frame[i][j]==1&&frame[i+1][j]==0)
			{
				frame[i][j]=0;
				frame[i+1][j]=1;
				judge=1;
			}
		}
		if (judge)
		{
			break;
		}
	} 
	if (interval_1==interval_static)          //频率制造器// 
	{
	  interval_1=0;                                      //计时清零// 
      board_1=rand()%13+1;
	  board_2=rand()%13+13;
	  board_3=rand()%13+24;
	  for (i=0;i<high;i++)
	  {
		  for (j=0;j<wide;j++)
		  {
			  if (i==high-1&&((j>=board_1-radius)&&(j<=board_1+radius)&&j>0||(j>=board_2-radius)&&(j<=board_2+radius)||(j>=board_3-radius)&&(j<=board_3+radius)))
			  { 
				  frame[i][j]=2;
			  }
		  }
	  }
	}
	else
	{
		interval_1=interval_1+1;
	}
}

		

void updateWithinput()
{
	if (kbhit())
	{
		ch=getch();
		if (ch=='A')
		{
	    	for (i=0;i<high;i++)
	          {
		        for (j=0;j<wide;j++)
		         {
		         	if (frame[i][j]==1)
		         	{
		         	  frame[i][j]=0;
					  frame[i][j-1]=1;	
					  break;
					}
				 }
			  }
		}
	    if (ch=='D')
		{
	    	for (i=0;i<high;i++)
	          {
		        for (j=0;j<wide;j++)
		         {
		         	if (frame[i][j]==1)
		         	{
		         	  frame[i][j]=0;
					  frame[i][j+1]=1;
					  break;	         //加入break的原因是不加入的话，循环会一直将1往后推导致这一排全为0了// 
					}
				 }
			  }
		}
	}
}

void gotoxy(int a, int b)
{
        int xx=0x0b;
        HANDLE hOutput;
        COORD loc;
        loc.X =a;
        loc.Y=b;
        hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOutput, loc);
        return;
}

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
int interval;
int board_1,board_2,board_3;
int ball;                                //加入小球// 

int main()
{
    starup();
	while(1)
	{
		gotoxy(0,0);
    	show();
    	updateWithoutinput();
	}
}

void starup()
{
	srand(time(NULL));
	radius=2;
	interval_static=10;
	interval=2;
	ball=wide/2;                        //小球坐标// 
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
			if (i==high-2&&j==ball)              //小球坐标赋值// 
			{
				frame[i][j]=1;
			}
		}
	}
}

void show()
{
	Sleep(100);
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
	srand(time(NULL));
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
            if (frame[i][j]==1&&frame[i+1][j]==2)         //加入小球以后，需要让小球和板一起上升// 
			{
				frame[i][j]=0;
				frame[i-1][j]=1;
			}
			else if (frame[i][j]==1&&frame[i+1][j]==0)
			{
				frame[i][j]=0;
				frame[i+1][j]=1;
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
	if (interval==interval_static)
	{
	  interval=0;
      board_1=rand()%13;
	  board_2=rand()%13+13;
	  board_3=rand()%13+24;
	  for (i=0;i<high;i++)
	  {
		  for (j=0;j<wide;j++)
		  {
			  if (i==high-1&&((j>=board_1-radius)&&(j<=board_1+radius)||(j>=board_2-radius)&&(j<=board_2+radius)||(j>=board_3-radius)&&(j<=board_3+radius)))
			  { 
				  frame[i][j]=2;
			  }
		  }
	  }
	}
	else
	{
		interval=interval+2;
	}
}

		

void updateWithinput()
{
	;
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

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
int radius;                             //木板的半径// 


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
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
			if (j==wide-1)                      //左右和上边框的赋值// 
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
			if (i==high-1&&j>(wide/2-3)&&j<(wide/2+3))     //底边时第一块板的初位置// 
			{
                frame[i][j]=2;
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
			if (frame[i][j]==2)                     //打印各处// 
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
		}
		printf ("\n");
	}
}


void updateWithoutinput()
{
	for (i=0;i<high;i++)
	{
		for (j=0;j<wide;j++)
		{
			if (frame[i][j]==2&&i>1)
			{
				frame[i-1][j]=2;
				frame[i][j]=0;
			}
			if (frame[i][j]==2&&i==1)
			{
                frame[i][j]=0;
			}
		}
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

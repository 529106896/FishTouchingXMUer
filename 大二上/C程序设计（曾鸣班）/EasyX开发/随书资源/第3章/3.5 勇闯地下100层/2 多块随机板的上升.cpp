#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define high 30
#define wide 40

//1Ϊ�ˣ�2Ϊ�壬3Ϊ�߽磬4Ϊ�ϱ߽�ľ��//
void starup();
void show();
void updateWithoutinput();
void updateWithinput();
void gotoxy(int a, int b);               //����//

int frame[high][wide];
int i,j;
int radius;


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
		}
		printf ("\n");
	}
}


void updateWithoutinput()
{
    srand(time(NULL));
	for (i=0;i<high;i++)        //�ӵײ����������İ壬�Զ����϶���ʵ�ַ���// 
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
	if (interval==interval_static)                     //ÿ��һ��ʱ������Ǿ�ˢ��һ�µ��£������ٳ��ּ���壬����������غϲ��֣���ɲ�ͬ��Ч���������������������// 
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
	��
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

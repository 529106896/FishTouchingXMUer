#include<stdio.h>
#include<stdlib.h>
#include <ctime>
#include <windows.h>
void move(char x,char y,int n, int **p);
void hanoi(int n,char one,char two,char three, int **p);
void changeshuzu(char x,char y,int n, int **p);
void changehigh(char x,char y); // 改变塔高
void print(int  **p); // 输出起始塔
void printstar(int **p); // 输出*
void gotoxy(int x,int y) ;  // 光标移动到(x,y)位置

static int higha,highb,highc,r,c; 
int main()
{
	int i;
	int **p;
	printf("input a number:");
	scanf("%d",&r);
	c=r*10;
    p = new int* [r]; // 动态分配二维数组
    p[0] = new int[r * c]; 
    for(i = 1; i < r; i++) // 动态分配二维数组
        p[i] = p[i-1] + c;
	higha=r;
	highb=0;
	highc=0;
	
	printf("the step to move %d diskes:\n\n",r);
	printstar(p);
	gotoxy(0,1);
	getchar();
	hanoi(r,'A','B','C',p);
	return 0;
}

void hanoi(int n,char one,char two,char three,int **p)
{	
	if(n==1)
		move(one,three,n,p);
	else
	{
		hanoi(n-1,one,three,two,p);
		move(one,three,n,p);
		hanoi(n-1,two,one,three,p);
	}
}

void move(char x,char y,int n,int **p) // move x:被移柱子 y：得到盘的柱子 n：盘的大小
{	
	getchar();
	printf("  %c->%c\n",x,y);	
	changeshuzu(x,y,n,p); // 改变数组
	print(p);	
	changehigh(x,y); // 变高
	gotoxy(0,1);
}

void print(int **p)
{	
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(p[i][j]==1)
				printf("*");
			else printf(" ");
		}
		printf("\n");
	}
}
void changehigh(char x,char y)
{
	switch(x)
	{
	case 'A':higha--;break;
	case 'B':highb--;break;
	case 'C':highc--;break;
	}
	switch(y)
	{
	case 'A':higha++;break;
	case 'B':highb++;break;
	case 'C':highc++;break;
	}
}

void changeshuzu(char x,char y,int n,int **p)
{	
	int i,j;

	// 移去 m-high为要去掉的行数
	if(x=='A')
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(i==r-higha&&j>=r-n&&j<=r+n-2)
					p[i][j]=0;
			}
	}
	else if(x=='B')
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(i==r-highb&&j>=3*r-n&&j<=3*r+n-2)
					p[i][j]=0;
			}
	}
	else if(x=='C')
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(i==r-highc&&j>=5*r-n&&j<=5*r+n-2)
					p[i][j]=0;
			}
	}
	
	// 添加 m-high-1为要去掉的行数
	if(y=='A')
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(i==r-higha-1&&j>=r-n&&j<=r+n-2)
					p[i][j]=1;
			}
	}
	else if(y=='B')
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(i==r-highb-1&&j>=3*r-n&&j<=3*r+n-2)
					p[i][j]=1;
			}
	}
	else if(y=='C')
	{
		for(i=0;i<r;i++)
			for(j=0;j<c;j++)
			{
				if(i==r-highc-1&&j>=5*r-n&&j<=5*r+n-2)
					p[i][j]=1;
			}
	}
}

void printstar(int **p)
{	
	int i,j;
	for(i=0;i<r;i++)
	{	for(j=0;j<c;j++)
	{
		if(j>=r-i-1&&j<=r+i-1)
			p[i][j]=1;
	}
	}
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(p[i][j]==1)
				printf("*");
			else printf(" ");
		}
		printf("\n");
	}	
}

void gotoxy(int x,int y)    // 光标移动到(x,y)位置
{
    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;                            
    HANDLE    hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);   
}

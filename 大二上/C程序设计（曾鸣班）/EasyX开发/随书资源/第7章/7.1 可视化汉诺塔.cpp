#include<stdio.h>
#include<stdlib.h>
#include <ctime>
#include <windows.h>
void move(char x,char y,int n, int **p);
void hanoi(int n,char one,char two,char three, int **p);
void changeshuzu(char x,char y,int n, int **p);
void changehigh(char x,char y); // �ı�����
void print(int  **p); // �����ʼ��
void printstar(int **p); // ���*
void gotoxy(int x,int y) ;  // ����ƶ���(x,y)λ��

static int higha,highb,highc,r,c; 
int main()
{
	int i;
	int **p;
	printf("input a number:");
	scanf("%d",&r);
	c=r*10;
    p = new int* [r]; // ��̬�����ά����
    p[0] = new int[r * c]; 
    for(i = 1; i < r; i++) // ��̬�����ά����
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

void move(char x,char y,int n,int **p) // move x:�������� y���õ��̵����� n���̵Ĵ�С
{	
	getchar();
	printf("  %c->%c\n",x,y);	
	changeshuzu(x,y,n,p); // �ı�����
	print(p);	
	changehigh(x,y); // ���
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

	// ��ȥ m-highΪҪȥ��������
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
	
	// ��� m-high-1ΪҪȥ��������
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

void gotoxy(int x,int y)    // ����ƶ���(x,y)λ��
{
    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;                            
    HANDLE    hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);   
}

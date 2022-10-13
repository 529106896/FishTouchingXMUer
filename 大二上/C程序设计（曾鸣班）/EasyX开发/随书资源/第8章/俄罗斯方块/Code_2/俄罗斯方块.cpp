#include<graphics.h>
#include <conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#pragma comment (lib,"Winmm.lib")
#define WIDTH 200//��Ϸ�����
#define HEIGHT 400//�߶�
#define UNIT 20//ÿ����Ϸ����λ��ʵ������

//ȫ�ֱ���
int g_arrBackGround[20][10]={0};//�����ָ�
int g_arrSqare[2][4]={0};
int n;
int t;//�����������
COLORREF c;//������ɫ

//��������
void startup();//��ʼ��
void show();//��ʾ��������ȫ��
void CreateRandonSqare();//�����ʾͼ��
void CopySqareToBack();//��ͼ��д�뱳������
void SqareDown();//�½�
void SqareLeft();//����
void SqareRight();//����
void SqareDown2();//�½�
int CanSqareDown();//������0�����½�������1������ף����½�
int CanSqareDown2();//������0�����½�������1������ף����½�,�뷽������
int CanSqareLeft();//������0�������ƣ�����1���������ߣ���������
int CanSqareLeft2();//������0�������ƣ�����1���������ߣ��������ƣ��뷽������
int CanSqareRight();//������0�������ƣ�����1��������ұߣ���������
int CanSqareRight2();//������0�������ƣ�����1��������ұߣ��������ƣ��뷽������
void PaintSqare();//������
void Change1TO2();//����֮��������1��2
void gotoxy(int x,int y);//����
void UpWithoutInput();//���û��޹ص�����
void ShowSqare2();//2��ʱ��Ҳ�����鵽����
void UpWithInput();//���û��йص�����



void UpWithInput()
{
	char input;
	while(kbhit())//�ж��Ƿ�������
	{
		input = getch();//�����û��Ĳ�ͬ�������ƶ�
		if(input==75)//����
		{
			if(CanSqareLeft()==1&&CanSqareLeft2()==1)
			{
				SqareLeft();
			}
		}
		if (input==77)//����
		{
			if(CanSqareRight()==1&&CanSqareRight2()==1)
			{
				SqareRight();
			}
			
		}
		if(input==80)//����
		{
			SqareDown2();
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
void UpWithoutInput()
{
	if (CanSqareDown()==1&&CanSqareDown2()==1)
	{
		SqareDown();
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

//ͼ��
void CreateRandonSqare()
{
	memset(g_arrSqare,0,sizeof(g_arrSqare));
	n=rand()%7;
	switch (n)
	{
	case 0://��
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			c=LIGHTRED;
			break;
		}
	case 1://--
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[0][2]=1;
			g_arrSqare[0][3]=1;
			c=YELLOW;
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
			
			break;
		}
	case 4://z
		{
			g_arrSqare[0][0]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			c=LIGHTCYAN;
		
			break;
		}
	case 5://��z
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][0]=1;	
			c=LIGHTMAGENTA;
			break;
		}
	case 6://��L
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
			c=GREEN;
			break;
		}
	}

}

//�ڱ�������ʾ
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

 
//ͼ���½�
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
void SqareDown2()
{
	int i,j;
	for(i=19;i>=0;i--)
	{
		for(j=0;j<10;j++)
		{
			if (g_arrBackGround[i][j]==1)
			{
				g_arrBackGround[i+1][j]=g_arrBackGround[i][j];
				g_arrBackGround[i][j]=0;
			}
		}
	}
}

//����
/*void beforegame()
{
	int password;//����123
	while(t<3)
	{
		printf("����������:");
		scanf(" %d",&password);
		if(password!=123)
		{
			printf("�������");
			t++;
		}	
		else
			break;
	}
	if(t==3)
	{
		printf("���û��ѱ���ס!!!");
		system("pause");
		exit(0);
	}
}
*/
//��ʼ��
void startup()
{
	srand((unsigned)time(NULL));
	initgraph(640,480);
	IMAGE img_bk;//����IMAGE����
	loadimage(&img_bk,_T("E:\\background.jpg"));//��ȡͼƬ��img������
	putimage(0,0,&img_bk);//�����꣨0,0��λ����ʾIMAGE����

	rectangle(-1,0,WIDTH+1,HEIGHT+1);
	rectangle(WIDTH+10,1,WIDTH+150,HEIGHT-280);
	{
		settextstyle(14, 0, _T("����"));
		outtextxy(WIDTH+60, 5, _T("Ԥ��"));
	}
	settextstyle(14, 0, _T("����"));
	outtextxy(215, 330, _T("����˵��"));
	outtextxy(215, 350, _T("�ϣ���ת"));
	outtextxy(215, 370, _T("������"));
	outtextxy(215, 390, _T("�ң�����"));
	outtextxy(215, 410, _T("�£�����"));
	outtextxy(215, 430, _T("�ո񣺳���"));
	outtextxy(215, 450, _T("ESC���˳�"));
	//mciSendString("open ����˹����\background.mp3 alias bkmusic", NULL, 0, NULL);//��������
	//mciSendString("play bkmusic repeat", NULL, 0, NULL);  // ѭ������
}

//������ʾ
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
		UpWithInput();
		UpWithoutInput();
		
	}
	getch();
	closegraph();
	return 0;
}

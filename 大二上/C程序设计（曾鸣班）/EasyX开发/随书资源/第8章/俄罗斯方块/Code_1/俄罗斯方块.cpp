#include<graphics.h>
#include <conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment (lib,"Winmm.lib")
#define WIDTH 200//��Ϸ�����
#define HEIGHT 400//�߶�
#define UNIT 20//ÿ����Ϸ����λ��ʵ������

//ȫ�ֱ���
int g_arrBackGround[20][10]={0};//�����ָ�
int g_arrSqare[2][4]={0};
int n;
int t;//�����������


//��������
void startup();
void show();
void CreateRandonSqare();
void CopySqareToBack();
void SqareDown();
void updateWithInput();
void updateWithoutInput();


//����
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
	n=rand()%7;
	switch (n)
	{
	case 0://��
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
	case 5://��z
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[0][1]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][0]=1;
			break;
		}
	case 6://��L
		{
			g_arrSqare[0][2]=1;
			g_arrSqare[1][0]=1;
			g_arrSqare[1][1]=1;
			g_arrSqare[1][2]=1;
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
	initgraph(640,480);
	IMAGE img_bk;//����IMAGE����
	loadimage(&img_bk,_T("E:\\background.jpg"));//��ȡͼƬ��img������
	putimage(0,0,&img_bk);//�����꣨0,0��λ����ʾIMAGE����

	rectangle(0,0,WIDTH,HEIGHT);
	rectangle(WIDTH+10,1,WIDTH+80,HEIGHT-320);
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
	CreateRandonSqare();
	CopySqareToBack();
}

//������ʾ
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

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
int g_nSqareID;
MOUSEMSG msg;
COLORREF c;//������ɫ
int g_nLine,g_nList;
int a;
int Score=0;
char strScore[10];
IMAGE img_bk1;//����IMAGE����
IMAGE img_bk2;


//��������
void gotoxy(int x,int y);//����
void startup();//��ʼ��
void show();//��ʾ��������ȫ��
void UpdateWithoutInput();//���û��޹ص�����
void UpdateWithInput();//���û��йص�����
void CreateRandonSqare();//�����ʾͼ��
void CopySqareToBack();//��ͼ��д�뱳������
void SqareDown();//�½�
void SqareLeft();//����
void SqareRight();//����
void OnChangeSqare();//����
void ChangeSqare();//����������������ı���
void ChangeLineSqare();//��������
int CanSqareChangeShape();//�������bug
int CanLineSqareChange();//�����������bug
int gameover();//�ж���Ϸ�Ƿ�ʧ��
int CanSqareDown();//������0�����½�������1������ף����½�
int CanSqareDown2();//������0�����½�������1������ף����½�,�뷽������
int CanSqareLeft();//������0�������ƣ�����1���������ߣ���������
int CanSqareLeft2();//������0�������ƣ�����1���������ߣ��������ƣ��뷽������
int CanSqareRight();//������0�������ƣ�����1��������ұߣ���������
int CanSqareRight2();//������0�������ƣ�����1��������ұߣ��������ƣ��뷽������
void PaintSqare();//������
void Change1TO2();//����֮��������1��2
void ShowSqare2();//2��ʱ��Ҳ�����鵽����
void DestroyOneLineSqare();//����



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
		if(g_arrBackGround[g_nLine][g_nList+i]==2||g_nList+i>9)//��
		{
			break;
			
		}

	}
	for(j=1;j<4;j++)
	{
		if(g_arrBackGround[g_nLine][g_nList-j]==2||g_nList-j<0)//��
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
	if (g_arrBackGround[g_nLine][g_nList-1]==1)//����
	{
		//����
		g_arrBackGround[g_nLine][g_nList-1]=0;
		g_arrBackGround[g_nLine][g_nList+1]=0;
		g_arrBackGround[g_nLine][g_nList+2]=0;

		if(g_arrBackGround[g_nLine+1][g_nList]==2)
		{
			//��ֵ
			g_arrBackGround[g_nLine-1][g_nList]=1;
			g_arrBackGround[g_nLine-2][g_nList]=1;
			g_arrBackGround[g_nLine-3][g_nList]=1;
		}
		else if(g_arrBackGround[g_nLine+2][g_nList]==2)
		{
			//��ֵ
			g_arrBackGround[g_nLine-1][g_nList]=1;
			g_arrBackGround[g_nLine-2][g_nList]=1;
			g_arrBackGround[g_nLine+1][g_nList]=1;
		}
		else if(g_nLine==0)
		{
			g_arrBackGround[g_nLine+1][g_nList]=1;
			g_arrBackGround[g_nLine+2][g_nList]=1;
			g_arrBackGround[g_nLine+3][g_nList]=1;
		}
		else
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine-1][g_nList]=1;
			g_arrBackGround[g_nLine+1][g_nList]=1;
			g_arrBackGround[g_nLine+2][g_nList]=1;
		}
		

	}
	else
	{
		//����
		g_arrBackGround[g_nLine-1][g_nList]=0;
		g_arrBackGround[g_nLine+1][g_nList]=0;
		g_arrBackGround[g_nLine+2][g_nList]=0;
		if(g_arrBackGround[g_nLine][g_nList+1]==2||g_nList==9)
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine][g_nList-1]=1;
			g_arrBackGround[g_nLine][g_nList-2]=1;
			g_arrBackGround[g_nLine][g_nList-3]=1;
			//��Ǹı�
			g_nList-=2;

		}
		else if(g_arrBackGround[g_nLine][g_nList+2]==2||g_nList==8)
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine][g_nList-1]=1;
			g_arrBackGround[g_nLine][g_nList+1]=1;
			g_arrBackGround[g_nLine][g_nList-2]=1;
			//��Ǹı�
			g_nList-=1;

		}
		else if(g_arrBackGround[g_nLine][g_nList-1]==2||g_nList==0)
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine][g_nList+3]=1;
			g_arrBackGround[g_nLine][g_nList+1]=1;
			g_arrBackGround[g_nLine][g_nList+2]=1;
			//��Ǹı�
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
	int arrSqare[3][3]={0};
	int i,j;
	int ntemp=2;
	//�ѱ������Ƴ���
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			arrSqare[i][j]=g_arrBackGround[g_nLine+i][g_nList+j];
		}
	}
	//���κ��ƻ�ȥ
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
	case 0://������
		return ;
	case 1://����
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
		//��ͨ����
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
	while(kbhit())//�ж��Ƿ�������
	{
		input = getch();//�����û��Ĳ�ͬ�������ƶ�
		if(input==75)//����
		{
			if(CanSqareLeft()==1&&CanSqareLeft2()==1)
			{
				SqareLeft();
				g_nList--;
			}
		}
		if (input==77)//����
		{
			if(CanSqareRight()==1&&CanSqareRight2()==1)
			{
				SqareRight();
				g_nList++;
			}
			
		}
		if(input==80)//����
		{
			if(CanSqareDown()==1&&CanSqareDown2()==1)
			{
				SqareDown();
				g_nLine++;
			}
		}
		if(input==72)//����
		{
			OnChangeSqare();

			
		}
		if(input==' ')
		{
			settextstyle(35, 0, _T("����"));
			settextcolor(MAGENTA);
			
			outtextxy(WIDTH/2-75, HEIGHT/2-15, _T("��Ϸ��ͣ"));
			FlushBatchDraw();
			system("pause");
			clearrectangle(WIDTH/2-75,HEIGHT/2-15,WIDTH-1,HEIGHT-1);
			
		}
		else if(input==27)
		{
			settextstyle(35, 0, _T("����"));
			settextcolor(GREEN);
			
			outtextxy(WIDTH/2-75, HEIGHT/2-15, _T("��Ϸ����"));
			FlushBatchDraw();
			system("pause");
			exit(0);

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
		DestroyOneLineSqare();
		if (gameover()==0)
		{
			settextstyle(35, 0, _T("����"));
			settextcolor(LIGHTRED);
			outtextxy(WIDTH/2-75, HEIGHT/2-15, _T("Gameover"));
			FlushBatchDraw();
			system("pause");
			exit(0);
		}
		CreateRandonSqare();
		CopySqareToBack();
		PaintSqare();
	}
	ShowSqare2();
}
int gameover()
{
	int i;
	for(i=0;i<10;i++)
	{
		if(g_arrBackGround[0][i]==2)
		{
			//��Ϸ����
			return 0;
		}
	}
	return 1;
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
	
}
void DestroyOneLineSqare()
{
	int i,j;
	int nTempi;
	int nsum=0;
	int k;
	for(i=19;i>=0;i--)
	{
		for(j=0;j<10;j++)
		{
			nsum+=g_arrBackGround[i][j];

		}
		if(nsum==20)
		{
			k=i;
			//����һ��
			
			for(nTempi=i-1;nTempi>=0;nTempi--)
			{
				for(j=0;j<10;j++)
				{
					clearrectangle(j*UNIT,k*UNIT,j*UNIT+UNIT,k*UNIT+UNIT);
					g_arrBackGround[nTempi+1][j]=g_arrBackGround[nTempi][j];
					clearrectangle(j*UNIT,nTempi*UNIT,j*UNIT+UNIT,nTempi*UNIT+UNIT);
					putimage(0,0,&img_bk2);//�����꣨0,0��λ����ʾIMAGE����
				}

			}
			Score++;
			mciSendString("stop jpmusic", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString("close jpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open .\\3.mp3 alias jpmusic", NULL, 0, NULL); // ����������
			mciSendString("play jpmusic ", NULL, 0, NULL); // ������һ��
			i=20;
			

		}
		nsum=0;
	}
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
	case 5://��z
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
	case 6://��L
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


//����
void beforegame()
{
	putimage(0,0,&img_bk1);
	setlinecolor(BLACK);
	setlinestyle(PS_NULL);
	rectangle(250,130,400,190);
	settextstyle(40, 0, _T("����"));
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	outtextxy(280, 140, _T("START"));
	settextstyle(30, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(480, 10, _T("����˹����"));
	if(MouseHit())
	{
		while(1)
		{
			msg=GetMouseMsg();
			if(msg.mkLButton&&msg.y<190 && msg.y>130 && msg.x<400 && msg.x>250)
				break;
		}
	}
}

//��ʼ��
void startup()
{
	srand((unsigned)time(NULL));
	initgraph(640,480);
	msg.x=0;
	msg.y=0;
	loadimage(&img_bk2,_T(".\\1.jpg"));//��ȡͼƬ��img������
	loadimage(&img_bk1,_T(".\\2.jpg"));
	mciSendString("open .\\1.mp3 alias bkmusic", NULL, 0, NULL);//��������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // ѭ������
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
				putimage(0,0,&img_bk2);//�����꣨0,0��λ����ʾIMAGE����
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID);
				rectangle(-1,0,WIDTH+1,HEIGHT+1);
				settextstyle(20, 0, _T("����"));
				setbkmode(TRANSPARENT);
				settextcolor(BROWN);
				outtextxy(WIDTH+15, 270, _T("����˵��"));
				outtextxy(WIDTH+15, 300, _T("�ϣ���ת"));
				outtextxy(WIDTH+15, 320, _T("������"));
				outtextxy(WIDTH+15, 340, _T("�ң�����"));
				outtextxy(WIDTH+15, 360, _T("�£�����"));
				outtextxy(WIDTH+15, 380, _T("�ո���ͣ"));
				outtextxy(WIDTH+15, 400, _T("ESC���˳�"));
				settextstyle(40, 0, _T("����"));
				outtextxy(WIDTH+25 , 30, _T("������"));
				
			}
		}
	}
	itoa(Score,strScore,10);
	settextstyle(40, 0, _T("����"));
	settextcolor(LIGHTMAGENTA);
	outtextxy(WIDTH+130,33,_T(strScore));
}	 
	
int main()
{
	
	startup();
	beforegame();
	CreateRandonSqare();
	CopySqareToBack();
	BeginBatchDraw();
	while(1)
	{	
		double start = (double)clock()/CLOCKS_PER_SEC;
		show();
		UpdateWithInput();
		UpdateWithoutInput();
		FlushBatchDraw();
		if(Score<10)
		{
			if((double)clock()/CLOCKS_PER_SEC-start < 1.0/3){
				Sleep((int)((1.0/3 - (double)clock()/CLOCKS_PER_SEC + start) * 1000));
		}
		
		
		}
		else if(Score>=10)
		{
			if((double)clock()/CLOCKS_PER_SEC-start < 1.0/5){
				Sleep((int)((1.0/5 - (double)clock()/CLOCKS_PER_SEC + start) * 1000));
			}
		}

	}
	EndBatchDraw();
	getch();
	closegraph();
	return 0;
}

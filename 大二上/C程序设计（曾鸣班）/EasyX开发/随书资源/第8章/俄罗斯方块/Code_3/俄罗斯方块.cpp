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
int g_nSqareID;
int g_nLine,g_nList;
int arrSqare[3][3]={0};
int a;


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

int CanSqareDown();//������0�����½�������1������ף����½�
int CanSqareDown2();//������0�����½�������1������ף����½�,�뷽������
int CanSqareLeft();//������0�������ƣ�����1���������ߣ���������
int CanSqareLeft2();//������0�������ƣ�����1���������ߣ��������ƣ��뷽������
int CanSqareRight();//������0�������ƣ�����1��������ұߣ���������
int CanSqareRight2();//������0�������ƣ�����1��������ұߣ��������ƣ��뷽������
void PaintSqare();//������
void Change1TO2();//����֮��������1��2
void ShowSqare2();//2��ʱ��Ҳ�����鵽����



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
		if(g_arrBackGround[g_nLine][g_nList+i]==2||g_nList+i>9)//�ұ߽�
		{
			break;
			
		}

	}
	for(j=1;j<4;j++)
	{
		if(g_arrBackGround[g_nLine][g_nList-j]==2||g_nList-j<0)//��߽�
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
		UpdateWithInput();
		UpdateWithoutInput();
		
	}
	getch();
	closegraph();
	return 0;
}

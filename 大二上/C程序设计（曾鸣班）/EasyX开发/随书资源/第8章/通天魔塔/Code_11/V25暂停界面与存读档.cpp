#include<graphics.h>
#include<stdio.h>
#include<conio.h>	//ͷ�ļ�

#define WIDTH 32
#define HIGH 24	//��״������

struct attribute
{
	int Level;					//����ȼ�
	int Life;					//��������ֵ
	int Attack;					//���﹥����
	int Defence;				//���������
	int GOLD;					//���ֽ����
	int Exp;					//ӵ�о���ֵ
	int GKnum;					//��Կ�׸���
	int RKnum;					//��Կ�׸���
	int YKnum;					//��Կ�׸���
	int BKnum;					//��Կ�׸���
};

struct monster
{
	int life;					//��������ֵ
	int att;					//���﹥����
	int def;					//���������
	int Gold;					//���ܹ���ɻ�����
	int exp;					//���ܹ���ɻ���ֵ
};

struct Picture					//���⿪��һ���ṹ�壬��ԭ�ṹ������������9999�������ж���IMAGE�ᵼ�¹��������
{
	IMAGE img_mon;				//ս����������ͼ
};

struct atlas
{
	int newcanvas[WIDTH][HIGH];	//�µĻ�������
};

//������ȫ�ֱ�������
IMAGE img_bk;						//����ͼƬ
IMAGE img_land;						//��·ͼƬ
IMAGE img_door;						//��ͼƬ
IMAGE img_wall;						//ǽͼƬ
IMAGE img_monster,img_monster00;	//����ͼƬ
IMAGE img_player1,img_player2;		//���ͼƬ
IMAGE img_Elf,img_Elf00;			//����ͼƬ
IMAGE img_NPC1,img_NPC01;			//NPCͼƬ
IMAGE img_tp1,img_tp01;				//����ˮ��ͼƬ
IMAGE img_panel;					//�������ͼƬ
IMAGE img_excalibur1,img_excalibur2;//ʥ��ͼƬ
IMAGE img_item1,img_item2;      //ʥ����ĵ���
IMAGE img_newbk;					//1�㼰���ϵı���ͼƬ
IMAGE img_player;					//ս�����������ͼ

int i,j,z;
int canvas[WIDTH][HIGH];	//��������
struct atlas map[6];		//�����ض������ĸ��㻭������ 
int player_x,player_y;		//���λ��
int step;					//�ƶ�����
int dialogue;				//�ж��Ƿ����Ի�
int Stair;					//���ڲ���
int FLOOR;					//���ڲ���
int Gold;					//���ֽ����
struct attribute p;			//��������������
struct monster m[9999];		//�������Բ���
struct Picture _m[10];		//��Ӧ�����ͼ
int OwnExcalibur;			//�ж��Ƿ�ӵ�е���ʥ��
int isdone;					//�ж�װ�������Ƿ��Ѿ����Ӹ�����
int isscan;					//�ж��Ƿ����ڲ鿴��������
int isgiven,isgivenG;       //�ж��Ƿ����Կ��
int iscolor;				//�ж�����Ƿ������ɵ�����ֲ���	
int isbattle;				//�ж��Ƿ�����ｻս
int battleover;				//�ж�ս���Ƿ����
int bossappear;				//�ж�BOSS�Ƿ����
int isCrystal;				//�ж����ϴ��͵�ˮ���Ƿ����
int gameover;				//�ж��Ƿ���Ϸ����
char lastinput;				//��¼��һ�μ��̼���
char avoid;					//��ֹlastinputδ������
TCHAR string[100];			//���ڴ��ת���������
int oldtime,newtime,time;
int counter1=0,counter2=0;
int timestart=0,move=-1,go=0;
int LIFE;
int start=0;
int isdone2=0,tips=0,test=0;
SYSTEMTIME ti;	

void transform(int number,TCHAR str[])			//������ת��Ϊ�ַ���
{
	int i=0;
	int j=0;
	TCHAR temp;
	for(i=0;i<100;i++)
		str[i]='\0';
	if( number>0 )
	{
		while(number>0)
		{
			str[i] = number%10+'0';
			number /= 10;
			i++;
		}
		i--;
		while(j<i)
		{
			temp=str[j];
			str[j]=str[i];
			str[i]=temp;
			j++;
			i--;
		}
	}
	else if(number<=0)
	{
		str[0]='0';
	}
}

void delay(DWORD ms)//������ʱ
{
	static DWORD oldtime=GetTickCount();

	while(GetTickCount()-oldtime<ms)
		Sleep(1);

	oldtime=GetTickCount();
}

void DefineBackground()	//�������ж��屳����ֵΪ0
{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			canvas[i][j]=0;
		}
	}
}
void DrawBackground()	//���Ʊ���
{	
	
	 if( FLOOR==0&&start==1 )
	{
		for(i=8;i<WIDTH;i++)
		{
			for(j=0;j<HIGH;j++)
			{
				if(canvas[i][j]==0)
				{
					loadimage(&img_bk, _T("E:\\ħ��project\\Resources\\Terrain\\T-SKY.jpg"));
					putimage(i*32, j*32, &img_bk);
				}
			}
		}
	}
	else if( FLOOR==1 )
	{
		loadimage(&img_newbk, _T("E:\\ħ��project\\Resources\\Map\\layer1.jpg"));
		putimage(256, 0, &img_newbk);
	}
	else if( FLOOR==2 )
	{
		loadimage(&img_newbk, _T("E:\\ħ��project\\Resources\\Map\\layer2.jpg"));
		putimage(256, 0, &img_newbk);
	}
	else if( FLOOR==3 )
	{
		loadimage(&img_newbk, _T("E:\\ħ��project\\Resources\\Map\\layer3.jpg"));
		putimage(256, 0, &img_newbk);
	}
}
void DefineRoad()	//�������ж����·��ֵΪ1
{
	if( FLOOR==0 )
	{
		for(j=8;j<12;j++)
		{	
			canvas[14][j]=1;
		}			
		for(j=9;j<12;j++)
		{
			canvas[15][j]=1;
		}
		for(j=11;j<13;j++)
		{
			canvas[16][j]=1;
		}
		for(j=HIGH-2;j<HIGH;j++)
		{
			canvas[16][j]=1;
		}
		for(j=11;j<14;j++)
		{
			canvas[17][j]=1;
		}
		for(j=HIGH-4;j<HIGH;j++)
		{
			canvas[17][j]=1;
		}
		for(j=11;j<15;j++)
		{
			canvas[18][j]=1;
			canvas[19][j]=1;
		}
		for(j=HIGH-7;j<HIGH;j++)
		{
			canvas[18][j]=1;
		}
		for(j=12;j<15;j++)
		{
			canvas[21][j]=1;
		}
		for(j=HIGH-8;j<HIGH;j++)
		{
			canvas[19][j]=1;
			canvas[21][j]=1;
		}
		for(i=21;i<24;i++)
		{
			for(j=8;j<10;j++)
			{
				canvas[i][j]=1;
			}
		}
		for(i=24;i<27;i++)
		{
			canvas[i][8]=1;
		}
		for(j=HIGH-6;j<HIGH;j++)
		{
			canvas[22][j]=1;
		}
		for(j=HIGH-4;j<HIGH;j++)
		{
			canvas[23][j]=1;
		}
		for(j=HIGH-3;j<HIGH;j++)
		{
			canvas[24][j]=1;
		}
		for(j=HIGH-1;j<HIGH;j++)
		{
			canvas[25][j]=1;
		}
		for(j=5;j<9;j++)
		{
			canvas[26][j]=1;
		}
		for(j=0;j<HIGH;j++)
		{
			canvas[20][j]=1;
		}	
	}
	else if( FLOOR==3 )	//�����·������ֵΪ9
	{
		for(i=17;i<=22;i++)
		{
			canvas[i][9]=9;
			canvas[i][14]=9;
		}
		for(j=10;j<=13;j++)
		{
			canvas[17][j]=9;
			canvas[22][j]=9;
		}
	}
}
void DrawRoad()	//���Ƶ�·
{	
	if(start==1)
{
	if( FLOOR==0 )
	{
		for(i=8;i<WIDTH;i++)
		{
			for(j=0;j<HIGH;j++)
			{
				if(canvas[i][j]==1)
				{
					loadimage(&img_land, _T("E:\\ħ��project\\Resources\\Terrain\\T-LAND.jpg"));
					putimage(i*32, j*32, &img_land);
				}
			}
		}
	}
}

}
void DefineWall()	//�������ж���ǽ��ֵΪ2
{
	if( FLOOR==0 )
	{
		for(j=8;j<13;j++)
		{	
			canvas[13][j]=2;
		}
		for(i=13;i<16;i++)
		{
			canvas[i][7]=2;
			canvas[i][12]=2;
		}
		canvas[15][8]=2;
		for(i=15;i<17;i++)
		{
			canvas[i][13]=2;
		}
		for(j=8;j<11;j++)
		{
			canvas[16][j]=2;
		}
		for(i=16;i<19;i++)
		{
			canvas[i][14]=2;
		}
		for(i=17;i<19;i++)
		{
			canvas[i][10]=2;
		}
		for(j=0;j<11;j++)
		{
			canvas[19][j]=2;
		}
		for(j=0;j<8;j++)
		{
			canvas[21][j]=2;
		}
		for(i=22;i<26;i++)
		{
			canvas[i][7]=2;
		}
		for(j=4;j<7;j++)
		{
			canvas[25][j]=2;
		}
		canvas[26][4]=2;
		for(j=4;j<10;j++)
		{
			canvas[27][j]=2;
		}
		for(i=24;i<27;i++)
		{
			canvas[i][9]=2;
		}
		for(i=21;i<25;i++)
		{
			canvas[i][10]=2;
		}
		canvas[19][15]=2;
		canvas[21][15]=2;
		for(j=12;j<15;j++)
		{
			canvas[22][j]=2;
		}
		canvas[21][12]=2;
		canvas[21][11]=2;
		canvas[21][15]=2;
		for(j=15;j<18;j++)
		{
			canvas[22][j]=2;
		}
		for(j=17;j<20;j++)
		{
			canvas[23][j]=2;
		}
		for(j=19;j<21;j++)
		{
			canvas[24][j]=2;
		}
		for(j=20;j<23;j++)
		{
			canvas[25][j]=2;
		}
		for(j=22;j<HIGH;j++)
		{
			canvas[26][j]=2;
		}
		for(j=15;j<17;j++)
		{
			canvas[18][j]=2;
		}
		for(j=16;j<20;j++)
		{
			canvas[17][j]=2;
		}
		for(j=19;j<22;j++)
		{
			canvas[16][j]=2;
		}
		for(j=HIGH-3;j<HIGH;j++)
		{
			canvas[15][j]=2;
		}
	}
	else if( FLOOR==1 )
	{
		for(i=8;i<WIDTH;i++)
		{
			canvas[i][0]=2;
			canvas[i][HIGH-1]=2;
		}
		for(j=0;j<HIGH;j++)
		{
			canvas[8][j]=2;
			canvas[WIDTH-1][j]=2;
		}
		canvas[9][4]=2;
		for(i=9;i<11;i++)
		{
			canvas[i][16]=2;
		}
		for(j=19;j<21;j++)
		{
			canvas[9][j]=2;
		}
		for(j=4;j<7;j++)
		{
			canvas[11][j]=2;
		}
		for(j=2;j<5;j++)
		{
			canvas[12][j]=2;
		}
		for(j=6;j<20;j++)
		{
			canvas[12][j]=2;
		}
		for(j=21;j<23;j++)
		{
			canvas[12][j]=2;
		}
		for(j=2;j<5;j++)
		{
			canvas[12][j]=2;
		}
		canvas[13][4]=2;
		canvas[13][6]=2;
		canvas[14][4]=2;
		canvas[14][6]=2;
		for(i=14;i<17;i++)
		{
			canvas[i][3]=2;
			canvas[i][7]=2;
		}
		for(i=13;i<20;i++)
		{
			canvas[i][11]=2;
		}
		for(i=13;i<18;i++)
		{
			canvas[i][16]=2;
		}
		canvas[16][1]=2;
		canvas[19][1]=2;
		for(i=16;i<20;i++)
		{
			canvas[i][4]=2;
		}
		for(i=19;i<22;i++)
		{
			canvas[i][3]=2;
		}
		for(i=16;i<24;i++)
		{
			canvas[i][6]=2;
		}
		canvas[21][5]=2;
		canvas[22][5]=2;
		for(i=23;i<26;i++)
		{
			canvas[i][3]=2;
		}
		canvas[23][4]=2;
		canvas[25][4]=2;
		canvas[25][1]=2;
		for(j=1;j<4;j++)
		{
			canvas[27][j]=2;
		}
		canvas[28][3]=2;
		canvas[30][3]=2;
		for(i=23;i<26;i++)
		{
			canvas[i][7]=2;
		}
		for(i=25;i<29;i++)
		{
			canvas[i][6]=2;
		}
		for(i=27;i<29;i++)
		{
			canvas[i][5]=2;
		}
		canvas[30][5]=2;
		canvas[30][6]=2;
		for(j=7;j<16;j++)
		{
			canvas[27][j]=2;
		}
		for(i=13;i<20;i++)
		{
			canvas[i][11]=2;
		}
		for(i=21;i<28;i++)
		{
			canvas[i][11]=2;
		}
		for(i=13;i<18;i++)
		{
			canvas[i][16]=2;
		}
		for(i=19;i<29;i++)
		{
			canvas[i][16]=2;
		}
		canvas[30][16]=2;
		for(j=17;j<23;j++)
		{
			canvas[16][j]=2;
		}
		for(i=17;i<19;i++)
		{
			canvas[i][19]=2;
		}
		canvas[20][18]=2;
		for(i=20;i<24;i++)
		{
			canvas[i][19]=2;
		}
		for(j=17;j<19;j++)
		{
			canvas[23][j]=2;
		}
		for(j=21;j<23;j++)
		{
			canvas[23][j]=2;
		}
	}
	else if( FLOOR==2 )
	{
		for(i=8;i<WIDTH;i++)
		{
			canvas[i][0]=2;
			canvas[i][HIGH-1]=2;
		}
		for(j=0;j<HIGH;j++)
		{
			canvas[8][j]=2;
			canvas[WIDTH-1][j]=2;
		}
		for(j=1;j<6;j++)
		{
			canvas[10][j]=2;
		}
		for(j=1;j<6;j++)
		{
			canvas[10][j]=2;
		}
		for(j=1;j<7;j++)
		{
			canvas[12][j]=2;
		}
		for(i=9;i<16;i++)
		{
			canvas[i][8]=2;
			canvas[i][12]=2;
			canvas[i][18]=2;
		}
		for(j=2;j<9;j++)
		{
			canvas[16][j]=2;
		}
		for(i=17;i<26;i++)
		{
			canvas[i][2]=2;
		}
		for(i=26;i<30;i++)
		{
			canvas[i][2]=2;
			canvas[i][6]=2;
			canvas[i][8]=2;
		}
		for(j=14;j<17;j++)
		{
			canvas[10][j]=2;
			canvas[12][j]=2;
		}
		for(j=20;j<23;j++)
		{
			canvas[10][j]=2;
			canvas[14][j]=2;
		}
		for(i=9;i<17;i++)
		{	canvas[i][10]=2;
		    canvas[i+3][14]=2;
		}
		for(j=3;j<6;j++)
		{	canvas[29][j]=2;
			canvas[25][j+1]=2;
			canvas[19][j+7]=2;
			canvas[17][j+7]=2;
			canvas[19][j+12]=2;
		}
		canvas[9][14]=2;
		canvas[18][12]=2;
		canvas[19][6]=2;
		for(i=13;i<15;i++)
		{
			canvas[i][3]=2;
			canvas[i][6]=2;
		}
		for(i=11;i<14;i++)
		{	
			canvas[i][20]=2;
		}
		for(j=18;j<22;j++)
		{
			canvas[16][j]=2;
		}
		for(j=4;j<9;j++)
		{
			canvas[18][j]=2;
			canvas[23][j]=2;
			canvas[18][j+13]=2;
			canvas[23][j+13]=2;
		}
		for(j=8;j<18;j++)
		{
			canvas[22][j]=2;
		}
		for(j=8;j<13;j++)
		{
			canvas[19][j]=2;
		}
		for(j=9;j<23;j++)
		{
			canvas[26][j]=2;
		}
		for(j=9;j<20;j++)
		{
			canvas[29][j]=2;
		}
		for(i=19;i<23;i++)
		{	
			canvas[i][4]=2;
			canvas[i][21]=2;
		}
	
	}
	else if(FLOOR==3)
	{
		for(i=10;i<=29;i++)
		{
			canvas[i][2]=2;
			canvas[i][21]=2;
		}
		for(i=12;i<=27;i++)
		{
			canvas[i][4]=2;
			canvas[i][19]=2;
		}
		for(i=14;i<=25;i++)
		{
			canvas[i][6]=2;
			canvas[i][17]=2;
		}
		for(i=16;i<=23;i++)
		{
			canvas[i][8]=2;
			canvas[i][15]=2;
		}
		for(j=2;j<=21;j++)
		{
			canvas[10][j]=2;
			canvas[29][j]=2;
		}
		for(j=4;j<=19;j++)
		{
			canvas[12][j]=2;
			canvas[27][j]=2;
		}
		for(j=6;j<=17;j++)
		{
			canvas[14][j]=2;
			canvas[25][j]=2;
		}
		for(j=8;j<=15;j++)
		{
			canvas[16][j]=2;
			canvas[23][j]=2;
		}
		canvas[18][10]=2;
		canvas[21][10]=2;
		canvas[18][13]=2;
		canvas[21][13]=2;
		canvas[12][20]=2;
		canvas[14][5]=2;
		canvas[24][15]=2;
		
	}
}
void DrawWall()	//����ǽ
{	if(start==1)
	{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if(canvas[i][j]==2)
			{
				if( FLOOR==0 )
				{
					loadimage(&img_wall, _T("E:\\ħ��project\\Resources\\Terrain\\T-BlockWALL.jpg"));
					putimage(i*32, j*32, &img_wall);
				}
			/*	else if( FLOOR==1 )
				{
					loadimage(&img_wall, _T("E:\\ħ��project\\Resources\\Terrain\\T-WoodenWALL.jpg"));
					putimage(i*32, j*32, &img_wall);
				}*/
			}
		}
	}
	}
}
void DefineDoor()	//�������ж����ŵ�ֵ������Ϊ3-8
{
	if( FLOOR==0 )
	{
		canvas[20][15]=3;
	}
/*	if( FLOOR==1 )
	{
		canvas[12][20]=4;
		canvas[11][16]=4;
		canvas[10][4]=4;
		canvas[12][1]=4;
		canvas[16][2]=4;
		canvas[19][2]=4;
		canvas[25][2]=4;
		canvas[22][3]=4;
		canvas[29][16]=4;
		canvas[23][20]=4;
		canvas[19][19]=4;
		canvas[18][16]=4;
	}  */
}
void DrawDoor()	//������
{
	if(start==1)
	{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if( canvas[i][j]==3 )
			{
				loadimage(&img_door, _T("E:\\ħ��project\\Resources\\Terrain\\T-IronDOOR.jpg"));
				putimage(i*32, j*32, &img_door);
			}
			/*if( canvas[i][j]==4 )
			{
				loadimage(&img_door, _T("E:\\ħ��project\\Resources\\Doors\\springdoor.jpg"));
				putimage(i*32, j*32, &img_door);
			}*/
		}
	}
	}
}
void Defineitems()	//�������ж�����Ʒ��ֵ������Ϊ10-99
{
	if( FLOOR==1 )
	{
		canvas[30][1]=10;
		canvas[14][10]=11;
		canvas[13][3]=12;
		canvas[17][21]=12;
		canvas[23][5]=12;
		canvas[19][2]=13;
		canvas[22][17]=13;
		canvas[30][22]=13;
		canvas[9][1]=20;
		canvas[26][10]=20;
		canvas[17][22]=20;

	}
	if( FLOOR==2 )
	{
		canvas[27][5]=21;
		canvas[20][19]=22;
		canvas[24][1]=12;
		canvas[21][19]=12;
		canvas[9][1]=12;
		canvas[13][15]=12;
		canvas[23][15]=12;
		canvas[11][1]=13;
		canvas[9][22]=13;
		canvas[27][9]=13;
		canvas[28][9]=13;
		canvas[13][4]=20;
		canvas[9][9]=20;
		canvas[19][20]=20;
		canvas[22][20]=20;
		canvas[12][22]=25;//��Կ��
	}
	if( FLOOR==3 )
	{
		canvas[15][7]=31;//���׽�
		canvas[14][18]=32;//������
		canvas[11][3]=30;//��ҩˮ
		canvas[28][20]=30;
		canvas[28][3]=30;
		canvas[24][8]=30;
	}
}
void Drawitems()
{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if(canvas[i][j]==10)	//���ƶ̽�
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_shortsword.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\shortsword.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==11)	//����ľ��
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_woodenshield.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\woodenshield.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==12)	//���ƹ����ͱ�ʯ
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_reddiamond.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\reddiamond.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==13)	//���Ʒ����ͱ�ʯ
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_bluediamond.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\bluediamond.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==20)	//���ƺ�ҩˮ
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_RedMedicine.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\RedMedicine.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==30)	//������ҩˮ
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_Item02-10_2_1.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\Item02-10_2_1.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==31)	//���ƾ��׽�
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_Item03-15_3_4.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\Item03-15_3_4.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==32)	//����������
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_Item03-15_2_4.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\Item03-15_2_4.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==22)	//���Ƹֶ�
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_steelshield.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\steelshield.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
			if(canvas[i][j]==25)	//������Կ��
			{
				loadimage(&img_item1, _T("E:\\ħ��project\\Resources\\Item\\_BlueKey.jpg"));
				loadimage(&img_item2, _T("E:\\ħ��project\\Resources\\Item\\BlueKey.jpg"));
				putimage(i*32, j*32, &img_item1,NOTSRCERASE);
				putimage(i*32, j*32, &img_item2,SRCINVERT);
			}
		}
	}
}
void DefineNPC()	//�������ж���NPC��ֵ������Ϊ100-999
{
	if( FLOOR==0 )
	{
		canvas[26][5]=100;
		canvas[14][8]=101;
	}
	else if( FLOOR==1 )
	{
	  canvas[15][4]=102;
	  canvas[15][22]=103;
	}
	else if(FLOOR==2)
	{
		canvas[9][11]=104;
		
	}
}
void DrawNPC()	//����NPC
{
	if(start==1)
	{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if(canvas[i][j]==100)	//���ƾ���
			{
				loadimage(&img_Elf, _T("E:\\ħ��project\\Resources\\Character\\_Elf.jpg"));
				loadimage(&img_Elf00, _T("E:\\ħ��project\\Resources\\Character\\Elf.jpg"));
				putimage(i*32, j*32, &img_Elf,NOTSRCERASE);
				putimage(i*32, j*32, &img_Elf00,SRCINVERT);
			}
			if(canvas[i][j]==101)	//��������
			{
				loadimage(&img_NPC01, _T("E:\\ħ��project\\Resources\\Character\\_NPC01.jpg"));
				loadimage(&img_NPC1, _T("E:\\ħ��project\\Resources\\Character\\NPC01.jpg"));
				putimage(i*32, j*32, &img_NPC01,NOTSRCERASE);
				putimage(i*32, j*32, &img_NPC1,SRCINVERT);
			}
			if(canvas[i][j]==102)	//����ɨ�ش���
			{
				loadimage(&img_NPC01, _T("E:\\ħ��project\\Resources\\Character\\_NPC02.jpg"));
				loadimage(&img_NPC1, _T("E:\\ħ��project\\Resources\\Character\\NPC02.jpg"));
				putimage(i*32, j*32, &img_NPC01,NOTSRCERASE);
				putimage(i*32, j*32, &img_NPC1,SRCINVERT);
			}
			if(canvas[i][j]==103)	//���ƿ��Ŵ�ү
			{
				loadimage(&img_NPC01, _T("E:\\ħ��project\\Resources\\Character\\_NPC03.jpg"));
				loadimage(&img_NPC1, _T("E:\\ħ��project\\Resources\\Character\\NPC03.jpg"));
				putimage(i*32, j*32, &img_NPC01,NOTSRCERASE);
				putimage(i*32, j*32, &img_NPC1,SRCINVERT);
			}
			if(canvas[i][j]==104)	//���Ʊ�ѩŮ��
			{
				loadimage(&img_NPC01, _T("E:\\ħ��project\\Resources\\Character\\_NPC04.jpg"));
				loadimage(&img_NPC1, _T("E:\\ħ��project\\Resources\\Character\\NPC04.jpg"));
				putimage(i*32, j*32, &img_NPC01,NOTSRCERASE);
				putimage(i*32, j*32, &img_NPC1,SRCINVERT);
			}
		}
	}
	}
}
void DefineMonster()	//�������ж�������ֵ������Ϊ1000-9999
{
	if( FLOOR==0 )
	{
		canvas[20][16]=9999;
	}
	else if( FLOOR==1 )
	{
		canvas[10][19]=1000;
		canvas[11][18]=1000;
		canvas[10][1]=1000;
		canvas[9][6]=1000;
		canvas[10][6]=1000;
		canvas[11][7]=1000;
		canvas[9][12]=1000;
		canvas[11][12]=1000;
		canvas[13][2]=1000;
		canvas[18][2]=1000;
		canvas[20][2]=1000;
		canvas[24][2]=1000;
		canvas[29][2]=1000;
		canvas[29][7]=1000;
		canvas[29][15]=1000;
		canvas[28][17]=1000;
		canvas[24][19]=1000;
		canvas[29][21]=1000;
		canvas[30][21]=1000;
		canvas[29][22]=1000;
		canvas[25][22]=1000;
		canvas[18][22]=1000;
		canvas[18][21]=1000;
		canvas[18][20]=1000;
		canvas[20][17]=1000;
		for(i=16;i<24;i++)
		{
			canvas[i][13]=1000;
		}
		for(i=16;i<24;i++)
		{
			canvas[i][14]=1000;
		}
		for(i=15;i<25;i++)
		{
			canvas[i][10]=1000;
		}
		for(i=17;i<23;i++)
		{
			canvas[i][9]=1000;
		}
		for(i=18;i<22;i++)
		{
			canvas[i][8]=1000;
		}
		for(i=19;i<21;i++)
		{
			canvas[i][7]=1000;
		}
		canvas[13][7]=1000;
		canvas[26][7]=1000;
	}
	else if( FLOOR==2 )
	{
		canvas[9][4]=2001;
		canvas[9][5]=2001;
		canvas[9][16]=2001;
		canvas[9][19]=2001;
		canvas[10][9]=2001;
		canvas[11][2]=2001;
		canvas[11][4]=2001;
		canvas[11][14]=2001;
		canvas[12][7]=2001;
		canvas[13][1]=2001;
		canvas[13][5]=2001;
		canvas[13][11]=2001;
		canvas[13][16]=2001;
		canvas[14][2]=2001;
		canvas[14][4]=2001;
		canvas[14][19]=2001;
		canvas[14][15]=2001;
		canvas[15][4]=2001;
		canvas[15][11]=2001;
		canvas[15][21]=2001;
		canvas[17][13]=2001;
		canvas[19][13]=2001;
		canvas[22][1]=2001;
		canvas[23][1]=2001;
		canvas[20][8]=2001;
		canvas[21][8]=2001;
		canvas[20][16]=2001;
		canvas[21][16]=2001;
		canvas[20][18]=2001;
		canvas[21][18]=2001;
		canvas[20][20]=2001;
		canvas[21][20]=2001;
		canvas[19][19]=2001;
		canvas[22][19]=2001;
		canvas[23][16]=2001;
		canvas[24][12]=2001;
		canvas[24][10]=2001;
		canvas[25][14]=2001;
		canvas[27][10]=2001;
		canvas[28][10]=2001;
		for(i=26;i<=28;i++)
		{
			canvas[i][3]=2001;
			canvas[i][4]=2001;
		}
		canvas[26][5]=2001;canvas[28][5]=2001;
		canvas[27][11]=2001;canvas[27][16]=2001;
		canvas[28][14]=2001;canvas[28][18]=2001;
		canvas[30][4]=2001;canvas[30][13]=2001;
		canvas[29][22]=2001;
	    canvas[20][5]=9997;
	}
	else if( FLOOR==3 )
	{
		canvas[11][17]=3002;
		canvas[11][13]=3002;
		canvas[11][14]=3002;
		canvas[11][15]=3002;
		canvas[11][10]=3002;
		canvas[11][8]=3002;
		canvas[11][6]=3002;
		canvas[11][4]=3002;
		canvas[12][3]=3002;
		canvas[14][3]=3002;
		canvas[19][3]=3002;
		canvas[22][3]=3002;
		canvas[23][3]=3002;
		canvas[24][3]=3002;
		canvas[26][3]=3002;
		canvas[28][4]=3002;
		canvas[28][9]=3002;
		canvas[28][10]=3002;
		canvas[28][11]=3002;
		canvas[28][15]=3002;
		canvas[28][17]=3002;
		canvas[28][19]=3002;
		canvas[27][20]=3002;
		canvas[24][20]=3002;
		canvas[20][20]=3002;
		canvas[17][20]=3002;
		canvas[16][20]=3002;
		canvas[15][20]=3002;
		canvas[13][7]=3003;
		canvas[13][9]=3003;
		canvas[13][10]=3003;
		canvas[13][11]=3003;
		canvas[13][14]=3003;
		canvas[13][17]=3003;
		canvas[13][18]=3003;
		canvas[15][18]=3003;
		canvas[18][18]=3003;
		canvas[20][18]=3003;
		canvas[24][18]=3003;
		canvas[25][18]=3003;
		canvas[26][17]=3003;
		canvas[26][13]=3003;
		canvas[26][11]=3003;
		canvas[26][7]=3003;
		canvas[25][5]=3003;
		canvas[22][5]=3003;
		canvas[20][5]=3003;
		canvas[18][5]=3003;
		canvas[15][8]=3004;
		canvas[15][10]=3004;
		canvas[15][11]=3004;
		canvas[15][13]=3004;
		canvas[16][16]=3004;
		canvas[19][16]=3004;
		canvas[22][16]=3004;
		canvas[24][11]=3004;
		canvas[24][10]=3004;
		canvas[23][7]=3004;
		canvas[20][7]=3004;
		canvas[18][7]=3004;
		canvas[17][9]=4005;
		canvas[17][14]=4005;
		canvas[22][9]=4005;
		canvas[22][14]=4005;
		canvas[20][12]=9996;
	}
}
void DrawMonster()	//���ƹ���
{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if(canvas[i][j]==1000)	//���ƴ�֮����
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-Fairy.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-Fairy.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if( canvas[i][j]==9998 )	//���ƴ�֮BOSS
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-SpringBoss.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-SpringBoss.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if( canvas[i][j]==9999 )	//����������
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-Porter.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-Porter.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if(canvas[i][j]==2001)	//���Ʊ���
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-ice.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-ice.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if(canvas[i][j]==3002)	//���ƶ����Ϲ�
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster13-07_1_1.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster13-07_1_1.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if(canvas[i][j]==3003)	//�����Ϲ���
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster13-07_2_1.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster13-07_2_1.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if(canvas[i][j]==3004)	//�����Ϲ���
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster13-07_3_1.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster13-07_3_1.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if( canvas[i][j]==9997 )	//���ƶ�֮BOSS
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-iceboss.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-iceboss.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if( canvas[i][j]==4005 )	//���ƴ�ʦ
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-magician.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-magician.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
			if( canvas[i][j]==9996 )	//��������BOSS
			{
				loadimage(&img_monster, _T("E:\\ħ��project\\Resources\\Monster\\_Monster-FinalBOSS.jpg"));
				loadimage(&img_monster00, _T("E:\\ħ��project\\Resources\\Monster\\Monster-FinalBOSS.jpg"));
				putimage(i*32, j*32, &img_monster,NOTSRCERASE);
				putimage(i*32, j*32, &img_monster00,SRCINVERT);
			}
		}
	}
}
void DefineCrystal()	//�������ж��崫��ˮ����ֵ������Ϊ10000-10005
{
	if( FLOOR==0 )
	{
		canvas[20][0]=10001;
	}
	else if( FLOOR==1 )
	{
		canvas[9][22]=10000;
		canvas[12][5]=10002;
	}
	else if( FLOOR==2 )
	{
		canvas[9][1]=10001;
		canvas[11][21]=10003;
	}
	else if( FLOOR==3 )
	{
		canvas[11][20]=10002;
	}
}
void DrawCrystal()	//���ƴ���ˮ�������������ڴ�ͳħ����¥��
{
	if(start==1)
	{
		if( FLOOR==1 && bossappear==0 )
		{   
			isCrystal=0;
		}
		for(i=8;i<WIDTH;i++)
		{
 			for(j=0;j<HIGH;j++)
			{
				if( canvas[i][j]==10000 )	//�����ƶ�����ʼ��Ĵ���ˮ��
				{
					loadimage(&img_tp1, _T("E:\\ħ��project\\Resources\\Terrain\\_T-Crystal.jpg"));
					loadimage(&img_tp01, _T("E:\\ħ��project\\Resources\\Terrain\\T-InitialCrystal.jpg"));
					putimage(i*32, j*32, &img_tp1,NOTSRCERASE);
					putimage(i*32, j*32, &img_tp01,SRCINVERT);
				}
				if( canvas[i][j]==10001)	//�����ƶ�����֮��Ĵ���ˮ��
				{
					loadimage(&img_tp1, _T("E:\\ħ��project\\Resources\\Terrain\\_T-Crystal.jpg"));
					loadimage(&img_tp01, _T("E:\\ħ��project\\Resources\\Terrain\\T-SpringCrystal.jpg"));
					putimage(i*32, j*32, &img_tp1,NOTSRCERASE);
					putimage(i*32, j*32, &img_tp01,SRCINVERT);
				}
				if( canvas[i][j]==10002 && isCrystal==1)	//�����ƶ�����֮��Ĵ���ˮ��
				{
					loadimage(&img_tp1, _T("E:\\ħ��project\\Resources\\Terrain\\_T-Crystal.jpg"));
					loadimage(&img_tp01, _T("E:\\ħ��project\\Resources\\Terrain\\T-WinterCrystal.jpg"));
					putimage(i*32, j*32, &img_tp1,NOTSRCERASE);
					putimage(i*32, j*32, &img_tp01,SRCINVERT);
				}
				if( canvas[i][j]==10003 )	//�����ƶ�������Ĵ���ˮ��
				{
					loadimage(&img_tp1, _T("E:\\ħ��project\\Resources\\Terrain\\_T-Crystal.jpg"));
					loadimage(&img_tp01, _T("E:\\ħ��project\\Resources\\Terrain\\T-InitialCrystal.jpg"));
					putimage(i*32, j*32, &img_tp1,NOTSRCERASE);
					putimage(i*32, j*32, &img_tp01,SRCINVERT);
				}
			}			
		}
	}
}
void DefineTransfermatrix()//���崫�������ֵΪ10006-10100
{
	if(FLOOR==2)
	{
		canvas[19][5]=10006;
		canvas[13][21]=10009;
		canvas[30][14]=10007;
		canvas[11][11]=10008;
	}
	if(FLOOR==3)
	{
		canvas[13][20]=10010;
		canvas[13][5]=10011;
		canvas[15][5]=10012;
		canvas[24][16]=10013;
		canvas[23][16]=0;
		canvas[24][14]=10014;
		canvas[19][11]=10015;
	}

}
void DrawTransfermatrix()//���ƴ�����
{
	
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if( canvas[i][j]>=10006&&canvas[i][j]<=10009)	//���ƴ�����
			{
				loadimage(&img_tp1, _T("E:\\ħ��project\\Resources\\Terrain\\_Transfer matrix.jpg"));
				loadimage(&img_tp01, _T("E:\\ħ��project\\Resources\\Terrain\\Transfer matrix.jpg"));
				putimage(i*32, j*32, &img_tp1,NOTSRCERASE);
				putimage(i*32, j*32, &img_tp01,SRCINVERT);
			}
			if( canvas[i][j]>=10010&&canvas[i][j]<=10015)	//���ƴ�����
			{
				loadimage(&img_tp1, _T("E:\\ħ��project\\Resources\\Terrain\\_Transfer matrix2.jpg"));
				loadimage(&img_tp01, _T("E:\\ħ��project\\Resources\\Terrain\\Transfer matrix2.jpg"));
				putimage(i*32, j*32, &img_tp1,NOTSRCERASE);
				putimage(i*32, j*32, &img_tp01,SRCINVERT);
			}
		}			
	}	
}
void DrawPlayer(char x)	//������ң�w��ʾ�泯ǰ��s��ʾ�泯��a��ʾ�泯��d��ʾ�泯��
{
	if(start==1)
	{
	if( x=='w' )
	{
		loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking10.jpg"));
		loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking10.jpg"));
		putimage(player_x*32, player_y*32, &img_player1,NOTSRCERASE);
		putimage(player_x*32, player_y*32, &img_player2,SRCINVERT);
	}
	else if( x=='s' )
	{
		loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior01.jpg"));
		loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior01.jpg"));
		putimage(player_x*32, player_y*32, &img_player1,NOTSRCERASE);
		putimage(player_x*32, player_y*32, &img_player2,SRCINVERT);
	}
	else if( x=='a' )
	{
		loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking04.jpg"));
		loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking04.jpg"));
		putimage(player_x*32, player_y*32, &img_player1,NOTSRCERASE);
		putimage(player_x*32, player_y*32, &img_player2,SRCINVERT);
	}
	else if( x=='d' )
	{
		loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking07.jpg"));
		loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking07.jpg"));
		putimage(player_x*32, player_y*32, &img_player1,NOTSRCERASE);
		putimage(player_x*32, player_y*32, &img_player2,SRCINVERT);
	}
	}
}
void ReDefine()	//���¶���������Ʒ����������Ĺ���ͱ�ʰȡ�ĵ��߸�ֵΪ1���Լ����ֶ�δ���ܵĴ�֮BOSS��ֵΪ9998
{
	for(i=8;i<WIDTH;i++)
	{
		for(j=0;j<HIGH;j++)
		{
			if( map[FLOOR].newcanvas[i][j]==1 || map[FLOOR].newcanvas[i][j]==9998 )
			{
				canvas[i][j]=map[FLOOR].newcanvas[i][j];
			}
		}
	}
}
void Entrance()	//��ʼ��������������������ݣ������ڻ���һ���Ϳ��ȥ��Ч�������ȶ������ƣ����ⱳ��ͼƬ��ʧ
{
	
	DefineBackground();
	DrawBackground();
	if(start==1)
	{
		DefineRoad();
		DrawRoad();
		DefineWall();
		DrawWall();
		DefineDoor();
		ReDefine();
		DrawDoor();
		Defineitems();
		ReDefine();
		Drawitems();
		DefineNPC();
		DrawNPC();
		DefineMonster();
		ReDefine();
		DrawMonster();
		DefineCrystal();
		DrawCrystal();
		DefineTransfermatrix();
		DrawTransfermatrix();
	}
}

void DrawWithoutPlayer()	//���Ƴ������뱳����������ͼƬ
{
	if(start==1)
	{
	if(FLOOR!=0)
	{
		DrawBackground();
	}
	DrawRoad();
	DrawWall();
	DrawDoor();
	Drawitems();
	DrawNPC();
	DrawMonster();
	DrawCrystal();
	DrawTransfermatrix();
	}
}

void DrawPanel()	//�����������
{
	if(start==1)
	{
		loadimage(&img_panel, _T("E:\\ħ��project\\Resources\\Character\\panel.jpg"));
		putimage(0, 0, &img_panel);
		settextcolor(WHITE);
		settextstyle(64, 0, _T("����"));
		transform(FLOOR,string);
		outtextxy(112, 32, string);		//���Ʋ���
		if( p.Level<10 )
		{
			transform(p.Level,string);
			outtextxy(144, 128, string);//���Ƶȼ�ֵ
		}
		else
		{
			transform(p.Level,string);
			outtextxy(112, 128, string);//���Ƶȼ�ֵ
		}
		transform(p.GKnum,string);
		outtextxy(144, 384, string);	//������Կ����
		transform(p.RKnum,string);
		outtextxy(144, 448, string);	//���ƺ�Կ����
		transform(p.YKnum,string);
		outtextxy(144, 512, string);	//���ƻ�Կ����
		transform(p.BKnum,string);
		outtextxy(144, 576, string);	//������Կ����
		settextstyle(32, 0, _T("����"));
		transform(p.Life,string);
		outtextxy(128, 192, string);	//��������ֵ
		transform(p.Attack,string);
		outtextxy(128, 224, string);	//���ƹ�����ֵ
		transform(p.Defence,string);
		outtextxy(128, 256, string);	//���Ʒ�����ֵ
		transform(p.GOLD,string);
		outtextxy(128, 288, string);	//���ƽ����
		transform(p.Exp,string);
		outtextxy(128, 319, string);	//���ƾ���ֵ
		if(OwnExcalibur)
		{
			loadimage(&img_excalibur1, _T("E:\\ħ��project\\Resources\\Item\\_excalibur.jpg"));
			loadimage(&img_excalibur2, _T("E:\\ħ��project\\Resources\\Item\\excalibur.jpg"));
			putimage(32, 672, &img_excalibur1,NOTSRCERASE);
			putimage(32, 672, &img_excalibur2,SRCINVERT);
		}
	}
}

void DrawCombatInterface(int num)	//����ս������
{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(400,250,880,520);
		settextcolor(WHITE);
		settextstyle(32, 0, _T("����"));
		TCHAR name1[] = _T("��ʿ");
		outtextxy(403, 253, name1);
		TCHAR LIFE1[] = _T("����ֵ");
		outtextxy(403, 290, LIFE1);
		transform(p.Life,string);
		outtextxy(550, 290, string);	//����ս��������ʿ����ֵ
		TCHAR ATTACK1[] = _T("������");
		outtextxy(403, 327, ATTACK1);
		transform(p.Attack,string);
		outtextxy(550, 327, string);	//����ս��������ʿ������ֵ
		TCHAR DEFENCE1[] = _T("������");
		outtextxy(403, 364, DEFENCE1);
		transform(p.Defence,string);
		outtextxy(550, 364, string);	//����ս��������ʿ������ֵ
		TCHAR name2[] = _T("����");
		outtextxy(813, 253, name2);
		TCHAR LIFE2[] = _T("����ֵ");
		outtextxy(781, 290, LIFE2);
		transform(m[num].life,string);
		outtextxy(700, 290, string);	//����ս�������������ֵ
		TCHAR ATTACK2[] = _T("������");
		outtextxy(781, 327, ATTACK2);
		transform(m[num].att,string);
		outtextxy(700, 327, string);	//����ս��������﹥����ֵ
		TCHAR DEFENCE2[] = _T("������");
		outtextxy(781, 364, DEFENCE2);
		transform(m[num].def,string);
		outtextxy(700, 364, string);	//����ս��������������ֵ
		putimage(403,421, &img_player);
		settextcolor(RED);
		settextstyle(64, 0, _T("����"));
		TCHAR fight[] = _T("VS");
		outtextxy(608, 421, fight);
		putimage(813,421, &_m[num%10].img_mon);
		settextcolor(WHITE);
		settextstyle(16, 0, _T("����"));
		TCHAR quit[] = _T("���ˣ�Q��");
		outtextxy(800, 500, quit);
}

void WriteRecordFile()  //�洢��Ϸ�����ļ��浵
{
	FILE *fp;
	fp = fopen(".\\GameRecord.dat","w");
	fprintf(fp,"%c %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",avoid,lastinput,player_x,player_y,FLOOR,p.Level,p.Life,p.Attack,p.Defence,p.Exp,p.GOLD,p.RKnum,p.BKnum,p.YKnum,p.GKnum,newtime,OwnExcalibur,isdone,isgiven,isgivenG,bossappear,isCrystal,m[2001].life,m[2001].att,m[2001].def);
	for(i=0;i<6;i++)
	{
		for(j=8;j<WIDTH;j++)
		{
			for(z=0;z<HIGH;z++)
			{
				if( map[i].newcanvas[j][z]!=0 )	//����Ϊ0����洢�ض���ֵ
				{
					fprintf(fp,"%d %d %d %d\n",i,j,z,map[i].newcanvas[j][z]);
				}
			}
		}
	}
	i=0;j=20;z=16;
	fprintf(fp,"%d %d %d %d\n",i,j,z,map[i].newcanvas[j][z]);	//��ֹԭ�����һ������δ������
	fclose(fp);
}

void ReadRecordFile()  //��ȡ��Ϸ�����ļ��浵
{
	FILE *fp;
	fp = fopen(".\\GameRecord.dat","r");
	fscanf(fp,"%c %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",&avoid,&lastinput,&player_x,&player_y,&FLOOR,&p.Level,&p.Life,&p.Attack,&p.Defence,&p.Exp,&p.GOLD,&p.RKnum,&p.BKnum,&p.YKnum,&p.GKnum,&oldtime,&OwnExcalibur,&isdone,&isgiven,&isgivenG,&bossappear,&isCrystal,&m[2001].life,&m[2001].att,&m[2001].def);
	while( fscanf(fp,"%d %d %d %d\n",&i,&j,&z,&map[i].newcanvas[j][z])!=EOF );
	fclose(fp);
}

void PauseMenu()	//��Ϸ��ʼ�����ͣ�˵����棬��ESC����
{
	cleardevice();	//����
	settextcolor(WHITE);
	settextstyle(50,0, _T("΢���ź�"));
	outtextxy(WIDTH*12, HIGH*9, _T("1 ������Ϸ"));
	outtextxy(WIDTH*12, HIGH*12, _T("2 ���浵��"));
	outtextxy(WIDTH*12, HIGH*15, _T("3 �˳�"));
	FlushBatchDraw();
	
	char input;
	if(_kbhit())  // �ж��Ƿ�������
	{
		input = _getch();  // �����û��Ĳ�ͬ������ִ�ж�Ӧ����
		if (input == '1') 
		{
			start = 1;
			Entrance();
			DrawPlayer(lastinput);
		}
		else if (input == '2')
		{
			WriteRecordFile();
			start = 1;
			Entrance();
			DrawPlayer(lastinput);
		}
		else if (input == '3')
		{
			start = 2;
			exit(0);
		}
	}
}

void startup()				//���ݳ�ʼ��
{
	dialogue=0;				//�Ի�Ϊ0ʱ��������>0ʱ���Ի�������
	FLOOR=3;				//��ʼλ��ħ���⾰�������ڵ�0��
	p.Level=1;				//��ʼ����ȼ�Ϊ1	
	p.Life=1000;			//��ʼ����ֵΪ1000	
	p.Attack=10;			//��ʼ������Ϊ10	
	p.Defence=80;			//��ʼ������Ϊ10
	p.GOLD=0;				//��ʼ���н����Ϊ0
	//p.GOLD=100;	            //�������ݣ���ҳ���100
	p.Exp=0;				//��ʼӵ�о���ֵΪ0
	p.GKnum=0;					
	p.RKnum=0;					
	p.YKnum=0;					
	p.BKnum=0;				//��ʼӵ�и���Կ����Ϊ0	
	OwnExcalibur=1;			//��ʼӵ��ʥ��
	isdone=0;				//0Ϊδִ�н�װ�����Ը������1Ϊ�Ѿ�ִ��
	isscan=0;				//0Ϊδ���ڲ鿴��������״̬�У�1Ϊ�����ڲ鿴״̬
	iscolor=0;				//0Ϊ���δ�����ɵ�����ֲ��֣�������ɫ����1Ϊ��������ִ�б�ɫ��ʾ
	isbattle=0;				//0Ϊδ����ս���У�1Ϊ�����ս������ս������
	battleover=0;			//0Ϊս��δ������1Ϊս������
	bossappear=0;			//0ΪBOSSδ���֣�1Ϊ�Ѿ�����
	isCrystal=1;			//0Ϊ����ʾ��1Ϊ��ʾ
	gameover=0;				//0Ϊ��Ϸδ������1Ϊ��Ϸ����
	isgiven=0;				//0Ϊδ�����κε��ߣ�1Ϊ�����˻�Կ�ף�2Ϊ�����˾����׹
    isgivenG=0;
	//player_x=20;
	//player_y=HIGH-1;		//��ҳ�ʼλ��
	//player_x=20;
	//player_y=5;  //����2�����λ��
	player_x=11;
	player_y=19;  //����3�����λ��
	step=8;					//������Ϊ1/4�ĸ��Ӵ�С
	lastinput='w';			//��ʼΪ��ʾ����泯ǰ
	avoid='w';
	m[1000].life=10;		//����1����ֵΪ10
	m[1000].att=21;			//����1������Ϊ21
	m[1000].def=7;			//����1������Ϊ7
	m[1000].exp=1;			//���ܹ���1��þ���ֵΪ1
	m[1000].Gold=1;			//���ܹ���1��ý��Ϊ1
	m[2001].life=70;		//����2����ֵΪ70
	m[2001].att=63;			//����2������Ϊ60
	m[2001].def=44;			//����2������Ϊ40
	m[2001].exp=5;			//���ܹ���2��þ���ֵΪ5
	m[2001].Gold=5;			//���ܹ���2��ý��Ϊ5
	m[3002].life=90;		//����3����ֵΪ90
	m[3002].att=77;			//����3������Ϊ77
	m[3002].def=54;			//����3������Ϊ54
	m[3002].exp=2;			//���ܹ���3��þ���ֵΪ2
	m[3002].Gold=2;			//���ܹ���3��ý��Ϊ2
	m[3003].life=120;		//����4����ֵΪ120
	m[3003].att=83;			//����4������Ϊ83
	m[3003].def=61;			//����4������Ϊ61
	m[3003].exp=4;			//���ܹ���4��þ���ֵΪ4
	m[3003].Gold=3;			//���ܹ���4��ý��Ϊ3
	m[3004].life=150;		//����5����ֵΪ150
	m[3004].att=99;			//����5������Ϊ99
	m[3004].def=67;			//����5������Ϊ67
	m[3004].exp=6;			//���ܹ���5��þ���ֵΪ6
	m[3004].Gold=5;			//���ܹ���5��ý��Ϊ5
	m[4005].life=250;		//����6����ֵΪ250
	m[4005].att=120;		//����6������Ϊ120
	m[4005].def=75;			//����6������Ϊ75
	m[4005].exp=10;			//���ܹ���6��þ���ֵΪ10
	m[4005].Gold=8;			//���ܹ���6��ý��Ϊ8
	m[9998].life=300;		//BOSS1����ֵΪ300
	m[9998].att=100;		//BOSS1������Ϊ100
	m[9998].def=30;			//BOSS1������Ϊ30
	m[9998].exp=50;			//����BOSS1��þ���ֵΪ50
	m[9998].Gold=30;		//����BOSS1��ý��Ϊ30
	m[9997].life=500;		//BOSS2����ֵΪ500
	m[9997].att=200;		//BOSS2������Ϊ200
	m[9997].def=100;		//BOSS2������Ϊ100
	m[9997].exp=100;		//����BOSS2��þ���ֵΪ100
	m[9997].Gold=50;		//����BOSS2��ý��Ϊ50
	m[9996].life=10000;		//����BOSS����ֵΪ10000
	m[9996].att=5000;		//����BOSS������Ϊ5000
	m[9996].def=5000;		//����BOSS������Ϊ5000
	m[9996].exp=1000;		//��������BOSS��þ���ֵΪ1000
	m[9996].Gold=500;		//��������BOSS��ý��Ϊ500

	for(i=0;i<6;i++)
	{
		for(j=8;j<WIDTH;j++)
		{
			for(z=0;z<HIGH;z++)
			{
				map[i].newcanvas[j][z]=0;	//���»���ȫ����ʼ����ֵΪ0
			}
		}
	}

	initgraph(1024,768);	//���廭����С
	BeginBatchDraw();	
	loadimage(&img_player, _T("E:\\ħ��project\\Resources\\Character\\WarriorB.jpg"));
	loadimage(&_m[0].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-FairyB.jpg"));
	loadimage(&_m[1].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-iceB.jpg"));
	loadimage(&_m[8].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-SpringBossB.jpg"));
	loadimage(&_m[7].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-icebossB.jpg"));
	loadimage(&_m[2].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-PumpkinSingleEyeB.jpg"));
	loadimage(&_m[3].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-PumpkinB.jpg"));
	loadimage(&_m[4].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-PumpkinKingB.jpg"));
	loadimage(&_m[5].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-magicianB.jpg"));
	loadimage(&_m[6].img_mon, _T("E:\\ħ��project\\Resources\\Monster\\Monster-FinalBOSSB.jpg"));
	if(start==0)
	{
		loadimage(&img_bk, _T("E:\\ħ��project\\Resources\\Map\\start.jpg"));
		putimage(0,0, &img_bk);
		FlushBatchDraw();
	}
	else
	{
		Entrance();
		DrawPlayer('w');
		DrawPanel();
		FlushBatchDraw();
	}
	
}

void show()						//��ʾ����
{
	while( start==3 )
	{
		PauseMenu();
	}
	if( isscan==0 )			//��δ�鿴��������ʱ���������ˢ��
	{
		DrawPanel();
	}
	if(start==1&&isdone2==0)
	{
		Entrance();
		DrawPlayer(lastinput);
		DrawPanel();
		isdone2=1;
	}
	FlushBatchDraw();
	Sleep(10);
}

void updateWithoutInput()	//���û������޹صĸ���
{
	if(FLOOR!=0&&OwnExcalibur==1)
	{
       test=1;
	}
	if(start==0&&tips==0)
	{
		loadimage(&img_bk, _T("E:\\ħ��project\\Resources\\Map\\start.jpg"));
		putimage(0,0, &img_bk);
	}
	else if(start==0&&tips==1)
	{
		loadimage(&img_bk, _T("E:\\ħ��project\\Resources\\Map\\tips.jpg"));
		putimage(0,0, &img_bk);
	}

	//�ж�ִ�жԻ�����
	if( dialogue==1 && iscolor==0 )	//�������˵ĶԻ�
	{
		DrawPanel();	//��ֹ�����Ի�ʱ���������߽�������ʾ����ͬ
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(500,480,750,580);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		TCHAR name[] = _T("������");
		outtextxy(503, 483, name);
		settextstyle(16, 0, _T("����"));
		TCHAR d1[] = _T("��������ߣ�����ʧ����Ҫ֮�");
		outtextxy(505,508,d1);
		TCHAR d2[] = _T("Ȼ����Ҫǰ�У�");
		outtextxy(505,529,d2);
		TCHAR yes[] = _T("��");
		outtextxy(593,550,yes);
		TCHAR no[] = _T("��");
		outtextxy(647,550,no);
	}
	if( dialogue==2 && iscolor==0 )	//�뾫��ĶԻ�
	{
		if( isgiven==0 )
		{
			DrawPanel();
			setfillcolor(BLACK);
			setlinecolor(RGB(255,20,180));
			setlinestyle(PS_SOLID ,3);
			fillrectangle(750,100,1000,200);
			settextstyle(20, 0, _T("����"));
			settextcolor(WHITE);
			TCHAR name[] = _T("����");
			outtextxy(753, 103, name);
			settextstyle(16, 0, _T("����"));
			TCHAR d1[] = _T("�ҵ�����Կ����ɢ���������ڣ���");
			outtextxy(755,128,d1);
			TCHAR d2[] = _T("�����������Կ�ף��ҿ���Ϊ����");
			outtextxy(755,149,d2);
			TCHAR d3[] = _T("��һЩ������");
			outtextxy(755,170,d3);
			TCHAR con[] = _T("-��˼���-");
			outtextxy(917,181,con);
		}
		else if( isgiven==1 && (p.YKnum!=1 || p.BKnum!=1 || p.GKnum!=1 || p.RKnum!=1) )
		{
			DrawPanel();
			setfillcolor(BLACK);
			setlinecolor(RGB(255,20,180));
			setlinestyle(PS_SOLID ,3);
			fillrectangle(750,100,1000,200);
			settextstyle(20, 0, _T("����"));
			settextcolor(WHITE);
			TCHAR name[] = _T("����");
			outtextxy(753, 103, name);
			settextstyle(16, 0, _T("����"));
			TCHAR d1[] = _T("�������ҵ�Կ�����������㣬��");
			outtextxy(755,128,d1);
			TCHAR d2[] = _T("��Ķ��Һ���Ҫ����Ȼ�Ҿͻز���");
			outtextxy(755,149,d2);
			TCHAR d3[] = _T("���ˣ���������Ұɣ�");
			outtextxy(755,170,d3);
			TCHAR con[] = _T("-��˼���-");
			outtextxy(917,181,con);
		}
		else if( isgiven==1 && p.YKnum==1 && p.BKnum==1 && p.GKnum==1 && p.RKnum==1 )
		{
			DrawPanel();
			setfillcolor(BLACK);
			setlinecolor(RGB(255,20,180));
			setlinestyle(PS_SOLID ,3);
			fillrectangle(750,100,1000,200);
			settextstyle(20, 0, _T("����"));
			settextcolor(WHITE);
			TCHAR name[] = _T("����");
			outtextxy(753, 103, name);
			settextstyle(16, 0, _T("����"));
			TCHAR d1[] = _T("лл��Ϊ��������Կ�ף������׹");
			outtextxy(755,128,d1);
			TCHAR d2[] = _T("���͸���ɣ�");
			outtextxy(755,149,d2);
			TCHAR con[] = _T("-��˼���-");
			outtextxy(917,181,con);
		}
		else if( isgiven==2 )
		{
			DrawPanel();
			setfillcolor(BLACK);
			setlinecolor(RGB(255,20,180));
			setlinestyle(PS_SOLID ,3);
			fillrectangle(750,100,1000,200);
			settextstyle(20, 0, _T("����"));
			settextcolor(WHITE);
			TCHAR name[] = _T("����");
			outtextxy(753, 103, name);
			settextstyle(16, 0, _T("����"));
			TCHAR d1[] = _T("̫��л���ˣ�Ը��������㣡");
			outtextxy(755,128,d1);
			TCHAR con[] = _T("-��˼���-");
			outtextxy(917,181,con);
		}
	}
	if( dialogue==3 && iscolor==0 )	//�����ߵĶԻ�
	{
		DrawPanel();
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(400,200,650,300);
		settextstyle(20, 0, _T("����"));
		settextcolor(WHITE);
		TCHAR name[] = _T("����");
		outtextxy(403, 203, name);
		settextstyle(16, 0, _T("����"));
		TCHAR d1[] = _T("��˵����ħ���������λ��ʦչ");
		outtextxy(405,228,d1);
		TCHAR d2[] = _T("������ػ������Ȼ��ܴ�ʦ�Ƴ�");
		outtextxy(405,249,d2);
		TCHAR d3[] = _T("��磬ħ���޷����ܡ�");
		outtextxy(405,270,d3);
		TCHAR con[] = _T("-��˼���-");
		outtextxy(567,281,con);
	}
	if( dialogue==4 && iscolor==0 )	//�뿴�Ŵ�ү�ĶԻ�
	{
		DrawPanel();
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(300,600,600,700);
		settextstyle(16, 0, _T("����"));
		settextcolor(WHITE);
		TCHAR name[] = _T("���Ŵ�ү");
		outtextxy(303, 603, name);
		settextstyle(12, 0, _T("����"));
		TCHAR d1[] = _T("  ð���ߣ���ӭ������֮�㣬����������������");
		outtextxy(305,624,d1);
		TCHAR d2[] = _T("ħ�����ڳ�˯��Ҫ�������е�С�����ܻ���ħ����");
		outtextxy(305,644,d2);
		TCHAR d3[] = _T("ħ��������ȡ�����������ٶȣ�ץ��ʱ��ɣ�");
		outtextxy(305,664,d3);
		TCHAR con[] = _T("-��˼���-");
		outtextxy(527,681,con);
	}
	if( dialogue==6 && iscolor==0 )	//���ѩŮ���ĶԻ�
	{
		DrawPanel();
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(300,300,600,400);
		settextstyle(16, 0, _T("����"));
		settextcolor(WHITE);
		TCHAR name[] = _T("��ѩŮ��");
		outtextxy(303, 303, name);
		settextstyle(12, 0, _T("����"));
		TCHAR d1[] = _T("  ð���ߣ���ӭ������֮�㣬����������˥�ܡ�");
		outtextxy(305,324,d1);
		TCHAR d2[] = _T("������Խ���������߶��������������µ�������");
		outtextxy(305,344,d2);
		TCHAR d3[] = _T("��Ĵ�������ȥð�հɣ�");
		outtextxy(305,364,d3);
		TCHAR con[] = _T("-��˼���-");
		outtextxy(527,381,con);
	}
	if( dialogue==5 && iscolor==0 )	//��ɨ�ش���ĶԻ�
	{
		DrawPanel();
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(512,128,790,275);
		settextstyle(16, 0, _T("����"));
		settextcolor(WHITE);
		TCHAR name[] = _T("ɨ�ش���");
		outtextxy(515,131, name);
		settextstyle(12, 0, _T("����"));
		TCHAR d1[] = _T("  ����������ý�Ҷһ����ԣ�����Ҫ������");
		outtextxy(529,148,d1);
		TCHAR d2[] = _T("     �ײ�һ +50���� 10��     BUY");
		outtextxy(515,165,d2);
		TCHAR d3[] = _T("     �ײͶ� +10���� 10��     BUY");
		outtextxy(515,195,d3);
		TCHAR d4[] = _T("     �ײ��� +10���� 10��     BUY");
		outtextxy(515,225,d4);
		TCHAR con[] = _T("-��˼���-");
		outtextxy(720,255,con);
	}
	if(OwnExcalibur && isdone==0)	//����ʥ��ʱ��������
	{
		p.Attack += 1000;
		isdone=1;
		DrawPanel();
	}
	if(OwnExcalibur==0 && isdone)	//ʧȥʥ��ʱ���Իָ�
	{
		p.Attack -= 1000;
		isdone=0;
		p.RKnum=1;
		DrawPanel();
	}
	if( player_x==20 && player_y==0 && FLOOR==0 )	//��0��ʱ����1���ת��
	{
		player_x=9;
		player_y=21;
		FLOOR=1;
		Entrance();
		DrawPlayer('d');
		lastinput='d';
		FlushBatchDraw();
	}
	else if( player_x==9 && player_y==22 && FLOOR==1 )	//��1��ʱ����0���ת��
	{
		player_x=20;
		player_y=1;
		timestart=0;
		FLOOR=0;
		Entrance();
		DrawPlayer('s');
		lastinput='s';
		FlushBatchDraw();
	}
	else if( player_x==12 && player_y==5 && FLOOR==1 && isCrystal )	//��1��ʱ����2���ת��
	{
		player_x=9;
		player_y=2;
		FLOOR=2;
		Entrance();
		DrawPlayer('s');
		lastinput='s';
		FlushBatchDraw();
		//move=1;
	}
	else if( player_x==9 && player_y==1 && FLOOR==2 )	//��2��ʱ����1���ת��
	{
		player_x=13;
		player_y=5;
		FLOOR=1;
		Entrance();
		DrawPlayer('d');
		lastinput='d';
		FlushBatchDraw();
	}
	else if( player_x==11 && player_y==21 && FLOOR==2 )	//��2��ʱ���������ת��
	{
		player_x=11;
		player_y=19;
		FLOOR=3;
		Entrance();
		DrawPlayer('w');
		lastinput='w';
		FlushBatchDraw();
	}
	else if( player_x==11 && player_y==20 && FLOOR==3 )	//�ڶ���ʱ����2���ת��
	{
		player_x=12;
		player_y=21;
		FLOOR=2;
		Entrance();
		DrawPlayer('d');
		lastinput='d';
		FlushBatchDraw();
	}
	if(FLOOR==2)//ʵ�ֶ�֮��˥������
	{
		if(move==1)
			go=1;
		if(counter2%10==0&&go==1)
		{	
			if(p.Life>200)
			p.Life=p.Life-(p.Life*counter2)/1000;
			
			if(p.Attack>10)
			p.Attack=p.Attack-(p.Attack*counter2)/500;
			
			if(p.Defence>10)
			p.Defence=p.Defence-(p.Defence*counter2)/500;

			if(p.Life<=200) {p.Life=200;counter2=0;}
			if(p.Attack<=10){p.Attack=10;counter2=0;}
			if(p.Defence<=10){p.Defence=10;counter2=0;}
			DrawPanel();
			go=0;
			move=-move;
		}
	    }
	if(FLOOR==1)//ʵ�ִ�֮�㡰����������
	{
		int num=canvas[player_x][player_y];	//�洢�����Ӧֵ
		m[num].life=m[num].life+m[num].life*(time/60)/3;
		m[num].att=m[num].att+m[num].att*(time/60)/20;
		m[num].def=m[num].def+m[num].def*(time/60)/10;
		LIFE=m[num].life;
	}
	
	if ( isbattle )	//����ս������
	{
		int num=canvas[player_x][player_y];	//�洢�����Ӧֵ
		LIFE=m[num].life;	//�洢��������ֵ
		DrawCombatInterface(num);
		FlushBatchDraw();
		delay(1000);
		while( m[num].life>0 && p.Life>0 )	//ֻҪ������������ֵΪ����ս������
		{
			char input;
			if( _kbhit() )
			{
				input=_getch();
				if( input=='q' )
				{
					battleover=1;
					m[num].life=LIFE;	//���ù�������ֵ����ֹ��һ��ս����ͬ���������ֵΪ0
					break;
				}
			}
			if( m[num].att-p.Defence>0 )
				p.Life-=(m[num].att-p.Defence);
			if( m[num].def<p.Attack )
				m[num].life-=(p.Attack-m[num].def);
			DrawCombatInterface(num);
			FlushBatchDraw();
			delay(1000);
		}
		if( battleover==0 )
		{
			p.Exp+=m[num].exp;	//��û��ܹ���Ӧ�þ���ֵ
			p.GOLD+=m[num].Gold;	//��û��ܹ���Ӧ�ý����
			canvas[player_x][player_y]=1;
			map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�¹��ﱻ����
			m[num].life=LIFE;	//���ù�������ֵ����ֹ��һ��ս����ͬ���������ֵΪ0
			battleover=1;	//ս��������־
		}	
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}

	if(m[9998].life<=0)
	{
		if(isgivenG==0)
		{
			setfillcolor(BLACK);
			setlinecolor(RGB(255,20,180));
			setlinestyle(PS_SOLID ,3);
			fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
			settextcolor(LIGHTRED);
			settextstyle(20, 0, _T("����"));
			TCHAR d1[] = _T("�����Կ�ף�");
			outtextxy(player_x*32-70,player_y*32-10,d1);
			FlushBatchDraw();
			delay(500);
		p.GKnum+=1;
		DrawPanel();
		isgivenG=1;
		}
	}
	if(canvas[player_x][player_y]==10)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��ö̽���");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Attack+=10;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==11)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("���ľ�ܣ�");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Defence+=10;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==12)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��ú챦ʯ��");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Attack+=2;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==13)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("�������ʯ��");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(1000);
		p.Defence+=2;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==20)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��ú�ҩˮ��");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Life+=50;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==30)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("�����ҩˮ��");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Life+=100;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==21)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��þ��ֽ���");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Attack+=20;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==22)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��øֶܣ�");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Defence+=20;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==31)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��þ��׽���");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Attack+=50;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==32)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("��������ף�");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.Defence+=50;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
	if(canvas[player_x][player_y]==25)
	{
		setfillcolor(BLACK);
		setlinecolor(RGB(255,20,180));
		setlinestyle(PS_SOLID ,3);
		fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
		settextcolor(LIGHTRED);
		settextstyle(20, 0, _T("����"));
		TCHAR d1[] = _T("�����Կ�ף�");
		outtextxy(player_x*32-70,player_y*32-10,d1);
		FlushBatchDraw();
		delay(500);
		p.BKnum+=1;
		canvas[player_x][player_y]=0;
		map[FLOOR].newcanvas[player_x][player_y]=1;	//��¼�µ��߱�ʰȡ
		DrawPanel();
		DrawWithoutPlayer();
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
   if(canvas[player_x][player_y]==10006)//������ת��1-1
	{
		player_x=13;
		player_y=21;
		//DrawTransfermatrix();
		DrawPanel();
		DefineTransfermatrix();
		DrawWithoutPlayer();
		canvas[13][21]=0;		//��ֹ�����ͻ�ȥ����ͬ
		DrawPlayer(lastinput);	//���»������н���
		FlushBatchDraw();
	}
   if( canvas[player_x][player_y]==10009)//������ת��1-2
   {
	   player_x=19;
	   player_y=5;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[19][5]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10007)//������ת��2-1
   {
	   player_x=11;
	   player_y=11;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[11][11]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10008)//������ת��2-2
   {
	   player_x=30;
	   player_y=14;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[30][14]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10010)//������ת��3-1
   {
	   player_x=13;
	   player_y=5;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[13][5]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10011)//������ת��3-2
   {
	   player_x=13;
	   player_y=20;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[13][20]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10012)//������ת��3-3
   {
	   player_x=24;
	   player_y=16;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[24][16]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10013)//������ת��3-4
   {
	   player_x=15;
	   player_y=5;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[15][5]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10014)//������ת��3-5
   {
	   player_x=19;
	   player_y=11;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[19][11]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }
   if( canvas[player_x][player_y]==10015)//������ת��3-6
   {
	   player_x=24;
	   player_y=14;
	   //DrawTransfermatrix();
	   DrawPanel();
	   DefineTransfermatrix();
	   DrawWithoutPlayer();
	   canvas[24][14]=0;
	   DrawPlayer(lastinput);	//���»������н���
	   FlushBatchDraw();
   }

	if( p.Exp>=p.Level*10 )	//����ֵ�ﵽ��ǰ�ȼ�10�ı���ʱ����
	{
		p.Exp-=p.Level*10;	//��ȥ�������辭��ֵ
		p.Level++;	//�ȼ�����
		p.Life+=50;	//����ʱ����ֵ���50
		p.Attack++;	//����ʱ���������1
		p.Defence++;	//����ʱ���������1
		DrawPanel();
		FlushBatchDraw();
	}

	if( FLOOR==1 )
	{
		int boss=1;	//�ж�ִ��BOSS�Ƿ����
		for(i=0;i<WIDTH;i++)
		{
			for(j=0;j<HIGH;j++)
			{
				if( canvas[i][j]==1000 )
				{
					boss=0;	//��������������δ�����ʱ��BOSS������
				}
			}
		}
		if( boss && bossappear==0 )	//���»��ƹ����BOSS����
		{
			canvas[13][5]=9998;
			map[FLOOR].newcanvas[13][5]=9998;//��¼��BOSS����
			DrawMonster();
			bossappear=1;
			isCrystal=1;
			DrawCrystal();
			FlushBatchDraw();
		}
	}

	if( FLOOR==3 )
	{
		int boss=5;	//�ж�ִ��BOSS�Ƿ�������5Ϊ��ȫ������1Ϊ��ǿǿ��״̬
		for(i=0;i<WIDTH;i++)
		{
			for(j=0;j<HIGH;j++)
			{
				if( canvas[i][j]==4005 )
				{
					boss--;	//�������ʦ����ʱ��BOSS�Ծɱ�ǿ��
				}
			}
		}
		if( boss )	//���¶���������ԣ�����BOSS
		{
			m[9996].life=10000/boss;	//����BOSS����ֵ�����ܴ�ʦ������
			m[9996].att=5000/boss;		//����BOSS�����������ܴ�ʦ������
			m[9996].def=5000/boss;		//����BOSS�����������ܴ�ʦ������
		}
		if( boss==5 )	//��ȫ����
		{
			m[9996].life=1000;			//����BOSS����ֵ��ȫ������Ϊ1000
			m[9996].att=250;			//����BOSS��������ȫ������Ϊ250
			m[9996].def=250;			//����BOSS��������ȫ������Ϊ250
		}
	}

	if( p.Life<=0 )	//�������ֵ��������Ϸ����
	{
		gameover=1;
	}

	if( gameover )	//��Ϸ������ʾ
	{
		cleardevice();	//��ջ���
		settextcolor(RED);
		settextstyle(64, 0, _T("����"));
		RECT r = {0, 0, 1024, 768};
		drawtext(_T("Game Over!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//������Ϸ������Ϣ
		FlushBatchDraw();
		EndBatchDraw();
		_getch();	//�����������
		closegraph();	//�رջ���
		exit(0);	//�˳���Ϸ
	}
}

void updateWithInput()		//���û������йصĸ��� 
{
	char input;
	MOUSEMSG m; 
	while(_kbhit())
	{
		DefineTransfermatrix();
		input=_getch();
		if(start==0)
		{
			if(input=='1'&&tips==0)	//����1��ʼ��Ϸ
				start=1;
			else if( input=='2' )	//����2����
			{
				ReadRecordFile();
				start=1;
				Entrance();
				DrawPanel();
				DrawPlayer(lastinput);
			}
			else if(input=='3')	//����3������ʾ����
				tips=1;
		}
		if(tips==1)
		{
			if(input=='z')	//����z���س�ʼ����
				tips=0;
		}
		if(OwnExcalibur==0)	//�����ã���n�����»��ʥ��
		{
			if(input=='n')
				OwnExcalibur=1;
		}
		if(FLOOR==1)
		{
			if(timestart==0)
			{
				GetLocalTime(&ti);
				oldtime=ti.wSecond +ti.wMinute*60+ti.wHour*3600;
				timestart=1;
			}
			
			if(timestart==1)
			{
				GetLocalTime(&ti);// ��ȡ��ǰʱ��
				newtime= ti.wSecond +ti.wMinute*60+ti.wHour*3600;  // ��������
			    time=newtime-oldtime;
			}
		}
		else if(FLOOR==2)
		{
			counter2+=1;
			move=-move;
		}
		if( input=='w' || input=='s' || input=='a' || input=='d' )
			lastinput=input;	//��¼��һ�����߰���
		if( dialogue==0 && isbattle==0 )		//���޶Ի�����ս������½������ߡ��Ի�������ͣ�����ж�
		{
			if( input==27 )	//����ESC����ACSII��Ϊ27��������ͣ����
			{
				start=3;
			}
			else if( input=='w' )
			{
				DrawWithoutPlayer();	//ÿ������ǰ�ó�����������ͼ��ˢ��
				DrawPlayer('w');	//�����Ƿ�ִ�����߶�������Ҫ����ת����������ת������֮��ͬ��
				if( canvas[player_x][player_y-1]==9999 )	//����������
				{
					dialogue=1;
				}
				else if( canvas[player_x][player_y-1]==100 )	//�뾫��Ի�
				{
					dialogue=2;
				}
				else if( canvas[player_x][player_y-1]==101 )	//�����߶Ի�
				{
					dialogue=3;
				}
				else if( canvas[player_x][player_y-1]==102 )	//���޹ܴ���Ի�
				{
					dialogue=5;
				}
			/*	else if( canvas[player_x][player_y-1]==4 )
				{
				}*/
				else if( canvas[player_x][player_y-1]!=2 && player_y>0 )		//������ʱǰ����Ϊǽ����δԽ�������ϱ߽磬ִ�����߶������������߶�����֮�������ж�����ͬ��
				{
					DrawWithoutPlayer();	//ÿ���ƶ��ó���������ͼ��ˢ������ͬ
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking11.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking11.jpg"));
					putimage(player_x*32, player_y*32-step, &img_player1,NOTSRCERASE);
					putimage(player_x*32, player_y*32-step, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();		//ÿ���ƶ������ƣ���ֹ�ƶ��������ɼ�����ͬ
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking10.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking10.jpg"));
					putimage(player_x*32, player_y*32-step*2, &img_player1,NOTSRCERASE);
					putimage(player_x*32, player_y*32-step*2, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking12.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking12.jpg"));
					putimage(player_x*32, player_y*32-step*3, &img_player1,NOTSRCERASE);
					putimage(player_x*32, player_y*32-step*3, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					player_y--;		//ÿ���ƶ�Ϊһ�񣬽����һ���ƶ��ı����λ�ã�֮��ͬ
					DrawPlayer('w');
					delay(1);
					FlushBatchDraw();
					if( canvas[player_x][player_y]==9 || canvas[player_x][player_y]==4005 )	//����ƶ�������·���ڸ�ʱ������ֵ������ͬ
					{
						p.Life-=50;
						DrawPanel();
					}
					if( canvas[player_x][player_y]>=1000 && canvas[player_x][player_y]<=9998 )	//����ƶ����������ڸ�ʱ������ս������ͬ
					{
						isbattle=1;
					}
				}
			}
			else if( input=='s' )
			{
				DrawWithoutPlayer();
				DrawPlayer('s');
				if( canvas[player_x][player_y+1]==103)	//�뿴�Ŵ�ү�Ի�
				{
					dialogue=4;
				}
			/*	if( canvas[player_x][player_y+1]==4 )
				{
				}*/
				else if( canvas[player_x][player_y+1]!=2 && player_y<HIGH-1 )
				{
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking02.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking02.jpg"));
					putimage(player_x*32, player_y*32+step, &img_player1,NOTSRCERASE);
					putimage(player_x*32, player_y*32+step, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior01.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior01.jpg"));
					putimage(player_x*32, player_y*32+step*2, &img_player1,NOTSRCERASE);
					putimage(player_x*32, player_y*32+step*2, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking03.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking03.jpg"));
					putimage(player_x*32, player_y*32+step*3, &img_player1,NOTSRCERASE);
					putimage(player_x*32, player_y*32+step*3, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					player_y++;
					DrawPlayer('s');
					delay(1);
					FlushBatchDraw();
					if( canvas[player_x][player_y]==9 || canvas[player_x][player_y]==4005 )	//����ƶ�������·���ڸ�ʱ������ֵ������ͬ
					{
						p.Life-=50;
						DrawPanel();
					}
					if( canvas[player_x][player_y]>=1000 && canvas[player_x][player_y]<=9998 )
					{
						isbattle=1;
					}
				}
			}
			else if( input=='a' )
			{
				DrawWithoutPlayer();
				DrawPlayer('a');
				if( canvas[player_x-1][player_y]==9999 )	//���������Ӵ������ˣ�����������
				{

				}
				else if( canvas[player_x-1][player_y]==104)	//���ѩŮ���Ի�
				{
					dialogue=6;
				}
				
			/*	else if( canvas[player_x-1][player_y]==4 )
				{
				} */
				else if( canvas[player_x-1][player_y]!=2  && player_x>0 )
				{
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking05.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking05.jpg"));
					putimage(player_x*32-step, player_y*32, &img_player1,NOTSRCERASE);
					putimage(player_x*32-step, player_y*32, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking04.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking04.jpg"));
					putimage(player_x*32-step*2, player_y*32, &img_player1,NOTSRCERASE);
					putimage(player_x*32-step*2, player_y*32, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking06.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking06.jpg"));
					putimage(player_x*32-step*3, player_y*32, &img_player1,NOTSRCERASE);
					putimage(player_x*32-step*3, player_y*32, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					player_x--;
					DrawPlayer('a');
					delay(1);
					FlushBatchDraw();					
					if( canvas[player_x][player_y]==9 || canvas[player_x][player_y]==4005 )	//����ƶ�������·���ڸ�ʱ������ֵ������ͬ
					{
						p.Life-=50;
						DrawPanel();
					}
					if( canvas[player_x][player_y]>=1000 && canvas[player_x][player_y]<=9998 )
					{
						isbattle=1;
					}
				}
			}
			else if( input=='d' )
			{
				DrawWithoutPlayer();
				DrawPlayer('d');
				if( canvas[player_x+1][player_y]==9999 )	//���������Ӵ������ˣ�����������
				{

				}
			/*	else if( canvas[player_x+1][player_y]==4 )
				{
				}*/
				else if( canvas[player_x+1][player_y]==103)	//�뿴�Ŵ�ү�Ի�
				{
					dialogue=4;
				}
				else if( canvas[player_x+1][player_y]!=2 && player_x<WIDTH-1 )
				{
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking08.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking08.jpg"));
					putimage(player_x*32+step, player_y*32, &img_player1,NOTSRCERASE);
					putimage(player_x*32+step, player_y*32, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking07.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking07.jpg"));
					putimage(player_x*32+step*2, player_y*32, &img_player1,NOTSRCERASE);
					putimage(player_x*32+step*2, player_y*32, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					loadimage(&img_player1, _T("E:\\ħ��project\\Resources\\Character\\_Warrior-Walking09.jpg"));
					loadimage(&img_player2, _T("E:\\ħ��project\\Resources\\Character\\Warrior-Walking09.jpg"));
					putimage(player_x*32+step*3, player_y*32, &img_player1,NOTSRCERASE);
					putimage(player_x*32+step*3, player_y*32, &img_player2,SRCINVERT);
					delay(1);
					FlushBatchDraw();
					DrawWithoutPlayer();
					player_x++;
					DrawPlayer('d');
					delay(1);
					FlushBatchDraw();					
					if( canvas[player_x][player_y]==9 || canvas[player_x][player_y]==4005 )	//����ƶ�������·���ڸ�ʱ������ֵ������ͬ
					{
						p.Life-=50;
						DrawPanel();
					}
					if( canvas[player_x][player_y]>=1000 && canvas[player_x][player_y]<=9998 )
					{
						isbattle=1;
					}
				}		
			}
			else if( input=='x' && OwnExcalibur )	//ӵ��ʥ��ʱ��Xһ��������������
			{
				for(i=0;i<WIDTH;i++)
				{
					for(j=0;j<HIGH;j++)
					{
						if( canvas[i][j]>=1000 && canvas[i][j]<=9999 )
						{
							canvas[i][j]=1;			
						}
					}
				}
				DrawWithoutPlayer();
				FlushBatchDraw();
			}
		}
	}
	if( battleover && isbattle )	//��ֹ��ս���а�����������ս���������Զ��ƶ�
	{
		isbattle=0;	
		battleover=0;	//����ս��
	}
	while(MouseHit())
	{
		m = GetMouseMsg();
		if( dialogue==0 && isbattle==0 )	//���޶Ի�����ս��������ܹ��鿴��������
		{
			if( m.x>=32 && m.y>=672 && m.y<=704 && m.x<=64 && OwnExcalibur && isscan==0 )
			{
				DrawPanel();
				setfillcolor(BLACK);
				setlinecolor(RGB(255,20,180));
				setlinestyle(PS_SOLID ,3);
				fillrectangle(m.x,m.y,m.x+180,m.y+70);
				settextstyle(20, 0, _T("����"));
				TCHAR name[] = _T("ʥ��");
				outtextxy(m.x+3,m.y+3,name);
				settextstyle(16, 0, _T("����"));
				TCHAR i1[] = _T("��ǿ֮����");
				outtextxy(m.x+5,m.y+28,i1);
				TCHAR i2[] = _T("�����߹�����+1000��");
				outtextxy(m.x+5,m.y+49,i2);
				isscan=1;	//���Ϊ���ڲ鿴��������״̬
			}
			else
			{
				isscan=0;	//����ƿ����Ϊ�ǲ鿴��������״̬
			}
		}
		else if( dialogue==1 )	//�����������˶Ի�������Ϸ
		{
			if( m.x>=593 && m.y>=550 && m.y<=566 && m.x<=609 )	//����ƶ������ǡ��֣������ɫ����ʾ
			{			
				settextcolor(RED);
				settextstyle(16, 0, _T("����"));
				TCHAR yes[] = _T("��");
				outtextxy(593,550,yes);
				iscolor=1;	//��ɫ��ʾ��ҵ������ͬ
				if( m.uMsg==WM_LBUTTONDOWN )	//����Ի����ǡ��Ĳ��֣������˺�����ʧ����ʧȥʥ��
				{
					canvas[20][16]=1;
					canvas[20][15]=1;
					map[FLOOR].newcanvas[20][16]=1;
					map[FLOOR].newcanvas[20][15]=1;	//��¼�������˺�����ʧ
					DefineBackground();
					DrawBackground();
					DefineRoad();
					DrawRoad();
					DefineWall();
					DrawWall();
					DefineNPC();
					DrawNPC();
					DrawPlayer('w');
					DefineCrystal();
					DrawCrystal();
					setfillcolor(BLACK);
					setlinecolor(RGB(255,20,180));
					setlinestyle(PS_SOLID ,3);
					fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
					settextcolor(GREEN);
					settextstyle(20, 0, _T("����"));
					TCHAR d1[] = _T("��ú�Կ�ף�");
					outtextxy(player_x*32-70,player_y*32-10,d1);
					FlushBatchDraw();
					delay(500);
					DefineBackground();
					DrawBackground();
					DefineRoad();
					DrawRoad();
					DefineWall();
					DrawWall();
					DefineNPC();
					DrawNPC();
					DrawPlayer('w');
					DefineCrystal();
					DrawCrystal();
					dialogue=0;
					OwnExcalibur=0;
				}
			}
			else if( m.x>=647 && m.y>=550 && m.y<=566 && m.x<=663 )	//����ƶ��������֣������ɫ����ʾ
			{			
				settextcolor(RED);
				settextstyle(16, 0, _T("����"));
				TCHAR no[] = _T("��");
				outtextxy(647,550,no);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )	//����Ի��򡰷񡱵Ĳ��֣��ָ�ԭ״
				{
					Entrance();
					DrawPlayer('w');
					dialogue=0;
				}
			}
			else
			{
				iscolor=0;	//����ƿ���ָ�ԭɫ����ͬ
			}
		}
		else if( dialogue==2 )	//�����뾫��Ի�������Ϸ
		{
			
			if( m.x>=917 && m.y>=181 && m.y<=197 && m.x<=997 )	//����ƶ������������֡��������ɫ����ʾ����ͬ
			{			
				settextcolor(RED);
				settextstyle(16, 0, _T("����"));
				TCHAR con[] = _T("-��˼���-");
				outtextxy(917,181,con);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )	//����Ի��򡰼��������֣���Ϸ��������ͬ
				{
					if(isgiven==0)
					{
						DefineBackground();
						DrawBackground();
						DefineRoad();
						DrawRoad();
						DefineWall();
						DrawWall();
						DefineNPC();
						DrawNPC();
						DrawPlayer('w');
						DefineCrystal();
						DrawCrystal();
						setfillcolor(BLACK);
						setlinecolor(RGB(255,20,180));
						setlinestyle(PS_SOLID ,3);
						fillrectangle(player_x*32-100,player_y*32-25,player_x*32+100,player_y*32+25);
						settextcolor(GREEN);
						settextstyle(20, 0, _T("����"));
						TCHAR d1[] = _T("��û�Կ�ף�");
						outtextxy(player_x*32-70,player_y*32-10,d1);
						FlushBatchDraw();
						delay(500);
						p.YKnum=1;
						isgiven=1;
					}
				    else if(p.YKnum==1&&p.BKnum==1&&p.GKnum==1&&p.RKnum==1)
					{
						p.YKnum=0;
						p.BKnum=0;
						p.GKnum=0;
						p.RKnum=0;
						DrawPanel();
						DrawBackground();
						DefineRoad();
						DrawRoad();
						DefineWall();
						DrawWall();
						DefineNPC();
						DrawNPC();
						DefineCrystal();
						DrawCrystal();
						DrawPlayer('w');
						setfillcolor(BLACK);
						setlinecolor(RGB(255,20,180));
						setlinestyle(PS_SOLID ,3);
						fillrectangle(750,200,1000,250);
						settextcolor(GREEN);
						settextstyle(20, 0, _T("����"));
						TCHAR d1[] = _T("��þ����׹��");
						outtextxy(800,215,d1);
						FlushBatchDraw();
						delay(2000);
					    p.Life+=500;
						p.Attack+=100;
						p.Defence+=100;
						DrawPanel();
						dialogue=0;
						isgiven=2;
					}
					DrawBackground();
					DefineRoad();
					DrawRoad();
					DefineWall();
					DrawWall();
					DefineNPC();
					DrawNPC();
					DefineCrystal();
					DrawCrystal();
					DrawPlayer('w');
					DrawPanel();
					dialogue=0;
				}
			}
			else
			{
				iscolor=0;
			}
		}
		else if( dialogue==3 )	//���������߶Ի�������Ϸ
		{
			if( m.x>=567 && m.y>=281 && m.y<=297 && m.x<=647 )
			{			
				settextcolor(RED);
				settextstyle(16, 0, _T("����"));
				TCHAR con[] = _T("-��˼���-");
				outtextxy(567,281,con);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					DrawBackground();
					DefineRoad();
					DrawRoad();
					DefineWall();
					DrawWall();
					DefineNPC();
					DrawNPC();
					DefineCrystal();
					DrawCrystal();
					DrawPlayer('w');
					dialogue=0;
				}
			}
			else 
			{
				iscolor=0;
			}
		}
		else if( dialogue==4)	//�����뿴�Ŵ�ү�Ի�������Ϸ
			{
				if( m.x>=527 && m.y>=681 && m.y<=687 && m.x<=607 )
				{			
					settextcolor(RED);
					settextstyle(12, 0, _T("����"));
					TCHAR con[] = _T("-��˼���-");
					outtextxy(527,681,con);
					iscolor=1;
					if( m.uMsg==WM_LBUTTONDOWN )
					{
						DrawBackground();
						DefineWall();
						DrawWall();
						DefineNPC();
						DrawNPC();
						DefineCrystal();
						DrawCrystal();
						DrawMonster();
						Drawitems();
						DrawPlayer(lastinput);
						dialogue=0;
					}
				}
				else 
			{
				iscolor=0;
			}
		}

		else if( dialogue==5)	//������ɨ�ش���Ի�
		{
			if( m.x>=720 && m.y>=255 && m.y<=267 && m.x<=750 )
			{			
				settextcolor(RED);
				settextstyle(12, 0, _T("����"));
				TCHAR con[] = _T("-��˼���-");
				outtextxy(720,255,con);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					DrawBackground();
					DefineWall();
					DrawWall();
					DefineNPC();
					DrawNPC();
					DefineCrystal();
					DrawCrystal();
					DrawMonster();
					Drawitems();
					DrawPlayer(lastinput);
					dialogue=0;
				}
			}
			else if( m.x>=690 && m.y>=165 && m.y<=177 && m.x<=710 )
			{			
				settextcolor(RED);
				settextstyle(12, 0, _T("����"));
				TCHAR d2[] = _T("BUY");
				outtextxy(689,165,d2);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					if(p.GOLD>=10)
					{
						p.Life+=50;
						p.GOLD-=10;
						DrawBackground();
						DefineWall();
						DrawWall();
						Drawitems();
						DefineNPC();
						DrawNPC();
						DrawMonster();
						DefineCrystal();
						DrawCrystal();
						DrawPlayer(lastinput);
						dialogue=0;
					}
				}
			}
			else if( m.x>=690 && m.y>=165 && m.y<=177 && m.x<=710 )
			{			
				settextcolor(RED);
				settextstyle(12, 0, _T("����"));
				TCHAR d2[] = _T("BUY");
				outtextxy(689,165,d2);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					if(p.GOLD>=10)
					{
						p.Life+=50;
						p.GOLD-=10;
						DrawBackground();
						DefineWall();
						DrawWall();
						Drawitems();
						DefineNPC();
						DrawNPC();
						DrawMonster();
						DefineCrystal();
						DrawCrystal();
						DrawPlayer(lastinput);
						dialogue=0;
					}
				}
			}
			}
			else if( m.x>=690 && m.y>=195 && m.y<=207 && m.x<=710 )
			{			
				settextcolor(RED);
				settextstyle(12, 0, _T("����"));
				TCHAR d2[] = _T("BUY");
				outtextxy(689,195,d2);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					if(p.GOLD>=10)
					{
						p.Attack+=10;
						p.GOLD-=10;
						DrawBackground();
						DefineWall();
						DrawWall();
						Drawitems();
						DefineNPC();
						DrawNPC();
						DrawMonster();
						DefineCrystal();
						DrawCrystal();
						DrawPlayer(lastinput);
						dialogue=0;
					}
				}
			}
			else if( m.x>=690 && m.y>=225 && m.y<=237 && m.x<=710 )
			{			
				settextcolor(RED);
				settextstyle(12, 0, _T("����"));
				TCHAR d2[] = _T("BUY");
				outtextxy(689,225,d2);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					if(p.GOLD>=10)
					{
						p.Defence+=10;
						p.GOLD-=10;
						DrawBackground();
						DefineWall();
						DrawWall();
						Drawitems();
						DefineNPC();
						DrawNPC();
						DrawMonster();
						DefineCrystal();
						DrawCrystal();
						DrawPlayer(lastinput);
						dialogue=0;
					}
				}
				else 
				{
					iscolor=0;
				}
			}

			else if(dialogue==6)
			{
				if( m.x>=527 && m.y>=381 && m.y<=393 && m.x<=547)
				{			
				settextcolor(RED);
				settextstyle(12, 0, _T("����"));
				TCHAR con[] = _T("-��˼���-");
				outtextxy(527,381,con);
				iscolor=1;
				if( m.uMsg==WM_LBUTTONDOWN )
				{
					
						DrawBackground();
						DefineWall();
						DrawWall();
						Drawitems();
						DefineNPC();
						DrawNPC();
						DrawMonster();
						DefineCrystal();
						DrawCrystal();
						DrawPlayer(lastinput);
						dialogue=0;
				}
				}
				else 
				{
					iscolor=0;
				}
			}

		}
	}

void main()
{

	startup();
	while(1)				//��Ϸѭ��ִ�� 
	{
		show();
		updateWithoutInput();
		updateWithInput();	
	}
	EndBatchDraw();
	_getch();
	closegraph();
}

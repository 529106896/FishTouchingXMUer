#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
float man_x;						//��������ĺ�����
float man_y;						//���������������
float man_vy_begin;					//��������Ĵ�ֱ�������ٶ�
float man_vx;						//���������ˮƽ�ٶ�
float man_vy;						//���������ʵʱ��ֱ�ٶ�
float a_vy;							//���崹ֱ�ٶȷ�����������ٶ�
int sky_if;							//����������ڼ�������״̬ ����״̬Ϊ1 �ǿ���״̬Ϊ0 ֻ�е��ǿ���״̬ʱ�ſ��԰���w������ ����״̬����������
float bullet_x[4],bullet_y[4];		//�����ͼ�Զ�������ӵ�������
float bullet_vx[4],bullet_vy[4];	//�����ͼ�Զ�������ӵ����ٶ�
float bullet_v1,bullet_v0;			//���������ٶ����
int shoot_time;						//�����������ʵ�����ӵ��̶�ʱ��η���һ��
int shoot_if;						//����������������ӵ���÷���һ��
int live;							//����������ڼ������������״̬
int walk_left;							//���ھ����ò�����һ��ͼƬ(��)
int walk_right;							//���ھ����ò�����һ��ͼƬ���ң�
IMAGE img_bk;						//���� IMAGE ���� ����
IMAGE img_man;						//���� IMAGE ���� ����
IMAGE walk_r;						//�����ߵĶ���
IMAGE walk_l;						//�����ߵĶ���
IMAGE walk_rz;						//�����ߵĶ������ֲ�
IMAGE walk_lz;						//�����ߵĶ������ֲ�
IMAGE zhezhao;
IMAGE img_bullet;					//���� IMAGE ���� ��ͼ�Զ������ӵ�
IMAGE img_start;	//���� IMAGE ����  ��ʼ����
IMAGE img_pause;    //���� IMAGE ����  ��ͣ����
int gameStatus=0;//��Ϸ״̬��0Ϊ��ʼ�˵����棬1Ϊ������Ϸ��2Ϊ������Ϸ״̬��3Ϊ��Ϸ��ͣ
void readRecordFile()  //��ȡ��Ϸ�����ļ��浵
{
	FILE *fp;
	fp = fopen(".\\gameRecord.dat","r");
	fscanf(fp,"%f %f %f %f",&man_x,&man_y,&bullet_x,&bullet_y);
	fclose(fp);
}
void writeRecordFile()  //�洢��Ϸ�����ļ��浵
{
	FILE *fp;
	fp = fopen(".\\gameRecord.dat","w");
	fprintf(fp,"%f %f %f %f",man_x,man_y,bullet_x,bullet_y);
	fclose(fp);
}
void startMenu() // ��ʼ�˵�����
{	
	putimage(0, 0, &img_start);//��ʾ����
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == '1') 
			gameStatus = 1;
		else if (input == '2')
		{
			readRecordFile();
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 2;
			exit(0);
		}
	}
}
void pauseMenu() // ��Ϸ��ͣ��˵����棬һ�㰴ESC���������ý���
{
	putimage(0, 0, &img_pause);	// ��ʾ����	
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == '1') 
			gameStatus = 1;
		else if (input == '2')
		{
			writeRecordFile();
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 2;
			exit(0);
		}
	}
}
void begining()						//��Ϸ��ʼ��ģ��
{
	man_x=100;
	man_y=633;
	man_vx=2;
	man_vy_begin=-6.5;
	man_vy=0;
	shoot_time=0;
	shoot_if=180;
	live=1;
	walk_left=0;						
	walk_right=0;

	bullet_v1=5;
	bullet_v0=0;
	int i;
	for(i=0;i<4;i++)
	{
		bullet_x[i]=bullet_y[i]=50;
		bullet_vx[i]=bullet_v1;
		bullet_vy[i]=bullet_v0;
	}
	
	a_vy=0.24;
	sky_if=0;
	loadimage(&img_bk, ".\\��ɫҩˮ�ڰ˹�.jpg",696,696);						// ��ȡ����ͼƬ�� img_bk ������
	loadimage(&img_man,".\\�ҵ�ҩˮ.jpg",37,37);			//��ȡ����ͼƬ��img_man ������
	loadimage(&zhezhao,".\\���ֲ�.jpg",37,37);			//��ȡ����ͼƬ��img_man ������
	loadimage(&walk_l,".\\����.jpg");								//��ȡ����ͼƬ��walk_l ������
	loadimage(&walk_lz,".\\2.jpg");								//��ȡ����ͼƬ��walk_lz ������
	loadimage(&img_bullet,".\\�ӵ�.jpg",30,30);					//��ȡ�ӵ�ͼƬ�� img_bullet ������
	loadimage(&img_start,".\\start.jpg",696,696);   //��ȡ�˵�������img_start ������
	loadimage(&img_pause,".\\pause.jpg",696,696);


	while (gameStatus==0)
		startMenu();//��ʼ�˵�����

}
int map_y_down(float x1,float y1)						//�����ͼ���� ��ͼ�����ж������Ƿ�ȵ����� �ȵ����ط�0 ���򷵻�0
{
	int judge;
	if(y1>=635)
		judge=635;
	else if(y1>=575&&y1<=582&&x1>=393&&x1<=533)//1
		judge=575;
	else if(y1>535&&y1<=542&&x1>=538&&x1<=629)//2
		judge=535;
	else if(y1>=474&&y1<=481&&x1>=413&x1<=508)//3
		judge=474;	
	else if(y1>=474&&y1<=481&&x1>250&&x1<346)//4
		judge=474;
	else if(y1>=474&&y1<=481&&x1>88&&x1<=185)//5
		judge=474;
	else if(y1>=535&&y1<=542&&x1<=185)//6
		judge=535;
	else if(y1>=413&&y1<=420&&x1<60)//7
		judge=413;
	else if(y1>=352&&y1<=359&&x1>86&&x1<=185)//8
		judge=352;
	else if(y1>=290&&y1<=297&&x1<62)//9
		judge=290;
	else if(y1>=230&&y1<=237&&x1>86&&x1<=185)//10
		judge=230;
	else if(y1>=169&&y1<=176&&x1<62)//11
		judge=169;
	else if(y1>=330&&y1<=338&&x1>=213&&x1<=260)//������1
		judge=330;
	else if(y1>=252&&y1<=259&&x1>=311&&x1<=547)//12
		judge=252;
	else if(y1>=252&&y1<=259&&x1>=550&&x1<=635)//13
		judge=252;
	else if(y1>=330&&y1<=337&&x1>=620)//14
		judge=330;
	else if(y1>=370&&y1<=377&&x1>=524&&x1<=629)//15
		judge=370;
	else if(y1>=330&&y1<=338&&x1>=505&&x1<=547)//������2
		judge=330;
	else if(y1>=330&&y1<=338&&x1>=470&&x1<=490)//������3
		judge=330;
	else if(y1>=88&&y1<=95&&x1<=635)//16
		judge=88;
	else if(y1>=555&&y1<=597&&x1>=642)//2
		judge=555;
	else 
		judge=0;
	return judge;

}
int map_y_up(float x2,float y2)						//�����ͼ���� �ж������ͷ���Ƿ���ǽ ���򷵻ط�0 ���򷵻�0
{
	int judge;
	if(y2<=23)
		judge=23;
	else if(y2<=631&&y2>=624&&x2>=393&&x2<=527)//1
		judge=631;
	else if(y2<=590&&y2>=583&&x2>=538&&x2<=629)//2
		judge=590;
	else if(y2<=530&&y2>=523&&x2>=413&x2<=508)//3
		judge=530;	
	else if(y2<=530&&y2>=523&&x2>=253&&x2<=343)//4
		judge=530;
	else if(y2<=530&&y2>=523&&x2>=88&&x2<=182)//5
		judge=530;
	else if(y2<=592&&y2>=584&&x2<=185)//6
		judge=592;
	else if(y2<=468&&y2>=457&&x2<60)//7
		judge=468;
	else if(y2<=346&&y2>=339&&x2<60)//7
		judge=346;
	else if(y2<=226&&y2>=219&&x2<60)//7
		judge=226;
	else if(y2>=136&&y2<=143&&x2<=635)//16
		judge=143;
	else if(y2>=401&&y2<=408&&x2>90&&x2<=185)//8
		judge=408;
	else if(y2>=503&&y2<=510&&x2<=16)//8
		judge=510;
	else if(y2<=284&&y2>=277&&x2<=126&&x2>86)//2
		judge=284;
	else if(y2>=521&&y2<=528&&x2>=642)//2
		judge=528;
	else if(y2>=299&&y2<=306&&x2>=360&&x2<=635)//zhongjian
		judge=306;
	else 
		judge=0;
	return judge;
}
int map_x_left(float x3,float y3)						//�����ͼ���� �ж����������Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	if(x3==18&&y3>=555)
		judge=1;
	else if(x3==18&&y3<=510)
		judge=1;
	else if(x3==534&&y3>=576)
		judge=1;
	else if(y3>=535&&y3<=590&&x3==630)//2
		judge=1;
	else if(y3>=475&&y3<=590&&x3==186)//2
		judge=1;
	else if(y3>=475&&y3<=590&&x3==186)//2
		judge=1;
	else if(y3>=225&&y3<=408&&x3==186)//2
		judge=1;
	else if(y3<=470&&y3>=405&&x3==60)//7
		judge=468;
	else if(y3>=475&&y3<=528&&x3==510)//3
		judge=1;
	else if(y3>=290&&y3<=340&&x3==62)//9
		judge=1;
	else if(y3>=169&&y3<=220&&x3==62)//11
		judge=1;
	else if(y3>=474&&y3<=530&&x3==346)//4
		judge=1;
	else if(y3>=252&&y3<=300&&x3==636)//13
		judge=1;
	else if(y3>=88&&y3<=136&&x3==636)//16
		judge=1;
	else
		judge=0;
	return judge;
}
int map_x_right(float x4,float y4)					//�����ͼ���� �ж�������ұ��Ƿ���ǽ ���򷵻�1 ���򷵻�0
{
	int judge;
	if(x4==640&&y4>=556)
		judge=1;
	else if(x4==640&&y4<=530)
		judge=1;
	else if(x4==474&&y4>=576)
		judge=1;
	else if(y4>=575&&y4<=631&&x4==392)//1
		judge=1;
	else if(y4>=535&&y4<=590&&x4==536)//2
		judge=1;
	else if(y4>=475&&y4<=590&&x4==126)//2
		judge=1;
	else if(y4>=235&&y4<=408&&x4==126)//2
		judge=1;
	else if(y4>=480&&y4<=531&&x4==88)//2
		judge=1;
	else if(y4>=475&&y4<=528&&x4==412)//3
		judge=1;
	else if(y4>=352&&y4<=400&&x4==86)//8
		judge=1;
	else if(y4>=230&&y4<=290&&x4==86)//10
		judge=1;
	else if(y4>=474&&y4<=530&&x4==250)//4
		judge=1;
	else
		judge=0;
	return judge;
}
void show()				//��Ϸ��ʾģ��
{
	putimage(0, 0, &img_bk);				// ������ (0, 0) λ����ʾ IMAGE ����
	putimage(man_x, man_y, &zhezhao,NOTSRCERASE);		//��ʾ������
	putimage(man_x, man_y, &img_man,SRCINVERT);		//��ʾ������
	
	/*if(GetAsyncKeyState('A')&0x8000)  
	{
		if(walk_left<=10)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,50,50,NOTSRCERASE);			//1
			putimage(man_x,man_y-10,50,50,&walk_l,50,50,SRCINVERT);				
		}
		if(walk_left<=20&&walk_left>10)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,100,100,NOTSRCERASE);			//2
			putimage(man_x,man_y-10,50,50,&walk_l,100,100,SRCINVERT);				
		}
		if(walk_left<=30&&walk_left>20)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,150,150,NOTSRCERASE);			//3
			putimage(man_x,man_y-10,50,50,&walk_l,200,200,SRCINVERT);				
		}
		if(walk_left<=40&&walk_left>30)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,250,250,NOTSRCERASE);			//4
			putimage(man_x,man_y-10,50,50,&walk_l,250,250,SRCINVERT);				
		}
		if(walk_left<=40&&walk_left>30)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,50,50,NOTSRCERASE);			//5
			putimage(man_x,man_y-10,50,50,&walk_l,50,50,SRCINVERT);				
		}
		if(walk_left<=50&&walk_left>40)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,50,50,NOTSRCERASE);			//6
			putimage(man_x,man_y-10,50,50,&walk_l,50,50,SRCINVERT);				
		}
		if(walk_left<=60&&walk_left>50)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,50,50,NOTSRCERASE);			//7
			putimage(man_x,man_y-10,50,50,&walk_l,50,50,SRCINVERT);				
		}
		if(walk_left<=70&&walk_left>60)
		{
			putimage(man_x,man_y-10,50,50,&walk_lz,50,50,NOTSRCERASE);			//8
			putimage(man_x,man_y-10,50,50,&walk_l,50,50,SRCINVERT);			
		}
		walk_left++;
	}
	walk_left=0;*/

	putimage(bullet_x[0],bullet_y[0],&img_bullet);
	if(shoot_time>=shoot_if)
		putimage(bullet_x[1],bullet_y[1],&img_bullet);
	if(shoot_time>=2*shoot_if)
		putimage(bullet_x[2],bullet_y[2],&img_bullet);
	if(shoot_time>=3*shoot_if)
		putimage(bullet_x[3],bullet_y[3],&img_bullet);
	
}

void without_input()				//���û������޹صĸ���
{
	man_y=man_y+man_vy;				//����Ĵ�ֱ�ٶ�man_y��ʼ����0��������Ȼ����α��ʽ�������ﲢ��������
	
		
		bullet_x[0]=bullet_x[0]+bullet_vx[0];
		bullet_y[0]=bullet_y[0]+bullet_vy[0];

		if(shoot_time>=shoot_if)
		{
			bullet_x[1]=bullet_x[1]+bullet_vx[1];
			bullet_y[1]=bullet_y[1]+bullet_vy[1];
		}
		if(shoot_time>=2*shoot_if)
		{
			bullet_x[2]=bullet_x[2]+bullet_vx[2];
			bullet_y[2]=bullet_y[2]+bullet_vy[2];
		
		}
		if(shoot_time>=3*shoot_if)
		{
			bullet_x[3]=bullet_x[3]+bullet_vx[3];
			bullet_y[3]=bullet_y[3]+bullet_vy[3];
		}
		shoot_time++;
		


	int i=0;
	for(i=0;i<4;i++)
	{
		if(bullet_x[i]==630&&bullet_y[i]==50)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==630&&bullet_y[i]==625)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==545&&bullet_y[i]==625)
		{
			bullet_vy[i]=-bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==545&&bullet_y[i]==180)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==80&&bullet_y[i]==180)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==80&&bullet_y[i]==525)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==0&&bullet_y[i]==525)
		{
			bullet_x[i]=695;
		}
		if(bullet_x[i]==385&&bullet_y[i]==525)
		{
			bullet_vy[i]=-bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_x[i]==385&&bullet_y[i]==325)
		{
			bullet_vy[i]=bullet_v0;
			bullet_vx[i]=-bullet_v1;
		}
		if(bullet_x[i]==210&&bullet_y[i]==325)
		{
			bullet_vy[i]=bullet_v1;
			bullet_vx[i]=bullet_v0;
		}
		if(bullet_y[i]==650)
		{
			bullet_vx[i]=bullet_v1;
			bullet_vy[i]=bullet_v0;
			bullet_x[i]=50;
			bullet_y[i]=50;
		}
	}
	for(i=0;i<4;i++)
	{
		if( ( (bullet_x[i]+15)- (man_x+18) )*( (bullet_x[i]+15)- (man_x+18) )+ ((bullet_y[i]+15)- (man_y+18) )* ((bullet_y[i]+15)- (man_y+18))<=33*33)    
		live=0;
	}

	if(!map_y_down(man_x,man_y))					//���õ�ͼ�������ж������Ƿ��ڿ���״̬
	{
		sky_if=1;					//������ﴦ�ڿ���״̬����sky_if��Ϊ1��
	}
	if(sky_if==1)				//���������״̬Ϊ1��ʱ�� �����ڿ���Ӧ���е��Զ����� 
	{
	
		if(man_vy<=-man_vy_begin)			//��������ٶ�Ϊ�������ٶ�
		{
			man_vy=man_vy+a_vy;		//�ڿ��е�ʱ���ٶ����������ٶȶ��ı�;	
		}
		
		if(map_y_up(man_x,man_y))					//���õ�ͼ���� ��ͼ�����ж�����ͷ���Ƿ���ǽ ���򷵻�1 ���򷵻�0
		{
			man_vy=0;										//����ͷ��ײ��ǽ ��ֱ�ٶȱ�Ϊ0	
			man_y=map_y_up(man_x,man_y)+1;
		}
		if(map_y_down(man_x,man_y))			//���õ�ͼ���� ��ͼ�����ж������Ƿ�ȵ����� �ȵ����ط�0 ���򷵻�0
		{
			man_vy=0;
			sky_if=0;						//����ȵ����� ��Ϊ�ǿ���״̬ 0
			man_y=map_y_down(man_x,man_y);
		}
	}

}

void user_input()				//���û������йصĸ���
{
	if(live)	
	{
		if(GetAsyncKeyState('A')&0x8000)  
		{
			if(!map_x_left(man_x,man_y))			//���õ�ͼ���� �ж����������Ƿ���ǽ ���򷵻�1 ���򷵻�0��ǰ����һ����!������ û��ǽ����0 ��!0����Ϊ�棩 
			{
				man_x-=2;  // λ������
			}
		}
		if(GetAsyncKeyState('D')&0x8000)
		{
			if(!map_x_right(man_x,man_y))			//���õ�ͼ���� �ж������ұ��Ƿ���ǽ ���򷵻�1 ���򷵻�0 (ǰ�����һ����!�� û��ǽ����0 ��!0��Ϊ��)
			{
				man_x+=2;  // λ������
			}		
		}
		if(sky_if==0)			//������ȵ�����Ϊ�ǿ���״̬ʱ ��w����������Ч����
		{
			if(GetAsyncKeyState('W')&0x8000)
			{
				man_vy=man_vy_begin;			//��w������Ч����֮�� ��������ӵ��һ����ֱ�����ϵĳ��ٶ�
			}
		}

	}
		char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 27) // ESC����ACSII��Ϊ27
		{
			gameStatus = 3;
		}
	}
}
void main()				//������
{
	initgraph(696,696);
	begining();
	BeginBatchDraw();
	while(1)
	{
		mciSendString("open .\\��������ս.mp3 alias bkmusic", NULL, 0, NULL);		//��������
		mciSendString("play bkmusic repeat", NULL, 0, NULL);						// ѭ������
		show();
		
		without_input();
		Sleep(15);
		user_input();
		FlushBatchDraw();
	}
	EndBatchDraw();
	getch();
	closegraph();
}

#include <stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include <string.h>
#define Width 1016
#define High 508
#define Num 10
#pragma comment(lib,"Winmm.lib")
//全局变量
float ball_x[Num],ball_y[Num]; //设母球为0号球
float start_x,start_y;       //杆的开端位置
float end_x,end_y;      //杆的末端位置
double sinA,cosA,sin_A=0,cos_A=0;       //各个球的角的正、余弦值
float dist;            //鼠标到母球的距离
float r,l,L;     //r为球的半径，l为杆开端到母球的距离，L为杆长
float ball_vx[Num] = {0},ball_vy[Num] = {0};    //x,y方向的分速度 
int hit,finalhit;          //鼠标是否点击的判断变量
int ballrunning[Num] = {0};   //记录球的运动状态，1表示运动，0表示静止
int i = 0,j = 0,p=High;
float power;      //定义台球击打力度 
int Wrong;       //加入犯规检测，如果母球进洞为1，表示犯规
int score_player1, score_player2,temp[Num] = {0};      /*定义分数score_player1,score_player2,
                                                                与得分情况temp[10]，temp[i]=0表示未被积分，为1表示已积分*/
int count;       //计算击打次数，奇数为player1击打，偶数为player2
int gameStatus;  //定义游戏状态
int mousehit = 0;
MOUSEMSG m;   //定义鼠标消息
IMAGE  img_bk;  //定义背景
IMAGE property1; //属性栏
IMAGE img_start;  //初始菜单
IMAGE ball0;
IMAGE ball_0;
IMAGE ball1;
IMAGE ball_1;
IMAGE ball2;
IMAGE ball_2;
IMAGE ball3;
IMAGE ball_3;
IMAGE ball4;
IMAGE ball_4;
IMAGE ball5;
IMAGE ball_5;
IMAGE ball6;
IMAGE ball_6;
IMAGE ball7;
IMAGE ball_7;
IMAGE ball8;
IMAGE ball_8;
IMAGE ball9;
IMAGE ball_9;
IMAGE point1;
IMAGE point_1;
IMAGE help;
void startup()           //初始化
{
	TCHAR c=_T('0'); 
	ball_x[0]=Width/4;
	ball_y[0]=High/2; 
	//初始化白球位置
	//初始化其他球位置
	r=14.5; 
	ball_x[1]=Width/2;
	ball_y[1]=High/2;
	ball_x[2]=ball_x[1]+(r+4)*1.73;
	ball_x[3]=ball_x[2];
	ball_x[4]=ball_x[3]+(r+4)*1.73;
	ball_x[6]=ball_x[5]=ball_x[4];
	ball_x[7]=ball_x[6]+(r+4)*1.73;
	ball_x[8]=ball_x[7];
	ball_x[9]=ball_x[8]+(r+4)*1.73;

	ball_y[5]=ball_y[9]=ball_y[1];
	ball_y[2]=ball_y[7]=ball_y[1]+(r+4);
	ball_y[3]=ball_y[8]=ball_y[1]-(r+4);
	ball_y[4]=ball_y[1]+2*(r+4);
	ball_y[6]=ball_y[1]-2*(r+4);
	l=30;
	L=100;
	hit=0;
	finalhit = 0;
	Wrong = 0;
	count = 1;
	score_player1=0;
	score_player2=0;
	initgraph(Width,High);
	BeginBatchDraw();
}      //
void loadpicture()         //图片加载
{
	loadimage(&img_bk,_T("台球游戏素材\\桌面.jpg"));
	loadimage(&property1,_T("台球游戏素材\\属性栏.jpg"));
	loadimage(&img_start,_T("台球游戏素材\\开始菜单.jpg"));
	loadimage(&ball0,_T("台球游戏素材\\tupian\\白球.jpg"));
	loadimage(&ball_0,_T("台球游戏素材\\tupian\\白球遮罩.jpg"));
	loadimage(&ball1,_T("台球游戏素材\\tupian\\褐球.jpg"));
	loadimage(&ball_1,_T("台球游戏素材\\tupian\\褐球遮罩.jpg"));
	loadimage(&ball2,_T("台球游戏素材\\tupian\\蓝色球.jpg"));
	loadimage(&ball_2,_T("台球游戏素材\\tupian\\蓝色球遮罩.jpg"));
	loadimage(&ball3,_T("台球游戏素材\\tupian\\粉球.jpg"));
	loadimage(&ball_3,_T("台球游戏素材\\tupian\\粉球遮罩.jpg"));
	loadimage(&ball4,_T("台球游戏素材\\tupian\\紫球.jpg"));
	loadimage(&ball_4,_T("台球游戏素材\\tupian\\紫球遮罩.jpg"));
	loadimage(&ball5,_T("台球游戏素材\\tupian\\橙球.jpg"));
	loadimage(&ball_5,_T("台球游戏素材\\tupian\\橙球遮罩.jpg"));
	loadimage(&ball6,_T("台球游戏素材\\tupian\\绿球.jpg"));
	loadimage(&ball_6,_T("台球游戏素材\\tupian\\绿球遮罩.jpg"));
	loadimage(&ball7,_T("台球游戏素材\\tupian\\红球.jpg"));
	loadimage(&ball_7,_T("台球游戏素材\\tupian\\红球遮罩.jpg"));
	loadimage(&ball8,_T("台球游戏素材\\tupian\\黑球.jpg"));
	loadimage(&ball_8,_T("台球游戏素材\\tupian\\黑球遮罩.jpg"));
	loadimage(&ball9,_T("台球游戏素材\\tupian\\黄色球.jpg"));
	loadimage(&ball_9,_T("台球游戏素材\\tupian\\黄色球遮罩.jpg"));
	loadimage(&point1,_T("台球游戏素材\\箭头.jpg"));
	loadimage(&point_1,_T("台球游戏素材\\箭头遮罩.jpg"));
	loadimage(&help,_T("台球游戏素材\\帮助栏.jpg"));
	mciSendString(L"open 台球游戏素材\\boom.mp3 alias jpmusic", NULL, 0, NULL);

}
void startMenu()//初始菜单界面
{
	putimage(0,0,&img_start);
	setbkmode(TRANSPARENT);
	if(MouseHit())     //检测是否有鼠标消息
	{
		m=GetMouseMsg();
		if(((m.x>=762)&&(m.x<=960))&&((m.y>=256)&&(m.y<=301)))
		{
			if(m.uMsg==WM_LBUTTONUP)
			{
				gameStatus=1;
			}

		}
		if(((m.x>=762)&&(m.x<=960))&&((m.y>=325)&&(m.y<=369)))
		{				
			if(m.uMsg==WM_LBUTTONUP)
			{
				mousehit = 1;
			}
		}
	}
	
	if (mousehit==1)
	{
		while(p>High*0.45)
		{		
			putimage(Width*0.2,p,&help);
			p--;
			FlushBatchDraw();
			Sleep(3);
		}
		putimage(Width*0.2,p,&help);

	}
	FlushBatchDraw();
	
}
void pauseMenu()  //初始暂停界面
{
	putimage(0,0,&img_bk);

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(30,0,_T("宋体"));
	outtextxy(Width*0.4,High*0.4,_T("1 继续游戏"));
	outtextxy(Width*0.4,High*0.5,_T("2 退出"));
	FlushBatchDraw();

	char input;
	if(kbhit())
	{
		input=getch();
		if(input=='1')
			gameStatus=1;
		if(input=='2')
		{
			gameStatus=2;
		}
	}
}
void gameOver()
{
	putimage(0,0,&img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0,_T("圆体"));
	outtextxy(Width*0.4,High*0.4,_T("游戏结束"));
	FlushBatchDraw();
}
void Judge()         //判断小球进洞，如果进洞，小球状态变为2，并拖到（0，0）处被隐藏
{
	for (i=0;i<Num;i++)
	{
		if (ball_x[i]>=935&&ball_x[i]<=956&&ball_y[i]>=53&&ball_y[i]<=69)
		{
			ballrunning[i] = 2; 
			ball_y[i] = 0;
			ball_x[i] = 0;
			ball_vx[i]=0;
			ball_vy[i]=0;
		}
			            //右上角洞口
		if (ball_x[i]>=486&&ball_x[i]<=528&&ball_y[i]<=55)
		{
			ballrunning[i] = 2; 
			ball_y[i] = 0;
			ball_x[i] = 0;
			ball_vx[i]=0;
			ball_vy[i]=0;
		}          //上顶部洞口
		if (ball_x[i]>=58&&ball_x[i]<=81&&ball_y[i]>=51&&ball_y[i]<=71)
		{
			ballrunning[i] = 2; 
			ball_y[i] = 0;
			ball_x[i] = 0;
			ball_vx[i]=0;
			ball_vy[i]=0;
		}           //左上角洞口
		if (ball_x[i]>=58&&ball_x[i]<=81&&ball_y[i]>=420&&ball_y[i]<=441)
		{
			ballrunning[i] = 2; 
			ball_y[i] = 0;
			ball_x[i] = 0;
			ball_vx[i]=0;
			ball_vy[i]=0;
		}            //左下角洞口
		if (ball_x[i]>=486&&ball_x[i]<=528&&ball_y[i]>=438)
		{
			ballrunning[i] = 2; 
			ball_y[i] = 0;
			ball_x[i] = 0;
			ball_vx[i]=0;
			ball_vy[i]=0;
		}             //下部洞口
		if (ball_x[i]>=935&&ball_x[i]<=957&&ball_y[i]>=425&&ball_y[i]<=445)
		{
			ballrunning[i] = 2; 
			ball_y[i] = 0;
			ball_x[i] = 0;
			ball_vx[i]=0;
			ball_vy[i]=0;
		}            //右下角洞口
		if (i==0&&ballrunning[i]==2)      //如果白球进洞，就任将其初始化在球桌上
		{
			ball_x[i] = rand()%957-r;
			ball_y[i] = rand()%442-r;
			if (ball_x[i]<=r+58)
			{
				ball_x[i]=r+70;
			}
			if (ball_y[i]<53+r)
			{
				ball_y[i]=r+70;
			}
			ball_vx[i]=0;
			ball_vy[i]=0;
			ballrunning[i]=0;
			Wrong = 1;
		}

	}
}
void scoreblanket()           //得分设置，i号球进洞加i分，母球进洞扣10分 
{
	int t,k=0,l;
	char a;
	TCHAR str1[100],str2[100];
	settextcolor(WHITE);
	settextstyle(15,0,_T("宋体"));
	_stprintf(str1,_T("%d"),score_player1);
	outtextxy(350,469, str1);
	_stprintf(str2,_T("%d"),score_player2);
	outtextxy(350,487, str2);
	if (count%2==0)              /*鼠标点击后已转换到玩家2，但这次打击的分数还是要记在玩家1上
								 所以判定反向*/
	{	
		for (i=0;i<Num;i++)
		{
			if (ballrunning[i]==2&&Wrong==0&&temp[i]==0)
			{
				score_player1+=i;			
				_stprintf(str1,_T("%d"),score_player1);
				outtextxy(350,469, str1);
				temp[i] = 1;
			}
			if (Wrong==1&&temp[i]==0)
			{
				score_player1-=10;
				_stprintf(str1,_T("%d"),score_player1);
				outtextxy(350,469, str1);
				Wrong = 0;
				temp[i] = 1;
			}
		}
	}
	else
	{
		for (i=0;i<Num;i++)
		{
			if (ballrunning[i]==2&&Wrong==0&&temp[i]==0)
			{
				score_player2+=i;			
				_stprintf(str2,_T("%d"),score_player2);
				outtextxy(350,487, str2);
				temp[i] = 1;
			}
			if (Wrong==1&&temp[i]==0)
			{
				score_player2-=10;
				_stprintf(str2,_T("%d"),score_player2);
				outtextxy(350,487, str2);
				Wrong = 0;
				temp[i] = 1;
			}
		}
	}

}
void boom()                     //碰撞模型
{
	Judge();
	if (hit == 1)
	{
		for (i=0;i<Num;i++)
		{	 
			if(ballrunning[i]!=2)      //球不进洞才发生碰撞
			{
					if((ball_x[i] <=r+58&&ball_y[i]>r+52&&ball_y[i]<442-r)||(ball_x[i]>=957-r&&ball_y[i]>r+52&&ball_y[i]<442-r))           //与左边界碰撞 
						ball_vx[i] = ball_vx[i]*(-1);                   //与左右边界碰撞 
					if((ball_y[i]<=r+52&&((ball_x[i]>r+58&&ball_x[i]<=486)||(ball_x[i]>=528&&ball_x[i]<957-r)))||(ball_y[i]>=442-r&&((ball_x[i]>r+58&&ball_x[i]<=486)||(ball_x[i]>=528&&ball_x[i]<957-r))))           //与上边界碰撞
						ball_vy[i] = ball_vy[i]*(-1);                   //与上下边界碰撞 
			
			
			ball_x[i] =ball_x[i]+ball_vx[i];
			ball_y[i] =ball_y[i]+ball_vy[i];
			//加入阻尼力
			ball_vx[i] = ball_vx[i]*0.998;
			ball_vy[i] = ball_vy[i]*0.998;
			//速度小于某值时直接令其静止
			if (sqrt(ball_vx[i]*ball_vx[i]+ball_vy[i]*ball_vy[i])<=0.1)
			{
				ball_vx[i] = 0;
				ball_vy[i] = 0;
				ballrunning[i] = 0;
			}
			}

		}
		float mindistance[Num][2];  //储存与nowrunning的球距离最近的球的下标和距离
		float d1,d2;
		float cosA1,sinA1;
		float p;
		struct Vectors
		{
			float s_x,s_y,t_x,t_y;     //球心连线向量与垂直连线向量
			float s1_x,s1_y,t1_x,t1_y;   //球心连线向量与垂直连线单位向量
			float v1s,v2s,v1t,v2t;  //v1,v2在s与t上投影
			float v1s_x,v1s_y,v2s_x,v2s_y,v1t_x,v1t_y,v2t_x,v2t_y;     //用于投影向量化
		};
		Vectors a;


		for (i=0;i<Num;i++)
		{
			mindistance[i][0] = 99999;
			mindistance[i][1] = -1;
		}
		for (i=0;i<Num;i++)
		{
			for (j=0;j<Num;j++)
			{
				if(i!=j)     //距离不与自己比
				{
					float d;
					d =  (ball_x[i]-ball_x[j])*(ball_x[i]-ball_x[j])+(ball_y[j]-ball_y[i])*(ball_y[j]-ball_y[i]);  //球之间的距离
					if(mindistance[i][0]>d)  
					{
						mindistance[i][0] = d;         //获取距离最小值
						mindistance[i][1] = j;            //获取与i号球距离最近的下标
					}
				}
			}

		}


		for(i=0;i<Num;i++)
		{

			if (mindistance[i][0]<=4*r*r)
					{
						j = mindistance[i][1];
						p = 2*r-sqrt(mindistance[i][0])+2; /*小球相粘是因为那一瞬间小球之间的最小距离并非是2r，可能小于2r，毕竟是小球先运动再进行碰撞	
					                                       判定，被撞小球可能没有运动出4*r*r的距离，所以不停碰撞，速度不停减小。
						                                   p计算的是应该拉开的距离*/
						d1 = ball_x[i]-ball_x[j];
						d2 = ball_y[i]-ball_y[j];
						cosA1 = sqrt(d1*d1/(d1*d1+d2*d2));       //小球连线与x负方向的cos,sin值
						sinA1 =sqrt(d2*d2/(d1*d1+d2*d2));
						if (d1>0)
						{
							cosA1=(-1)*cosA1;
						}
						if (d2>0)
						{
							sinA1=(-1)*sinA1;
						}
						setcolor(BLACK);
						setfillcolor(BLACK);
						fillcircle(ball_x[j],ball_y[j],r); //擦除被撞球 
						//把两小球拉开
						ball_x[j]+=p*cosA1;
						ball_y[j]+=p*sinA1;
						if (j==0)
						{
							setcolor(WHITE);
							setfillcolor(WHITE);
							fillcircle(ball_x[j],ball_y[j],r);
						}
						else
						{
							setcolor(BLUE);
							setfillcolor(BLUE);
							fillcircle(ball_x[j],ball_y[j],r);
						}
					}
		}

	
		for (i=0;i<Num;i++)
		{
			float temp;
			if(mindistance[i][0]<=4*r*r+80&&ballrunning[i]==1)            //判断是否碰撞，若是进行速度动量分配，方向传递
			{
				//mciSendString(L"play jpmusic from 0",NULL,0,NULL);   //重头播放
				j =mindistance[i][1];
				a.s_x = ball_x[i]-ball_x[j];
				a.s_y = ball_y[i]-ball_y[j];    //计算s(球心连线)向量
				a.t_x = a.s_y*(-1);
				a.t_y = a.s_x;
				a.s1_x = a.s_x/(sqrt(a.s_x*a.s_x+a.s_y*a.s_y));
				a.s1_y = a.s_y/(sqrt(a.s_x*a.s_x+a.s_y*a.s_y));  //s单位向量
				a.t1_x = a.t_x/(sqrt(a.t_x*a.t_x+a.t_y*a.t_y));
				a.t1_y = a.t_y/(sqrt(a.t_x*a.t_x+a.t_y*a.t_y));  //t单位向量
				a.v1s = ball_vx[i]*a.s1_x+ball_vy[i]*a.s1_y;
				a.v1t = ball_vx[i]*a.t1_x+ball_vy[i]*a.t1_y;     //v1在s,t上的投影
				a.v2s = ball_vx[j]*a.s1_x+ball_vy[j]*a.s1_y;
				a.v2t = ball_vx[j]*a.t1_x+ball_vy[j]*a.t1_y;     //v2在s,t上的投影
				temp = a.v1s;
				a.v1s =a.v2s;
				a.v2s = temp;                                      //交换s方向的速度的值
				//转换为向量
				a.v1s_x = a.v1s*a.s1_x;
				a.v1s_y = a.v1s*a.s1_y;
				a.v1t_x = a.v1t*a.t1_x;
				a.v1t_y =a.v1t*a.t1_y;
				ball_vx[i] = 1.0*(a.v1s_x*1+a.v1t_x*1);
				ball_vy[i] = 1.0*(a.v1s_y*1+a.v1t_y*1);

				a.v2s_x = a.v2s*a.s1_x;
				a.v2s_y = a.v2s*a.s1_y;
				a.v2t_x = a.v2t*a.t1_x;
				a.v2t_y =a.v2t*a.t1_y;
				ball_vx[j] = 1.0*(a.v2s_x*1+a.v2t_x*1);   //还原至速度
				ball_vy[j] = 1.0*(a.v2s_y*1+a.v2t_y*1);
				ballrunning[j] = 1;
				mindistance[j][0] = 999999999;   // 避免交换两次速度，又回去了
				mindistance[j][1] = -1;

			}
		}
	}		
	Sleep(3);
}
void againboom()                 //第二次击打功能
{
	int count = 0; //定义计数器
	if (hit==1)     //在上一次击打结束之前一直为0
	{
		count = 0;
	}
	for (i=0;i<Num;i++)      //计算屏幕中停下的小球数量
	{
		if (ballrunning[i]==0||ballrunning[i]==2)
		{
			count++;
		}
	}
	if (count==10&&ballrunning[0]!=2)       //全停下时则表示击打结束
	{
		hit = 0;
		//使得杆出现在白球周围
		dist=sqrt((m.x-ball_x[0])*(m.x-ball_x[0])+(m.y-ball_y[0])*(m.y-ball_y[0]));  //鼠标到母球的距离
		sinA=(m.y-ball_y[0])/dist;     //算出鼠标与母球连线与水平夹角的正弦值
		cosA=(m.x-ball_x[0])/dist;     //算出鼠标与母球连线与水平夹角的余弦值
		start_x=ball_x[0]+l*cosA;      //算出球杆开端位置
		start_y=ball_y[0]+l*sinA;
		end_x=start_x+L*cosA;       //算出球杆末端位置
		end_y=start_y+L*sinA;
	}

}
void powercontrol()             //力度控制
{
	char input;
	float power;
	struct point
	{
		int toppoint_x,toppoint_y;
		int leftpoint_x,leftpoint_y;
		int rightpoint_x,rightpoint_y;
		int pointmovespeed;
	};
	point p;
	p.toppoint_x = 796;         //三角形的顶部坐标
	p.toppoint_y = 18+464;
	p.rightpoint_x = 796+18;     //三角的右底角坐标
	p.rightpoint_y= 464;
	p.leftpoint_x = 796-18;      //三角的左底角坐标
	p.leftpoint_y = 464;
	p.pointmovespeed = 8;        //三角的移动速度
	if (hit==0)
	{
		finalhit = 0;
	}
	POINT pts[3] = { {p.toppoint_x, p.toppoint_y}, {p.leftpoint_x, p.leftpoint_y}, {p.rightpoint_x, p.rightpoint_y} };	
	setpolyfillmode(WINDING);
	setfillcolor(RED);
	solidpolygon(pts, 3);
	while(hit==1&&finalhit==0)          //力度条的运行要两个条件，一个是方向确定，一个是没有按空格结束
	{
		//重新绘图
		putimage(0,0,&img_bk);    //放入桌面
		putimage(28,467,&property1); //放入属性栏
		scoreblanket();
		if (ballrunning[0]!=2)
		{			

			putimage(ball_x[0]-15,ball_y[0]-15,&ball_0,NOTSRCERASE);
			putimage(ball_x[0]-15,ball_y[0]-15,&ball0,SRCINVERT);
		}
		if (ballrunning[1]!=2)
		{				
			putimage(ball_x[1]-15,ball_y[1]-15,&ball_1,NOTSRCERASE);
			putimage(ball_x[1]-15,ball_y[1]-15,&ball1,SRCINVERT);
		}
		if (ballrunning[2]!=2)
		{				
			putimage(ball_x[2]-15,ball_y[2]-15,&ball_2,NOTSRCERASE);
			putimage(ball_x[2]-15,ball_y[2]-15,&ball2,SRCINVERT);
		}
		if (ballrunning[3]!=2)
		{				
			putimage(ball_x[3]-16,ball_y[3]-15,&ball_3,NOTSRCERASE);
			putimage(ball_x[3]-16,ball_y[3]-15,&ball3,SRCINVERT);
		}
		if (ballrunning[4]!=2)
		{				
			putimage(ball_x[4]-16,ball_y[4]-15,&ball_4,NOTSRCERASE);
			putimage(ball_x[4]-16,ball_y[4]-15,&ball4,SRCINVERT);
		}
		if (ballrunning[5]!=2)
		{				
			putimage(ball_x[5]-16,ball_y[5]-15,&ball_5,NOTSRCERASE);
			putimage(ball_x[5]-16,ball_y[5]-15,&ball5,SRCINVERT);
		}
		if (ballrunning[6]!=2)
		{				
			putimage(ball_x[6]-15,ball_y[6]-15,&ball_6,NOTSRCERASE);
			putimage(ball_x[6]-15,ball_y[6]-15,&ball6,SRCINVERT);
		}
		if (ballrunning[7]!=2)
		{				
			putimage(ball_x[7]-16,ball_y[7]-15,&ball_7,NOTSRCERASE);
			putimage(ball_x[7]-16,ball_y[7]-15,&ball7,SRCINVERT);
		}
		if (ballrunning[8]!=2)
		{				
			putimage(ball_x[8]-15,ball_y[8]-15,&ball_8,NOTSRCERASE);
			putimage(ball_x[8]-15,ball_y[8]-15,&ball8,SRCINVERT);
		}
		if (ballrunning[9]!=2)
		{				
			putimage(ball_x[9]-16,ball_y[9]-15,&ball_9,NOTSRCERASE);
			putimage(ball_x[9]-16,ball_y[9]-15,&ball9,SRCINVERT);
		}
		//画杆
			if (count%2==0)    /*如果count为偶数则为玩家1，用黄色杆，
				                 这里需要在鼠标点击后杆停留一会，所以count++但还是处于玩家1击打的状态，故判定反向*/
			{		
				setlinestyle(PS_SOLID, 6);
				setcolor(YELLOW);
				line(start_x,start_y,end_x,end_y);
			}
			else               //如果count为奇数则为玩家2，用蓝色杆
			{
				setlinestyle(PS_SOLID, 6);
				setcolor(BLUE);
				line(start_x,start_y,end_x,end_y);
			}
			if (count%2==0||count==1)
			{
				putimage(10,460,&point_1,NOTSRCERASE);   //放入箭头
				putimage(10,460,&point1,SRCINVERT);
			}
			else
			{
				putimage(10,478,&point_1,NOTSRCERASE);   //放入箭头
				putimage(10,478,&point1,SRCINVERT);
			}
		p.toppoint_x+=p.pointmovespeed;
		p.leftpoint_x+=p.pointmovespeed;
		p.rightpoint_x+=p.pointmovespeed;
		pts[0].x = p.toppoint_x;
		pts[0].y = p.toppoint_y;
		pts[1].x = p.leftpoint_x;
		pts[1].y = p.leftpoint_y;
		pts[2].x = p.rightpoint_x;
		pts[2].y = p.rightpoint_y;
		if (p.toppoint_x>=960||p.toppoint_x<=796)   //走到力度条尽头就反向
		{
			p.pointmovespeed = p.pointmovespeed*(-1);
		}
		setpolyfillmode(WINDING);
		setfillcolor(RED);
		solidpolygon(pts, 3);		
		if (kbhit())
		{
			input = getch();
			if (input==' ')
			{
				finalhit=1;
				power = (p.toppoint_x-796)/15;
				ball_vx[0] =(-1)*cosA*power;
				ball_vy[0] =(-1)*sinA*power;
				break;
			}
		}
		FlushBatchDraw();
		Sleep(100);
	}

}
void show()
{	

	putimage(0,0,&img_bk);    //放入桌面
	setbkmode(TRANSPARENT);
	putimage(28,467,&property1); //放入属性栏
	powercontrol();
	//放入球的图片
		if (ballrunning[0]!=2)
		{			
			putimage(ball_x[0]-15,ball_y[0]-15,&ball_0,NOTSRCERASE);
			putimage(ball_x[0]-15,ball_y[0]-15,&ball0,SRCINVERT);
		}
		if (ballrunning[1]!=2)
		{				
			putimage(ball_x[1]-15,ball_y[1]-15,&ball_1,NOTSRCERASE);
			putimage(ball_x[1]-15,ball_y[1]-15,&ball1,SRCINVERT);
		}
		if (ballrunning[2]!=2)
		{				
			putimage(ball_x[2]-15,ball_y[2]-15,&ball_2,NOTSRCERASE);
			putimage(ball_x[2]-15,ball_y[2]-15,&ball2,SRCINVERT);
		}
		if (ballrunning[3]!=2)
		{				
			putimage(ball_x[3]-16,ball_y[3]-15,&ball_3,NOTSRCERASE);
			putimage(ball_x[3]-16,ball_y[3]-15,&ball3,SRCINVERT);
		}
		if (ballrunning[4]!=2)
		{				
			putimage(ball_x[4]-16,ball_y[4]-15,&ball_4,NOTSRCERASE);
			putimage(ball_x[4]-16,ball_y[4]-15,&ball4,SRCINVERT);
		}
		if (ballrunning[5]!=2)
		{				
			putimage(ball_x[5]-16,ball_y[5]-15,&ball_5,NOTSRCERASE);
			putimage(ball_x[5]-16,ball_y[5]-15,&ball5,SRCINVERT);
		}
		if (ballrunning[6]!=2)
		{				
			putimage(ball_x[6]-15,ball_y[6]-15,&ball_6,NOTSRCERASE);
			putimage(ball_x[6]-15,ball_y[6]-15,&ball6,SRCINVERT);
		}
		if (ballrunning[7]!=2)
		{				
			putimage(ball_x[7]-16,ball_y[7]-15,&ball_7,NOTSRCERASE);
			putimage(ball_x[7]-16,ball_y[7]-15,&ball7,SRCINVERT);
		}
		if (ballrunning[8]!=2)
		{				
			putimage(ball_x[8]-15,ball_y[8]-15,&ball_8,NOTSRCERASE);
			putimage(ball_x[8]-15,ball_y[8]-15,&ball8,SRCINVERT);
		}
		if (ballrunning[9]!=2)
		{				
			putimage(ball_x[9]-16,ball_y[9]-15,&ball_9,NOTSRCERASE);
			putimage(ball_x[9]-16,ball_y[9]-15,&ball9,SRCINVERT);
		}
	//画杆
	if(hit!=1)
	{
		if (count%2!=0)    //如果count为奇数则为玩家1，用黄色杆
		{		
			setlinestyle(PS_SOLID, 6);
			setcolor(YELLOW);
			line(start_x,start_y,end_x,end_y);
		}
		else               //如果count为偶数则为玩家2，用蓝色杆
		{
			setlinestyle(PS_SOLID, 6);
			setcolor(BLUE);
			line(start_x,start_y,end_x,end_y);
		}
	}
	if (count%2==0||count==1)
	{
		putimage(10,460,&point_1,NOTSRCERASE);   //放入箭头
		putimage(10,460,&point1,SRCINVERT);
	}
	else
	{
		putimage(10,478,&point_1,NOTSRCERASE);   //放入箭头
		putimage(10,478,&point1,SRCINVERT);
	}
	scoreblanket();
	FlushBatchDraw();   //开始批量绘图
}
void clean()
{	
		setlinestyle(PS_SOLID, 6);
		setcolor(BLACK);
		line(start_x,start_y,end_x,end_y);  //隐藏上一帧球杆
}
void updatewithinput()
{
	if(MouseHit())     //检测是否有鼠标消息
	{
		m=GetMouseMsg();
		if((m.uMsg==WM_MOUSEMOVE)&&(hit == 0))
		{
			dist=sqrt((m.x-ball_x[0])*(m.x-ball_x[0])+(m.y-ball_y[0])*(m.y-ball_y[0]));  //鼠标到母球的距离
			sinA=(m.y-ball_y[0])/dist;     //算出鼠标与母球连线与水平夹角的正弦值
			cosA=(m.x-ball_x[0])/dist;     //算出鼠标与母球连线与水平夹角的余弦值
			start_x=ball_x[0]+l*cosA;      //算出球杆开端位置
			start_y=ball_y[0]+l*sinA;
			end_x=start_x+L*cosA;       //算出球杆末端位置
			end_y=start_y+L*sinA;

		}
		if(m.uMsg==WM_LBUTTONUP)
		{
			hit=1;
			ballrunning[0] = 1;
			count++;

		}
		

	}
	char input;
	if(kbhit())
	{
		input=getch();
		if(input==27)
		{
			gameStatus=3;
		}
	}
}
void winnerjudge()
{
	int sum;
	sum=0;
	for (i=1;i<Num;i++)
	{
		if(temp[i]==1)
			sum++;
	}
	if (sum==9)
	{		
		if (score_player1>score_player2)
		{		
			settextstyle(50,0,_T("宋体"));
			settextcolor(BLACK);
			outtextxy(420,220,_T("Game over"));
			outtextxy(480,280,_T("Player1 Win!"));
		}
		else if (score_player1==score_player2)
		{		
			settextstyle(50,0,_T("宋体"));
			settextcolor(BLACK);
			outtextxy(420,220,_T("Game over"));
			outtextxy(480,280,_T("平局！"));
		}
		else
		{
			settextstyle(50,0,_T("宋体"));
			settextcolor(BLACK);
			outtextxy(420,220,_T("Game over"));
			outtextxy(480,280,_T("Player2 Win!"));
		}
		FlushBatchDraw();
		system("pause");
		exit(0);

	}

}
void updatewithoutinput()
{
	boom();
	againboom();
}
void main()
{
	loadpicture();
	startup();
	while(1)
	{	
		if(gameStatus==0)
			startMenu();
		if(gameStatus==1)
		{
			while(1)
			{
				show();
				clean();
				updatewithoutinput();
				updatewithinput();
				if(gameStatus==3)
					break;
			}
		}
		if(gameStatus==3)
			pauseMenu();
		if(gameStatus==2)
			gameOver();
	}
	EndBatchDraw();
	getch();
	closegraph();
}
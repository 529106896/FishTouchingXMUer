#include <stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#define Width 1016
#define High 508
#define Num 10

//全局变量
float ball_x[Num],ball_y[Num]; //设母球为0号球
float start_x,start_y;       //杆的开端位置
float end_x,end_y;      //杆的末端位置
float sinA,cosA;       //各个球的角的正、余弦值
float dist;            //鼠标到母球的距离
float r,l,L;     //r为球的半径，l为杆开端到母球的距离，L为杆长
float ball_vx[Num] = {0},ball_vy[Num] = {0};    //x,y方向的分速度 
int hit;          //鼠标是否点击的判断变量
int ballrunning[Num] = {0};   //记录球的运动状态，1表示运动，0表示静止
int i = 0,j = 0;
MOUSEMSG m;   //定义鼠标消息

void startup()
{
	 
	ball_x[0]=Width/4;
	ball_y[0]=High/2; 
	//初始化白球位置
	//初始化其他球位置
	r=10; 
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
	initgraph(Width,High);
	BeginBatchDraw();
}
void boom()
{
	if (hit == 1)
	{
		for (i=0;i<Num;i++)
		{	         
			if((ball_x[i]<=r&&ball_y[i]<=r)||(ball_x[i]<=r&&ball_y[i]>=High)||(ball_x[i]>=Width&&ball_y[i]<=r)||(ball_x[i]>=Width&&ball_y[i]<=r))
			{
				ball_vx[i] = ball_vx[i]*(-1); 
				ball_vy[i] = ball_vy[i]*(-1);
			}	                //与四角碰撞
			else
			{
				if((ball_x[i] <=r&&ball_y[i]>r&&ball_y[i]<High)||(ball_x[i]>=Width-r&&ball_y[i]>r&&ball_y[i]<High))           //与左边界碰撞 
					ball_vx[i] = ball_vx[i]*(-1);                   //与左右边界碰撞 
				if((ball_y[i]<=r&&ball_x[i]>r&&ball_x[i]<Width)||ball_y[i] >= High-r&&ball_x[i]>r&&ball_x[i]<Width)           //与上边界碰撞
					ball_vy[i] = ball_vy[i]*(-1);                   //与上下边界碰撞 
			}
			ball_x[i] =ball_x[i]+ball_vx[i];
			ball_y[i] =ball_y[i]+ball_vy[i];
			//加入阻尼力
			ball_vx[i] = ball_vx[i]*0.999;
			ball_vy[i] = ball_vy[i]*0.999;
			//速度小于某值时直接令其静止
			if (sqrt(ball_vx[i]*ball_vx[i]+ball_vy[i]*ball_vy[i])<=0.1)
			{
				ball_vx[i] = 0;
				ball_vy[i] = 0;
				ballrunning[i] = 0;
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
			if(mindistance[i][0]<=4*r*r&&ballrunning[i]==1)            //判断是否碰撞，若是进行速度动量分配，方向传递
			{
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
void againboom()
{
	int count = 0; //定义计数器
	if (hit==1)     //在上一次击打结束之前一直为0
	{
		count = 0;
	}
	for (i=0;i<Num;i++)      //计算屏幕中停下的小球数量
	{
		if (ballrunning[i]==0)
		{
			count++;
		}
	}
	if (count==10)       //全停下时则表示击打结束
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
void show()
{
	//画白色母球
	
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(ball_x[0],ball_y[0],r);

	//画蓝色球
	for (i=1;i<Num;i++)
	{	
		setcolor(BLUE);
		setfillcolor(BLUE);
		fillcircle(ball_x[i],ball_y[i],r);
	}

	//画杆
	if(hit!=1)
	{
		setlinestyle(PS_SOLID, 6);
		setcolor(YELLOW);
		line(start_x,start_y,end_x,end_y);
	}
	FlushBatchDraw();   //开始批量绘图
}
void clean()
{	
	if (hit == 1)
	{	
		for (i=0;i<Num;i++)
		{			
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillcircle(ball_x[i],ball_y[i],r);        //隐藏上一帧球

		}
	}
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
			ball_vx[0] =(-1)*cosA*5;
			ball_vy[0] =(-1)*sinA*5;
		}
		

	}
}

void updatewithoutinput()
{
	boom();
	againboom();
}

void main()
{
	startup();
	while(1)
	{
		show();
		clean();
		updatewithoutinput();
		updatewithinput();
	}
	EndBatchDraw();
	getch();
	closegraph();
}
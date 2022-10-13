#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#pragma comment(lib,"Winmm.lib")
int high,wedith;
int x,y;//坐标
int gap;//点与点之间的间距
int i;
MOUSEMSG m;
struct Circle
{
int x;
int y;
int get;
};
struct point
{
int x;
int y;
};
point p[10];
Circle c[4];
void starup()
{

high=390;
wedith=550;
initgraph(high,wedith);
gap=95;
p[1].x=100;p[2].x=100+gap;p[3].x=100+gap*2;
p[4].x=100;p[5].x=100+gap;p[6].x=100+gap*2;
p[7].x=100;p[8].x=100+gap;p[9].x=100+gap*2;

p[1].y=180;p[4].y=180+gap;p[7].y=180+gap*2;
p[2].y=180;p[5].y=180+gap;p[8].y=180+gap*2;
p[3].y=180;p[6].y=180+gap;p[9].y=180+gap*2;


for(i=1;i<=3;i++)
{	
c[i].x=p[i].x;
c[i].y=p[9].y+gap;
c[i].get=0;
}
}
void show()
{
BeginBatchDraw();
setfillcolor(RGB(31,78,121));//设置背景颜色
solidrectangle(0,0,high,wedith);//画背景
//测试1在c处画环
setlinestyle(PS_SOLID,5);
setfillcolor(RGB(31,78,121));
fillcircle(c[1].x,c[1].y,24);
//画九个点
setcolor(WHITE);
setfillcolor(WHITE);
for(x=p[1].x;x<=p[3].x;x+=gap)
{
fillcircle(x,p[1].y,1);//第一排的点
}
for(x=p[4].x;x<=p[6].x;x+=gap)
{
fillcircle(x,p[4].y,1);//第二排的点
}
for(x=p[7].x;x<=p[9].x;x+=gap)
{
fillcircle(x,p[7].y,1);//第三排的点
}

FlushBatchDraw();
}
void withoutinput()
{

}
void withinput()
{
m=GetMouseMsg();
if(m.uMsg == WM_LBUTTONDOWN/*&&m.x<=c[1].x+24&&m.x>=c[1].x-24&&m.y>=c[1].y-24&&m.y<=c[1].y+24*/)
{
c[1].get=1;
}
if(c[1].get==1)
{
c[1].x=m.x;
c[1].y=m.y;
if(m.uMsg == WM_LBUTTONUP)
c[1].get=0;

}
}
void main()
{

starup();
while(1)
{
show();
withoutinput();
withinput();
}
EndBatchDraw();
getch();
closegraph();

}
/*
setlinestyle(PS_SOLID,5);
setfillcolor(RGB(31,78,121));
fillcircle(195,275,24);
fillcircle(195,275,17);	
fillcircle(195,275,10);
*/
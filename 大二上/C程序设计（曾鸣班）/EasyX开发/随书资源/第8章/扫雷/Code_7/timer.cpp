
////////////////////////////////////////////
// 程序编写：BestAns <BestAns@qq.com>
// 最后更新：2010-10-30
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

SYSTEMTIME start;


int times()
{

	SYSTEMTIME ti;
	int sum = 0;
	GetLocalTime(&ti);		// 获取当前时间
	
	sum += ti.wHour - start.wHour;
	sum *= 60;
	sum += ti.wMinute - start.wMinute;
	sum *= 60;
	sum += ti.wSecond - start.wSecond;
	return sum;
}


void main()
{
	SYSTEMTIME ti;
initgraph(640, 480);		// 初始化 640 x 480 的绘图窗口
GetLocalTime(&start);


// 绘制表针
while (1)				// 按任意键退出钟表程序
{
	times();
}

closegraph();				// 关闭绘图窗口
}
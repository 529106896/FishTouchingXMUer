
////////////////////////////////////////////
// �����д��BestAns <BestAns@qq.com>
// �����£�2010-10-30
//
#include <graphics.h>
#include <conio.h>
#include <math.h>

SYSTEMTIME start;


int times()
{

	SYSTEMTIME ti;
	int sum = 0;
	GetLocalTime(&ti);		// ��ȡ��ǰʱ��
	
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
initgraph(640, 480);		// ��ʼ�� 640 x 480 �Ļ�ͼ����
GetLocalTime(&start);


// ���Ʊ���
while (1)				// ��������˳��ӱ����
{
	times();
}

closegraph();				// �رջ�ͼ����
}
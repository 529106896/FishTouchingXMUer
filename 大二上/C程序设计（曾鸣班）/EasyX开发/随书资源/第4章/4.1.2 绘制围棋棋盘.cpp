// ����Χ������
#include <graphics.h>
#include <conio.h>
int main()
{
	int step = 30;
	// ��ʼ����ͼ����
	initgraph(600, 600);	
	// ���ñ���ɫΪ��ɫ
	setbkcolor(YELLOW);
	// �ñ���ɫ�����Ļ
	cleardevice();
	
	setlinestyle(PS_SOLID, 2);  // ��ʵ�ߣ����Ϊ2������
	setcolor(RGB(0,0,0));  // ����Ϊ��ɫ
	
	int i;
	for(i=1; i<=19; i++)  // �����ߺ�����
	{
		line(i*step, 1*step, i*step,  19*step);
		line(1*step, i*step, 19*step, i*step);
	}
	getch();
	closegraph();
	return 0;
}

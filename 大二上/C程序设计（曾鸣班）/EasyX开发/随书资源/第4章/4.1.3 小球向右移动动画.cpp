#include <graphics.h>
#include <conio.h>
int main()
{
	initgraph(640, 480);
	for(int x=100; x<540; x+=20)
	{
		// ���ƻ��ߡ���ɫ����Բ
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(x, 100, 20);
		// ��ʱ
		Sleep(200);
		// ���ƺ��ߡ���ɫ����Բ
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, 100, 20);
	}
	closegraph();
	return 0;
}

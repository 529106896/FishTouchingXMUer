#include <graphics.h>		// ���� EasyX ͼ�ο�
#include <conio.h>
int main()
{
	initgraph(640, 480);	// ��ʼ��640��480�Ļ���
	setcolor(YELLOW);     // Բ������Ϊ��ɫ
	setfillcolor(GREEN);    // Բ�ڲ�λ��ɫ���
	fillcircle(100, 100, 20);  // ��Բ��Բ��(100, 100)���뾶 20
	getch();				// �����������
	closegraph();			// �ر�ͼ�ν���
	return 0;
}

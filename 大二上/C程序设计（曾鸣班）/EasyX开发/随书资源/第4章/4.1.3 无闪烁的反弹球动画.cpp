#include <graphics.h>
#include <conio.h>
#define High 480  // ��Ϸ����ߴ�
#define Width 640

int main()
{
	float ball_x,ball_y; // С�������
	float ball_vx,ball_vy; // С����ٶ�
	float radius;  // С��İ뾶
	
	initgraph(Width, High);
	ball_x = Width/2;
	ball_y = High/2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;
	
	BeginBatchDraw();
	while (1)
	{
		// ���ƺ��ߡ���ɫ����Բ
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(ball_x, ball_y, radius);
		
		// ����СԲ����
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;
		
		if ((ball_x<=radius)||(ball_x>=Width-radius))
			ball_vx = -ball_vx;
		if ((ball_y<=radius)||(ball_y>=High-radius))
			ball_vy = -ball_vy;	
		
		// ���ƻ��ߡ���ɫ����Բ
		setcolor(YELLOW);
		setfillcolor(GREEN);
		fillcircle(ball_x, ball_y, radius);
		
		FlushBatchDraw();
		
		// ��ʱ
		Sleep(3);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

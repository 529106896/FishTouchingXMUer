#include <conio.h>
#include <graphics.h>
#include<windows.h>
#define High 480  // ��Ϸ����ߴ�
#define Width 640
// ȫ�ֱ���
int ball_x,ball_y; // С�������
int ball_vx,ball_vy; // С����ٶ�
int radius; // С��İ뾶
int bar1_left,bar1_right,bar1_top,bar1_bottom; // ����1����������λ������
int bar2_left,bar2_right,bar2_top,bar2_bottom; // ����2����������λ������
int bar_height,bar_width; // ����ĸ߶ȡ����

void startup()  // ���ݳ�ʼ��
{
	ball_x = Width/2;
	ball_y = High/2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;

	bar_width = Width/30;
	bar_height = High/2;

	bar1_left = Width * 1/20;
	bar1_top = High/4;
	bar1_right = bar1_left + bar_width;	
	bar1_bottom = bar1_top + bar_height;	

	bar2_left = Width * 18.5/20;
	bar2_top = High/4;
	bar2_right = bar2_left + bar_width;	
	bar2_bottom = bar2_top + bar_height;

	initgraph(Width,High);
	BeginBatchDraw();
}

void clean()  // ��������
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius); 	
	fillcircle(ball_x, ball_y, radius); 
	bar(bar1_left,bar1_top,bar1_right,bar1_bottom);	
	bar(bar2_left,bar2_top,bar2_right,bar2_bottom);	
}	

void show()  // ��ʾ����
{
	setcolor(GREEN);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);	// ������Բ	
	
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	bar(bar1_left,bar1_top,bar1_right,bar1_bottom);	// ���ƻ�ɫ����
	bar(bar2_left,bar2_top,bar2_right,bar2_bottom);	

	FlushBatchDraw();
	// ��ʱ
	Sleep(3);	
}	

void updateWithoutInput()  // ���û������޹صĸ���
{
	// �����СԲ��ײ��СԲ����
	if (ball_x+radius>=bar2_left && ball_y+radius>=bar2_top && ball_y+radius<=bar2_bottom)
		ball_vx = -ball_vx;	
	else if (ball_x-radius<=bar1_right && ball_y+radius>=bar1_top && ball_y+radius<=bar1_bottom)
		ball_vx = -ball_vx;	
	
	// ����СԲ����
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;
		
	if ((ball_x<=radius)||(ball_x>=Width-radius))
		ball_vx = -ball_vx;
	if ((ball_y<=radius)||(ball_y>=High-radius))
		ball_vy = -ball_vy;	
}

void updateWithInput()  // ���û������йصĸ���
{	
		int step = 1;
		if (GetAsyncKeyState(0x57) & 0x8000 )  // w
			bar1_top-=step;
		if ((GetAsyncKeyState(0x53) & 0x8000)) //s
			bar1_top+=step;
		if ((GetAsyncKeyState(VK_UP) & 0x8000))     // �Ϸ����
			bar2_top-=step;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000))  // �·����
			bar2_top+=step;	

		bar1_bottom = bar1_top + bar_height;	
		bar2_bottom = bar2_top + bar_height;
}

void gameover()
{
	EndBatchDraw();
	closegraph();
}

int main()
{
	startup();  // ���ݳ�ʼ��	
	while (1)  //  ��Ϸѭ��ִ��
	{
		clean();  // ��֮ǰ���Ƶ�����ȡ��
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();     // ���û������йصĸ���
		show();  // ��ʾ�»���
	}
	gameover();     // ��Ϸ��������������
	return 0;
}

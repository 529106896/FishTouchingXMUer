#include <conio.h>
#include <graphics.h>

#define High 480  // ��Ϸ����ߴ�
#define Width 640
#define Brick_num 10 // ש�����

// ȫ�ֱ���
int ball_x,ball_y; // С�������
int ball_vx,ball_vy; // С����ٶ�
int radius;  // С��İ뾶
int bar_x,bar_y; // ������������
int bar_high,bar_width;  // ����ĸ߶ȺͿ��
int bar_left,bar_right,bar_top,bar_bottom; // �������������λ������

int isBrickExisted[Brick_num]; // ÿ��ש���Ƿ���ڣ�1Ϊ���ڣ�0Ϊû����
int brick_high,brick_width; // ÿ��ש��ĸ߶ȺͿ��

void startup()  // ���ݳ�ʼ��
{
	ball_x = Width/2;
	ball_y = High/2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;
	
	bar_high = High/20;
	bar_width = Width/2;
	bar_x = Width/2;
	bar_y = High - bar_high/2;
	bar_left = bar_x - bar_width/2;
	bar_right = bar_x + bar_width/2;
	bar_top = bar_y - bar_high/2;
	bar_bottom = bar_y + bar_high/2;

	brick_width = Width/Brick_num;
	brick_high = High/Brick_num;

	int i;
	for (i=0;i<Brick_num;i++)
		isBrickExisted[i] = 1;
	
	initgraph(Width, High);
	BeginBatchDraw();
}

void clean()  // ��������
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y, radius); 	// ���ƺ��ߡ���ɫ����Բ
	bar(bar_left,bar_top,bar_right,bar_bottom);	// ���ƺ��ߡ���ɫ���ĵ���

	int i,brick_left,brick_right,brick_top,brick_bottom;	
	for (i=0;i<Brick_num;i++)
	{
		brick_left = i*brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_high;
		if (!isBrickExisted[i])	 // ש��û���ˣ����ƺ�ɫ
			fillrectangle(brick_left,brick_top,brick_right,brick_bottom);
	}
}	

void show()  // ��ʾ����
{
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);	// ���ƻ��ߡ���ɫ����Բ
	bar(bar_left,bar_top,bar_right,bar_bottom);	// ���ƻ��ߡ���ɫ���ĵ���

	int i,brick_left,brick_right,brick_top,brick_bottom;

	for (i=0;i<Brick_num;i++)
	{
		brick_left = i*brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_high;

		if (isBrickExisted[i])	 // ש����ڣ�����ש��
		{
			setcolor(WHITE);
			setfillcolor(RED);
			fillrectangle(brick_left,brick_top,brick_right,brick_bottom);	// ����ש��
		}
	}

	FlushBatchDraw();
	// ��ʱ
	Sleep(3);	
}	

void updateWithoutInput()  // ���û������޹صĸ���
{
	// �����СԲ��ײ��СԲ����
	if ( ( (ball_y+radius >= bar_top) && (ball_y+radius < bar_bottom-bar_high/3) )
		||  ( (ball_y-radius <= bar_bottom) && (ball_y-radius > bar_top-bar_high/3) ) )
		if ( (ball_x>=bar_left) && (ball_x<=bar_right) )
				ball_vy = -ball_vy;

	// ����СԲ����
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;
	
	// СԲ�ͱ߽���ײ
	if ((ball_x==radius)||(ball_x==Width-radius))
		ball_vx = -ball_vx;
	if ((ball_y==radius)||(ball_y==High-radius))
		ball_vy = -ball_vy;	

	// �ж�СԲ�Ƿ��ĳ��ש����ײ
	int i,brick_left,brick_right,brick_bottom;
	for (i=0;i<Brick_num;i++)
	{
		if (isBrickExisted[i])	 // ש����ڣ����ж�
		{
			brick_left = i*brick_width;
			brick_right = brick_left + brick_width;
			brick_bottom = brick_high;
			if ( (ball_y==brick_bottom+radius) && (ball_x>=brick_left) && (ball_x<=brick_right) )
			{
				isBrickExisted[i] = 0;
				ball_vy = -ball_vy;	
			}
		}
	}
}

void updateWithInput()  // ���û������йصĸ���
{	
	MOUSEMSG m;		// ���������Ϣ
	if (MouseHit())  //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();  	// ��ȡһ�������Ϣ
		if(m.uMsg == WM_MOUSEMOVE)
		{
			// ����ƶ�ʱ�������λ�õ���������ڵ�λ��
			bar_x = m.x;
			bar_y = m.y;
			bar_left = bar_x - bar_width/2;
			bar_right = bar_x + bar_width/2;
			bar_top = bar_y - bar_high/2;
			bar_bottom = bar_y + bar_high/2;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			// ��������������ʼ��С���λ��Ϊ������������
			ball_x = bar_x;
			ball_y = bar_top - radius-3;
		}
	}
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

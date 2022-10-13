#include <graphics.h>
#include <math.h>
#include <time.h>

#define WIDTH		1024		// ��Ļ��
#define HEIGHT		768			// ��Ļ��
#define NUM_MOVERS	800			// С������
#define	FRICTION	0.96f		// Ħ����/����ϵ��

// ����С��ṹ
struct Mover
{
	COLORREF	color;			// ��ɫ
	float		x, 	y;			// ����
	float		vX,	vY;			// �ٶ�
	float       radius;         // �뾶
};

// ����ȫ�ֱ���
Mover	movers[NUM_MOVERS];		// С������
int		mouseX,		mouseY;			// ��ǰ�������
int		prevMouseX,	prevMouseY;		// �ϴ��������
int		mouseVX,	mouseVY;		// ����ٶ�
int		isMouseDown;				// �������Ƿ���

// ������ʱ
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();	
	while(GetTickCount() - oldtime < ms)
		Sleep(1);	
	oldtime = GetTickCount();
}

void startup()
{
	// �����������
	srand((unsigned int)time(NULL));

	// ��ʼ��С������
	for (int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x   = rand()%WIDTH;
		movers[i].y   = rand()%HEIGHT;
		movers[i].vX  = float(cos(float(i))) * (rand() % 34);
		movers[i].vY  = float(sin(float(i))) * (rand() % 34);
		movers[i].radius  = (rand() % 34)/15.0;
	}

	// ��ʼ������������ǰ������ꡢ�ϴ�������궼�ڻ�������
	mouseX = prevMouseX = WIDTH / 2;
	mouseY = prevMouseY = HEIGHT / 2;

	isMouseDown = 0; // ��ʼ���δ����

	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
}

void show()
{
	clearrectangle(0,0,WIDTH-1,HEIGHT - 1);	// ��ջ���ȫ����������

	for(int i = 0; i < NUM_MOVERS; i++)
	{
		// ��С��
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(movers[i].x + 0.5), int(movers[i].y + 0.5), int(movers[i].radius + 0.5));
	}
	
	FlushBatchDraw();
	delay(5);
}

void updateWithoutInput()
{
	float toDist   = WIDTH * 0.86;  // �������룬С���������ڴ˷�Χ�ڣ����ܵ����ڵ�����
	float blowDist = WIDTH * 0.5;   // ������룬С���������ڴ˷�Χ�ڣ����ܵ�����ĳ���
	float stirDist = WIDTH * 0.125; // �Ŷ����룬С���������ڴ˷�Χ�ڣ����ܵ������Ŷ�

	// ǰ���������м�����ƶ��ľ��룬��Ϊ�����ٶ�
	mouseVX    = mouseX - prevMouseX;
	mouseVY    = mouseY - prevMouseY;
	
	// �����ϴ�������������Ϊ��¼�����������
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	for(int i = 0; i < NUM_MOVERS; i++)  // ������С�����
	{
		float x  = movers[i].x;  // ��ǰС������
		float y  = movers[i].y;
		float vX = movers[i].vX;  // ��ǰС���ٶ�
		float vY = movers[i].vY;

		float dX = x - mouseX;    // ���㵱ǰС��λ�ú����λ�õĲ�
		float dY = y - mouseY; 
		float d  = sqrt(dX * dX + dY * dY);    // ��ǰС������λ�õľ���
		
		// ���潫dX��dY��һ��������ӳ���򣬺;��볤���޹ء�
		if (d!=0)
		{
			dX = dX/d;
			dY = dY/d;
		}
		else
		{
			dX = 0;
			dY = 0;
		}

		// С�������� < toDist���ڴ˷�Χ��С����ܵ���������
		if (d < toDist)
		{
			// ����������ļ��ٶȷ��ȣ�С��������Խ��������ļ��ٶ�Խ�󡣵���������ֵ���Ա����������ֵҪС�ܶ�
			float toAcc = (1 - (d / toDist)) * WIDTH * 0.0014f;
			// ��dX��dY��һ��������Ϣ�����ٶȷ���ֵtoAcc���õ��µ�С���ٶ�
			vX = vX - dX * toAcc;
			vY = vY - dY * toAcc;			
		}

		// �����������£�����С�������� < blowDist���ڴ����Χ�ڣ����ܵ����������
		if (isMouseDown && d < blowDist)
		{
			// ���������ļ��ٶȷ���(Acceleration)�������ʽ��ʾС��������Խ���������������ļ��ٶ�Խ��
			float blowAcc = (1 - (d / blowDist)) * 10;
			// ������õ���dX��dY��һ��������Ϣ������ļ��ٶȷ���ֵblowAcc���õ��µ�С���ٶ�
			//  float(rand()) / RAND_MAX ����[0,1]֮��������
			// 0.5f - float(rand()) / RAND_MAX ����[-0.5,0.5]֮��������������һЩ�Ŷ�
			vX = vX + dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY = vY + dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}

		// С�������� < stirDist���ڴ˷�Χ��С����ܵ������Ŷ�
		if (d < stirDist)
		{
			// �Ŷ�������ļ��ٶȷ��ȣ�С��������Խ��������ļ��ٶ�Խ���Ŷ�����ֵ��С
			float mAcc = (1 - (d / stirDist)) * WIDTH * 0.00026f;
			// ����ٶ�Խ�죬������Ŷ���Խ��
			vX = vX + mouseVX * mAcc;
			vY = vY + mouseVY * mAcc;			
		}

		// С���˶���һ�����ᣨĦ���������ٶ��𽥼���
		vX = vX * FRICTION;
		vY = vY * FRICTION;
		
		// �ٶȵľ���ֵ
		float avgVX = abs(vX);
		float avgVY = abs(vY);
		// ���������ٶȵ�ƽ��
		float avgV  = (avgVX + avgVY) * 0.5f;
		
		// ��Ϊ��������������ã�����ٶȹ�С�Ļ�������һ��[0,3]������������ԱȽϴ�ĸ������ٶȱ��
		if (avgVX < 0.1) 
			vX = vX * float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1) 
			vY = vY * float(rand()) / RAND_MAX * 3;
		
		// С��İ뾶��[0.4,3.5]֮�䣬�ٶ�Խ�󣬰뾶Խ��
		float sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		movers[i].radius = sc;
		
		// ����λ��+�ٶȣ�����С�������
		float nextX = x + vX;
		float nextY = y + vY;
		
		// С������������������ĸ��߽�Ļ���λ����Ϊ�߽紦���ٶȷ���
		if	(nextX > WIDTH)	
		{ 
			nextX = WIDTH;	
			vX = -1*vX; 
		}
		else if (nextX < 0)	
		{
			nextX = 0;		
			vX = -1*vX; 
		}
		if	(nextY > HEIGHT)
		{ 
			nextY = HEIGHT;	
			vY = -1*vY; 
		}
		else if (nextY < 0)	
		{ 
			nextY = 0;		
			vY = -1*vY; 
		}
		
		// ����С��λ�á��ٶȵĽṹ������
		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x  = nextX;
		movers[i].y  = nextY;
	}	
}

void updateWithInput()
{
	MOUSEMSG m;		// ���������Ϣ
	while (MouseHit())  //��⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.uMsg==WM_MOUSEMOVE) // ����ƶ��Ļ������µ�ǰ����������
		{
			mouseX = m.x;	
			mouseY = m.y;
		}
		else if (m.uMsg==WM_LBUTTONDOWN)  // ����������
			isMouseDown = 1;
		else if (m.uMsg==WM_LBUTTONUP)    // ������̧��
			isMouseDown = 0;
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
		show();  // ��ʾ����
		updateWithInput();     // ���û������йصĸ���
		updateWithoutInput();  // ���û������޹صĸ���
	}
	gameover();     // ��Ϸ��������������
	return 0;
}

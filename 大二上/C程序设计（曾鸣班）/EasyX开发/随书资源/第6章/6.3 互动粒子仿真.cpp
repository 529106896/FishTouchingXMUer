#include <graphics.h>
#include <math.h>
#include <time.h>

#define WIDTH		1024		// 屏幕宽
#define HEIGHT		768			// 屏幕高
#define NUM_MOVERS	800			// 小球数量
#define	FRICTION	0.96f		// 摩擦力/阻尼系数

// 定义小球结构
struct Mover
{
	COLORREF	color;			// 颜色
	float		x, 	y;			// 坐标
	float		vX,	vY;			// 速度
	float       radius;         // 半径
};

// 定义全局变量
Mover	movers[NUM_MOVERS];		// 小球数组
int		mouseX,		mouseY;			// 当前鼠标坐标
int		prevMouseX,	prevMouseY;		// 上次鼠标坐标
int		mouseVX,	mouseVY;		// 鼠标速度
int		isMouseDown;				// 鼠标左键是否按下

// 绝对延时
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();	
	while(GetTickCount() - oldtime < ms)
		Sleep(1);	
	oldtime = GetTickCount();
}

void startup()
{
	// 设置随机种子
	srand((unsigned int)time(NULL));

	// 初始化小球数组
	for (int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x   = rand()%WIDTH;
		movers[i].y   = rand()%HEIGHT;
		movers[i].vX  = float(cos(float(i))) * (rand() % 34);
		movers[i].vY  = float(sin(float(i))) * (rand() % 34);
		movers[i].radius  = (rand() % 34)/15.0;
	}

	// 初始化鼠标变量，当前鼠标坐标、上次鼠标坐标都在画布中心
	mouseX = prevMouseX = WIDTH / 2;
	mouseY = prevMouseY = HEIGHT / 2;

	isMouseDown = 0; // 初始鼠标未按下

	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
}

void show()
{
	clearrectangle(0,0,WIDTH-1,HEIGHT - 1);	// 清空画面全部矩形区域

	for(int i = 0; i < NUM_MOVERS; i++)
	{
		// 画小球
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(movers[i].x + 0.5), int(movers[i].y + 0.5), int(movers[i].radius + 0.5));
	}
	
	FlushBatchDraw();
	delay(5);
}

void updateWithoutInput()
{
	float toDist   = WIDTH * 0.86;  // 吸引距离，小球距离鼠标在此范围内，会受到向内的吸力
	float blowDist = WIDTH * 0.5;   // 打击距离，小球距离鼠标在此范围内，会受到向外的斥力
	float stirDist = WIDTH * 0.125; // 扰动距离，小球距离鼠标在此范围内，会受到鼠标的扰动

	// 前后两次运行间鼠标移动的距离，即为鼠标的速度
	mouseVX    = mouseX - prevMouseX;
	mouseVY    = mouseY - prevMouseY;
	
	// 更新上次鼠标坐标变量，为记录这次鼠标的坐标
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	for(int i = 0; i < NUM_MOVERS; i++)  // 对所有小球遍历
	{
		float x  = movers[i].x;  // 当前小球坐标
		float y  = movers[i].y;
		float vX = movers[i].vX;  // 当前小球速度
		float vY = movers[i].vY;

		float dX = x - mouseX;    // 计算当前小球位置和鼠标位置的差
		float dY = y - mouseY; 
		float d  = sqrt(dX * dX + dY * dY);    // 当前小球和鼠标位置的距离
		
		// 下面将dX、dY归一化，仅反映方向，和距离长度无关。
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

		// 小球距离鼠标 < toDist，在此范围内小球会受到鼠标的吸引
		if (d < toDist)
		{
			// 吸引力引起的加速度幅度，小球距离鼠标越近，引起的加速度越大。但吸引力的值明显比上面斥力的值要小很多
			float toAcc = (1 - (d / toDist)) * WIDTH * 0.0014f;
			// 由dX、dY归一化方向信息，加速度幅度值toAcc，得到新的小球速度
			vX = vX - dX * toAcc;
			vY = vY - dY * toAcc;			
		}

		// 当鼠标左键按下，并且小球距离鼠标 < blowDist（在打击范围内，会受到向外的力）
		if (isMouseDown && d < blowDist)
		{
			// 打击力引起的加速度幅度(Acceleration)，这个公式表示小球距离鼠标越近，打击斥力引起的加速度越大
			float blowAcc = (1 - (d / blowDist)) * 10;
			// 由上面得到的dX、dY归一化方向信息，上面的加速度幅度值blowAcc，得到新的小球速度
			//  float(rand()) / RAND_MAX 产生[0,1]之间的随机数
			// 0.5f - float(rand()) / RAND_MAX 产生[-0.5,0.5]之间的随机数，加入一些扰动
			vX = vX + dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY = vY + dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}

		// 小球距离鼠标 < stirDist，在此范围内小球会受到鼠标的扰动
		if (d < stirDist)
		{
			// 扰动力引起的加速度幅度，小球距离鼠标越近，引起的加速度越大。扰动力的值更小
			float mAcc = (1 - (d / stirDist)) * WIDTH * 0.00026f;
			// 鼠标速度越快，引起的扰动力越大
			vX = vX + mouseVX * mAcc;
			vY = vY + mouseVY * mAcc;			
		}

		// 小球运动有一个阻尼（摩擦力），速度逐渐减少
		vX = vX * FRICTION;
		vY = vY * FRICTION;
		
		// 速度的绝对值
		float avgVX = abs(vX);
		float avgVY = abs(vY);
		// 两个方向速度的平均
		float avgV  = (avgVX + avgVY) * 0.5f;
		
		// 因为有上面阻尼的作用，如果速度过小的话，乘以一个[0,3]的随机数，会以比较大的概率让速度变大
		if (avgVX < 0.1) 
			vX = vX * float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1) 
			vY = vY * float(rand()) / RAND_MAX * 3;
		
		// 小球的半径在[0.4,3.5]之间，速度越大，半径越大
		float sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		movers[i].radius = sc;
		
		// 根据位置+速度，更新小球的坐标
		float nextX = x + vX;
		float nextY = y + vY;
		
		// 小球如果超过上下左右四个边界的话，位置设为边界处，速度反向
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
		
		// 更新小球位置、速度的结构体数组
		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x  = nextX;
		movers[i].y  = nextY;
	}	
}

void updateWithInput()
{
	MOUSEMSG m;		// 定义鼠标消息
	while (MouseHit())  //检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg==WM_MOUSEMOVE) // 鼠标移动的话，更新当前鼠标坐标变量
		{
			mouseX = m.x;	
			mouseY = m.y;
		}
		else if (m.uMsg==WM_LBUTTONDOWN)  // 鼠标左键按下
			isMouseDown = 1;
		else if (m.uMsg==WM_LBUTTONUP)    // 鼠标左键抬起
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
	startup();  // 数据初始化	
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithInput();     // 与用户输入有关的更新
		updateWithoutInput();  // 与用户输入无关的更新
	}
	gameover();     // 游戏结束、后续处理
	return 0;
}

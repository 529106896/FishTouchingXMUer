#include <graphics.h>
#include <conio.h>
int main()
{	
	initgraph(640, 480); // 初始化图形窗口
	MOUSEMSG m;		// 定义鼠标消息	
	while(1)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();		
		if(m.uMsg == WM_MOUSEMOVE)
		{
			// 鼠标移动的时候在鼠标位置画白色的小点
			putpixel(m.x, m.y, WHITE);
		}			
		else if (m.uMsg == WM_LBUTTONDOWN)
		{ 
			// 鼠标左键按下时在鼠标位置画一个方块
			rectangle(m.x-5, m.y-5, m.x+5, m.y+5);
		}
		else if (m.uMsg == WM_RBUTTONUP)
		{ 
			// 鼠标右键按下又抬起后，画一个圆
			circle(m.x, m.y, 10);
		}
	}
	return 0;
}

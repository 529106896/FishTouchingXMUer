#include <graphics.h>
#include <conio.h>
int main()
{	
	initgraph(640, 480); // ��ʼ��ͼ�δ���
	MOUSEMSG m;		// ���������Ϣ	
	while(1)
	{
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();		
		if(m.uMsg == WM_MOUSEMOVE)
		{
			// ����ƶ���ʱ�������λ�û���ɫ��С��
			putpixel(m.x, m.y, WHITE);
		}			
		else if (m.uMsg == WM_LBUTTONDOWN)
		{ 
			// ����������ʱ�����λ�û�һ������
			rectangle(m.x-5, m.y-5, m.x+5, m.y+5);
		}
		else if (m.uMsg == WM_RBUTTONUP)
		{ 
			// ����Ҽ�������̧��󣬻�һ��Բ
			circle(m.x, m.y, 10);
		}
	}
	return 0;
}

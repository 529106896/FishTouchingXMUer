// ���ƹ�����������
#include <graphics.h>
#include <conio.h>
int main()
{
	int step = 50;
	// ��ʼ����ͼ����
	initgraph(500, 500);	
	// ���ñ���ɫΪ��ɫ
	setbkcolor(YELLOW);
	// �ñ���ɫ�����Ļ
	cleardevice();
	
	int i,j;
	for(i=1;i<=8;i++)  
	{
		for(j=1;j<=8;j++)  
		{
			if ((i+j)% 2 ==1)
			{
				setfillcolor(BLACK);
				solidrectangle(i*step,j*step,(i+1)*step,(j+1)*step); 	// ���ƺ�ɫ����
			}
			else
			{
				setfillcolor(WHITE);
				solidrectangle(i*step,j*step,(i+1)*step,(j+1)*step); 	// ���ư�ɫ����
			}
		}
	}
	getch();
	closegraph();
	return 0;
}

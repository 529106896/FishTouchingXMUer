#include<graphics.h>
#include<conio.h>

void main()
{
	//������
	int x,y;
	initgraph(390,550);
	setfillcolor(RGB(31,78,121));
	solidrectangle(0,0,390,550);

	//����
	setcolor(WHITE);
	setfillcolor(WHITE);
	for(x = 100; x<=290; x+=95)
	{
		fillcircle(x, 180, 4);	//��һ�ŵĵ�
	}
	for(x = 100; x<=290; x+=95)
	{
		fillcircle(x, 275, 4);	//��һ�ŵĵ�
	}
	for(x = 100; x<=290; x+=95)
	{
		fillcircle(x, 370, 4);	//��һ�ŵĵ�
	}
	
	getch();
	closegraph();

}
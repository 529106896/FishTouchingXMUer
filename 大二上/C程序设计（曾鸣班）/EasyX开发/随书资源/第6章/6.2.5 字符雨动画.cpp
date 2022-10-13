#include <graphics.h>
#include <time.h>
#include <conio.h>
#define High 800  // ��Ϸ����ߴ�
#define Width 1000
#define CharSize 25 // ÿ���ַ���ʾ�Ĵ�С
void main()
{
	int highNum = High/CharSize;
	int widthNum = Width/CharSize;
	// �洢��Ӧ�ַ���������Ҫ����ַ���ASCII��
	int CharRain[Width/CharSize][High/CharSize]; 
	int CNum[Width/CharSize]; // ÿһ�е���Ч�ַ�����
	int ColorG[Width/CharSize]; // ÿһ���ַ�����ɫ
	int i,j,x,y;
	srand((unsigned) time(NULL)); // ���������������
	for (i=0;i<widthNum;i++) // ��ʼ���ַ�����
	{
		CNum[i] = (rand() % (highNum*9/10)) + highNum/10; // ��һ�е���Ч�ַ�����
		ColorG[i] = 255;
		for (j=0;j<CNum[i];j++)
			CharRain[j][i] = (rand() % 26) + 65;  // ����A-Z�����ASCII��
	}
	initgraph(Width, High);
	BeginBatchDraw();
	setfont(25, 10, "Courier");	// ��������
	// ����ÿһ֡�����ַ������ƶ���Ȼ������������µ��ַ�
	while (1)
	{
		for (i=0;i<widthNum;i++)
		{
			if (CNum[i]<highNum-1)  // ����һ���ַ�û������ʱ
			{
				for (j=CNum[i]-1;j>=0;j--)  // �����ƶ�һ��
					CharRain[j+1][i] = CharRain[j][i];
				CharRain[0][i] =  (rand() % 26) + 65;  // ������Ĳ���A-Z�����ASCII��
				CNum[i] = CNum[i] +1; // ��һ�е���Ч�ַ��ĸ���+1
			}
			else // ��һ���ַ��Ѿ�����
			{
				if (ColorG[i]>40)
					ColorG[i] = ColorG[i] - 20; // ��������һ���𽥱䰵
				else
				{
					CNum[i] = (rand() % (highNum/3)) + highNum/10; // ��һ���ַ��ĸ���
					ColorG[i] = (rand() % 75) + 180;  // ��һ���ַ�����ɫ
					for (j=0;j<CNum[i];j++)  // ���³�ʼ����һ���ַ�
						CharRain[j][i] = (rand() % 26) + 65;  // ����A-Z�����ASCII��
				}
			}
		}
		// ��������ַ�����
		for (i=0;i<widthNum;i++)
		{
			x = i*CharSize; // ��ǰ�ַ���x����
			for (j=0;j<CNum[i];j++)
			{
				y = j*CharSize;  // ��ǰ�ַ���y����
				setcolor(RGB(0,ColorG[i],0));
				outtextxy(x, y, CharRain[j][i]); // �����ǰ�ַ�
			}
		}		
		FlushBatchDraw();
		Sleep(100);
		clearrectangle(0,0,Width-1,High-1);	// ��ջ���ȫ����������
	}	
	EndBatchDraw();
	getch();
	closegraph();
}

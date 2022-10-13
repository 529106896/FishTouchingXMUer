#include <graphics.h>
#include <time.h>
#include <conio.h>
#define High 800  // 游戏画面尺寸
#define Width 1000
#define CharSize 25 // 每个字符显示的大小
void main()
{
	int highNum = High/CharSize;
	int widthNum = Width/CharSize;
	// 存储对应字符矩阵中需要输出字符的ASCII码
	int CharRain[Width/CharSize][High/CharSize]; 
	int CNum[Width/CharSize]; // 每一列的有效字符个数
	int ColorG[Width/CharSize]; // 每一列字符的颜色
	int i,j,x,y;
	srand((unsigned) time(NULL)); // 设置随机函数种子
	for (i=0;i<widthNum;i++) // 初始化字符矩阵
	{
		CNum[i] = (rand() % (highNum*9/10)) + highNum/10; // 这一列的有效字符个数
		ColorG[i] = 255;
		for (j=0;j<CNum[i];j++)
			CharRain[j][i] = (rand() % 26) + 65;  // 产生A-Z的随机ASCII码
	}
	initgraph(Width, High);
	BeginBatchDraw();
	setfont(25, 10, "Courier");	// 设置字体
	// 下面每一帧，让字符向下移动，然后最上面产生新的字符
	while (1)
	{
		for (i=0;i<widthNum;i++)
		{
			if (CNum[i]<highNum-1)  // 当这一列字符没有填满时
			{
				for (j=CNum[i]-1;j>=0;j--)  // 向下移动一格
					CharRain[j+1][i] = CharRain[j][i];
				CharRain[0][i] =  (rand() % 26) + 65;  // 最上面的产生A-Z的随机ASCII码
				CNum[i] = CNum[i] +1; // 这一列的有效字符的个数+1
			}
			else // 这一列字符已经填满
			{
				if (ColorG[i]>40)
					ColorG[i] = ColorG[i] - 20; // 让满的这一列逐渐变暗
				else
				{
					CNum[i] = (rand() % (highNum/3)) + highNum/10; // 这一列字符的个数
					ColorG[i] = (rand() % 75) + 180;  // 这一列字符的颜色
					for (j=0;j<CNum[i];j++)  // 重新初始化这一列字符
						CharRain[j][i] = (rand() % 26) + 65;  // 产生A-Z的随机ASCII码
				}
			}
		}
		// 输出整个字符矩阵
		for (i=0;i<widthNum;i++)
		{
			x = i*CharSize; // 当前字符的x坐标
			for (j=0;j<CNum[i];j++)
			{
				y = j*CharSize;  // 当前字符的y坐标
				setcolor(RGB(0,ColorG[i],0));
				outtextxy(x, y, CharRain[j][i]); // 输出当前字符
			}
		}		
		FlushBatchDraw();
		Sleep(100);
		clearrectangle(0,0,Width-1,High-1);	// 清空画面全部矩形区域
	}	
	EndBatchDraw();
	getch();
	closegraph();
}

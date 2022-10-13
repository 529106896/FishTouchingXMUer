#include <graphics.h>
#include <conio.h>
int main()
{
	initgraph(480, 300);
	IMAGE img_human,img_walls;	// 定义 IMAGE 对象
	loadimage(&img_human, "D:\\行走素材图.jpg");
	loadimage(&img_walls, "D:\\walls.gif");
	int x,y; // 小人整体的坐标位置
	x = 250;
	y = 80;
	int left_i = 0;  // 向左行走动画的序号
	int right_i = 0; // 向右行走动画的序号
	char input;
	
	int maps[8][5] = {0}; // 存储地图信息，0为空地，1为墙
	int i,j;
	// 以下让地图四个边界为墙
	for (i=0;i<8;i++)
	{
		maps[i][0] = 1;
		maps[i][4] = 1;
	}
	for (j=0;j<5;j++)
	{
		maps[0][j] = 1;
		maps[7][j] = 1;
	}
	
	// 显示地图图案
	for (i=0;i<8;i++)
		for (j=0;j<5;j++)
			if (maps[i][j]==1)
				putimage(i*60,j*60,&img_walls);
			
			putimage(x,y,75,130,&img_human,0,0);
			BeginBatchDraw();
			
			while (1)
			{
				if(kbhit())  // 判断是否有输入
				{
					input = getch();  // 根据用户的不同输入来移动，不必输入回车
					if (input == 'a') // 左移
					{   
						clearrectangle(x,y,x+75,y+130);	// 清空画面全部矩形区域
						left_i++;
						if (x>60) // 没有达到左边的墙，才移动小人的坐标
							x = x-10;
						putimage(x,y,75,130,&img_human,left_i*75,0);	
						FlushBatchDraw();
						Sleep(1);
						if (left_i==3)
							left_i = 0;
					}
					else if (input == 'd')  // 右移
					{
						clearrectangle(x,y,x+75,y+130);	// 清空画面全部矩形区域
						right_i++;
						if (x<340) // 没有达到右边的墙，才移动小人的坐标
							x = x+10;
						putimage(x,y,75,130,&img_human,right_i*75,120);	
						FlushBatchDraw();
						Sleep(1);
						if (right_i==3)
							right_i = 0;				
					}
				}
			}
			return 0;
}

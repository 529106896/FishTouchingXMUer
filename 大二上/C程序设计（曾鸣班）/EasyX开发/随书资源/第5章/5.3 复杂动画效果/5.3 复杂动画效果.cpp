#include <graphics.h>
#include <conio.h>
int main()
{
	initgraph(480, 300);
	IMAGE img_human,img_walls;	// ���� IMAGE ����
	loadimage(&img_human, "D:\\�����ز�ͼ.jpg");
	loadimage(&img_walls, "D:\\walls.gif");
	int x,y; // С�����������λ��
	x = 250;
	y = 80;
	int left_i = 0;  // �������߶��������
	int right_i = 0; // �������߶��������
	char input;
	
	int maps[8][5] = {0}; // �洢��ͼ��Ϣ��0Ϊ�յأ�1Ϊǽ
	int i,j;
	// �����õ�ͼ�ĸ��߽�Ϊǽ
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
	
	// ��ʾ��ͼͼ��
	for (i=0;i<8;i++)
		for (j=0;j<5;j++)
			if (maps[i][j]==1)
				putimage(i*60,j*60,&img_walls);
			
			putimage(x,y,75,130,&img_human,0,0);
			BeginBatchDraw();
			
			while (1)
			{
				if(kbhit())  // �ж��Ƿ�������
				{
					input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
					if (input == 'a') // ����
					{   
						clearrectangle(x,y,x+75,y+130);	// ��ջ���ȫ����������
						left_i++;
						if (x>60) // û�дﵽ��ߵ�ǽ�����ƶ�С�˵�����
							x = x-10;
						putimage(x,y,75,130,&img_human,left_i*75,0);	
						FlushBatchDraw();
						Sleep(1);
						if (left_i==3)
							left_i = 0;
					}
					else if (input == 'd')  // ����
					{
						clearrectangle(x,y,x+75,y+130);	// ��ջ���ȫ����������
						right_i++;
						if (x<340) // û�дﵽ�ұߵ�ǽ�����ƶ�С�˵�����
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

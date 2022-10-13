#include <graphics.h>
#include <conio.h>
#include <math.h>
#define High 480  // ��Ϸ����ߴ�
#define Width 640
#define BallNum 15 // С�����

int main()
{
	float ball_x[BallNum],ball_y[BallNum]; // С�������
	float ball_vx[BallNum],ball_vy[BallNum]; // С����ٶ�
	float radius;  // С��İ뾶
	int i,j;

	radius = 20;

	for (i=0;i<BallNum;i++) // ���С���λ�����ٶ�
	{
		ball_x[i] = rand()%int(Width-4*radius) + 2*radius;
		ball_y[i] = rand()%int(High-4*radius) + 2*radius;
		ball_vx[i] = (rand()%2)*2 - 1;
		ball_vy[i] = (rand()%2)*2 - 1;
	}

	initgraph(Width, High);	
	BeginBatchDraw();

	while (1)
	{
		// ���ƺ��ߡ���ɫ����Բ
		setcolor(BLACK);
		setfillcolor(BLACK);
		for (i=0;i<BallNum;i++)
			fillcircle(ball_x[i], ball_y[i], radius);
		
		// ����СԲ����
		for (i=0;i<BallNum;i++)
		{
			ball_x[i] = ball_x[i] + ball_vx[i];
			ball_y[i] = ball_y[i] + ball_vy[i];
			
			// �ѳ����߽��С��������
			if (ball_x[i]<radius)
				ball_x[i] = radius;
			if (ball_y[i]<radius)
				ball_y[i] = radius;
			if (ball_x[i]>Width-radius)
				ball_x[i] = Width-radius;
			if (ball_y[i]>High-radius)
				ball_y[i] = High-radius;
		}
		
		// �ж��Ƿ��ǽ����ײ
		for (i=0;i<BallNum;i++)
		{	
			if ((ball_x[i]<=radius)||(ball_x[i]>=Width-radius))
				ball_vx[i] = -ball_vx[i];
			if ((ball_y[i]<=radius)||(ball_y[i]>=High-radius))
				ball_vy[i] = -ball_vy[i];	
		}
		
		float minDistances2[BallNum][2]; // ��¼ĳ��С�򣬾����������С��ľ��룬���С����±�
		for (i=0;i<BallNum;i++)
		{
			minDistances2[i][0] = 9999999;
			minDistances2[i][1] = -1;
		}
		
		// �������С������֮��ľ���ƽ��
		for (i=0;i<BallNum;i++)
		{
			for (j=0;j<BallNum;j++)
			{
				if (i!=j) // �Լ����Լ�����Ҫ��
				{
					float dist2;
					dist2 = (ball_x[i] - ball_x[j])*(ball_x[i] - ball_x[j])
						+ (ball_y[i] - ball_y[j])*(ball_y[i] - ball_y[j]);
					if (dist2<minDistances2[i][0])
					{
						minDistances2[i][0] = dist2;
						minDistances2[i][1] = j;
					}
				}
			}
		}	
		
		// �ж���֮���Ƿ���ײ
		for (i=0;i<BallNum;i++)
		{
			if (minDistances2[i][0]<=4*radius*radius) // ��С����С����ֵ��������ײ
			{
				j = minDistances2[i][1];
				// �����ٶ�				
				int temp;
				temp = ball_vx[i]; ball_vx[i] = ball_vx[j]; ball_vx[j] = temp;
				temp = ball_vy[i]; ball_vy[i] = ball_vy[j]; ball_vy[j] = temp;
				
				minDistances2[j][0] = 999999999; // ���⽻�������ٶȣ��ֻ�ȥ��
				minDistances2[j][1] = -1;
			}
		}
		
		// ���ƻ��ߡ���ɫ����Բ
		setcolor(YELLOW);
		setfillcolor(GREEN);
		for (i=0;i<BallNum;i++)
			fillcircle(ball_x[i], ball_y[i], radius);
		
		FlushBatchDraw();
		
		// ��ʱ
		Sleep(3);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

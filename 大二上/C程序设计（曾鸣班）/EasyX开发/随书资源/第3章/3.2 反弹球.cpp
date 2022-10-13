#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cwindow.h>

#define High 15  // ��Ϸ����ߴ�
#define Width 20

// ȫ�ֱ���
int ball_x,ball_y; // С�������
int ball_vx,ball_vy; // С����ٶ�
int position_x,position_y; // ������������
int ridus;  // ����뾶��С
int left,right; // ��������λ��
int canvas[High][Width] = {0}; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
// 0Ϊ�ո�1ΪС��O��2Ϊ����*��3Ϊ����#

void gotoxy(int x,int y)  //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup()  // ���ݳ�ʼ��
{
	ridus = 5;
	position_x = High-1;
	position_y = Width/2;
	left = position_y - ridus;
	right = position_y + ridus;

	ball_x = position_x-1;
	ball_y = position_y;
	ball_vx = -1;
	ball_vy = 1;
	canvas[ball_x][ball_y] = 1;	

	int k,i;
	for (k=left;k<=right;k++)  // ����
		canvas[position_x][k] = 2;	

	for (k=0;k<Width;k++)  // �Ӽ���ש��
		for (i=0;i<High/4;i++)  
			canvas[i][k] = 3;
}

void show()  // ��ʾ����
{
	gotoxy(0,0);    // ����ƶ���ԭ��λ�ã������ػ�����
	int i,j;
	for (i=0;i<High;i++)
	{
		for (j=0;j<Width;j++)
		{
			if (canvas[i][j]==0)
				printf(" ");   //   ����ո�
			else if (canvas[i][j]==1)
				printf("0");   //   ���С��0
			else if (canvas[i][j]==2)
				printf("*");   //   �������*
			else if (canvas[i][j]==3)
				printf("#");   //   ���ש��#
		}
		printf("|\n"); // ��ʾ�ұ߽�
	}
	for (j=0;j<Width;j++)
		printf("-"); // ��ʾ�±߽�
	printf("\n");
}	

void updateWithoutInput()  // ���û������޹صĸ���
{
	if (ball_x==High-2)
	{
		if ( (ball_y>=left) && (ball_y<=right) )   // �����嵲ס
		{			
		}
		else    // û�б����嵲ס
		{
			printf("��Ϸʧ��\n");
			system("pause");
			exit(0);
		}	
	}
	
	static int speed = 0;  
	if (speed<7)
		speed++;
	if (speed == 7)
	{
		speed = 0;
		
		canvas[ball_x][ball_y] = 0;		
		// ����С������
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;		
		canvas[ball_x][ball_y] = 1;
		
		// �����߽�󷴵�		
		if ((ball_x==0)||(ball_x==High-2))
			ball_vx = -ball_vx;
		if ((ball_y==0)||(ball_y==Width-1))
			ball_vy = -ball_vy;			
		
		// ����ש��󷴵�
		if (canvas[ball_x-1][ball_y]==3)
		{
			ball_vx = -ball_vx;
			canvas[ball_x-1][ball_y] = 0;
			printf("\a");
		}
	}
}

void updateWithInput()  // ���û������йصĸ���
{	
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a' && left>0)   
		{
			canvas[position_x][right] = 0;
			position_y--;  // λ������
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][left] = 2;
		}
		if (input == 'd' && right<Width-1)
		{
			canvas[position_x][left] = 0;
			position_y++;  // λ������
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][right] = 2;
		}
	}
}

int main()
{
	startup();  // ���ݳ�ʼ��	
	while (1)  //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();     // ���û������йصĸ���
	}
	return 0;
}

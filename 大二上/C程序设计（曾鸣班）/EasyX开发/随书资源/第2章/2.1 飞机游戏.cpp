#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// ȫ�ֱ���
int position_x,position_y; // �ɻ�λ��
int bullet_x,bullet_y; // �ӵ�λ��
int enemy_x,enemy_y; // �л�λ��
int high,width; //  ��Ϸ����ߴ�
int score; // �÷�

void gotoxy(int x,int y)  //����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor() // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void startup() // ���ݳ�ʼ��
{
	high = 20;
	width = 30;
	position_x = high/2;
	position_y = width/2;
	bullet_x = -2;
	bullet_y = position_y;
	enemy_x = 0;
	enemy_y = position_y;
	score = 0;

	HideCursor(); // ���ع��
}

void show()  // ��ʾ����
{
	gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������ػ�����
	int i,j;
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
		{
			if ((i==position_x) && (j==position_y))
				printf("*");  //   ����ɻ�*
			else if ((i==enemy_x) && (j==enemy_y))
				printf("@");  //   ����л�@
			else if ((i==bullet_x) && (j==bullet_y))
				printf("|");  //   ����ӵ�|
			else
				printf(" ");  //   ����ո�
		}
		printf("\n");
	}
	printf("�÷֣�%d\n",score);
}	

void updateWithoutInput()  // ���û������޹صĸ���
{	
	if (bullet_x>-1)
		bullet_x--; 
	
	if ((bullet_x==enemy_x) && (bullet_y==enemy_y))  // �ӵ����ел�
	{
		score++;                // ������1
		enemy_x = -1;           // �����µķɻ�
		enemy_y = rand()%width;
		bullet_x = -2;          // �ӵ���Ч
	}
	if (enemy_x>high)   // �л��ܳ���ʾ��Ļ
	{
		enemy_x = -1;           // �����µķɻ�
		enemy_y = rand()%width;
	}
	
	// �������Ƶл������ƶ����ٶȡ�ÿ������ѭ�������ƶ�һ�εл�
	// �����޸ĵĻ����û����������ٶȻ��Ǳ��ֺܿ죬������NPC���ƶ���ʾ���Խ���
	static int speed = 0;  
	if (speed<20)
		speed++;
	if (speed == 20)
	{
		enemy_x++;			
		speed = 0;
	}
}

void updateWithInput()  // ���û������йصĸ���
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == 'a')   
			position_y--;  // λ������
		if (input == 'd')
			position_y++;  // λ������
		if (input == 'w')
			position_x--;  // λ������
		if (input == 's')
			position_x++;  // λ������
		if (input == ' ')  // �����ӵ�
		{
			bullet_x = position_x-1;  // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
			bullet_y = position_y;
		}
		
	}
}

int main()
{
	startup();  // ���ݳ�ʼ��	
	while (1) //  ��Ϸѭ��ִ��
	{
		show();  // ��ʾ����
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
	return 0;
}


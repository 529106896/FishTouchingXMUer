#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

#define width 600
#define high 400
#define X 120
#define Y 80
#define distence 33

int x_man, y_man;         //ը���˵�����
int speed;                //ը�����ƶ����ٶ�
int map[X][Y] = { 0 };     
/*��ʼ�������ͼ��0Ϊ���ߺڿ飬1Ϊ����ը���ϰ���
2Ϊ��ը���ϰ���ͼ�㣬22Ϊʵ���ϰ�
3Ϊը����*/

int i = 0, turn = 0;        //ը����ѭ������  iΪ�����꣬jΪ������
//turn=0Ϊ���£�turn=1Ϊ���ϣ�turn=2����turn=3ʤ����turn=4����,turn=5����


IMAGE img_man,img_stop;

//���ϰ�ͼƬ�ڸǵĲ���ȫ�帳ֵ
void givedate(int x,int y)         
{
	int i, j;
	for (i = x; i < x + 3; i++)
	{
		for (j = y; j < y + 3; j++)
		{
			map[i][j] = 22;
		}
	}
	map[x][y] = 2;
}

//����ͼƬ
void loadpicture()     
{
	loadimage(&img_man, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\����\\����.jpg"));
	loadimage(&img_stop, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\���ϰ�.jpg"));
}

/*���ݳ�ʼ��*/ 
void startup()        
{
	x_man = 2;
	y_man = 2;
	putimage(x_man*10, y_man*10,distence, distence, &img_man, 0, 0);
}


/*��ͼ��ʼ��*/
void datemap()         
{
	initgraph(width, high);
	int i, j;
	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			if (i  == x_man&&j == y_man)
				map[i][j] = 3;
		}
	}
	/*���Ƶ�ͼ�ϰ�*/
	map[3][3*8] = 2;
	//givedate(3, 3 * 8);
	//��һ��
	map[2 * 3][2 * 3] = 2;
	//givedate(2 * 3, 2 * 3);
	map[2 * 3][4 * 3] = 2;
	//givedate(2 * 3,4 * 3);
	map[2 * 3][5 * 3] = 2;
	//givedate(2 * 3,5 * 3);
	map[2 * 3][6 * 3] = 2;
	map[2 * 3][8 * 3] = 2;
	map[2 * 3][10 * 3] = 2;
	//�ڶ���
	map[3 * 3][4 * 3] = 2;
	map[3 * 3][8 * 3] = 2;
	//������
	map[4 * 3][3] = 2;
	map[4 * 3][3 * 3] = 2;
	map[4 * 3][4 * 3] = 2;
	map[4 * 3][6 * 3] = 2;
	map[4 * 3][8 * 3] = 2;
	map[4 * 3][10 * 3] = 2;
	//������
	map[6 * 3][2 * 3] = 2;
	map[6 * 3][3 * 3] = 2;
	map[6 * 3][4 * 3] = 2;
	map[6 * 3][6 * 3] = 2;
	map[6 * 3][8 * 3] = 2;
	map[6 * 3][10 * 3] = 2;
	//������
	map[7 * 3][10 * 3] = 2;
	//������
	map[8 * 3][2 * 3] = 2;
	map[8 * 3][4 * 3] = 2;
	map[8 * 3][6 * 3] = 2;
	map[8 * 3][8 * 3] = 2;
	map[8 * 3][10 * 3] = 2;
	//�ڰ���
	map[10 * 3][2 * 3] = 2;
	map[10 * 3][3 * 3] = 2;
	map[10 * 3][4 * 3] = 2;
	map[10 * 3][6 * 3] = 2;
	map[10 * 3][8 * 3] = 2;
	map[10 * 3][10 * 3] = 2;
	//��ʮ��
	map[12 * 3][2 * 3] = 2;
	map[12 * 3][4 * 3] = 2;
	map[12 * 3][6 * 3] = 2;
	map[12 * 3][8 * 3] = 2;
	map[12 * 3][9 * 3] = 2;
	map[12 * 3][11 * 3] = 2;
	//��ʮ����
	map[13 * 3][6 * 3] = 2;
	map[13 * 3][8 * 3] = 2;
	//��ʮ����
	map[14 * 3][3] = 2;
	map[14 * 3][2 * 3] = 2;
	map[14 * 3][4 * 3] = 2;
	map[14 * 3][5 * 3] = 2;
	map[14 * 3][6 * 3] = 2;
	map[14 * 3][8 * 3] = 2;
	map[14 * 3][10 * 3] = 2;
	//��ʮ����
	map[16 * 3][2 * 3] = 2;
	map[16 * 3][4 * 3] = 2;
	map[16 * 3][6 * 3] = 2;
	map[16 * 3][8 * 3] = 2;
	map[16 * 3][10 * 3] = 2;
	//��ʮ����
	map[17 * 3][8 * 3] = 2;
	//��ʮ����
	map[18 * 3][2 * 3] = 2;
	map[18 * 3][4 * 3] = 2;
	map[18 * 3][6 * 3] = 2;
	map[18 * 3][7 * 3] = 2;
	map[18 * 3][8 * 3] = 2;
	map[18 * 3][10 * 3] = 2;
		
	
	BeginBatchDraw();
}

//��ʾ����
void show()
{
	int i, j;
	//cleardevice();

	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			if (map[i][j] == 2)
				putimage(i * 10, j * 10, &img_stop);
			//if (map[i][j] == 3)
				//putimage(x_man * 10, y_man * 10, distence, distence, &img_man, 0, 0);
		
		}
	}
	FlushBatchDraw();
}

// ���û������޹صĸ���
/*void updateWithoutInput()      
{

}*/

//���û������йصĸ���
void updateWithInput()          
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		if (ch == 'w'&&y_man>0)
		{
			cleardevice();
			i++;
			turn = 1;
			//if(map[x_man][y_man]!=22&& map[x_man][y_man] != 2)    //���ϰ���ײ���ж�
				y_man--;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}

		if (ch == 's'&&y_man+ distence / 10 + 1<Y)
		{
			cleardevice();
			i++;
			turn = 0;
			//if(map[x_man][y_man+ distence / 10]!=22&& map[x_man][y_man + distence / 10] != 2)
				y_man++;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}
		if (ch == 'a'&&x_man>0)
		{
			cleardevice();
			i++;
			turn = 2;
			//if(map[x_man][y_man]!=22&& map[x_man][y_man] != 2)
				x_man--;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}
		if (ch == 'd'&&x_man+ distence / 10 + 1<X)
		{
			cleardevice();
			i++;
			turn = 5;
			//if(map[x_man+ distence / 10][y_man]!=22&& map[x_man + distence / 10][y_man] != 2)
				x_man++;
			putimage(x_man * 10, y_man * 10, distence, distence, &img_man, i*distence, turn*distence);
			Sleep(1);
			if (i == 2)
				i = 0;
		}
	}
}

//��Ϸ����
void gameover()    
{
	_getch();
	closegraph();
	EndBatchDraw();
}

void main()
{
	loadpicture();//����ͼƬ
	startup();  // ���ݳ�ʼ��
	datemap();  //��ͼ��ʼ��
	
	while (1)  //  ��Ϸѭ��ִ��
	{
		updateWithInput();     // ���û������йصĸ���
		show();  // ��ʾ����
		//updateWithoutInput();  // ���û������޹صĸ���
		
	}
	gameover();     // ��Ϸ��������������
}

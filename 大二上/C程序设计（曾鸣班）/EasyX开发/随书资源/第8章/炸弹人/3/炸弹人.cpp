#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<windows.h>


#define width 600         //600*400�Ļ���
#define high 400
#define X 60            //��ͼ����ĺ�����
#define Y 40            //��ͼ�����������  
#define distence 30     //����ͼ��ĳ�����ȡ������ͼ��Ϊ�����Ρ�������
#define speed 2          //�����ƶ����ٶ�
#define control 10       //��������10

int x_man, y_man;         //ը���˵�����

int map[X][Y] = { 0 };     
/*��ʼ�������ͼ��0Ϊ���ߺڿ飬1Ϊ����ը���ϰ���
2Ϊ��ը���ϰ���ͼ�㣬22Ϊ�ϰ���ײ�ж���ֵ
3Ϊը����*/

int order = 0, turn = 0;        
//ը����ѭ������  orderΪ�����꣬jΪ������
//turn=0Ϊ���£�turn=1Ϊ���ϣ�turn=2����turn=3ʤ����turn=4����,turn=5����


IMAGE img_man, img_man1;
IMAGE img_stop, img_stop1;
IMAGE img_bk;

//���ϰ�ͼƬ�ڸǵĲ���ȫ�帳ֵ
void givedate(int x,int y)         
{
	map[x][y + 1] = 22;
	map[x][y + 2] = 22;
	map[x + 1][y] = 22;
	map[x + 1][y + 1] = 22;
	map[x + 1][y + 2] = 22;
	map[x + 2][y] = 22;
	map[x + 2][y + 1] = 22;
	map[x + 2][y + 2] = 22;
}

//����ͼƬ
void loadpicture()     
{
	loadimage(&img_man, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\����\\����.jpg"));
	loadimage(&img_stop, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\�ϰ�.jpg"));
	loadimage(&img_stop1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\�ϰ�1.jpg"));
	loadimage(&img_man1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\����\\����1.jpg"));
	loadimage(&img_bk, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\��ͼ.jpg"));
}

/*���ݳ�ʼ��*/ 
void startup()        
{
	x_man = 20;
	y_man = 20;
}


/*��ͼ��ʼ��*/
void datemap()         
{
	initgraph(width, high);
	/*���Ƶ�ͼ�ϰ�*/
	map[3][3*8] = 2;
	givedate(3, 3 * 8);
	//��һ��
	map[2 * 3][2 * 3] = 2;
	givedate(2 * 3, 2 * 3);
	map[2 * 3][4 * 3] = 2;
	givedate(2 * 3,4 * 3);
	map[2 * 3][5 * 3] = 2;
	givedate(2 * 3,5 * 3);
	map[2 * 3][6 * 3] = 2;
	givedate(2 * 3, 6 * 3);
	map[2 * 3][8 * 3] = 2;
	givedate(2 * 3, 8 * 3);
	map[2 * 3][10 * 3] = 2;
	givedate(2 * 3, 10 * 3);
	//�ڶ���
	map[3 * 3][4 * 3] = 2;
	givedate(3 * 3, 4 * 3);
	map[3 * 3][8 * 3] = 2;
	givedate(3 * 3, 8 * 3);
	//������
	map[4 * 3][3] = 2;
	givedate(4 * 3, 3);
	map[4 * 3][3 * 3] = 2;
	givedate(4 * 3, 3 * 3);
	map[4 * 3][4 * 3] = 2;
	givedate(4 * 3, 4 * 3);
	map[4 * 3][6 * 3] = 2;
	givedate(4 * 3, 6 * 3);
	map[4 * 3][8 * 3] = 2;
	givedate(4 * 3, 8 * 3);
	map[4 * 3][10 * 3] = 2;
	givedate(4 * 3, 10 * 3);
	//������
	map[6 * 3][2 * 3] = 2;
	givedate(6 * 3, 2 * 3);
	map[6 * 3][3 * 3] = 2;
	givedate(6 * 3, 3 * 3);
	map[6 * 3][4 * 3] = 2;
	givedate(6 * 3, 4 * 3);
	map[6 * 3][6 * 3] = 2;
	givedate(6 * 3, 6 * 3);
	map[6 * 3][8 * 3] = 2;
	givedate(6 * 3, 8 * 3);
	map[6 * 3][10 * 3] = 2;
	givedate(6 * 3, 10 * 3);
	//������
	map[7 * 3][10 * 3] = 2;
	givedate(7 * 3, 10 * 3);
	//������
	map[8 * 3][2 * 3] = 2;
	givedate(8 * 3, 2 * 3);
	map[8 * 3][4 * 3] = 2;
	givedate(8 * 3, 4 * 3);
	map[8 * 3][6 * 3] = 2;
	givedate(8 * 3, 6 * 3);
	map[8 * 3][8 * 3] = 2;
	givedate(8 * 3, 8 * 3);
	map[8 * 3][10 * 3] = 2;
	givedate(8 * 3, 10 * 3);
	//�ڰ���
	map[10 * 3][2 * 3] = 2;
	givedate(10 * 3, 2 * 3);
	map[10 * 3][3 * 3] = 2;
	givedate(10 * 3, 3 * 3);
	map[10 * 3][4 * 3] = 2;
	givedate(10 * 3, 4 * 3);
	map[10 * 3][6 * 3] = 2;
	givedate(10 * 3, 6 * 3);
	map[10 * 3][8 * 3] = 2;
	givedate(10 * 3, 8 * 3);
	map[10 * 3][10 * 3] = 2;
	givedate(10 * 3, 10 * 3);
	//��ʮ��
	map[12 * 3][2 * 3] = 2;
	givedate(12 * 3, 2 * 3);
	map[12 * 3][4 * 3] = 2;
	givedate(12 * 3, 4 * 3);
	map[12 * 3][6 * 3] = 2;
	givedate(12 * 3, 6 * 3);
	map[12 * 3][8 * 3] = 2;
	givedate(12 * 3, 8 * 3);
	map[12 * 3][9 * 3] = 2;
	givedate(12 * 3, 9 * 3);
	map[12 * 3][11 * 3] = 2;
	givedate(12 * 3, 11 * 3);
	//��ʮ����
	map[13 * 3][6 * 3] = 2;
	givedate(13 * 3, 6 * 3);
	map[13 * 3][8 * 3] = 2;
	givedate(13 * 3, 8 * 3);
	//��ʮ����
	map[14 * 3][3] = 2;
	givedate(14 * 3, 1 * 3);
	map[14 * 3][2 * 3] = 2;
	givedate(14 * 3, 2 * 3);
	map[14 * 3][4 * 3] = 2;
	givedate(14 * 3, 4 * 3);
	map[14 * 3][5 * 3] = 2;
	givedate(14 * 3, 5 * 3);
	map[14 * 3][6 * 3] = 2;
	givedate(14 * 3, 6 * 3);
	map[14 * 3][8 * 3] = 2;
	givedate(14 * 3, 8 * 3);
	map[14 * 3][10 * 3] = 2;
	givedate(14 * 3, 10 * 3);
	//��ʮ����
	map[16 * 3][2 * 3] = 2;
	givedate(16 * 3, 2 * 3);
	map[16 * 3][4 * 3] = 2;
	givedate(16 * 3, 4 * 3);
	map[16 * 3][6 * 3] = 2;
	givedate(16 * 3, 6 * 3);
	map[16 * 3][8 * 3] = 2;
	givedate(16 * 3, 8 * 3);
	map[16 * 3][10 * 3] = 2;
	givedate(16 * 3, 10 * 3);
	//��ʮ����
	map[17 * 3][8 * 3] = 2;
	givedate(17 * 3, 8 * 3);
	//��ʮ����
	map[18 * 3][2 * 3] = 2;
	givedate(18 * 3, 2 * 3);
	map[18 * 3][4 * 3] = 2;
	givedate(18 * 3, 4 * 3);
	map[18 * 3][6 * 3] = 2;
	givedate(18 * 3, 6 * 3);
	map[18 * 3][7 * 3] = 2;
	givedate(18 * 3, 7 * 3);
	map[18 * 3][8 * 3] = 2;
	givedate(18 * 3, 8 * 3);
	map[18 * 3][10 * 3] = 2;
	givedate(18 * 3, 10 * 3);
		
	
	BeginBatchDraw();
}

//��ʾ����
void show()
{
	int i, j;
	putimage(0, 0, &img_bk);

	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			
			if (map[i][j] == 2)
			{
				putimage(i * 10, j * 10, &img_stop1, NOTSRCERASE);
				putimage(i * 10, j * 10, &img_stop, SRCINVERT);
			}
				
				
		}
	}
	putimage(x_man, y_man, distence, distence, &img_man1, order*distence, turn*distence, NOTSRCERASE);
	putimage(x_man, y_man, distence, distence, &img_man, order*distence, turn*distence, SRCINVERT);
	FlushBatchDraw();
}

// ���û������޹صĸ���
/*void updateWithoutInput()      
{

}*/

//���û������йصĸ���
void updateWithInput()          
{
	static int num = 0;
	if ((GetAsyncKeyState(0x57) & 0x8000))//w 
	{
		if (num < control)
			num++;
		else if(num== control)
		{
			if (y_man>0)
			{

				order++;
				turn = 1;
		
				if (map[(x_man + distence / 2) / 10][y_man / 10] != 2 && map[(x_man + distence / 2) / 10][y_man / 10] != 22)
				{
					y_man = y_man - speed;
				}
			
			
				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(0x53) & 0x8000))//s
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (y_man + distence <high)
			{

				order++;
				turn = 0;
				
				if (map[(x_man + distence / 2) / 10][(y_man + distence) / 10] != 2 && map[(x_man + distence / 2) / 10][(y_man + distence) / 10] != 22)
				{
					y_man = y_man + speed;
				}

			
				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(0x41) & 0x8000))//a 
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (x_man>0)
			{
				order++;
				turn = 2;	
				if (map[x_man/10][(y_man + distence / 2)/10] != 22 && map[x_man / 10][(y_man + distence / 2) / 10] != 2)
				{
					x_man = x_man - speed;
				}
				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
		}
	}
	if ((GetAsyncKeyState(0x44) & 0x8000))//d
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (x_man + distence  <width)
			{
				order++;
				turn = 5;
				if (map[(x_man + distence) / 10][(y_man + distence / 2) / 10] != 22 && map[(x_man + distence) / 10][(y_man + distence / 2) / 10] != 2)
				{
					x_man = x_man + speed;
				}
			
				Sleep(1);
				if (order == 3)
					order = 0;
			}
			num = 0;
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
		show();  // ��ʾ����
		updateWithInput();     // ���û������йصĸ���
		//updateWithoutInput();  // ���û������޹صĸ���
		
	}
	gameover();     // ��Ϸ��������������
}

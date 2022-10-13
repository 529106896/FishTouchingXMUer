#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<windows.h>
#include<time.h>

#define width 600         //600*400�Ļ���
#define high 400
#define X 60            //��ͼ����ĺ�����
#define Y 40            //��ͼ�����������  
#define distence 30     //����ͼ��ĳ�����ȡ������ͼ��Ϊ�����Ρ�������
#define speed 2          //�����ƶ����ٶ�
#define control 10       //��������10
#define Boomwid 23       //ը����
#define Boomhig 33        //ը����
#define armewid 17        //���˿�
#define armehig 30       //���˸�

int x_man, y_man;         //ը���˵�����
int x_boom=-30, y_boom=-30;       //ը��������
int arme_x[3] = { 150,15 * 30,13 * 30 };           //���˵ĺ�����
int arme_y[3] = { 30,30,9*30 };            //���˵�������

int map[X][Y] = { 0 };
/*��ʼ�������ͼ��0Ϊ���ߺڿ飬1Ϊ����ը���ϰ���
2Ϊ��ը���ϰ���ͼ�㣬22Ϊ�ϰ���ײ�ж���ֵ
3Ϊը����*/

int order = 0, turn = 0;
//ը����ѭ������  orderΪ�����꣬turnΪ������
//turn=0Ϊ���£�turn=1Ϊ���ϣ�turn=2����turn=3ʤ����turn=4����,turn=5����
int boom_order = 0, boom_turn = 0;
//ը����ѭ�����ţ�boom_orderΪ������,boom_turnΪ������
int arme_order[3] = { 0 }, arme_turn[3] = { 0 };
//���˵�ѭ�����ţ�arme_orderΪ�����꣬arme_turnΪ������
int armenum = 3;

int whether = 0;       //����ը�������ı���
int boom = 0;          //�ж�ը���Ƿ�ը�ı�����0Ϊû�б�ը������0Ϊ��ը
int boom_up = 0, boom_down = 0, boom_left = 0, boom_right = 0;//�������ҵı�ը�ж�

int over = 1;       //��Ϸ�Ƿ���е��жϳ���  1Ϊ���У�0Ϊ�����˳���2Ϊʤ���˳�

clock_t begin, end;

IMAGE img_man, img_man1;
IMAGE img_stop, img_stop1;
IMAGE img_bk;
IMAGE img_boom, img_boom1;
IMAGE img_fail;
IMAGE img_arme,img_arme1;

//���ϰ�ͼƬ�ڸǵĲ���ȫ�帳ֵ
void givedate(int x, int y)
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
	loadimage(&img_man1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\����\\����1.jpg"));

	loadimage(&img_stop, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\�ϰ�.jpg"));
	loadimage(&img_stop1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\�ϰ�1.jpg"));

	loadimage(&img_bk, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ͼ\\��ͼ.jpg"));

	loadimage(&img_boom, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ը.jpg"));
	loadimage(&img_boom1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��ը1.jpg"));

	loadimage(&img_fail, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\fail.jpg"));

	loadimage(&img_arme, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��������ͼ.jpg"));
	loadimage(&img_arme1, _T("D:\\Գ\\��ĩ����ҵ\\�ز�\\��������ͼ1.jpg"));
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
	map[3][3 * 8] = 2;
	givedate(3, 3 * 8);
	//��һ��
	map[2 * 3][2 * 3] = 2;
	givedate(2 * 3, 2 * 3);
	map[2 * 3][4 * 3] = 2;
	givedate(2 * 3, 4 * 3);
	map[2 * 3][5 * 3] = 2;
	givedate(2 * 3, 5 * 3);
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

	if (whether > 0)
	{
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		//��ʾը��
	}
	if (boom > 0)
	{
		boom_turn = 1;
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
		putimage(x_boom, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		if (boom_up > 0)
		{
			boom_turn = 4;
			putimage(x_boom, y_boom - Boomhig, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom, y_boom - Boomhig, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		if (boom_down > 0)
		{
			boom_turn = 5;
			putimage(x_boom, y_boom + Boomhig, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom, y_boom + Boomhig, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		if (boom_left > 0)
		{
			boom_turn = 2;
			putimage(x_boom - Boomwid, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom - Boomwid, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		if (boom_right > 0)
		{
			boom_turn = 3;
			putimage(x_boom + Boomwid, y_boom, Boomwid, Boomhig, &img_boom1, boom_order*Boomwid, boom_turn*Boomhig, NOTSRCERASE);
			putimage(x_boom + Boomwid, y_boom, Boomwid, Boomhig, &img_boom, boom_order*Boomwid, boom_turn*Boomhig, SRCINVERT);
		}
		boom_turn = 0;
	}


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
	//��ʾը����
	
	for (i = 0; i < 3; i++)
	{
		putimage(arme_x[i], arme_y[i], armewid, armehig, &img_arme1, arme_order[i]*armewid, arme_turn[i]*armehig, NOTSRCERASE);
		putimage(arme_x[i], arme_y[i], armewid, armehig, &img_arme, arme_order[i]*armewid, arme_turn[i]*armehig, SRCINVERT);
	}

	FlushBatchDraw();
	if (over == 0)
	{
		putimage(0, 0, &img_fail);
		FlushBatchDraw();
		Sleep(100);
		exit(0);
	}
	if (armenum == 0)
	{
		Sleep(100);
		exit(0);
	}
	
}

//���û������޹صĸ���
void updateWithoutInput()
{
	static int x = 0;              //ը����ըʱ���ж�
	if (whether>0)
	{
		if (x < 5)
			x++;
		if (x == 5)
		{
			boom_order++;
			if (boom_order == 3)
				boom_order = 0;
		}
		end = clock();
		if (((double)end - begin) / CLK_TCK >2)
		{
			begin = clock();
			boom = 1;
			
		}
	}
	if (boom > 0)                   //ը����ը��ʱ���ж�
	{
		if (x < 5)
			x++;
		if (x == 5)
		{
			boom_order++;
			if (boom_order == 3)
				boom_order = 0;
		}
		end = clock();
		if (((double)end - begin) / CLK_TCK >0.5)
		{
			boom = 0;
			whether = 0;
		}
		if (map[(x_boom + 5) / 10 - Boomhig/10][(y_boom + 5) / 10 + 1] == 0)       //ը���Ϸ��ı�ը�ж�   y+1Ϊ�˱������м��ж�
			boom_up++;
		if (map[(x_boom + 5) / 10 + Boomhig / 10][(y_boom + 5) / 10 + 1] == 0)      //ը���·��ı�ը�ж�   
			boom_down++;
		if (map[(x_boom + 5) / 10 + 1][(y_boom + 5) / 10 - Boomwid / 10] == 0)     //ը�����ı�ը�ж�
			boom_left++;
		if (map[(x_boom+5) / 10 + 1][(y_boom +5)/ 10 + Boomwid / 10] == 0)      //ը���Ҳ�ı�ը�ж�
			boom_right++;
		
		//ը���˺��ж�
		if (x_man <= x_boom + 2*Boomwid&&x_man >= x_boom - Boomwid)
		{
			if (y_man <= y_boom + Boomhig&&y_man >= y_boom)
			{
				over = 0;
			}
		}
		if (y_man <= y_boom + 2 * Boomhig&&y_man >= y_boom - Boomhig)
		{
			if (x_man <= x_boom + Boomwid&&x_man >= x_boom)
			{
				over = 0;
			}
		}
	}
	
	//�����ƶ�����ģ��
	static int armespeed[3] = { 0 };  //�����ƶ�����
	//����1
	if (arme_x[0] == 150 && arme_y[0] == 30)  //����ת
	{
		arme_turn[0] = 1;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	}
	else if (arme_x[0] == 150 && arme_y[0] == 150)       //����ת
	{
		arme_turn[0] = 2;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	} 
	else if (arme_x[0] == 13 * 30 && arme_y[0] == 150)   //����ת
	{
		arme_turn[0] = 3;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	}
	else if (arme_x[0] == 13 * 30 && arme_y[0] == 30)     //����ת
	{
		arme_turn[0] = 0;
		arme_order[0]++;
		if (arme_order[0] == 3)
			arme_order[0] = 0;
	}
	//����1�ƶ�
	if (arme_x[0] == 150 && arme_y[0] < 150)           //�����ƶ�
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_y[0]++;
		}
	}		
	else if (arme_x[0] == 13 * 30 && arme_y[0] > 30)    //�����ƶ�
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_y[0]--;
		}
	}		
	else if (arme_y[0] == 150 && arme_x[0] < 13 * 30)   //�����ƶ�
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_x[0]++;
		}
	}		
	else if (arme_y[0] == 30 && arme_x[0] > 150)       //�����ƶ�
	{
		if (armespeed[0] < 10)
			armespeed[0]++;
		if (armespeed[0] == 10)
		{
			armespeed[0] = 0;
			arme_x[0]--;
		}
	}		

	//����2
	if (arme_x[1] == 15*30 && arme_y[1] == 30)  //����ת
	{
		arme_turn[1] = 1;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	else if (arme_x[1] == 15 * 30 && arme_y[1] == 7 * 30)   //����ת
	{
		arme_turn[1] = 2;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	else if (arme_y[1] == 7 * 30 && arme_x[1] == 17 * 30)   //����ת
	{
		arme_turn[1] = 3;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	else if (arme_x[1] == 17 * 30 && arme_y[1] == 30)       //����ת
	{
		arme_turn[1] = 0;
		arme_order[1]++;
		if (arme_order[1] == 3)
			arme_order[1] = 0;
	}
	//����2�ƶ�
	if (arme_x[1] == 15 * 30 && arme_y[1] < 7 * 30)     //�����ƶ�
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_y[1]++;
		}
	}
	else if (arme_y[1] == 7 * 30 && arme_x[1] < 17 * 30)    //�����ƶ�
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_x[1]++;
		}
	}
	else if (arme_x[1] == 17 * 30 && arme_y[1] > 30)      //�����ƶ�
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_y[1]--;
		}
	}
	else if (arme_y[1] == 30 && arme_x[1] > 15 * 30)       //�����ƶ�
	{
		if (armespeed[1] < 10)
			armespeed[1]++;
		if (armespeed[1] == 10)
		{
			armespeed[1] = 0;
			arme_x[1]--;
		}
	}

	//����3
	if(arme_x[2] == 13*30 && arme_y[2] == 9*30)  //����ת
	{
		arme_turn[2] = 1;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	if (arme_x[2] == 13 * 30 && arme_y[2] == 11 * 30)       //����ת
	{
		arme_turn[2] = 2;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	if (arme_x[2] == 17 * 30 && arme_y[2] == 11 * 30)        //����ת
	{
		arme_turn[2] = 3;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	if (arme_x[2] == 17 * 30 && arme_y[2] == 9 * 30)         //����ת
	{
		arme_turn[2] = 0;
		arme_order[2]++;
		if (arme_order[2] == 3)
			arme_order[2] = 0;
	}
	//����3�ƶ�
	if (arme_x[2] == 13 * 30 && arme_y[2] < 11 * 30)         //�����ƶ�
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_y[2]++;
		}
	}
	else if (arme_y[2] == 11 * 30 && arme_x[2] < 17 * 30)            //�����ƶ�
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_x[2]++;
		}
	}
	else if (arme_x[2] == 17 * 30 && arme_y[2] > 9 * 30)          //�����ƶ�
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_y[2]--;
		}
	}
	else if (arme_y[2] == 9 * 30 && arme_x[2] > 13 * 30)         //�����ƶ�
	{
		if (armespeed[2] < 10)
			armespeed[2]++;
		if (armespeed[2] == 10)
		{
			armespeed[2] = 0;
			arme_x[2]--;
		}
	}
}

//���û������йصĸ���
void updateWithInput()
{
	static int num = 0;
	if ((GetAsyncKeyState(0x57) & 0x8000))//w 
	{
		if (num < control)
			num++;
		else if (num == control)
		{
			if (y_man>30)
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
			if (y_man + distence <high-30)
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
			if (x_man>30)
			{
				order++;
				turn = 2;
				if (map[x_man / 10][(y_man + distence / 2) / 10] != 22 && map[x_man / 10][(y_man + distence / 2) / 10] != 2)
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
			if (x_man + distence  <width-30)
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
	if ((GetAsyncKeyState(VK_SPACE)))
	{
		if (whether == 0)
		{
			begin = clock();
			x_boom = x_man;
			y_boom = y_man;
			whether++;
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
		updateWithoutInput();  // ���û������޹صĸ���
	}
	gameover();     // ��Ϸ��������������
}

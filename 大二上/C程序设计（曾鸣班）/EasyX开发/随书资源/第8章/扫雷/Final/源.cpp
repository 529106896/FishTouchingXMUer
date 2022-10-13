#include<stdlib.h>
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<windows.h> 
#include<math.h>
#include<conio.h>
#define sm_len 20
#define NBomb 10
#pragma comment(lib,"Winmm.lib")


int map[20][20];//��Ҫ��ͼ 10��ʾ���ף�2��ʾ��ǣ�3��ʾ����
int mask[20][20];//��ͼ����  -1��ʾδ������Ϊ�ո���(init) 3��ʾ�Ѿ����� 1��ʾ�ʺ� 2��ʾ���
int Mx, My;//���λ��
int mark = 0;//ǿ�ƽ��� 0��ʾ���Լ�����1��ʾ�˳�ѭ������Ϸ����
int jud = 0;//ʤ���ж� 0��ʾ��ʼ״̬��δʤ����1��ʾʤ��
SYSTEMTIME start;//��ʱģ��



IMAGE  num_2[9];//����ʾ���û�����Χ�׵�ͼƬ����Ԥ����
IMAGE  bomb_2_1;//��ɫΪ��ɫ�ĵ��ף����ڱ�ը����ʾ���û���
IMAGE  bomb_2_2;//��ɫΪ��ɫ�ĵ��ף�������ʾ����û�������׵�λ��
IMAGE  flag_2_1;//���ڱ�ʾС����
IMAGE  flag_2_2;//���ڱ�־�ʺŵ�ͼƬԤ����
IMAGE  StateSetUp;//����Ԥ�����ʼ�����ұ�״̬
IMAGE  StateVictory;//���ڶ���ʤ�����ұߵ�״̬
IMAGE  StateFailure;//���ڶ���ʧ�ܺ��ұߵ�״̬
IMAGE masks_2[10];//�����ұߵļ�ʱ�����õ�������
IMAGE Background;//���屳��ͼƬ
IMAGE dot;//������ʾ���Ҳ�״̬����ĵ�
IMAGE Score;//������ʾ�ų��ĵ���


//��������ĺ���������Ԥ����ͼƬ
void drawinit()
{
	loadimage(&num_2[0], "./images/pg1.bmp");//������ʾ�Ѿ������Ŀո�
	loadimage(&num_2[1], "./images/p1.bmp");
	loadimage(&num_2[2], "./images/p2.bmp");
	loadimage(&num_2[3], "./images/p3.bmp");
	loadimage(&num_2[4], "./images/p4.bmp");
	loadimage(&num_2[5], "./images/p5.bmp");
	loadimage(&num_2[6], "./images/p6.bmp");
	loadimage(&num_2[7], "./images/p7.bmp");
	loadimage(&num_2[8], "./images/p8.bmp");
	//���ϵ�Ϊ�������ʾ��Χ�׵ĸ���
	loadimage(&bomb_2_1, "./images/bomb.bmp");
	loadimage(&bomb_2_2, "./images/redbomb.bmp");
	loadimage(&Score, "./images/r1.bmp");
	//����Ϊ�����ը����ʾ���׼���ص�ͼƬ
	loadimage(&flag_2_1, "./images/flag.bmp");
	loadimage(&flag_2_2, "./images/flag2.bmp");
	//����Ϊ�һ����ʺ��Լ����ı�ʶ
	loadimage(&masks_2[0], "./images/t0.bmp");
	loadimage(&masks_2[1], "./images/t1.bmp");
	loadimage(&masks_2[2], "./images/t2.bmp");
	loadimage(&masks_2[3], "./images/t3.bmp");
	loadimage(&masks_2[4], "./images/t4.bmp");
	loadimage(&masks_2[5], "./images/t5.bmp");
	loadimage(&masks_2[6], "./images/t6.bmp");
	loadimage(&masks_2[7], "./images/t7.bmp");
	loadimage(&masks_2[8], "./images/t8.bmp");
	loadimage(&masks_2[9], "./images/t9.bmp");
	loadimage(&dot, "./images/dot.bmp");
	//����Ϊʱ�ӵ���ʾ
	loadimage(&StateSetUp, "./images/r2.bmp");
	loadimage(&StateVictory, "./images/r3.bmp");
	loadimage(&StateFailure, "./images/r4.bmp");
	//����Ϊ״̬����ͼƬ
	loadimage(&Background, "./images/bg.bmp");//����ͼ
	return;
}

void Setup()//���ݵĳ�ʼ��
{
	int i, j, k;
	int x, y;//���׵���ʱ����
	srand((int)time(0));//�������׼��
	//����Ϊ�Ե��ײ��Լ���ʾ��ĳ�ʼ��
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			mask[j][i] = -1;
		}
	}
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			map[j][i] = 0;
		}
	}
	//����Ϊ��4������ķֱ���
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10 + 10;
		y = rand() % 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10;
		y = rand() % 10 + 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	for (k = 0; k < NBomb; k++)
	{
		x = rand() % 10 + 10;
		y = rand() % 10 + 10;
		if (map[y][x] != 10)
		{
			map[y][x] = 10;
		}
		else
		{
			k--;
		}
	}
	//���Ҳ�״̬�Լ���ʱ���ĳ�ʼ��
	putimage(736, 460, &dot);
	putimage(736, 481, &dot);
	putimage(640, 80, &StateSetUp);
}


void Show()//ÿ�ζ������»���
{
	int i, j;
	BeginBatchDraw();//��ʼ������ͼ
	putimage(0, 0, &Background);//�Ա���ͼ�ĳ�ʼ��
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (mask[j][i] == 2 )
			{
				putimage(i * 32, j * 32, &flag_2_1);//����ȫ�ֲ��ұ�ǳ�����
			}
			if (mask[j][i] == 1)
			{
				putimage(i * 32, j * 32, &flag_2_2);//����ȫ�ֲ��ұ���ʺ�
			}
			if (map[j][i] == 3 && mask[j][i] == 0)
			{
				putimage(i * 32+1, j * 32+1, &num_2[0]);//����ȫ�ֲ�����ʾ�������ĸ���
			}
			//����ȫ�ֲ�����ʾ����Χ�׵�����1-8
			if (map[j][i] == 11 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[1]);
			}
			if (map[j][i] == 22 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[2]);
			}
			if (map[j][i] == 33 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[3]);
			}
			if (map[j][i] == 44 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[4]);
			}
			if (map[j][i] == 55 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[5]);
			}
			if (map[j][i] == 66 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[6]);
			}
			if (map[j][i] == 77 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[7]);
			}
			if (map[j][i] == 88 && mask[j][i] == 0)
			{
				putimage(i * 32 + 1, j * 32 + 1, &num_2[8]);
			}
		}
	}
	EndBatchDraw();//������ͼ
}








int poi_sum(int x, int y, int size)//ͳ����Χ8���������׵�����
{
	int sum;
	int nx, ny;
	int lei;
	lei = 10;
	sum = 0;

	nx = x - 1, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x - 1, ny = y;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x - 1, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y + 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x + 1, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}
	nx = x, ny = y - 1;
	if (nx >= 0 && ny >= 0 && nx < size && ny < size)
	{
		if (map[ny][nx] == lei)
		{
			sum++;
		}
	}

	return sum;
}

void do_null(int x, int y)//�����յ㴦������ǿո��ӣ�����ʾ����������
{

	map[y][x] = 3;
	return;
}

void not_null(int x, int y, int nums)//�����ǿմ��������Χ���ף�����ʾ��Χ�׵ĸ���
{
	if (nums == 1)
	{
		map[y][x] = 11;
	}
	if (nums == 2)
	{
		map[y][x] = 22;
	}
	if (nums == 3)
	{
		map[y][x] = 33;
	}
	if (nums == 4)
	{
		map[y][x] = 44;
	}
	if (nums == 5)
	{
		map[y][x] = 55;
	}
	if (nums == 6)
	{
		map[y][x] = 66;
	}
	if (nums == 7)
	{
		map[y][x] = 77;
	}
	if (nums == 8)
	{
		map[y][x] = 88;
	}
	return;
}

void duires(int n_x, int n_y, int size)
{
	typedef struct dui {
		int x;
		int y;
	}*duis;

	duis du;
	int head, tail, leis, tx, ty, i;
	du = (duis)malloc(sizeof(dui)*size*size);

	//��ʼ��
	head = 0;
	tail = 1;

	du[head].x = n_x;
	du[head].y = n_y;


	leis = poi_sum(n_x, n_y, size);
	if (leis > 0)//�ж���Χ�Ƿ�����
	{
		free(du);
		not_null(n_x, n_y, leis);
		return;
	}

	mask[n_y][n_x] = 0;

	while (head != tail)//��ͷβ��Ų����ʱ��ѭ��ִ�����²���
	{
		n_x = du[head].x;//��ȡͷ�����ָ������
		n_y = du[head].y;//��ȡͷ�����ָ������
		leis = poi_sum(n_x, n_y, size);
		if (leis > 0)
		{
			not_null(n_x, n_y, leis);
		}
		else
		{
			for (i = 0; i < 9; i++)//���ѭ��
			{

				tx = n_x + i % 3 - 1; ty = n_y + i / 3 - 1;//��ǰ�㸽����9����
				if (tx == n_x && ty == n_y)//�ų�����
				{
					continue;
				}
				if (tx >= 0 && ty >= 0 && tx <size && ty < size && mask[ty][tx] == -1)//�������ж�����ʱ
				{
					leis = poi_sum(tx, ty, size);//������ʱ����Χ����Ŀ
					mask[ty][tx] = 0;
					if (leis > 0)
					{
						not_null(tx, ty, leis);
					}
					else
					{
						do_null(tx, ty);
						du[tail].x = tx;
						du[tail].y = ty;
						tail++;//βָ���һ
					}
				}
			}
		}
		head++;//ͷָ�����һλ
	}
	free(du);//��Ӧmalloc
}




void Control()
{
	int x, y;
	int i, j;
	MOUSEMSG m;
	m = GetMouseMsg();//�����λ�õĻ�ȡ������
	if (m.uMsg == WM_MOUSEMOVE)//������λ�õĸ��٣�����ѡ�п�
	{
		x = m.x / 32;
		y = m.y / 32;
		if (x < 20 && y < 20)
		{
			setlinestyle(PS_SOLID, 4);
			setlinecolor(0x58d827);
			rectangle(32 * x, 32 * y, 32 * x + 32, 32 * y + 32);
		}
	}
	if (m.uMsg == WM_LBUTTONDOWN)//�������ж�
	{
		x = m.x / 32;
		y = m.y / 32;
		if (mask[y][x] != 2)//��������ʾ������½��в���
		{
			if (map[y][x] == 0)//�ڵ����û���׵������
			{
				map[y][x] = 3;
				duires(x, y, 20);//���ݸ����ĳ���
			}
			for (i = 1; i < 9; i++)
			{
				if (map[y][x] == 11 * i)//�����Χ�����֣���ֹͣ���ٴα����
				{
					mask[y][x] = 0;
				}
			}
			if (map[y][x] == 10)//����������ж�
			{
				for (i = 0; i < 20; i++)
				{
					for (j = 0; j < 20; j++)
					{
						if (map[j][i] == 10)//�Ե����׺��ͼ����ʾ
						{
							if (j == y&&i == x)
							{
								putimage(i * 32 + 1, j * 32 + 1, &bomb_2_2);
							}
							else if(mask[j][i]==2)
							{
								putimage(i * 32 + 1, j * 32 + 1, &Score);
							}
							else
							{
								putimage(i * 32 + 1, j * 32 + 1, &bomb_2_1);
							}
						}
					}
				}
				mark = 1;//ǿ�ƽ���
				//����Ϊ��ը�������
				mciSendString("stop fmusic", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
				mciSendString("close fmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
				mciSendString("open .\\audio\\fail.mp3 alias fmusic", NULL, 0, NULL); // ��ʧ������
				mciSendString("play fmusic", NULL, 0, NULL); // ������һ��
			}
		}
		//����Ϊ���������������
		mciSendString("stop cmusic", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
		mciSendString("close cmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString("open .\\audio\\click.wav alias cmusic", NULL, 0, NULL); // ����������
		mciSendString("play cmusic", NULL, 0, NULL); // ������һ��
	}
	if (m.uMsg == WM_RBUTTONDOWN)//�һ����ڱ���ʺ��Լ�����
	{
		x = m.x / 32;
		y = m.y / 32;
		if (mask[y][x] != 2 && mask[y][x] != 1 && mask[y][x] != 0)
		{
			mask[y][x] = 2;
		}
		else if (mask[y][x] == 1)//�������
		{
			mask[y][x] = -1;
		}
		else if (mask[y][x] == 2)//����ʺ�
		{
			mask[y][x] = 1;
		}
	}
}



void Time()
{
	int t1, t2;
	int i, j;
	int a, b;
	int sum;
	SYSTEMTIME ti;
	sum = 0;
	GetLocalTime(&ti);		// ��ȡ��ǰʱ��
	sum += ti.wHour - start.wHour;
	sum *= 60;
	sum += ti.wMinute - start.wMinute;
	sum *= 60;
	sum += ti.wSecond - start.wSecond;
	i = 0;
	j = 0;
	t1 = sum;
	t2 = sum / 60;//��ʱ����Ӻ������Ļ���
	while (i != 2)
	{
		if (i == 0)
		{
			t1 = sum % 60;
		}
		a = t1 % 10;
		putimage(780 - 32 * i, 450, &masks_2[a]);//��ʾ����
		t1 = t1 / 10;
		i++;
	}
	while (j != 2)
	{
		b = t2 % 10;
		putimage(700 - 32 * j, 450, &masks_2[b]);//��ʾ����
		t2 = t2 / 10;
		j++;
	}
}


void Judge()
{
	int i, j;
	int cnt;
	cnt = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (mask[i][j] == 2 && map[i][j] == 10)//ʤ���ж�
			{
				cnt++;
			}
		}
	}
	if (cnt == 4 * NBomb)//ʤ��������Ϸ������������
	{
		mark = 1;
		jud = 1;
		mciSendString("stop wmusic", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
		mciSendString("close wmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
		mciSendString("open .\\audio\\win.mp3 alias wmusic", NULL, 0, NULL); // ��ʤ������
		mciSendString("play wmusic", NULL, 0, NULL); // ������һ��
	}
}

int main()
{
	int op = 1;
	char input;
	initgraph(840, 640);//��ʼ����ͼ
	GetLocalTime(&start);//��ȡϵͳʱ��
	drawinit();//Ԥ����ͼƬ
	Setup();//��ʼ������
	do//����������������
	{
		while (1)
		{
			Judge();
			Show();
			Time();
			Control();	
			Sleep(5);
			if (mark == 1)//ǿ�ƽ���
			{
				if (jud == 1)
				{
					putimage(640, 80, &StateVictory);//��ʾʤ��ͼƬ
				}
				else
				{
					putimage(640, 80, &StateFailure);//��ʾʧ��ͼƬ
				}
				input = _getch();//�����û����жϣ��Ƿ����¿�ʼ��Ϸ
				if (input == 'y')
				{
					op = 1;
					mark = 0;
					jud = 0;
					initgraph(840, 640);
					GetLocalTime(&start);
					drawinit();
					Setup();
				}
				if (input == 'n')
				{
					op = 0;
					break;
				}
			}
		}
	} while (op==1);//������Ϸ
	closegraph();//�رջ�ͼ
	return 0;
}

//��ʾ��� ����������ƶ�

//����1����������ƶ�ʱ����ͣ��
//GetAsyncKeyState���
//����2������ͼ����ҵĴ�С��������
//loadimage�����
//����3������ܳ��߽�
//��ҿ����ƶ���������


#include<graphics.h>
#include<conio.h>


#define length 1000//��Ϸ������
#define high 640//��Ϸ����߶�


struct yu
{
	double position_x;//������
	double position_y;//������
	double v_x;//ˮƽ�ٶ�
	double v_y;//��ֱ�ٶ�
};
yu player;//���

IMAGE img_p1;//���ͼƬ
IMAGE img_p1bei;
IMAGE img_bk;//����ͼƬ
char input;


void startup()
{
	loadimage(&img_bk, _T("D:\\background.jpg"),1000,640,true);
	loadimage(&img_p1, _T("D:\\player.jpg"),80,80,true);
	loadimage(&img_p1bei, _T("D:\\playerbei.jpg"),80,80,true);//�Ƿ���� IMAGE �Ĵ�С����ӦͼƬ

	player.position_x=length/2.0;//��Һ�����
	player.position_y=high/2.0;//���������
	player.v_x=0.4;//���ˮƽ�ٶ�
	player.v_y=0.4;//�����ֱ�ٶ�

	initgraph(length,high);//�����С
	BeginBatchDraw();
}


void show()
{
	putimage(0, 0, &img_bk);//��ʾ����
	putimage(player.position_x, player.position_y, &img_p1bei,NOTSRCERASE);//��ʾ���
	putimage(player.position_x, player.position_y, &img_p1,SRCINVERT);

	FlushBatchDraw();
}


void updateWithoutInput()
{

}


void updateWithInput()
{
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (player.position_x>0))
		player.position_x=player.position_x-player.v_x;  //����
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (player.position_x<length-80))
		player.position_x=player.position_x+player.v_x;  //����
	if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  player.position_y>0)
		player.position_y=player.position_y-player.v_y;  //����
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  player.position_y<high-80)
		player.position_y=player.position_y+player.v_y;  //����

}


void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}


void main()
{
	startup();
	while(1)
	{
		show();
		updateWithoutInput() ;
		updateWithInput(); 
	}
	gameover();
}

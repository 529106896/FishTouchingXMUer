#include <graphics.h>
#include <conio.h>

// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

IMAGE img_bk,img_bd1,img_bd2,img_bar_up1,img_bar_up2,img_bar_down1,img_bar_down2;int bird_x;
int bird_y;

void startup()
{
	initgraph(350, 600);
	loadimage(&img_bk, "D:\\background.jpg");	
	loadimage(&img_bd1, "D:\\bird1.jpg");
	loadimage(&img_bd2, "D:\\bird2.jpg");	
	loadimage(&img_bar_up1, "D:\\bar_up1.gif");
	loadimage(&img_bar_up2, "D:\\bar_up2.gif");
	loadimage(&img_bar_down1, "D:\\bar_down1.gif");
	loadimage(&img_bar_down2, "D:\\bar_down2.gif");
	bird_x = 50;
	bird_y = 200;
	BeginBatchDraw();
	
	mciSendString("open D:\\background.mp3 alias bkmusic", NULL, 0, NULL);//�򿪱�������
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // ѭ������
}

void show()
{
	putimage(0, 0, &img_bk);	// ��ʾ����	
	putimage(150, -300, &img_bar_up1,NOTSRCERASE); // ��ʾ��һ����ϰ���
	putimage(150, -300, &img_bar_up2,SRCINVERT);
	putimage(150, 400, &img_bar_down1,NOTSRCERASE); // ��ʾ��һ����ϰ���
	putimage(150, 400, &img_bar_down2,SRCINVERT);
	putimage(bird_x, bird_y, &img_bd1,NOTSRCERASE); // ��ʾС��	
	putimage(bird_x, bird_y, &img_bd2,SRCINVERT);
	FlushBatchDraw();
	Sleep(50);
}

void updateWithoutInput()
{
	if (bird_y<500)
		bird_y = bird_y+3;
}

void updateWithInput()
{
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  
		if (input == ' ' && bird_y>20)  
		{
			bird_y = bird_y - 60;
			mciSendString("close jpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open D:\\Jump.mp3 alias jpmusic", NULL, 0, NULL); // ����������
            mciSendString("play jpmusic", NULL, 0, NULL); // ������һ��
		}
	}
}

void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
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
	gameover();     // ��Ϸ��������������
	return 0;
}

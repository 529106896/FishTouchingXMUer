#include <graphics.h>
#include <conio.h>
#include <string.h>
#pragma comment(lib,"Winmm.lib")
void PlayMusicOnce(char *fileName)
{
	char cmdString1[50] = "open ";
	strcat(cmdString1,fileName);
	strcat(cmdString1," alias tmpmusic");
	mciSendString("close tmpmusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
	mciSendString(cmdString1, NULL, 0, NULL); // ������
	mciSendString("play tmpmusic", NULL, 0, NULL); // ������һ��
}
int main()
{
	initgraph(640, 480);
	while (1)
	{
		PlayMusicOnce("D:\\Jump.mp3");
		Sleep(1500);
		PlayMusicOnce("D:\\f_gun.mp3");
		Sleep(1500);
	}
	getch();
	return 0;
}

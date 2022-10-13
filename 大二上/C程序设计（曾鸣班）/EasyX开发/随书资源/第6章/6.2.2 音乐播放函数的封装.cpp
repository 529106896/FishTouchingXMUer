#include <graphics.h>
#include <conio.h>
#include <string.h>
#pragma comment(lib,"Winmm.lib")
void PlayMusicOnce(char *fileName)
{
	char cmdString1[50] = "open ";
	strcat(cmdString1,fileName);
	strcat(cmdString1," alias tmpmusic");
	mciSendString("close tmpmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString(cmdString1, NULL, 0, NULL); // 打开音乐
	mciSendString("play tmpmusic", NULL, 0, NULL); // 仅播放一次
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

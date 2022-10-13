#include <graphics.h>
#include <conio.h>
int main()
{
	initgraph(640, 480);
	for(int y=0; y<=480; y=y+48)
		line(0, y, 640, y);
	getch();
	closegraph();
	return 0;
}

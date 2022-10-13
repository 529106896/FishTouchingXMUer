#include <graphics.h>
#include <conio.h>
int main()
{
   initgraph(640, 256);
   for(int y=0; y<256; y++)
   {
       setcolor(RGB(0,0,y));
       line(0, y, 640, y);
   }
   getch();
   closegraph();
   return 0;
}

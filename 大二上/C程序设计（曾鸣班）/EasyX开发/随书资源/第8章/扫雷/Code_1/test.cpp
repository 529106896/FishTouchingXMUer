#include<graphics.h>
#include<conio.h>
#include"change.h"
#define s1 600
#define PI 3.14159265358979





#define s1 600
#define s2 1000
#define b_step 10
int main()
{
	double i, j;
	int tx, ty, tx2, ty2;
	double step;
	initgraph(s1,s1);
	state ma;
	ma.fu =PI*13/30;
	ma.zhu =PI/9;
	ma.h = 160;
	ma.d = ma.h/2;
	ma.x = s1/2;
	ma.y = s1/2;
	pois tar;
	pois sou;
	sou.z = 0;
	c_init(ma);
	for (i = 0; i < s2; i += 3*b_step)
	{
		step = b_step;
		j = 0;
		sou.y = j;
		sou.x = i;
		sou.z = 0;
		tar = change(ma, sou);
		tx2 = s1 / 2 - tar.x;
		ty2 = s1 / 2 - tar.y;
		for (j = 0; j < s2; j += step)
		{
			sou.y = j;
			sou.x = i;
			sou.z = 0;
			tar = change(ma, sou);
			tx = s1 / 2 - tar.x;
			ty = s1 / 2 - tar.y;

			if (abs(tx - tx2) + abs(ty - ty2) < 0.1 *b_step && abs(tx - tx2) + abs(ty - ty2))
			{
				j -= step;
				step *= 2;
				continue;
			}
			if (abs(tx - tx2) + abs(ty - ty2) > 1 *b_step && abs(tx - tx2) + abs(ty - ty2))
			{
				j -= step;
				step /= 2;
				continue;
			}

			if (tx <= s1 && ty <= s1 && tx >= 0 && ty >= 0 && tar.z == 0)
			{
				setlinecolor(GREEN);
				line(tx2, ty2, tx, ty);
			}
			tx2 = tx;
			ty2 = ty;
		}



		j = 0;
		sou.y = i;
		sou.x = j;
		sou.z = 0;
		tar = change(ma, sou);
		tx2 = s1 / 2 - tar.x;
		ty2 = s1 / 2 - tar.y;
		for (j = 0; j < s2; j += step)
		{
			sou.y = i;
			sou.x = j;
			sou.z = 0;
			tar = change(ma, sou);
			tx = s1 / 2 - tar.x;
			ty = s1 / 2 - tar.y;

			if (abs(tx - tx2) + abs(ty - ty2) < 0.1*b_step && abs(tx - tx2) + abs(ty - ty2))
			{
				j -= step;
				step *= 2;
				continue;
			}
			if (abs(tx - tx2) + abs(ty - ty2) > 1*b_step && abs(tx - tx2) + abs(ty - ty2))
			{
				j -= step;
				step /= 2;
				continue;
			}



			if (tx <= s1 && ty <= s1 && tx >= 0 && ty >= 0 && tar.z == 0)
			{
				setlinecolor(GREEN);
				line(tx, ty, tx2, ty2);
			}
			ty2 = ty;
			tx2 = tx;
		}



	}
	while (1);
	closegraph();
	return 0;
}



/*


void put_kuai(int left, int right, int top, int floor, pois conor, int len, int nums, long long int color)//以结构体传递坐标
{

	state ma;
	ma.fu = PI * 9 / 30;
	ma.zhu = PI / 4;
	ma.h = 160;
	ma.d = ma.h / 2;
	ma.x = s1 / 2;
	ma.y = s1 / 2;

	static int dates[80];
	int i;
	pois t;
	for (i = 0; i < nums*2; i+=2)
	{
		dates[i] = conor.x + i*len / nums;
		dates[i + 1] = conor.y;
	}
	for (i = nums * 2; i < nums * 4; i += 2)
	{
		dates[i] = conor.x + len;
		dates[i + 1] = conor.y + (i - nums * 2)*len / nums;
	}
	for (i = nums * 4; i < nums * 6; i += 2)
	{
		dates[i] = conor.x + (i - nums * 4)*len / nums;
		dates[i + 1] = conor.y + len;
	}

	for (i = nums * 6; i < nums * 8; i += 2)
	{
		dates[i] = conor.x;
		dates[i + 1] = conor.y +len - (i - nums * 6)*len / nums;
	}

	for (i = 0; i < 8 * nums; i += 2);
	{
		t.x = dates[i];
		t.y = dates[i + 1];
		t = change(ma, t);
		dates[i] = t.x;
		dates[i + 1] = t.y;
		if (t.z != 0)
		{
			;
		}
	}
	return;
}


int main()
{
	state ma;
	ma.fu = PI * 9 / 30;
	ma.zhu = PI / 4;
	ma.h = 160;
	ma.d = ma.h / 2;
	ma.x = s1 / 2;
	ma.y = s1 / 2;
	pois tar;
	pois sou;
	sou.z = 0;
	c_init(ma);
	return 0;
}




*/



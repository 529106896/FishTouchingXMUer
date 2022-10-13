#include<math.h>

double ca1, cb1;
double sa1, sb1;

typedef struct state{
	double x;
	double y;
	double h;
	double d;
	double fu;
	double zhu;
}state;

typedef struct pois{
	double x;
	double y;
	double z;
}pois;

int c_init(state tai)
{
	double a1,b1;
	a1 = -tai.fu;
	b1 = -tai.zhu;
	ca1 = cos(a1);
	cb1 = cos(b1);
	sb1 = sin(b1);
	sa1 = sin(a1);
	return 0;
}

pois change(state tai, pois tar)
{
	pois answer;
	double x1, y1, z1;
	double x2, y2, z2;
	double r1, r2;
	double k;
	x1 = tai.x;
	y1 = tai.y;
	z1 = tai.h;
	x2 = tar.x;
	y2 = tar.y;
	z2 = tar.z;// read from struct
	
	x1 = x2 - x1;
	y1 = y2 - y1;
	z1 = z2 - z1;// reset to yuan

	x2 = x1 * cb1 + y1 * sb1;
	y2 = y1 * cb1 - x1 * sb1;// change zhuan jiao to 0
	x1 = x2;
	y1 = y2;
	/*
	r1 = sqrt(x1 * x1 + y1 * y1);
	r2 = r1 * ca1 + z1 * sa1;
	z2 = z1 * ca1 - r1 * sa1;
	x2 = r2 / r1 * x1;
	y2 = r2 / r1 * y1;
	x1 = x2;
	y1 = y2;
	z1 = z2;// change fu jiao to 0
	*/

	x2 = x1 * ca1 + z1 * sa1;
	z2 = z1 * ca1 - x1 * sa1;
	x1 = x2;
	z1 = z2;

	k = tai.d / x1;
	x2 = k * y1;
	y2 = k * z1; // tou shi bian huan
	
	answer.x = (int) x2;
	answer.y = (int) y2;
	
	if(x1 >= tai.d)
	{	
		answer.z = 0;
	}
	else
	{		
		answer.z = -1;
	}
	
	return answer;// shu chu	
}

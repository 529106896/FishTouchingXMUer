#define _CRT_SECURE_NO_WARNINGS 1
#include <GL/GLUT.H>  
#include <windows.h>      
#include <math.h>      
#include <gl/GL.h>      
#include <iostream>

using namespace std;
double mouseX, mouseY;

int times = 0;
int point_num = 0;

GLfloat ctrlPoints[][2] =
{
		{ -0.5, 0.5 },
		{ -0.1, 0.7 },
		{ 0.2, 0.3 },
		{ -0.3, 0.2},
		{-0.4,0.0},
		{ -0.2, -0.2},
		{0.1,-0.3},
		{0.4,-0.1}
		/*
		{ -0.5, 0.5 },
		{ -0.1, 0.7 },
		{ 0.2, 0.3 },
		{ -0.3, 0.2},
		{-0.4,0.0},
		{ -0.2, -0.2},
		{0.1,-0.3},
		{ -0.5, 0.5 },
		{ -0.1, 0.7 },
		{ 0.2, 0.3 },
		{ -0.3, 0.2},
		{-0.4,0.0},
		{ -0.2, -0.2},
		{0.1,-0.3}*/
};


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}


void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (x <= 250)
				mouseX = (x - 250) * (1.0 / 250.0);
			else if (x > 250)
				mouseX = (x - 250) * (1.0 / 250.0);

			if (y <= 250)
				mouseY = (250 - y) * (1.0 / 250.0);
			else if (y > 250)
				mouseY = (250 - y) * (1.0 / 250.0);

			ctrlPoints[point_num][0] = mouseX;
			ctrlPoints[point_num][1] = mouseY;
			//cout << mouseX << " " << mouseY << endl;

			point_num++;
			if (point_num >= 100)
				point_num = 100;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			point_num--;
			if (point_num <= 0)
				point_num = 0;
		}
	}
}


void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(5);
	glColor3f(1.0, 0.0, 0.0);

	for (int i = 0; i < point_num; i++)
	{
		glBegin(GL_POINTS);
		glVertex2fv(&ctrlPoints[i][0]);
		glEnd();
	}

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < point_num; i++)
	{
		glVertex2fv(&ctrlPoints[i][0]);
	}
	glEnd();

	int n = point_num;	//阶数
	float* xarray = new float[n];
	float* yarray = new float[n];

	GLfloat ps[101][2];

	int u = 0;
	for (double t = 0.0; t <= 1; t += 0.01)
	{
		for (int i = 1; i < n; ++i)
		{
			for (int j = 0; j < n - i; ++j)
			{
				if (i == 1) // i==1时,第一次迭代,由已知控制点计算  
				{
					xarray[j] = ctrlPoints[j][0] * (1 - t) + ctrlPoints[j + 1][0] * t;
					yarray[j] = ctrlPoints[j][1] * (1 - t) + ctrlPoints[j + 1][1] * t;
					continue;
				}
				// i != 1时,通过上一次迭代的结果计算  
				xarray[j] = xarray[j] * (1 - t) + xarray[j + 1] * t;
				yarray[j] = yarray[j] * (1 - t) + yarray[j + 1] * t;

			}

		}
		ps[u][0] = xarray[0];
		ps[u][1] = yarray[0];
		u++;
	}

	if (times == 100)
		times = 0;
	times++;

	glColor3f(0, 0, 0);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < times; i++)
	{
		glVertex2fv(ps[i]);
	}
	glEnd();

	glBegin(GL_POINTS);
	glVertex2fv(ps[times]);
	glEnd();

	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:
		exit(0);
		break;
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myidle()
{
	Sleep(15);
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(myidle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseFunc);
	glutMainLoop();
	return 0;
}
#include <iostream>
#include <gl/glut.h>
#include <cmath>
#define PI	3.14
#define CIRCLE_RADIUS 0.5
int circle_points = 120;

void init() 
{
	glClearColor(0, 0, 0, 0);
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	double angle = 2 * PI / circle_points;
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.2, 0.5, 0.5);

	glBegin(GL_POLYGON);

	double angle1 = 0.0;

	int i = 0;
	for (; i < 20; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0,0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	angle1 -= angle;
	for (; i < 40; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0, 0);
	glEnd();

	glColor3f(0.5, 1, 0.5);
	glBegin(GL_POLYGON);
	angle1 -= angle;
	for (; i < 60; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0, 0);
	glEnd();

	glColor3f(0.8, 0.4, 0.7);
	glBegin(GL_POLYGON);
	angle1 -= angle;
	for (; i < 80; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0, 0);
	glEnd();

	glColor3f(0.5, 0.3, 0.2);
	glBegin(GL_POLYGON);
	angle1 -= angle;
	for (; i < 100; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0, 0);
	glEnd();

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	angle1 -= angle;
	for (; i < 120; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0, 0);
	glEnd();

	glColor3f(0.5, 0.1, 0.9);
	glBegin(GL_POLYGON);
	angle1 -= angle;
	for (; i < 130; i++)
	{
		glVertex2d(CIRCLE_RADIUS * cos(angle1), CIRCLE_RADIUS * sin(angle1));
		angle1 += angle;
	}
	glVertex2d(0, 0);
	glEnd();

	glFlush();
}

int main(int argc, TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("这是一个很丑的圆，特别特别丑");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}

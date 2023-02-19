#include <GL/glut.h>
#include <time.h>

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	GLfloat vertices[3][2] = { {0.0,0.0},{25.0,50.0},{50.0,0.0} };
	int i, j, k;
	int rand();
	GLfloat p[2] = { 7.5,5.0 };
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);


	float a, b, c;
	for (k = 0; k < 50000; k++)
	{
		j = rand() % 3;
		p[0] = (p[0] + vertices[j][0]) / 2.0;
		p[1] = (p[1] + vertices[j][1]) / 2.0;

		glVertex2fv(p);
	}


	glEnd();
	glFlush();
}


void idlefunc()
{
	//改变动画参数
	glutPostRedisplay();
	float a, b, c;
	a = (float)(rand() % 100 + 1) / 100;
	b = (float)(rand() % 100 + 1) / 100;
	c = (float)(rand() % 100 + 1) / 100;
	glColor3f(a, b, c);
}


void main(int argc, char** argv)
{
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("蹦 迪 特 效");
	glutDisplayFunc(display);
	glutIdleFunc(idlefunc);
	myinit();
	glutMainLoop();
}
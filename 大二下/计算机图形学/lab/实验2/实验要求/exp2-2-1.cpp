#define NDEBUG
#include <GL/glut.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	//��������ѡһ������Ч��
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//���������������Σ������иĳɻ���������
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glFlush(); /* clear buffers */
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//��������������ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//���������ѡһ������Ч��
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.3, 10.0);


	//�����������������������Է�λ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/*
void idlefunc()
{
	//�ı䶯������
	glutPostRedisplay();
}
*/

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

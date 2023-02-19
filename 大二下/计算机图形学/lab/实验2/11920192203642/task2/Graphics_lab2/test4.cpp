#define NDEBUG
#include <GL/glut.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//��������ѡһ������Ч��
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	//���������������Σ������иĳɻ���������
	glBegin(GL_TRIANGLES);
	//glBegin(GL_QUADS);

	//������������������HEDC����������������
	//H
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(-0.5, -0.5, -0.5);

	//C
	glColor3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);

	//D
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);

	//��������������������������������

	//E
	glColor3f(0.2, 0.4, 0.8);
	glVertex3f(-0.5, 0.5, -0.5);

	//H
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(-0.5, -0.5, -0.5);

	//D
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);

	//����������EFGH��������
	//H
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(-0.5, -0.5, -0.5);

	//E
	glColor3f(0.2, 0.4, 0.8);
	glVertex3f(-0.5, 0.5, -0.5);

	//F
	glColor3f(0.2, 0.8, 0.2);
	glVertex3f(0.5, 0.5, -0.5);

	//��������������������������������

	//G
	glColor3f(0.8, 0.2, 0.8);
	glVertex3f(0.5, -0.5, -0.5);

	//F
	glColor3f(0.2, 0.8, 0.2);
	glVertex3f(0.5, 0.5, -0.5);

	//H
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(-0.5, -0.5, -0.5);

	//����������HGBC��������
	//H
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(-0.5, -0.5, -0.5);

	//G
	glColor3f(0.8, 0.2, 0.8);
	glVertex3f(0.5, -0.5, -0.5);

	//B
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//��������������������������������

	//C
	glColor3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);

	//B
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//H
	glColor3f(0.8, 0.4, 0.2);
	glVertex3f(-0.5, -0.5, -0.5);

	//����������ABCD����������������
	//A
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);

	//D
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);

	//B
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//��������������������������������
	
	//C
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.5);

	//D
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);

	//B
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//����������AFED��������
	//A
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);

	//F
	glColor3f(0.2, 0.8, 0.2);
	glVertex3f(0.5, 0.5, -0.5);

	//E
	glColor3f(0.2, 0.4, 0.8);
	glVertex3f(-0.5, 0.5, -0.5);

	//��������������������

	//D
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);

	//E
	glColor3f(0.2, 0.4, 0.8);
	glVertex3f(-0.5, 0.5, -0.5);

	//A
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);

	

	//������������������ABGF����������������
	//A
	glColor3f(1, 0, 0);
	glVertex3f(0.5, 0.5, 0.5);

	//B
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//G
	glColor3f(0.8, 0.2, 0.8);
	glVertex3f(0.5, -0.5, -0.5);

	//��������������������������������

	//F
	glColor3f(0.2, 0.8, 0.2);
	glVertex3f(0.5, 0.5, -0.5);

	//G
	glColor3f(0.8, 0.2, 0.8);
	glVertex3f(0.5, -0.5, -0.5);

	//A
	glColor3f(1, 0, 0);
	glVertex3f(0.5, 0.5, 0.5);

	

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
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 5.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 3.5);


	//�����������������������Է�λ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 1.5, 1.9, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);
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

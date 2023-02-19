#define NDEBUG
#include <GL/glut.h>
#include <Eigen/Core>
#include <iostream>
#include <vector>
#include "MyTransform.hpp"

using namespace std;


int WinSizeW;
int WinSizeH;

Eigen::Matrix4f mModelView;
Eigen::Matrix4f mProjection;
Eigen::Matrix4f mViewPort;


void SetProjectMatrix()
{
	mProjection.setZero();
	mProjection(0, 0) = 1.0;
	mProjection(1, 1) = 1.0;
	mProjection(2, 2) = -1.22222;
	mProjection(2, 3) = -2.22222;
	mProjection(3, 2) = -1.0;
}

void SetViewPortMatrix()
{
	mViewPort.setZero();
	mViewPort(0, 0) = 250.0;
	mViewPort(1, 1) = 250.0;
	mViewPort(0, 3) = 250.0;
	mViewPort(1, 3) = 250.0;
	mViewPort(2, 2) = 1.0;
	mViewPort(3, 3) = 1.0;
}

void SetMatrix()
{
	static float angle = 0.0;
	angle += 0.01;
	mModelView.setIdentity();
	mProjection.setIdentity();

	myTranslate(0.0, 0.0, -6);
	myRotateX(angle);
	myRotateY(angle);
	myRotateZ(angle);
	//myRotate(angle, 2.0, 1.0, 0.0);
	myTranslate(0.0, 0.0, 6);

	//myFrustum(-1, 1, -1, 1, 1, 10);
	SetProjectMatrix();
}

void init(void)
{
	mModelView.setIdentity();
	mProjection.setIdentity();
	mViewPort.setIdentity();

	glClearColor(0.949, 0.949, 0.949, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_SMOOTH);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetMatrix();

	vector<vector<Eigen::Vector3f> > tris;

	vector<Eigen::Vector3f> tri1(3);
	tri1[0] = Eigen::Vector3f(4.0, 0, -6.000);
	tri1[1] = Eigen::Vector3f(-2.0, 3.0, -6.000);
	tri1[2] = Eigen::Vector3f(-2.0, -3.0, -6.000);

	//vector<Eigen::Vector3f> tri2(3);
	//tri2[0] = Eigen::Vector3f(3.0, 0, -4.000);
	//tri2[1] = Eigen::Vector3f(-1.0, 1.0, -4.000);
	//tri2[2] = Eigen::Vector3f(-1.0, -1.0, -4.000);

	tris.push_back(tri1);
	//tris.push_back(tri2);

	vector<Eigen::Vector3f> tri_trans;

	for (int i = 0; i < tris.size(); ++i)
	{
		tri_trans = VertexTransform(tris[i]);

		glBegin(GL_TRIANGLES);
		glColor3ub(226, 86, 97);
		glVertex3fv(tri_trans[0].data());

		glColor3ub(214, 167, 201);
		glVertex3fv(tri_trans[1].data());

		glColor3ub(87, 150, 204);
		glVertex3fv(tri_trans[2].data());
		glEnd();

	}

	glFlush();

	glutPostRedisplay();
}


void reshape(int w, int h)
{
	WinSizeW = w;
	WinSizeH = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//myViewPort(0, 0, w, h);
	SetViewPortMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//����near��farд�����ǶԵģ�
	//��Ϊ��һ��z��ȡ���Ѿ��������Լ�������Ĺ���������
	//�˴�����׷��,�������������⴦��
	//�Ժ����Լ�д�Ĵ����У���ȻҪд�� glOrtho(0, w, 0.0, h, -1.0, 1.0);
	glOrtho(0, w, 0.0, h, 1.0, -1.0);
	
	//�����������������������Է�λ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}




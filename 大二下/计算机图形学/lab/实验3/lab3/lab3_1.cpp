#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <vector>

using namespace std;

float *vertex_arr;			//坐标数组
float *vertex_norm_arr;		//法向分量数组
int *face_arr;			//面数组
int vertex_num = 0;
int face_num = 0;

void PlyLoader()
{
	FILE* fp;
	fp = fopen("lizhenxiout.ply", "r");
	if (!fp)
	{
		cout << "File doesn't exist!" << endl;
		exit(-1);
	}

	char buffer[100];	//用于存取每次读取的结果
	memset(buffer, 0, sizeof(buffer));
	fseek(fp, 0, SEEK_SET);

	//vector<float> vertext

	//读取坐标数量与面的数量
	while (fgets(buffer, 100, fp))
	{
		if (strncmp(buffer, "element vertex", strlen("element vertex")) == 0)
		{
			strcpy(buffer, buffer + strlen("element vertex"));
			vertex_num = atoi(buffer);
			//cout << vertex_num << endl;
		}
		if (strncmp(buffer, "element face", strlen("element face")) == 0)
		{
			strcpy(buffer, buffer + strlen("element face"));
			face_num = atoi(buffer);
			//cout << face_num << endl;
		}
		if (strncmp(buffer, "end_header", strlen("end_header")) == 0)
		{
			break;
		}
	}

	vector<float> pos_vertex;
	vector<float> norm_vertex;

	float pos_x;
	float pos_y;
	float pos_z;
	float norm_x;
	float norm_y;
	float norm_z;
	int i = 0;
	while (i < vertex_num && fgets(buffer, 100, fp))
	{
		sscanf(buffer, "%f %f %f %f %f %f", &pos_x, &pos_y, &pos_z, &norm_x, &norm_y, &norm_z);
		pos_vertex.push_back(pos_x);
		pos_vertex.push_back(pos_y);
		pos_vertex.push_back(pos_z);
		norm_vertex.push_back(norm_x);
		norm_vertex.push_back(norm_x);
		norm_vertex.push_back(norm_x);
		i++;
	}
	int j = 0;
	int face_index1;
	int face_index2;
	int face_index3;
	vector<int> face_vertex;
	while (j < face_num && fgets(buffer, 100, fp))
	{
		if (buffer[0] == '3' && buffer[1] == ' ')
		{
			sscanf(buffer + 1, "%d %d %d", &face_index1, &face_index2, &face_index3);
			face_vertex.push_back(face_index1);
			face_vertex.push_back(face_index2);
			face_vertex.push_back(face_index3);
		}
		j++;
	}
	fclose(fp);

	vertex_arr = new float[pos_vertex.size()];
	vertex_norm_arr = new float[norm_vertex.size()];
	face_arr = new int[face_vertex.size()];

	memcpy(vertex_arr, &pos_vertex[0], pos_vertex.size() * sizeof(float));
	memcpy(vertex_norm_arr, &norm_vertex[0], norm_vertex.size() * sizeof(float));
	memcpy(face_arr, &face_vertex[0], face_vertex.size() * sizeof(int));

	//vertex_arr = (float*)malloc(sizeof(float) * pos_vertex.size());
	//vertex_norm_arr = (float*)malloc(sizeof(float) * norm_vertex.size());
	//face_arr = (int*)malloc(sizeof(int) * face_vertex.size());

	//copy(pos_vertex.begin(), pos_vertex.end(), vertex_arr);
	//copy(norm_vertex.begin(), norm_vertex.end(), vertex_norm_arr);
	//copy(face_vertex.begin(), face_vertex.end(), face_arr);
}

void init(int open)
{
	glClearColor(1, 1, 1, 0);
	glColor3f(1, 0, 0);
	glShadeModel(GL_SMOOTH);

	//镜面反射指数
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//高光指数
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//光源位置
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	//环境光参数
	GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	//物体材质
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//注册光源
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);

	if (open == 0)
		//开启光源
		glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.5);
	for (int i = 0; i < face_num; i++)
	{
		glNormal3f(vertex_norm_arr[face_arr[i * 3] * 3], vertex_norm_arr[face_arr[i * 3] * 3 + 1], vertex_norm_arr[face_arr[i * 3] * 3 + 2]);
		glVertex3f(vertex_arr[face_arr[i * 3] * 3], vertex_arr[face_arr[i * 3] * 3 + 1], vertex_arr[face_arr[i * 3] * 3 + 2]);
		glNormal3f(vertex_norm_arr[face_arr[i * 3 + 1] * 3], vertex_norm_arr[face_arr[i * 3 + 1] * 3 + 1], vertex_norm_arr[face_arr[i * 3 + 1] * 3 + 2]);
		glVertex3f(vertex_arr[face_arr[i * 3 + 1] * 3], vertex_arr[face_arr[i * 3 + 1] * 3 + 1], vertex_arr[face_arr[i * 3 + 1] * 3 + 2]);
		glNormal3f(vertex_norm_arr[face_arr[i * 3 + 2] * 3], vertex_norm_arr[face_arr[i * 3 + 2] * 3 + 1], vertex_norm_arr[face_arr[i * 3 + 2] * 3 + 2]);
		glVertex3f(vertex_arr[face_arr[i * 3 + 2] * 3], vertex_arr[face_arr[i * 3 + 2] * 3 + 1], vertex_arr[face_arr[i * 3 + 2] * 3 + 2]);
	}
	glEnd();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	cout << w << " " << h << endl;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1500.0 * 500 / (GLfloat)w, 1500.0 * 500 / (GLfloat)w, -1500.0 * 500 / (GLfloat)h, 1500.0 * 500 / (GLfloat)h, -3000.0, 3000.0);
	glMatrixMode(GL_MODELVIEW);
}

void idlefunc()
{
	glutPostRedisplay();
}


void keyboard(GLubyte key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	PlyLoader();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init(0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
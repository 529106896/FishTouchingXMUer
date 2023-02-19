#include <GL/glut.h>
#include <math.h>

int xIndex, yIndex;//用于查看鼠标最近的控制点
bool onwork = false;
int times = 0;

GLfloat pts[4][4][3] = 
{
        { { -5, 0, 8 }, { -2, 2, 0 }, { 2, 2, 0 }, { 5, 0, 8 } },
        { {-5, 3, 2  }, { -2, 3, 0 }, { 2, 3, 0 }, { 5, 3, 2 } },
        { { -5, 6, 8 }, { -2, 6, 3 }, { 2, 6, 3 }, { 5, 6, 8 } },
        { { -5, 9, 0 }, { -2, 7, 0 }, { 2, 7, 0 }, { 5, 9, 0 } }
};

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &pts[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    int i, j;
    if (times == 50)
    {
        //Sleep(1000);
        times = 0;
    }
        
    times++;
    for (j = 0; j <= times; j++) 
    {
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= times; i++)
        {
            glEvalCoord2f((GLfloat)i / 50.0, (GLfloat)j / 50.0);
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= times; i++)
        {
            glEvalCoord2f((GLfloat)j / 50.0, (GLfloat)i / 50.0);
        }
        glEnd();
    }

    glColor3f(0.0, 0.0, 1.0);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++) 
    {
        for (j = 0; j < 4; j++) 
        {
            glVertex2fv(pts[i][j]);
        }
    }
    glEnd();

    glFlush();
}
void display()
{
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &pts[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}
//计算鼠标点击处与控制点之间的距离
double distance(int x, int y, float x2, float y2)
{
    double dis = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
    return dis;
}
//将屏幕坐标转换为世界坐标
void change(int* result)
{
    int x = result[0], y = result[1];
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winx, winy, winz;
    GLdouble posX, posY, posZ;
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winx = (float)x;
    winy = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winy), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);
    gluUnProject(winx, winy, winz, modelview, projection, viewport, &posX, &posY, &posZ);
    result[0] = posX;
    result[1] = posY;
}
void click(int button, int state, int winx, int winy)
{
    int result[] = { winx, winy };
    change(result);
    int x = result[0], y = result[1];
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        double dis = distance(x, y, pts[0][0][0], pts[0][0][1]);
        double disTemp = dis;
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 4; j++) 
            {
                dis = distance(x, y, pts[i][j][0], pts[i][j][1]);
                if (dis <= disTemp) 
                {
                    xIndex = i;
                    yIndex = j;
                    disTemp = dis;
                    onwork = true;
                }
            }
        }
    }
}
void motion(int winx, int winy)
{
    int result[] = { winx, winy };
    change(result);
    int x = result[0], y = result[1];
    if (onwork) 
    {
        pts[xIndex][yIndex][0] = x;
        pts[xIndex][yIndex][1] = y;
        draw();
    }
}

void myidle()
{
    Sleep(60);
    glutPostRedisplay();
}

void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Bezier");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(myidle);
    glutMouseFunc(click);
    glutMotionFunc(motion);
    glutMainLoop();
}
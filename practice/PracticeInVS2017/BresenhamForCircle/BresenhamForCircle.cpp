#include <GL\glut.h>

void draw8points(int x, int y, int x0, int y0)
{   //利用对称画出8个点
    glBegin(GL_POINTS);
    glVertex2i(x0 + x, y0 + y);
    glVertex2i(-x0 + x, y0 + y);
    glVertex2i(x0 + x, -y0 + y);
    glVertex2i(-x0 + x, -y0 + y);
    glVertex2i(y0 + y, x0 + x);
    glVertex2i(-y0 + y, x0 + x);
    glVertex2i(y0 + y, -x0 + x);
    glVertex2i(-y0 + y, -x0 + x);
    glEnd();
}

void drawcircle(int x, int y, int r)
{
    int x0 = r, y0 = 0, p = 5 - (r << 2);
    int x1, y1;
    draw8points(x, y, x0, y0);  //起始点
    do
    {   //逆时针画点
        y1 = y0 + 1;
        //判断下一个点x坐标
        if (p < 0)
            x1 = x0;
        else
            x1 = x0 - 1;
        draw8points(x, y, x1, y1);
        //更新判别式
        if (p < 0)
            p = p + (y0 << 3) + 12;
        else
            p = p + ((y0 - x0) << 3) + 20;
        y0 = y1;
        x0 = x1;
    } while (x0 > y0);
}

void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    drawcircle(0, 0, 300);
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(GLdouble)w / 2.0, (GLdouble)w / 2.0,
        -(GLdouble)h / 2.0, (GLdouble)h / 2.0,
        -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle");

    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

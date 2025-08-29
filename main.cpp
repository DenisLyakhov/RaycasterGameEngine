#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/GL.h>

float playerX;
float playerY;

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerX, playerY);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawPlayer();
    glutSwapBuffers();
}

void init() {

    playerX = 400;
    playerY = 300;

    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 800, 600, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Default window");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
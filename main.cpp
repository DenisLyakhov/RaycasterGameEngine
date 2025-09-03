#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/GL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float playerX;
float playerY;

float speedX;
float speedY;

int levelWidth = 10;
int levelHeight = 10;

int levelObstacles[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void movementConfig(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
        playerX -= speedX;
    else if (key == GLUT_KEY_RIGHT)
        playerX += speedX;
    else if (key == GLUT_KEY_DOWN)
        playerY += speedY;
    else if (key == GLUT_KEY_UP)
        playerY -= speedY;

    glutPostRedisplay();
}

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

    speedX = 10;
    speedY = 10;

    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Default window");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(movementConfig);
    glutMainLoop();
}
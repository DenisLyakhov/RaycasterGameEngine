#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/GL.h>

#include <iostream>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650

float playerX;
float playerY;

float dirX;
float dirY;
float dirA;

float speedX;
float speedY;

int levelWidth = 10;
int levelHeight = 10;

int blockSize = 64;
int blockPadding = 1;

int levelObstacles[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

void drawLevelObstacles() {

    std::cout << levelObstacles[14];

    for (int i = 0; i < levelWidth; i++) {
        for (int j = 0; j < levelHeight; j++) {
            if (levelObstacles[j * levelHeight + i] == 1) {
                glColor3f(1, 1, 1);
            }
            else {
                glColor3f(0, 0, 0);
            }

            int lowerLeftX = i * blockSize;
            int lowerLeftY = j * blockSize;

            glBegin(GL_QUADS);
            glVertex2i(lowerLeftX + blockPadding, lowerLeftY + blockPadding);
            glVertex2i(lowerLeftX + blockPadding, lowerLeftY + blockSize - blockPadding);
            glVertex2i(lowerLeftX + blockSize - blockPadding, lowerLeftY + blockSize - blockPadding);
            glVertex2i(lowerLeftX + blockSize - blockPadding, lowerLeftY + blockPadding);
            glEnd();
        }
    }
}

void movementConfig(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) {
        dirA -= 0.1;

        if (dirA < 0) {
            dirA += 2 * M_PI;
        }

        dirX = cos(dirA) * 5;
        dirY = sin(dirA) * 5;
    }
    else if (key == GLUT_KEY_RIGHT) {
        dirA += 0.1;

        if (dirA > 2 * M_PI) {
            dirA -= 2 * M_PI;
        }

        dirX = cos(dirA) * 5;
        dirY = sin(dirA) * 5;
    }
    else if (key == GLUT_KEY_DOWN) {
        playerX -= dirX;
        playerY -= dirY;
    }
    else if (key == GLUT_KEY_UP) {
        playerX += dirX;
        playerY += dirY;
    }

    glutPostRedisplay();
}

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(playerX, playerY);
    glEnd();

    // TODO: add direction vector
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawLevelObstacles();
    drawPlayer();
    glutSwapBuffers();
}

void init() {

    playerX = 400;
    playerY = 300;

    speedX = 10;
    speedY = 10;

    dirX = cos(dirA) * 5;
    dirY = sin(dirA) * 5;

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
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/GL.h>

#include <iostream>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650
#define RAYS 1

float playerX;
float playerY;

float dirX;
float dirY;
float dirA;

float speedX;
float speedY;

int levelWidth = 10;
int levelHeight = 10;
int levelDim = 10;

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

void checkCollisionHorizontal() {
    int rayX;
    int rayY;

    int offsetX;
    int offsetY;

    int wallX;
    int wallY;

    int lineOfSight;

    // Ray's line of sight current distance
    lineOfSight = 0;

    float atan = -1 / tan(dirA);

    // Ray pointed up
    if (dirA > M_PI) {
        // round DOWN to the nearest multiple of the blockSize
        rayY = (((int)playerY) / blockSize) * blockSize - 0.0001;
        rayX = (playerY - rayY) * atan + playerX;

        offsetY = -blockSize;
        offsetX = -offsetY * atan;
    }

    // Ray pointed down
    if (dirA < M_PI) {
        // round UP to the nearest multiple of the blockSize
        rayY = (((int)playerY) / blockSize) * blockSize + blockSize;
        rayX = (playerY - rayY) * atan + playerX;

        offsetY = blockSize;
        offsetX = -offsetY * atan;
    }

    // Ray pointed left/right
    if (dirA == 0 || dirA == M_PI) {
        rayX = playerX;
        rayY = playerY;
        lineOfSight = levelDim;
    }

    // Extending the ray until it reaches a wall or is out of bounds
    while (lineOfSight < levelDim) {
        wallX = rayX / blockSize;
        wallY = rayY / blockSize;

        int index = wallY * levelWidth + wallX;

        if (index >= 0 && index < levelWidth * levelHeight && levelObstacles[index] == 1) {
            lineOfSight = levelDim;
        }
        else {
            rayX += offsetX;
            rayY += offsetY;
            lineOfSight += 1;
        }
    }

    glColor3f(0, 0, 1);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(playerX, playerY);
    glVertex2i(rayX, rayY);
    glEnd();
}

void checkCollisionVertical() {
    int rayX;
    int rayY;

    int offsetX;
    int offsetY;

    int wallX;
    int wallY;

    int lineOfSight;

    // Ray's line of sight current distance
    lineOfSight = 0;

    float ntan = -tan(dirA);

    // Ray pointed left
    if (dirA > M_PI/2 && dirA < 3*M_PI/2) {
        // round DOWN to the nearest multiple of the blockSize
        rayX = (((int)playerX) / blockSize) * blockSize - 0.0001;
        rayY = (playerX - rayX) * ntan + playerY;

        offsetX = -blockSize;
        offsetY = -offsetX * ntan;
    }

    // Ray pointed right
    if (dirA < M_PI / 2 || dirA > 3 * M_PI / 2) {
        // round UP to the nearest multiple of the blockSize
        rayX = (((int)playerX) / blockSize) * blockSize + blockSize;
        rayY = (playerX - rayX) * ntan + playerY;

        offsetX = blockSize;
        offsetY = -offsetX * ntan;
    }

    // Ray pointed up/down
    if (dirA == 0 || dirA == M_PI) {
        rayX = playerX;
        rayY = playerY;
        lineOfSight = levelDim;
    }

    // Extending the ray until it reaches a wall or is out of bounds
    while (lineOfSight < levelDim) {
        wallX = rayX / blockSize;
        wallY = rayY / blockSize;

        int index = wallY * levelWidth + wallX;

        if (index >= 0 && index < levelWidth * levelHeight && levelObstacles[index] == 1) {
            lineOfSight = levelDim;
        }
        else {
            rayX += offsetX;
            rayY += offsetY;
            lineOfSight += 1;
        }
    }

    glColor3f(1, 0, 0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(playerX, playerY);
    glVertex2i(rayX, rayY);
    glEnd();
}

void drawRays() {
    for (int ray = 0; ray < RAYS; ray++) {
        //checkCollisionHorizontal();
        checkCollisionVertical();
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

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(playerX, playerY);
    glVertex2i(playerX + dirX * 5, playerY + dirY * 5);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawLevelObstacles();
    drawPlayer();
    drawRays();
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
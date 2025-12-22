#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Original rectangle vertices
float rectangle[4][2] = {
    {-50, -30},
    {50, -30},
    {50, 30},
    {-50, 30}
};

// Translation parameters
float tx = 40, ty = 60;

void drawGrid() {
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    
    // Grid lines
    for (int x = -200; x <= 200; x += 20) {
        glVertex2i(x, -200);
        glVertex2i(x, 200);
    }
    for (int y = -200; y <= 200; y += 20) {
        glVertex2i(-200, y);
        glVertex2i(200, y);
    }
    
    // Axes
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(-200, 0);
    glVertex2i(200, 0);
    glVertex2i(0, -200);
    glVertex2i(0, 200);
    glEnd();
}

void drawRectangle(float rect[4][2], float r, float g, float b, bool filled = true) {
    glColor3f(r, g, b);
    
    if (filled) {
        glBegin(GL_POLYGON);
    } else {
        glBegin(GL_LINE_LOOP);
    }
    
    for (int i = 0; i < 4; i++) {
        glVertex2f(rect[i][0], rect[i][1]);
    }
    glEnd();
}

void translateRectangle(float rect[4][2], float tx, float ty) {
    for (int i = 0; i < 4; i++) {
        rect[i][0] += tx;
        rect[i][1] += ty;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    
    // Original rectangle (blue)
    drawRectangle(rectangle, 0.0, 0.0, 1.0);
    
    // Create translated rectangle
    float translatedRect[4][2];
    for (int i = 0; i < 4; i++) {
        translatedRect[i][0] = rectangle[i][0] + tx;
        translatedRect[i][1] = rectangle[i][1] + ty;
    }
    
    // Translated rectangle (red, wireframe)
    drawRectangle(translatedRect, 1.0, 0.0, 0.0, false);
    
    // Draw translation vector
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(tx, ty);
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Translation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
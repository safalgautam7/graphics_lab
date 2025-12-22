#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

void plotEllipsePoints(int x, int y, int cx, int cy) {
    glBegin(GL_POINTS);
    glVertex2i(cx + x, cy + y);
    glVertex2i(cx - x, cy + y);
    glVertex2i(cx + x, cy - y);
    glVertex2i(cx - x, cy - y);
    glEnd();
}

void midpointEllipse(int cx, int cy, int rx, int ry) {
    int x = 0;
    int y = ry;
    
    // Region 1
    int p1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    
    glColor3f(1.0, 0.0, 0.0); // Red color
    plotEllipsePoints(x, y, cx, cy);
    
    while ((2 * ry * ry * x) <= (2 * rx * rx * y)) {
        x++;
        if (p1 < 0) {
            p1 = p1 + (2 * ry * ry * x) + (ry * ry);
        } else {
            y--;
            p1 = p1 + (2 * ry * ry * x) - (2 * rx * rx * y) + (ry * ry);
        }
        plotEllipsePoints(x, y, cx, cy);
    }
    
    // Region 2
    int p2 = (ry * ry * (x + 0.5) * (x + 0.5)) + 
             (rx * rx * (y - 1) * (y - 1)) - 
             (rx * rx * ry * ry);
    
    while (y > 0) {
        y--;
        if (p2 > 0) {
            p2 = p2 - (2 * rx * rx * y) + (rx * rx);
        } else {
            x++;
            p2 = p2 + (2 * ry * ry * x) - (2 * rx * rx * y) + (rx * rx);
        }
        plotEllipsePoints(x, y, cx, cy);
    }
}

void drawGrid() {
    glColor3f(0.5, 0.5, 0.5); // Gray color for grid
    glBegin(GL_LINES);
    
    // Draw vertical lines
    for (int x = -200; x <= 200; x += 20) {
        glVertex2i(x, -200);
        glVertex2i(x, 200);
    }
    
    // Draw horizontal lines
    for (int y = -200; y <= 200; y += 20) {
        glVertex2i(-200, y);
        glVertex2i(200, y);
    }
    
    // Draw axes
    glColor3f(0.0, 0.0, 0.0); // Black for axes
    glVertex2i(-200, 0);
    glVertex2i(200, 0);
    glVertex2i(0, -200);
    glVertex2i(0, 200);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    midpointEllipse(0, 0, 100, 60);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glPointSize(3.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Ellipse Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
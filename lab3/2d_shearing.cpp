#include <windows.h>
#include <GL/glut.h>
#include <iostream>

// Original rectangle vertices
float rectangle[4][2] = {
    {50, 50},    // Bottom left
    {150, 50},   // Bottom right
    {150, 150},  // Top right
    {50, 150}    // Top left
};

// Shearing factors
float shx = 0.5f;   // Shear in X direction
float shy = 0.3f;   // Shear in Y direction

void drawGrid() {
    // Light gray grid
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_LINES);
    
    // Vertical lines
    for (int x = -200; x <= 200; x += 20) {
        glVertex2i(x, -200);
        glVertex2i(x, 200);
    }
    
    // Horizontal lines
    for (int y = -200; y <= 200; y += 20) {
        glVertex2i(-200, y);
        glVertex2i(200, y);
    }
    glEnd();
    
    // Black axes
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(-200, 0);
    glVertex2i(200, 0);
    glVertex2i(0, -200);
    glVertex2i(0, 200);
    glEnd();
    glLineWidth(1.0f);
}

void drawRectangle(float rect[4][2], float r, float g, float b) {
    // Draw outline only
    glColor3f(r, g, b);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(rect[i][0], rect[i][1]);
    }
    glEnd();
    glLineWidth(1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    
    // Original rectangle (blue outline)
    drawRectangle(rectangle, 0.0f, 0.0f, 1.0f);
    
    // X-sheared rectangle (red outline)
    float xSheared[4][2];
    for (int i = 0; i < 4; i++) {
        xSheared[i][0] = rectangle[i][0] + shx * rectangle[i][1];
        xSheared[i][1] = rectangle[i][1];
    }
    drawRectangle(xSheared, 1.0f, 0.0f, 0.0f);
    
    // Y-sheared rectangle (green outline)
    float ySheared[4][2];
    for (int i = 0; i < 4; i++) {
        ySheared[i][0] = rectangle[i][0];
        ySheared[i][1] = rectangle[i][1] + shy * rectangle[i][0];
    }
    drawRectangle(ySheared, 0.0f, 1.0f, 0.0f);
    
    // Display information
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Title
    glRasterPos2f(-190, 190);
    std::string title = "2D SHEARING TRANSFORMATION";
    for (int i = 0; i < title.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, title[i]);
    }
    
    // Shearing factors
    glRasterPos2f(-190, 175);
    std::string shearInfo = "Shearing Factors: shx = " + std::to_string(shx) + ", shy = " + std::to_string(shy);
    for (int i = 0; i < shearInfo.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, shearInfo[i]);
    }
    
    // Color Legend
    glRasterPos2f(-190, 160);
    std::string legend = "COLOR LEGEND:";
    for (int i = 0; i < legend.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, legend[i]);
    }
    
    // Blue - Original
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(-180, 145);
    std::string blueText = "BLUE: Original Rectangle";
    for (int i = 0; i < blueText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, blueText[i]);
    }
    
    // Red - X-Sheared
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-180, 130);
    std::string redText = "RED: X-Sheared (x' = x + shx*y)";
    for (int i = 0; i < redText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, redText[i]);
    }
    
    // Green - Y-Sheared
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-180, 115);
    std::string greenText = "GREEN: Y-Sheared (y' = y + shy*x)";
    for (int i = 0; i < greenText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, greenText[i]);
    }
    
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Shearing - Simple Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
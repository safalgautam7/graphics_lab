#include <windows.h>
#include <GL/glut.h>
#include <iostream>

// Original triangle vertices (1st quadrant)
float triangle[3][2] = {
    {50, 30},    // Bottom left
    {150, 30},   // Bottom right  
    {100, 100}   // Top center
};

// Fixed scaling factors
float sx = 1.5f;   // Scale in X direction
float sy = 2.0f;   // Scale in Y direction

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

void drawTriangle(float tri[3][2], float r, float g, float b, const char* label) {
    // Draw filled triangle
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
    
    // Draw outline
    glColor3f(r * 0.7f, g * 0.7f, b * 0.7f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
    
    // Draw label at centroid
    float cx = (tri[0][0] + tri[1][0] + tri[2][0]) / 3.0f;
    float cy = (tri[0][1] + tri[1][1] + tri[2][1]) / 3.0f;
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(cx + 5, cy + 5);
    for (int i = 0; label[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    
    // Original triangle (blue)
    drawTriangle(triangle, 0.0f, 0.0f, 1.0f, "Original");
    
    // Scaled triangle (red)
    float scaledTriangle[3][2];
    for (int i = 0; i < 3; i++) {
        scaledTriangle[i][0] = triangle[i][0] * sx;
        scaledTriangle[i][1] = triangle[i][1] * sy;
    }
    drawTriangle(scaledTriangle, 1.0f, 0.0f, 0.0f, "Scaled");
    
    // Display scaling factors
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-190, 190);
    
    std::string info = "2D Scaling - Fixed Example";
    for (int i = 0; i < info.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, info[i]);
    }
    
    glRasterPos2f(-190, 175);
    std::string scaleInfo = "Scaling Factors: sx = " + std::to_string(sx) + ", sy = " + std::to_string(sy);
    for (int i = 0; i < scaleInfo.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, scaleInfo[i]);
    }
    
    glRasterPos2f(-190, 160);
    std::string coords = "Original Triangle: (50,30), (150,30), (100,100)";
    for (int i = 0; i < coords.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, coords[i]);
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
    glutCreateWindow("2D Scaling - Simple Fixed Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
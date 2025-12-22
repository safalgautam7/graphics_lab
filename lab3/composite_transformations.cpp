#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Original triangle vertices
float triangle[3][2] = {
    {30, 30},    // Bottom left
    {120, 30},   // Bottom right
    {75, 90}     // Top
};

// Transformation parameters (fixed values)
float angle = 45.0f;     // Rotation angle in degrees
float tx = 80.0f, ty = 60.0f; // Translation
float sx = 1.5f, sy = 1.8f;   // Scaling
float shx = 0.2f;        // Shearing in X

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

void drawTriangle(float tri[3][2], float r, float g, float b) {
    // Draw outline only (no fill)
    glColor3f(r, g, b);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
    glLineWidth(1.0f);
}

void applyCompositeTransformation(float tri[3][2], float result[3][2]) {
    float rad = angle * 3.14159f / 180.0f;
    
    for (int i = 0; i < 3; i++) {
        float x = tri[i][0];
        float y = tri[i][1];
        
        // 1. Scaling first
        x *= sx;
        y *= sy;
        
        // 2. Rotation
        float xr = x * cos(rad) - y * sin(rad);
        float yr = x * sin(rad) + y * cos(rad);
        x = xr;
        y = yr;
        
        // 3. Shearing
        x = x + shx * y;
        
        // 4. Translation
        x += tx;
        y += ty;
        
        result[i][0] = x;
        result[i][1] = y;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    
    // Original triangle (blue)
    drawTriangle(triangle, 0.0f, 0.0f, 1.0f);
    
    // Apply individual transformations step by step
    float afterScale[3][2];
    float afterRotate[3][2];
    float afterShear[3][2];
    float afterAll[3][2];
    
    // 1. Only Scaling (red)
    for (int i = 0; i < 3; i++) {
        afterScale[i][0] = triangle[i][0] * sx;
        afterScale[i][1] = triangle[i][1] * sy;
    }
    drawTriangle(afterScale, 1.0f, 0.0f, 0.0f);
    
    // 2. Scaling + Rotation (green)
    float rad = angle * 3.14159f / 180.0f;
    for (int i = 0; i < 3; i++) {
        float x = afterScale[i][0];
        float y = afterScale[i][1];
        afterRotate[i][0] = x * cos(rad) - y * sin(rad);
        afterRotate[i][1] = x * sin(rad) + y * cos(rad);
    }
    drawTriangle(afterRotate, 0.0f, 1.0f, 0.0f);
    
    // 3. Scaling + Rotation + Shearing (yellow)
    for (int i = 0; i < 3; i++) {
        afterShear[i][0] = afterRotate[i][0] + shx * afterRotate[i][1];
        afterShear[i][1] = afterRotate[i][1];
    }
    drawTriangle(afterShear, 1.0f, 1.0f, 0.0f);
    
    // 4. Complete composite transformation (magenta)
    applyCompositeTransformation(triangle, afterAll);
    drawTriangle(afterAll, 1.0f, 0.0f, 1.0f);
    
    // Display information
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Title
    glRasterPos2f(-190, 190);
    std::string title = "COMPOSITE TRANSFORMATIONS";
    for (int i = 0; i < title.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, title[i]);
    }
    
    // Parameters
    glRasterPos2f(-190, 175);
    std::string params = "Parameters: Scale(" + std::to_string(sx) + "," + std::to_string(sy) + 
                        ") Rotate(" + std::to_string(angle) + "deg) Shear(shx=" + std::to_string(shx) + 
                        ") Translate(" + std::to_string(tx) + "," + std::to_string(ty) + ")";
    for (int i = 0; i < params.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, params[i]);
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
    std::string blueText = "BLUE: Original Triangle";
    for (int i = 0; i < blueText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, blueText[i]);
    }
    
    // Red - After Scaling
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-180, 130);
    std::string redText = "RED: After Scaling";
    for (int i = 0; i < redText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, redText[i]);
    }
    
    // Green - After Scaling + Rotation
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-180, 115);
    std::string greenText = "GREEN: After Scaling + Rotation";
    for (int i = 0; i < greenText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, greenText[i]);
    }
    
    // Yellow - After Scaling + Rotation + Shearing
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(-180, 100);
    std::string yellowText = "YELLOW: After Scaling + Rotation + Shearing";
    for (int i = 0; i < yellowText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, yellowText[i]);
    }
    
    // Magenta - Complete Composite
    glColor3f(1.0f, 0.0f, 1.0f);
    glRasterPos2f(-180, 85);
    std::string magentaText = "MAGENTA: Complete Composite (All 4 transforms)";
    for (int i = 0; i < magentaText.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, magentaText[i]);
    }
    
    // Transformation order
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-190, 70);
    std::string order = "Transformation Order: 1. Scale 2. Rotate 3. Shear 4. Translate";
    for (int i = 0; i < order.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, order[i]);
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
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Composite Transformations - Simple");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
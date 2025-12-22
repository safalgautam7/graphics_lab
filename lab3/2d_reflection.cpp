#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Asymmetric triangle vertices that clearly show all reflections
float triangle[3][2] = {
    {-80, -40},   // Left bottom
    {40, 80},     // Top right
    {100, -60}    // Right bottom (asymmetric)
};

// Reflection states
bool reflectX = true;
bool reflectY = false;
bool reflectXY = false;

void drawGrid() {
    glColor3f(0.9, 0.9, 0.9); // Light gray grid
    glBegin(GL_LINES);
    
    // Draw grid lines
    for (int x = -300; x <= 300; x += 40) {
        glVertex2i(x, -300);
        glVertex2i(x, 300);
    }
    for (int y = -300; y <= 300; y += 40) {
        glVertex2i(-300, y);
        glVertex2i(300, y);
    }
    
    // Draw axes in black
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glVertex2i(-300, 0);
    glVertex2i(300, 0);
    glVertex2i(0, -300);
    glVertex2i(0, 300);
    glLineWidth(1.0);
    glEnd();
}

void drawTriangle(float tri[3][2], float r, float g, float b, const char* label) {
    glColor3f(r, g, b);
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
    
    // Draw outline
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
    
    // Draw label near the centroid
    float cx = (tri[0][0] + tri[1][0] + tri[2][0]) / 3.0;
    float cy = (tri[0][1] + tri[1][1] + tri[2][1]) / 3.0;
    
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(cx + 5, cy + 5);
    for (int i = 0; label[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    
    // Draw reflection lines with different styles
    glLineWidth(1.5);
    
    if (reflectX) {
        // X-axis reflection line
        glColor3f(0.8, 0.2, 0.2); // Dark red
        glLineStipple(2, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex2i(-300, 0);
        glVertex2i(300, 0);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    if (reflectY) {
        // Y-axis reflection line
        glColor3f(0.2, 0.2, 0.8); // Dark blue
        glLineStipple(2, 0xCCCC);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex2i(0, -300);
        glVertex2i(0, 300);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    if (reflectXY) {
        // Y=X line (diagonal)
        glColor3f(0.2, 0.8, 0.2); // Dark green
        glLineStipple(2, 0x8888);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex2i(-300, -300);
        glVertex2i(300, 300);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    glLineWidth(1.0);
    
    // Original triangle (dark blue)
    drawTriangle(triangle, 0.0, 0.0, 0.8, "Original");
    
    // Apply reflections based on toggles
    if (reflectX) {
        float reflectedX[3][2];
        for (int i = 0; i < 3; i++) {
            reflectedX[i][0] = triangle[i][0];
            reflectedX[i][1] = -triangle[i][1]; // Flip Y coordinate
        }
        drawTriangle(reflectedX, 0.8, 0.0, 0.0, "Reflect X");
        
        // Draw reflection lines from original to reflected
        glColor3f(1.0, 0.5, 0.5);
        glLineStipple(1, 0xF0F0);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        for (int i = 0; i < 3; i++) {
            glVertex2f(triangle[i][0], triangle[i][1]);
            glVertex2f(reflectedX[i][0], reflectedX[i][1]);
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    if (reflectY) {
        float reflectedY[3][2];
        for (int i = 0; i < 3; i++) {
            reflectedY[i][0] = -triangle[i][0]; // Flip X coordinate
            reflectedY[i][1] = triangle[i][1];
        }
        drawTriangle(reflectedY, 0.0, 0.8, 0.0, "Reflect Y");
        
        // Draw reflection lines from original to reflected
        glColor3f(0.5, 0.8, 0.5);
        glLineStipple(1, 0xF0F0);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        for (int i = 0; i < 3; i++) {
            glVertex2f(triangle[i][0], triangle[i][1]);
            glVertex2f(reflectedY[i][0], reflectedY[i][1]);
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    if (reflectXY) {
        float reflectedXY[3][2];
        for (int i = 0; i < 3; i++) {
            // Swap x and y for reflection about y=x
            reflectedXY[i][0] = triangle[i][1];
            reflectedXY[i][1] = triangle[i][0];
        }
        drawTriangle(reflectedXY, 0.8, 0.8, 0.0, "Reflect X=Y");
        
        // Draw reflection lines from original to reflected
        glColor3f(0.8, 0.8, 0.5);
        glLineStipple(1, 0xF0F0);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        for (int i = 0; i < 3; i++) {
            glVertex2f(triangle[i][0], triangle[i][1]);
            glVertex2f(reflectedXY[i][0], reflectedXY[i][1]);
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    
    // Draw instructions
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-280, 280);
    std::string instructions = "Controls: X=Reflect X, Y=Reflect Y, D=Reflect Diagonal, A=All Off, S=All On";
    for (int i = 0; i < instructions.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, instructions[i]);
    }
    
    // Draw coordinate labels
    glRasterPos2f(280, -10);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
    glRasterPos2f(10, 280);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
    
    // Draw quadrant labels
    glRasterPos2f(150, 150);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'I');
    glRasterPos2f(-160, 150);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'I');
    glRasterPos2f(150, -160);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'I');
    glRasterPos2f(-160, -160);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'V');
    
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
        case 'X':
            reflectX = !reflectX;
            break;
        case 'y':
        case 'Y':
            reflectY = !reflectY;
            break;
        case 'd':
        case 'D':
            reflectXY = !reflectXY;
            break;
        case 'a':
        case 'A':
            reflectX = reflectY = reflectXY = false;
            break;
        case 's':
        case 'S':
            reflectX = reflectY = reflectXY = true;
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Reflection - (Press: X, Y, D, A, S, ESC)");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
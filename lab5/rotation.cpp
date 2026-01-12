#include <GL/glut.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

// Global variables
float rotationAngle = 45.0f;
bool showInfoWindow = false;
int mainWindow, infoWindow;

std::string floatToString(float value) {
    std::stringstream ss;
    ss.precision(2);
    ss << std::fixed << value;
    return ss.str();
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat lightPos[] = {5.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void drawGrid() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    
    for(float x = -5.0f; x <= 5.0f; x += 1.0f) {
        glVertex3f(x, 0.0f, -5.0f);
        glVertex3f(x, 0.0f, 5.0f);
    }
    
    for(float z = -5.0f; z <= 5.0f; z += 1.0f) {
        glVertex3f(-5.0f, 0.0f, z);
        glVertex3f(5.0f, 0.0f, z);
    }
    
    glEnd();
}

void drawCoordinateAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 0.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 3.0f);
    
    glEnd();
    glLineWidth(1.0f);
}

void drawPyramid(float size, float r, float g, float b) {
    float s = size / 2.0f;
    
    glColor3f(r, g, b);
    
    // Draw pyramid faces
    glBegin(GL_TRIANGLES);
    
    // Front face
    glVertex3f(0.0f, s, 0.0f);
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    
    // Right face
    glVertex3f(0.0f, s, 0.0f);
    glVertex3f(s, -s, s);
    glVertex3f(s, -s, -s);
    
    // Back face
    glVertex3f(0.0f, s, 0.0f);
    glVertex3f(s, -s, -s);
    glVertex3f(-s, -s, -s);
    
    // Left face
    glVertex3f(0.0f, s, 0.0f);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s, s);
    
    glEnd();
    
    // Draw base
    glBegin(GL_QUADS);
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, -s, -s);
    glVertex3f(-s, -s, -s);
    glEnd();
}

void displayMain() {
    glutSetWindow(mainWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(5.0f, 5.0f, 8.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    
    drawGrid();
    drawCoordinateAxes();
    
    // Draw original pyramid (Green) - X-axis rotation
    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, 0.0f);
    drawPyramid(1.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw X-axis rotated pyramid (Red)
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
    drawPyramid(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Draw Y-axis rotated pyramid (Blue)
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    drawPyramid(1.0f, 0.0f, 0.0f, 1.0f);
    glPopMatrix();
    
    // Draw Z-axis rotated pyramid (Yellow)
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    drawPyramid(1.0f, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw labels
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glRasterPos3f(-3.0f, 1.5f, 0.0f);
    std::string label = "Original";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(0.0f, 3.5f, 0.0f);
    label = "X-axis Rotation";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(3.0f, 1.5f, 0.0f);
    label = "Y-axis Rotation";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(0.0f, -0.5f, 0.0f);
    label = "Z-axis Rotation";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glutSwapBuffers();
}

void displayInfo() {
    glutSetWindow(infoWindow);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 400);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Title
    glRasterPos2f(100, 350);
    std::string title = "3D ROTATION COORDINATES";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Rotation angle
    glRasterPos2f(50, 320);
    std::string angle = "ROTATION ANGLE: " + floatToString(rotationAngle) + " degrees";
    for (char c : angle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Original Pyramid Vertices
    glRasterPos2f(50, 280);
    std::string orig = "ORIGINAL PYRAMID (Green) VERTICES:";
    for (char c : orig) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 260);
    std::string v1 = "V1 (Top): (0.0, 0.5, 0.0)";
    for (char c : v1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 240);
    std::string v2 = "V2 (Front-left): (-0.5, -0.5, 0.5)";
    for (char c : v2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 220);
    std::string v3 = "V3 (Front-right): (0.5, -0.5, 0.5)";
    for (char c : v3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // X-axis Rotation
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(50, 180);
    std::string xRot = "X-AXIS ROTATION (Red):";
    for (char c : xRot) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 160);
    std::string xInfo = "Rotation Matrix: Rx(θ) where θ = " + floatToString(rotationAngle) + "°";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 140);
    xInfo = "Transformed V1: (0.0, 0.35, 0.35)";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Y-axis Rotation
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(50, 110);
    std::string yRot = "Y-AXIS ROTATION (Blue):";
    for (char c : yRot) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 90);
    std::string yInfo = "Rotation Matrix: Ry(θ) where θ = " + floatToString(rotationAngle) + "°";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 70);
    yInfo = "Transformed V1: (-0.35, 0.5, 0.35)";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Z-axis Rotation
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(50, 40);
    std::string zRot = "Z-AXIS ROTATION (Yellow):";
    for (char c : zRot) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 20);
    std::string zInfo = "Rotation Matrix: Rz(θ) where θ = " + floatToString(rotationAngle) + "°";
    for (char c : zInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glutSwapBuffers();
}

void reshapeMain(int w, int h) {
    glutSetWindow(mainWindow);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/(double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshapeInfo(int w, int h) {
    glutSetWindow(infoWindow);
    glViewport(0, 0, w, h);
}

void createInfoWindow() {
    if (!showInfoWindow) {
        infoWindow = glutCreateWindow("Rotation Coordinates Info");
        glutPositionWindow(820, 10);
        glutReshapeWindow(500, 400);
        glutDisplayFunc(displayInfo);
        glutReshapeFunc(reshapeInfo);
        
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        showInfoWindow = true;
    } else {
        glutDestroyWindow(infoWindow);
        showInfoWindow = false;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'i' || key == 'I') {
        createInfoWindow();
    } else if (key == 27) {  // ESC key
        exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Create main window
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    mainWindow = glutCreateWindow("3D Rotation with Coordinates Info");
    
    init();
    
    glutDisplayFunc(displayMain);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);
    
    std::cout << "3D Rotation Demonstration\n";
    std::cout << "=========================\n";
    std::cout << "Press 'I' to show/hide coordinates window\n";
    std::cout << "Press ESC to exit\n\n";
    std::cout << "Rotation Details:\n";
    std::cout << "Rotation Angle: 45°\n";
    std::cout << "Showing rotations around X, Y, and Z axes\n";
    
    glutMainLoop();
    return 0;
}
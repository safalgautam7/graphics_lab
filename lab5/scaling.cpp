#include <GL/glut.h>
#include <iostream>
#include <string>
#include <sstream>

// Global variables
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
    
    // Draw original pyramid (Green)
    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, 0.0f);
    drawPyramid(1.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw uniformly scaled pyramid (Red)
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    drawPyramid(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Draw non-uniformly scaled pyramid (Blue)
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f);
    glScalef(0.8f, 1.8f, 1.2f);
    drawPyramid(1.0f, 0.0f, 0.0f, 1.0f);
    glPopMatrix();
    
    // Draw reduced pyramid (Yellow)
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(0.6f, 0.6f, 0.6f);
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
    label = "Uniform Scale 1.5x";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(3.0f, 1.5f, 0.0f);
    label = "Non-uniform Scale";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(0.0f, -0.5f, 0.0f);
    label = "Reduction 0.6x";
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
    gluOrtho2D(0, 600, 0, 400);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Title
    glRasterPos2f(150, 370);
    std::string title = "3D SCALING COORDINATES";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Original Pyramid Vertices
    glRasterPos2f(50, 340);
    std::string orig = "ORIGINAL PYRAMID (Green) VERTICES:";
    for (char c : orig) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 320);
    std::string v1 = "V1 (Top): (0.0, 0.5, 0.0)";
    for (char c : v1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 300);
    std::string v2 = "V2 (Front-left): (-0.5, -0.5, 0.5)";
    for (char c : v2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 280);
    std::string v3 = "V3 (Front-right): (0.5, -0.5, 0.5)";
    for (char c : v3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Uniform Scaling
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(50, 250);
    std::string uniScale = "UNIFORM SCALING (Red):";
    for (char c : uniScale) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 230);
    std::string uniInfo = "Scale Factors: Sx = 1.5, Sy = 1.5, Sz = 1.5";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 210);
    uniInfo = "Transformed V1: (0.0, 0.75, 0.0)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 190);
    uniInfo = "Transformed V2: (-0.75, -0.75, 0.75)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Non-uniform Scaling
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(50, 160);
    std::string nonUniScale = "NON-UNIFORM SCALING (Blue):";
    for (char c : nonUniScale) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 140);
    std::string nonUniInfo = "Scale Factors: Sx = 0.8, Sy = 1.8, Sz = 1.2";
    for (char c : nonUniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 120);
    nonUniInfo = "Transformed V1: (0.0, 0.9, 0.0)";
    for (char c : nonUniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 100);
    nonUniInfo = "Transformed V2: (-0.4, -0.9, 0.6)";
    for (char c : nonUniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Reduction Scaling
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(50, 70);
    std::string redScale = "REDUCTION SCALING (Yellow):";
    for (char c : redScale) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 50);
    std::string redInfo = "Scale Factors: Sx = 0.6, Sy = 0.6, Sz = 0.6";
    for (char c : redInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 30);
    redInfo = "Transformed V1: (0.0, 0.3, 0.0)";
    for (char c : redInfo) {
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
        infoWindow = glutCreateWindow("Scaling Coordinates Info");
        glutPositionWindow(820, 10);
        glutReshapeWindow(600, 400);
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
    mainWindow = glutCreateWindow("3D Scaling with Coordinates Info");
    
    init();
    
    glutDisplayFunc(displayMain);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);
    
    std::cout << "3D Scaling Demonstration\n";
    std::cout << "=======================\n";
    std::cout << "Press 'I' to show/hide coordinates window\n";
    std::cout << "Press ESC to exit\n\n";
    std::cout << "Scaling Details:\n";
    std::cout << "Uniform scaling: 1.5x all axes\n";
    std::cout << "Non-uniform scaling: X:0.8, Y:1.8, Z:1.2\n";
    std::cout << "Reduction scaling: 0.6x all axes\n";
    
    glutMainLoop();
    return 0;
}
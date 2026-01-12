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

void drawCube(float size, float r, float g, float b) {
    float s = size / 2.0f;
    
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    
    // Front face
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);
    
    // Back face
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, -s, -s);
    
    // Top face
    glVertex3f(-s, s, -s);
    glVertex3f(-s, s, s);
    glVertex3f(s, s, s);
    glVertex3f(s, s, -s);
    
    // Bottom face
    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, -s, s);
    glVertex3f(-s, -s, s);
    
    // Right face
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, s, s);
    glVertex3f(s, -s, s);
    
    // Left face
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s, s);
    glVertex3f(-s, s, s);
    glVertex3f(-s, s, -s);
    
    glEnd();
}

void applyShearing(int axis, float shearX, float shearY, float shearZ) {
    GLfloat shearMatrix[16];
    
    // Initialize as identity matrix
    for(int i = 0; i < 16; i++) {
        shearMatrix[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
    
    switch(axis) {
        case 0: // Shear along X-axis
            shearMatrix[4] = shearY; // XY shear
            shearMatrix[8] = shearZ; // XZ shear
            break;
        case 1: // Shear along Y-axis
            shearMatrix[1] = shearX; // YX shear
            shearMatrix[9] = shearZ; // YZ shear
            break;
        case 2: // Shear along Z-axis
            shearMatrix[2] = shearX; // ZX shear
            shearMatrix[6] = shearY; // ZY shear
            break;
    }
    
    glMultMatrixf(shearMatrix);
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
    
    // Draw original cube (Green)
    glPushMatrix();
    glTranslatef(-3.0f, 2.0f, 0.0f);
    drawCube(1.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw X-axis sheared cube (Red)
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    applyShearing(0, 0.0f, 0.5f, 0.3f);
    drawCube(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Draw Y-axis sheared cube (Blue)
    glPushMatrix();
    glTranslatef(3.0f, 2.0f, 0.0f);
    applyShearing(1, 0.4f, 0.0f, 0.2f);
    drawCube(1.0f, 0.0f, 0.0f, 1.0f);
    glPopMatrix();
    
    // Draw Z-axis sheared cube (Yellow)
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    applyShearing(2, 0.3f, 0.2f, 0.0f);
    drawCube(1.0f, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw labels
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glRasterPos3f(-3.0f, 3.5f, 0.0f);
    std::string label = "Original";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(0.0f, 3.5f, 0.0f);
    label = "X-axis Shear";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(3.0f, 3.5f, 0.0f);
    label = "Y-axis Shear";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(0.0f, -0.5f, 0.0f);
    label = "Z-axis Shear";
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
    gluOrtho2D(0, 600, 0, 450);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Title
    glRasterPos2f(150, 420);
    std::string title = "3D SHEARING COORDINATES";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Original Cube Vertices
    glRasterPos2f(50, 380);
    std::string orig = "ORIGINAL CUBE (Green) VERTICES (Front Face):";
    for (char c : orig) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 360);
    std::string v1 = "V1: (-0.5, -0.5, 0.5)";
    for (char c : v1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 340);
    std::string v2 = "V2: (0.5, -0.5, 0.5)";
    for (char c : v2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 320);
    std::string v3 = "V3: (0.5, 0.5, 0.5)";
    for (char c : v3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 300);
    std::string v4 = "V4: (-0.5, 0.5, 0.5)";
    for (char c : v4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // X-axis Shearing
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(50, 270);
    std::string xShear = "X-AXIS SHEARING (Red):";
    for (char c : xShear) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 250);
    std::string xInfo = "Shear Factors: XY = 0.5, XZ = 0.3";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 230);
    xInfo = "Transformed V1: (-0.5, -0.25, 0.35)";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 210);
    xInfo = "Transformed V2: (0.5, 0.25, 0.65)";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Y-axis Shearing
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(50, 180);
    std::string yShear = "Y-AXIS SHEARING (Blue):";
    for (char c : yShear) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 160);
    std::string yInfo = "Shear Factors: YX = 0.4, YZ = 0.2";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 140);
    yInfo = "Transformed V1: (-0.7, -0.5, 0.4)";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 120);
    yInfo = "Transformed V2: (0.3, -0.5, 0.6)";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Z-axis Shearing
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(50, 90);
    std::string zShear = "Z-AXIS SHEARING (Yellow):";
    for (char c : zShear) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 70);
    std::string zInfo = "Shear Factors: ZX = 0.3, ZY = 0.2";
    for (char c : zInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 50);
    zInfo = "Transformed V1: (-0.35, -0.4, 0.5)";
    for (char c : zInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 30);
    zInfo = "Transformed V2: (0.65, -0.4, 0.5)";
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
        infoWindow = glutCreateWindow("Shearing Coordinates Info");
        glutPositionWindow(820, 10);
        glutReshapeWindow(600, 450);
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
    mainWindow = glutCreateWindow("3D Shearing with Coordinates Info");
    
    init();
    
    glutDisplayFunc(displayMain);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);
    
    std::cout << "3D Shearing Demonstration\n";
    std::cout << "=========================\n";
    std::cout << "Press 'I' to show/hide coordinates window\n";
    std::cout << "Press ESC to exit\n\n";
    std::cout << "Shearing Details:\n";
    std::cout << "X-axis shearing: XY=0.5, XZ=0.3\n";
    std::cout << "Y-axis shearing: YX=0.4, YZ=0.2\n";
    std::cout << "Z-axis shearing: ZX=0.3, ZY=0.2\n";
    
    glutMainLoop();
    return 0;
}
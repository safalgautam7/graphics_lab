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
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    
    // Set up lighting
    GLfloat lightPos[] = {5.0f, 5.0f, 10.0f, 1.0f};
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    GLfloat matSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat matShininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
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
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawPyramid(1.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw scaled pyramid (Red)
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    drawPyramid(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Draw labels
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glRasterPos3f(-3.0f, 1.5f, 0.0f);
    std::string label = "Original";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(0.0f, 3.5f, 0.0f);
    label = "Scaled 1.5x";
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
    
    glRasterPos2f(70, 260);
    std::string v4 = "V4 (Back-right): (0.5, -0.5, -0.5)";
    for (char c : v4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 240);
    std::string v5 = "V5 (Back-left): (-0.5, -0.5, -0.5)";
    for (char c : v5) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Uniform Scaling
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(50, 200);
    std::string uniScale = "SCALED PYRAMID (Red):";
    for (char c : uniScale) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 180);
    std::string uniInfo = "Scale Factors: Sx = 1.5, Sy = 1.5, Sz = 1.5";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 150);
    uniInfo = "Transformed V1: (0.0, 0.75, 0.0)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 130);
    uniInfo = "Transformed V2: (-0.75, -0.75, 0.75)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 110);
    uniInfo = "Transformed V3: (0.75, -0.75, 0.75)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 90);
    uniInfo = "Transformed V4: (0.75, -0.75, -0.75)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 70);
    uniInfo = "Transformed V5: (-0.75, -0.75, -0.75)";
    for (char c : uniInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
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
    std::cout << "Scaling: 1.5x uniform scaling on all axes\n";
    
    glutMainLoop();
    return 0;
}
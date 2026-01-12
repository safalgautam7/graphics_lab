#include <GL/glut.h>
#include <iostream>
#include <string>
#include <sstream>

// Global variables
float translateX = 2.0f, translateY = 1.5f, translateZ = -1.0f;
bool showInfoWindow = false;
int mainWindow, infoWindow;

// Function to format float to string
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

void displayMain() {
    glutSetWindow(mainWindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(3.0f, 4.0f, 6.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    
    drawGrid();
    drawCoordinateAxes();
    
    // Draw original cube (Green) at position (0,0,0)
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawCube(1.0f, 0.0f, 1.0f, 0.0f);
    
    // Draw coordinate point
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
    
    // Draw translated cube (Red)
    glPushMatrix();
    glTranslatef(2.0f, 1.5f, -1.0f);
    drawCube(1.0f, 1.0f, 0.0f, 0.0f);
    
    // Draw coordinate point
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
    
    glPointSize(1.0f);
    
    // Draw connecting line
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 1.5f, -1.0f);
    glEnd();
    
    // Draw labels in main window
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-2.0f, 1.5f, 0.0f);
    std::string label = "Original (0,0,0)";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(2.0f, 2.0f, -1.0f);
    label = "Translated (2.0,1.5,-1.0)";
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
    gluOrtho2D(0, 400, 0, 300);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Title
    glRasterPos2f(50, 250);
    std::string title = "3D TRANSLATION COORDINATES";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Original Coordinates
    glRasterPos2f(50, 200);
    std::string orig = "ORIGINAL CUBE (Green):";
    for (char c : orig) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 180);
    std::string origPos = "Local Position: (0.0, 0.0, 0.0)";
    for (char c : origPos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 160);
    origPos = "World Coordinates: (-2.0, 0.0, 0.0)";
    for (char c : origPos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Translated Coordinates
    glRasterPos2f(50, 120);
    std::string trans = "TRANSLATED CUBE (Red):";
    for (char c : trans) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 100);
    std::string transPos = "Local Position: (0.0, 0.0, 0.0)";
    for (char c : transPos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 80);
    transPos = "World Coordinates: (" + 
               floatToString(2.0f) + ", " + 
               floatToString(1.5f) + ", " + 
               floatToString(-1.0f) + ")";
    for (char c : transPos) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Translation Vector
    glRasterPos2f(50, 50);
    std::string transVec = "TRANSLATION VECTOR:";
    for (char c : transVec) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 30);
    std::string vector = "T = (" + 
                         floatToString(translateX) + ", " + 
                         floatToString(translateY) + ", " + 
                         floatToString(translateZ) + ")";
    for (char c : vector) {
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
        infoWindow = glutCreateWindow("Translation Coordinates Info");
        glutPositionWindow(820, 10);
        glutReshapeWindow(400, 300);
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
    mainWindow = glutCreateWindow("3D Translation with Coordinates Info");
    
    init();
    
    glutDisplayFunc(displayMain);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);
    
    std::cout << "3D Translation Demonstration\n";
    std::cout << "============================\n";
    std::cout << "Press 'I' to show/hide coordinates window\n";
    std::cout << "Press ESC to exit\n\n";
    std::cout << "Translation Details:\n";
    std::cout << "Original Position: (0,0,0)\n";
    std::cout << "Translation Vector: (2.0, 1.5, -1.0)\n";
    std::cout << "Final Position: (2.0, 1.5, -1.0)\n";
    
    glutMainLoop();
    return 0;
}
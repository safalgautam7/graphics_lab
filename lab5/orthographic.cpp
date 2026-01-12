#include <GL/glut.h>
#include <iostream>
#include <string>
#include <sstream>

// Global variables
bool showInfoWindow = false;
bool orthographicView = true;
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
    
    // Draw grid lines
    for(float x = -5.0f; x <= 5.0f; x += 1.0f) {
        glVertex3f(x, -5.0f, 0.0f);
        glVertex3f(x, 5.0f, 0.0f);
    }
    
    for(float y = -5.0f; y <= 5.0f; y += 1.0f) {
        glVertex3f(-5.0f, y, 0.0f);
        glVertex3f(5.0f, y, 0.0f);
    }
    
    glEnd();
}

void drawCoordinateAxes() {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(4.0f, 0.0f, 0.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 4.0f, 0.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 4.0f);
    
    glEnd();
    
    // Draw axis labels
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f(4.2f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos3f(0.0f, 4.2f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos3f(0.0f, 0.0f, 4.2f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z');
    
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
    
    if (orthographicView) {
        // Set orthographic projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-6.0, 6.0, -6.0, 6.0, 0.1, 50.0);
    } else {
        // Set perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, 800.0/600.0, 0.1, 100.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (orthographicView) {
        // Set orthographic view
        gluLookAt(0.0f, 0.0f, 10.0f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);
    } else {
        // Set perspective view
        gluLookAt(5.0f, 5.0f, 10.0f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);
    }
    
    // Draw grid
    drawGrid();
    
    // Draw coordinate axes
    drawCoordinateAxes();
    
    // Draw text labels
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-5.5f, 5.5f, 0.0f);
    std::string label = orthographicView ? 
        "Orthographic Projection - No Perspective" : 
        "Perspective Projection - With Depth";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Draw multiple 3D objects
    // Cube 1 (Red) - Closest
    glPushMatrix();
    glTranslatef(-3.0f, 3.0f, -2.0f);
    drawCube(1.0f, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    
    // Pyramid 1 (Green)
    glPushMatrix();
    glTranslatef(3.0f, 3.0f, -4.0f);
    drawPyramid(1.0f, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Cube 2 (Blue)
    glPushMatrix();
    glTranslatef(-3.0f, -3.0f, -6.0f);
    drawCube(1.0f, 0.0f, 0.0f, 1.0f);
    glPopMatrix();
    
    // Pyramid 2 (Yellow)
    glPushMatrix();
    glTranslatef(3.0f, -3.0f, -8.0f);
    drawPyramid(1.0f, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
    
    // Draw a larger object in center (Magenta)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    drawCube(1.5f, 1.0f, 0.0f, 1.0f);
    glPopMatrix();
    
    // Draw Z-coordinate labels
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-3.5f, 2.0f, -2.0f);
    label = "Z = -2.0";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(2.5f, 2.0f, -4.0f);
    label = "Z = -4.0";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(-3.5f, -2.0f, -6.0f);
    label = "Z = -6.0";
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos3f(2.5f, -2.0f, -8.0f);
    label = "Z = -8.0";
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
    std::string title = "ORTHOGRAPHIC PROJECTION INFO";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Orthographic vs Perspective
    glRasterPos2f(50, 340);
    std::string projType = orthographicView ? 
        "CURRENT: ORTHOGRAPHIC PROJECTION" : 
        "CURRENT: PERSPECTIVE PROJECTION";
    for (char c : projType) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Orthographic Properties
    glRasterPos2f(50, 310);
    std::string orthoProps = "ORTHOGRAPHIC PROJECTION PROPERTIES:";
    for (char c : orthoProps) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 290);
    std::string prop1 = "1. No perspective distortion";
    for (char c : prop1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 270);
    std::string prop2 = "2. Parallel lines remain parallel";
    for (char c : prop2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 250);
    std::string prop3 = "3. Objects appear same size regardless of distance";
    for (char c : prop3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 230);
    std::string prop4 = "4. Preserves angles and shapes";
    for (char c : prop4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 210);
    std::string prop5 = "5. Commonly used in CAD and technical drawings";
    for (char c : prop5) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Object Coordinates
    glRasterPos2f(50, 180);
    std::string objCoords = "OBJECT WORLD COORDINATES:";
    for (char c : objCoords) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glRasterPos2f(70, 160);
    std::string cube1 = "Red Cube: (-3.0, 3.0, -2.0)";
    for (char c : cube1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 140);
    std::string pyramid1 = "Green Pyramid: (3.0, 3.0, -4.0)";
    for (char c : pyramid1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 120);
    std::string cube2 = "Blue Cube: (-3.0, -3.0, -6.0)";
    for (char c : cube2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 100);
    std::string pyramid2 = "Yellow Pyramid: (3.0, -3.0, -8.0)";
    for (char c : pyramid2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 80);
    std::string centerCube = "Magenta Center Cube: (0.0, 0.0, -5.0)";
    for (char c : centerCube) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Note
    glRasterPos2f(50, 50);
    std::string note = "NOTE: In orthographic view, objects at Z=-2 and Z=-8";
    for (char c : note) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 30);
    note = "appear the same size despite different distances!";
    for (char c : note) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glutSwapBuffers();
}

void reshapeMain(int w, int h) {
    glutSetWindow(mainWindow);
    glViewport(0, 0, w, h);
}

void reshapeInfo(int w, int h) {
    glutSetWindow(infoWindow);
    glViewport(0, 0, w, h);
}

void createInfoWindow() {
    if (!showInfoWindow) {
        infoWindow = glutCreateWindow("Orthographic Projection Info");
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
    } else if (key == 'p' || key == 'P') {
        orthographicView = !orthographicView;
        std::cout << "Switched to " << 
            (orthographicView ? "Orthographic" : "Perspective") << 
            " projection\n";
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
    mainWindow = glutCreateWindow("Orthographic Projection with Info");
    
    init();
    
    glutDisplayFunc(displayMain);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);
    
    std::cout << "Orthographic Projection Demonstration\n";
    std::cout << "====================================\n";
    std::cout << "Press 'I' to show/hide info window\n";
    std::cout << "Press 'P' to toggle Orthographic/Perspective\n";
    std::cout << "Press ESC to exit\n\n";
    std::cout << "Features:\n";
    std::cout << "1. Toggle between Orthographic and Perspective views\n";
    std::cout << "2. Grid showing X-Y plane coordinates\n";
    std::cout << "3. Multiple objects at different Z positions\n";
    std::cout << "4. Info window shows coordinates and properties\n";
    
    glutMainLoop();
    return 0;
}
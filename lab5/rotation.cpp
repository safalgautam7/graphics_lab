#include <GL/glut.h> 
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

// Global variables
float rotationAngle = 45.0f;
bool showInfoWindow = false;
int mainWindow, infoWindow;
bool showXAxis = false;
bool showYAxis = false;
bool showZAxis = false;
bool showOriginal = true;

// Camera control variables
float cameraDistance = 12.0f;
float cameraAngleH = 45.0f;  // Horizontal angle (azimuth)
float cameraAngleV = 30.0f;  // Vertical angle (elevation)
float cameraX, cameraY, cameraZ;

void updateCameraPosition() {
    // Convert spherical coordinates to Cartesian
    float radH = cameraAngleH * M_PI / 180.0f;
    float radV = cameraAngleV * M_PI / 180.0f;
    
    cameraX = cameraDistance * cos(radV) * cos(radH);
    cameraY = cameraDistance * sin(radV);
    cameraZ = cameraDistance * cos(radV) * sin(radH);
}

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
    
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    
    updateCameraPosition();
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
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    
    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 0.0f);
    
    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 3.0f);
    
    glEnd();
    
    // Draw axis labels
    glColor3f(1.0f, 0.0f, 0.0f);  // Red for X
    glRasterPos3f(3.2f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
    
    glColor3f(0.0f, 1.0f, 0.0f);  // Green for Y
    glRasterPos3f(0.0f, 3.2f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
    
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue for Z
    glRasterPos3f(0.0f, 0.0f, 3.2f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z');
    
    glLineWidth(1.0f);
}

void drawCube(float size, float r, float g, float b) {
    float s = size / 2.0f;
    
    glColor3f(r, g, b);
    
    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);
    glEnd();
    
    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, -s, -s);
    glEnd();
    
    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-s, s, -s);
    glVertex3f(-s, s, s);
    glVertex3f(s, s, s);
    glVertex3f(s, s, -s);
    glEnd();
    
    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, -s, s);
    glVertex3f(-s, -s, s);
    glEnd();
    
    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, s, s);
    glVertex3f(s, -s, s);
    glEnd();
    
    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
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
    
    gluLookAt(cameraX, cameraY, cameraZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    
    drawGrid();
    drawCoordinateAxes();
    
    // Draw instruction text
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-5.0f, 4.5f, -5.0f);
    std::string instructions = "Controls: X/Y/Z-rotation, O-original, I-info, Arrow keys-camera";
    for (char c : instructions) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Draw camera info
    glRasterPos3f(-5.0f, 4.0f, -5.0f);
    std::string camInfo = "Camera: H=" + floatToString(cameraAngleH) + "° V=" + 
                          floatToString(cameraAngleV) + "° D=" + floatToString(cameraDistance);
    for (char c : camInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Draw original cube (Green)
    if (showOriginal) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        drawCube(2.0f, 0.0f, 1.0f, 0.0f);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(0.0f, 1.5f, 0.0f);
        std::string label = "Original";
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
        glPopMatrix();
    }
    
    // Draw X-axis rotated cube (Red)
    if (showXAxis) {
        glPushMatrix();
        glTranslatef(3.0f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
        drawCube(2.0f, 1.0f, 0.0f, 0.0f);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(0.0f, 1.5f, 0.0f);
        std::string label = "X-rotation";
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
        glPopMatrix();
    }
    
    // Draw Y-axis rotated cube (Blue)
    if (showYAxis) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 3.0f);
        glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
        drawCube(2.0f, 0.0f, 0.0f, 1.0f);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(0.0f, 1.5f, 0.0f);
        std::string label = "Y-rotation";
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
        glPopMatrix();
    }
    
    // Draw Z-axis rotated cube (Yellow)
    if (showZAxis) {
        glPushMatrix();
        glTranslatef(-3.0f, 0.0f, 0.0f);
        glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
        drawCube(2.0f, 1.0f, 1.0f, 0.0f);
        
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos3f(0.0f, 1.5f, 0.0f);
        std::string label = "Z-rotation";
        for (char c : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
        }
        glPopMatrix();
    }
    
    // Draw status text
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(-5.0f, 3.5f, -5.0f);
    std::string status = "Active: " + std::string(showOriginal ? "Original " : "") + 
                         std::string(showXAxis ? "X-rotation " : "") + 
                         std::string(showYAxis ? "Y-rotation " : "") + 
                         std::string(showZAxis ? "Z-rotation" : "");
    for (char c : status) {
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
    gluOrtho2D(0, 500, 0, 450);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Title
    glRasterPos2f(100, 420);
    std::string title = "3D ROTATION COORDINATES";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Camera controls
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(50, 390);
    std::string camTitle = "CAMERA CONTROLS:";
    for (char c : camTitle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 370);
    std::string cam1 = "Arrow Keys: Rotate camera horizontally/vertically";
    for (char c : cam1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 355);
    std::string cam2 = "W/S: Move camera closer/farther";
    for (char c : cam2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 340);
    std::string cam3 = "R: Reset camera to default position";
    for (char c : cam3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 325);
    std::string cam4 = "Current: H=" + floatToString(cameraAngleH) + "° V=" + 
                       floatToString(cameraAngleV) + "° Dist=" + floatToString(cameraDistance);
    for (char c : cam4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Rotation angle
    glRasterPos2f(50, 295);
    std::string angle = "ROTATION ANGLE: " + floatToString(rotationAngle) + " degrees";
    for (char c : angle) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Cube Information
    glRasterPos2f(50, 265);
    std::string cubeInfo = "CUBE DIMENSIONS: 2x2x2 units";
    for (char c : cubeInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // X-axis Rotation
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(50, 225);
    std::string xRot = "X-AXIS ROTATION (Red):";
    for (char c : xRot) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 205);
    std::string xInfo = "Rotation around X-axis by " + floatToString(rotationAngle) + "°";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 190);
    xInfo = "Matrix: Rx(θ) = [[1, 0, 0], [0, cosθ, -sinθ], [0, sinθ, cosθ]]";
    for (char c : xInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Y-axis Rotation
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(50, 160);
    std::string yRot = "Y-AXIS ROTATION (Blue):";
    for (char c : yRot) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 140);
    std::string yInfo = "Rotation around Y-axis by " + floatToString(rotationAngle) + "°";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 125);
    yInfo = "Matrix: Ry(θ) = [[cosθ, 0, sinθ], [0, 1, 0], [-sinθ, 0, cosθ]]";
    for (char c : yInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Z-axis Rotation
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2f(50, 95);
    std::string zRot = "Z-AXIS ROTATION (Yellow):";
    for (char c : zRot) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(70, 75);
    std::string zInfo = "Rotation around Z-axis by " + floatToString(rotationAngle) + "°";
    for (char c : zInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(70, 60);
    zInfo = "Matrix: Rz(θ) = [[cosθ, -sinθ, 0], [sinθ, cosθ, 0], [0, 0, 1]]";
    for (char c : zInfo) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    // Preset views
    glColor3f(0.5f, 1.0f, 0.5f);
    glRasterPos2f(50, 30);
    std::string presets = "Preset Views: 1-Front, 2-Top, 3-Side, 4-Isometric";
    for (char c : presets) {
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
        glutReshapeWindow(500, 450);
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
    switch(key) {
        case 'x':
        case 'X':
            showXAxis = !showXAxis;
            showYAxis = false;
            showZAxis = false;
            showOriginal = false;
            break;
            
        case 'y':
        case 'Y':
            showYAxis = !showYAxis;
            showXAxis = false;
            showZAxis = false;
            showOriginal = false;
            break;
            
        case 'z':
        case 'Z':
            showZAxis = !showZAxis;
            showXAxis = false;
            showYAxis = false;
            showOriginal = false;
            break;
            
        case 'o':
        case 'O':
            showOriginal = true;
            showXAxis = false;
            showYAxis = false;
            showZAxis = false;
            break;
            
        case 'i':
        case 'I':
            createInfoWindow();
            break;
            
        case 'a':
        case 'A':
            showOriginal = true;
            showXAxis = true;
            showYAxis = true;
            showZAxis = true;
            break;
            
        case 'w':
        case 'W':
            // Move camera closer
            cameraDistance -= 0.5f;
            if (cameraDistance < 3.0f) cameraDistance = 3.0f;
            updateCameraPosition();
            break;
            
        case 's':
        case 'S':
            // Move camera farther
            cameraDistance += 0.5f;
            if (cameraDistance > 25.0f) cameraDistance = 25.0f;
            updateCameraPosition();
            break;
            
        case 'r':
        case 'R':
            // Reset camera
            cameraDistance = 12.0f;
            cameraAngleH = 45.0f;
            cameraAngleV = 30.0f;
            updateCameraPosition();
            break;
            
        // Preset camera views
        case '1':
            // Front view
            cameraAngleH = 0.0f;
            cameraAngleV = 0.0f;
            updateCameraPosition();
            break;
            
        case '2':
            // Top view
            cameraAngleH = 0.0f;
            cameraAngleV = 89.0f;
            updateCameraPosition();
            break;
            
        case '3':
            // Side view
            cameraAngleH = 90.0f;
            cameraAngleV = 0.0f;
            updateCameraPosition();
            break;
            
        case '4':
            // Isometric view
            cameraAngleH = 45.0f;
            cameraAngleV = 35.26f;
            updateCameraPosition();
            break;
            
        case 27:  // ESC key
            exit(0);
            break;
    }
    
    glutSetWindow(mainWindow);
    glutPostRedisplay();
    
    if (showInfoWindow) {
        glutSetWindow(infoWindow);
        glutPostRedisplay();
    }
}

void specialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:
            cameraAngleH -= 5.0f;
            updateCameraPosition();
            break;
            
        case GLUT_KEY_RIGHT:
            cameraAngleH += 5.0f;
            updateCameraPosition();
            break;
            
        case GLUT_KEY_UP:
            cameraAngleV += 5.0f;
            if (cameraAngleV > 89.0f) cameraAngleV = 89.0f;
            updateCameraPosition();
            break;
            
        case GLUT_KEY_DOWN:
            cameraAngleV -= 5.0f;
            if (cameraAngleV < -89.0f) cameraAngleV = -89.0f;
            updateCameraPosition();
            break;
    }
    
    glutSetWindow(mainWindow);
    glutPostRedisplay();
    
    if (showInfoWindow) {
        glutSetWindow(infoWindow);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Create main window
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    mainWindow = glutCreateWindow("3D Cube Rotation Demo - Camera Control");
    
    init();
    
    showOriginal = true;
    
    glutDisplayFunc(displayMain);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    std::cout << "3D Cube Rotation Demonstration with Camera Control\n";
    std::cout << "===================================================\n";
    std::cout << "Rotation Controls:\n";
    std::cout << "  X - Toggle X-axis rotation (Red cube)\n";
    std::cout << "  Y - Toggle Y-axis rotation (Blue cube)\n";
    std::cout << "  Z - Toggle Z-axis rotation (Yellow cube)\n";
    std::cout << "  O - Show original cube only (Green)\n";
    std::cout << "  A - Show all cubes\n";
    std::cout << "  I - Show/hide info window\n\n";
    std::cout << "Camera Controls:\n";
    std::cout << "  Arrow Keys - Rotate camera view\n";
    std::cout << "  W/S - Move camera closer/farther\n";
    std::cout << "  R - Reset camera to default position\n\n";
    std::cout << "Preset Camera Views:\n";
    std::cout << "  1 - Front view\n";
    std::cout << "  2 - Top view\n";
    std::cout << "  3 - Side view\n";
    std::cout << "  4 - Isometric view\n\n";
    std::cout << "  ESC - Exit\n\n";
    std::cout << "Fixed Rotation Angle: 45°\n";
    
    glutMainLoop();
    return 0;
}
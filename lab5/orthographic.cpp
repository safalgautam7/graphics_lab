#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Window dimensions
int windowWidth = 1200;
int windowHeight = 800;

// View mode: 0 = 3D, 1 = Top, 2 = Front, 3 = Right
int viewMode = 0;

// Rotation angles for 3D view
float rotX = 30.0f;
float rotY = 45.0f;

// Mouse interaction
int lastMouseX, lastMouseY;
bool mouseRotating = false;

// Draw a grid on a plane
void drawGrid(float size, int divisions, bool xz = true) {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    
    float step = size / divisions;
    float half = size / 2.0f;
    
    for (int i = 0; i <= divisions; i++) {
        float pos = -half + i * step;
        
        if (xz) {
            // XZ plane (horizontal)
            glVertex3f(pos, 0, -half);
            glVertex3f(pos, 0, half);
            glVertex3f(-half, 0, pos);
            glVertex3f(half, 0, pos);
        } else {
            // XY plane (vertical)
            glVertex3f(pos, -half, 0);
            glVertex3f(pos, half, 0);
            glVertex3f(-half, pos, 0);
            glVertex3f(half, pos, 0);
        }
    }
    glEnd();
    
    // Draw axes
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    
    // X axis - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(half, 0, 0);
    
    // Y axis - Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, half, 0);
    
    // Z axis - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, half);
    
    glEnd();
    glLineWidth(1.0f);
}

// Draw a 3D house-like object
void draw3DObject() {
    // Base cube
    glColor3f(0.8f, 0.6f, 0.4f);
    glutSolidCube(1.0);
    
    // Draw cube wireframe
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glutWireCube(1.01);
    glLineWidth(1.0f);
    
    // Roof (pyramid)
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    
    glColor3f(0.6f, 0.3f, 0.2f);
    glutSolidCone(0.7, 0.5, 4, 1);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glutWireCone(0.71, 0.51, 4, 1);
    glLineWidth(1.0f);
    
    glPopMatrix();
    
    // Door
    glColor3f(0.3f, 0.2f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, -0.25f, 0.51f);
    glScalef(0.3f, 0.5f, 0.02f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Window
    glColor3f(0.5f, 0.7f, 0.9f);
    glPushMatrix();
    glTranslatef(0.3f, 0.15f, 0.51f);
    glScalef(0.25f, 0.25f, 0.02f);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Setup orthographic projection for different views
void setupOrthographicView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float viewSize = 2.5f;
    
    switch(viewMode) {
        case 0: // 3D Perspective-like orthographic
            glOrtho(-viewSize, viewSize, -viewSize, viewSize, -10, 10);
            break;
        case 1: // Top view (looking down Y axis)
            glOrtho(-viewSize, viewSize, -viewSize, viewSize, -10, 10);
            break;
        case 2: // Front view (looking down Z axis)
            glOrtho(-viewSize, viewSize, -viewSize, viewSize, -10, 10);
            break;
        case 3: // Right view (looking down X axis)
            glOrtho(-viewSize, viewSize, -viewSize, viewSize, -10, 10);
            break;
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    setupOrthographicView();
    
    glLoadIdentity();
    
    // Set up camera based on view mode
    switch(viewMode) {
        case 0: // 3D view with rotation
            glRotatef(rotX, 1, 0, 0);
            glRotatef(rotY, 0, 1, 0);
            drawGrid(4.0f, 8, true);
            break;
            
        case 1: // Top view
            glRotatef(90, 1, 0, 0);
            drawGrid(4.0f, 8, true);
            break;
            
        case 2: // Front view
            drawGrid(4.0f, 8, false);
            break;
            
        case 3: // Right view
            glRotatef(90, 0, 1, 0);
            drawGrid(4.0f, 8, false);
            break;
    }
    
    // Draw the 3D object
    draw3DObject();
    
    // Draw view label
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    const char* viewName;
    switch(viewMode) {
        case 0: viewName = "3D View (Click and drag to rotate)"; break;
        case 1: viewName = "Top View (Orthographic)"; break;
        case 2: viewName = "Front View (Orthographic)"; break;
        case 3: viewName = "Right View (Orthographic)"; break;
    }
    
    glRasterPos2i(10, windowHeight - 20);
    for (const char* c = viewName; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    const char* instructions = "Keys: 1=3D  2=Top  3=Front  4=Right  ESC=Quit";
    glRasterPos2i(10, windowHeight - 45);
    for (const char* c = instructions; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    setupOrthographicView();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1':
            viewMode = 0;
            break;
        case '2':
            viewMode = 1;
            break;
        case '3':
            viewMode = 2;
            break;
        case '4':
            viewMode = 3;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (viewMode == 0) { // Only allow rotation in 3D view
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                mouseRotating = true;
                lastMouseX = x;
                lastMouseY = y;
            } else {
                mouseRotating = false;
            }
        }
    }
}

void motion(int x, int y) {
    if (mouseRotating && viewMode == 0) {
        rotY += (x - lastMouseX) * 0.5f;
        rotX += (y - lastMouseY) * 0.5f;
        
        lastMouseX = x;
        lastMouseY = y;
        
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat lightPos[] = {2.0f, 3.0f, 2.0f, 1.0f};
    GLfloat lightAmb[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDif[] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    
    std::cout << "Orthographic Projection Viewer\n";
    std::cout << "Controls:\n";
    std::cout << "  1 - 3D View (click and drag to rotate)\n";
    std::cout << "  2 - Top View\n";
    std::cout << "  3 - Front View\n";
    std::cout << "  4 - Right View\n";
    std::cout << "  ESC - Quit\n";
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Orthographic Projection - Multiple Views");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}
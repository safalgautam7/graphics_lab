#include <windows.h>
#include <GL/glut.h>
#include <iostream>

// Clipping window boundaries
const int X_MIN = -80;
const int X_MAX = 80;
const int Y_MIN = -80;
const int Y_MAX = 80;

// Region codes
const int INSIDE = 0;    // 0000
const int LEFT = 1;      // 0001
const int RIGHT = 2;     // 0010
const int BOTTOM = 4;    // 0100
const int TOP = 8;       // 1000

// One comprehensive line that crosses all boundaries
// Changed variable names to avoid conflict with built-in y1
float line_x1 = -120, line_y1 = -50;  // Start point (outside left)
float line_x2 = 120, line_y2 = 100;   // End point (outside right and top)

int computeCode(float x, float y) {
    int code = INSIDE;
    
    if (x < X_MIN) code |= LEFT;
    else if (x > X_MAX) code |= RIGHT;
    
    if (y < Y_MIN) code |= BOTTOM;
    else if (y > Y_MAX) code |= TOP;
    
    return code;
}

bool cohenSutherlandClip(float &x1, float &y1, float &x2, float &y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;
    
    while (true) {
        if (!(code1 | code2)) {
            // Both endpoints inside clipping window
            accept = true;
            break;
        } else if (code1 & code2) {
            // Both endpoints outside on same side
            break;
        } else {
            // Line needs clipping
            int codeOut = code1 ? code1 : code2;
            float x, y;
            
            // Find intersection point
            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }
            
            // Replace outside point with intersection point
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    return accept;
}

void drawGrid() {
    // Light gray grid
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_LINES);
    
    for (int x = -150; x <= 150; x += 30) {
        glVertex2i(x, -150);
        glVertex2i(x, 150);
    }
    for (int y = -150; y <= 150; y += 30) {
        glVertex2i(-150, y);
        glVertex2i(150, y);
    }
    glEnd();
    
    // Axes
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(-150, 0);
    glVertex2i(150, 0);
    glVertex2i(0, -150);
    glVertex2i(0, 150);
    glEnd();
    glLineWidth(1.0f);
}

void drawClipWindow() {
    // Draw clipping window
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(X_MIN, Y_MIN);
    glVertex2i(X_MAX, Y_MIN);
    glVertex2i(X_MAX, Y_MAX);
    glVertex2i(X_MIN, Y_MAX);
    glEnd();
    glLineWidth(1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawClipWindow();
    
    // Store original coordinates
    float orig_x1 = -120, orig_y1 = -50;
    float orig_x2 = 120, orig_y2 = 100;
    
    // Calculate clipped coordinates
    float clip_x1 = orig_x1, clip_y1 = orig_y1;
    float clip_x2 = orig_x2, clip_y2 = orig_y2;
    
    // Apply Cohen-Sutherland algorithm
    bool visible = cohenSutherlandClip(clip_x1, clip_y1, clip_x2, clip_y2);
    
    // Draw original line (dashed blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(2.0f);
    glLineStipple(2, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex2f(orig_x1, orig_y1);
    glVertex2f(orig_x2, orig_y2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    // Draw clipped line (solid green)
    if (visible) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex2f(clip_x1, clip_y1);
        glVertex2f(clip_x2, clip_y2);
        glEnd();
    }
    
    // Draw endpoint markers
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    // Original endpoints
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(orig_x1, orig_y1);
    glVertex2f(orig_x2, orig_y2);
    // Clipped endpoints (if different)
    if (visible) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(clip_x1, clip_y1);
        glVertex2f(clip_x2, clip_y2);
    }
    glEnd();
    
    // Display information
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glRasterPos2f(-140, 140);
    std::string title = "COHEN-SUTHERLAND LINE CLIPPING (SINGLE LINE)";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glRasterPos2f(-140, 125);
    std::string line = "Original Line: (-120,-50) to (120,100)";
    for (char c : line) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-140, 110);
    if (visible) {
        std::string clipped = "Clipped Line: (" + std::to_string((int)clip_x1) + "," + 
                             std::to_string((int)clip_y1) + ") to (" + 
                             std::to_string((int)clip_x2) + "," + 
                             std::to_string((int)clip_y2) + ")";
        for (char c : clipped) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    } else {
        std::string msg = "Line completely outside clipping window";
        for (char c : msg) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(-140, 95);
    std::string window = "Clipping Window: (-80,-80) to (80,80)";
    for (char c : window) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-140, 80);
    std::string legend = "BLUE (dashed): Original | GREEN (solid): Clipped | Dots: Endpoints";
    for (char c : legend) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Region codes display
    glRasterPos2f(-140, 60);
    std::string codes = "Region Codes: INSIDE=0000, LEFT=0001, RIGHT=0010, BOTTOM=0100, TOP=1000";
    for (char c : codes) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-150, 150, -150, 150);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping - Fixed");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
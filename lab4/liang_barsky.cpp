#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Clipping window boundaries
const float X_MIN = -60;
const float X_MAX = 60;
const float Y_MIN = -60;
const float Y_MAX = 60;

// A line that better demonstrates parametric clipping
// Line goes from bottom-left to top-right, crossing through the window
float start_x = -100, start_y = -100;  // Start point (outside bottom-left)
float end_x = 120, end_y = 80;         // End point (outside top-right)

bool liangBarskyClip(float &x1, float &y1, float &x2, float &y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    // Parameters p and q for Liang-Barsky
    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x1 - X_MIN, X_MAX - x1, y1 - Y_MIN, Y_MAX - y1};
    
    float u1 = 0.0f;  // Entry point parameter
    float u2 = 1.0f;  // Exit point parameter
    
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            // Line is parallel to boundary
            if (q[i] < 0) {
                return false;  // Line is completely outside
            }
        } else {
            float r = q[i] / p[i];
            if (p[i] < 0) {
                // Potential entry point
                u1 = fmax(u1, r);
            } else {
                // Potential exit point
                u2 = fmin(u2, r);
            }
        }
    }
    
    if (u1 > u2) {
        return false;  // Line is completely outside
    }
    
    // Calculate clipped endpoints using parametric equations
    float nx1 = x1 + u1 * dx;
    float ny1 = y1 + u1 * dy;
    float nx2 = x1 + u2 * dx;
    float ny2 = y1 + u2 * dy;
    
    x1 = nx1; y1 = ny1;
    x2 = nx2; y2 = ny2;
    
    return true;
}

void drawGrid() {
    // Light gray grid
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_LINES);
    
    for (int x = -120; x <= 120; x += 30) {
        glVertex2i(x, -120);
        glVertex2i(x, 120);
    }
    for (int y = -120; y <= 120; y += 30) {
        glVertex2i(-120, y);
        glVertex2i(120, y);
    }
    glEnd();
    
    // Black axes
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(-120, 0);
    glVertex2i(120, 0);
    glVertex2i(0, -120);
    glVertex2i(0, 120);
    glEnd();
    glLineWidth(1.0f);
}

void drawClipWindow() {
    // Draw clipping window (blue border)
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(X_MIN, Y_MIN);
    glVertex2f(X_MAX, Y_MIN);
    glVertex2f(X_MAX, Y_MAX);
    glVertex2f(X_MIN, Y_MAX);
    glEnd();
    glLineWidth(1.0f);
    
    // Label the clipping window
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(X_MIN + 5, Y_MAX - 15);
    std::string label = "Clipping Window";
    for (char c : label) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawClipWindow();
    
    // Store original coordinates
    float orig_x1 = -100, orig_y1 = -100;
    float orig_x2 = 120, orig_y2 = 80;
    
    // Calculate clipped coordinates
    float clip_x1 = orig_x1, clip_y1 = orig_y1;
    float clip_x2 = orig_x2, clip_y2 = orig_y2;
    
    // Apply Liang-Barsky algorithm
    bool visible = liangBarskyClip(clip_x1, clip_y1, clip_x2, clip_y2);
    
    // Draw original line (thick dashed red)
    glColor3f(1.0f, 0.3f, 0.3f);
    glLineWidth(2.5f);
    glLineStipple(2, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex2f(orig_x1, orig_y1);
    glVertex2f(orig_x2, orig_y2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    // Draw clipped line (thick solid green)
    if (visible) {
        glColor3f(0.2f, 0.8f, 0.2f);
        glLineWidth(4.0f);
        glBegin(GL_LINES);
        glVertex2f(clip_x1, clip_y1);
        glVertex2f(clip_x2, clip_y2);
        glEnd();
    }
    
    // Draw endpoint markers
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    // Original endpoints (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(orig_x1, orig_y1);
    glVertex2f(orig_x2, orig_y2);
    
    // Clipped endpoints (green)
    if (visible) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(clip_x1, clip_y1);
        glVertex2f(clip_x2, clip_y2);
    }
    glEnd();
    
    // Draw arrows to show clipping
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glLineStipple(1, 0xF0F0);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    // Connect original to clipped endpoints
    glVertex2f(orig_x1, orig_y1);
    glVertex2f(clip_x1, clip_y1);
    glVertex2f(orig_x2, orig_y2);
    glVertex2f(clip_x2, clip_y2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    // Display information at top
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glRasterPos2f(-110, 115);
    std::string title = "LIANG-BARSKY LINE CLIPPING ALGORITHM";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glRasterPos2f(-110, 100);
    std::string line = "Original Line: (-100,-100) to (120,80)";
    for (char c : line) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-110, 85);
    if (visible) {
        std::string clipped = "Clipped Segment: (" + 
                             std::to_string((int)clip_x1) + "," + 
                             std::to_string((int)clip_y1) + ") to (" + 
                             std::to_string((int)clip_x2) + "," + 
                             std::to_string((int)clip_y2) + ")";
        for (char c : clipped) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glRasterPos2f(-110, 70);
    std::string window = "Clipping Window: (-60,-60) to (60,60)";
    for (char c : window) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Algorithm explanation
    glRasterPos2f(-110, 55);
    std::string algo = "Liang-Barsky uses parametric line equations:";
    for (char c : algo) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-110, 45);
    std::string formula1 = "Line: x = x1 + u*dx, y = y1 + u*dy where 0 ≤ u ≤ 1";
    for (char c : formula1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-110, 35);
    std::string formula2 = "Clip against boundaries: Xmin ≤ x1+u*dx ≤ Xmax, Ymin ≤ y1+u*dy ≤ Ymax";
    for (char c : formula2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Visual legend
    glRasterPos2f(-110, 20);
    std::string legend = "RED (dashed): Original Line | GREEN (solid): Clipped Segment";
    for (char c : legend) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-110, 10);
    std::string dots = "Red dots: Original endpoints | Green dots: Clipped endpoints";
    for (char c : dots) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Show parametric values
    if (visible) {
        float dx = orig_x2 - orig_x1;
        float dy = orig_y2 - orig_y1;
        float u_entry = (clip_x1 - orig_x1) / dx;
        float u_exit = (clip_x2 - orig_x1) / dx;
        
        glRasterPos2f(-110, -10);
        std::string param = "Parametric values: u_entry = " + 
                           std::to_string(u_entry).substr(0, 4) + 
                           ", u_exit = " + 
                           std::to_string(u_exit).substr(0, 4);
        for (char c : param) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    }
    
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-120, 120, -120, 120);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang-Barsky Line Clipping - Diagonal Line Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
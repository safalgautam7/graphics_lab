#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

// Clipping window boundaries
const float X_MIN = -50;
const float X_MAX = 50;
const float Y_MIN = -50;
const float Y_MAX = 50;

struct Point {
    float x, y;
    Point(float x = 0, float y = 0) : x(x), y(y) {}
};

// Single pentagon that crosses all boundaries
std::vector<Point> polygon = {
    Point(-80, 0),      // Left side
    Point(-20, 60),     // Top-left
    Point(60, 40),      // Top-right
    Point(80, -30),     // Right side
    Point(0, -80)       // Bottom
};

enum Edge { LEFT_EDGE, RIGHT_EDGE, BOTTOM_EDGE, TOP_EDGE };

Point intersect(Point p1, Point p2, Edge edge) {
    Point intersectPt;
    
    switch (edge) {
        case LEFT_EDGE:
            intersectPt.x = X_MIN;
            intersectPt.y = p1.y + (p2.y - p1.y) * (X_MIN - p1.x) / (p2.x - p1.x);
            break;
        case RIGHT_EDGE:
            intersectPt.x = X_MAX;
            intersectPt.y = p1.y + (p2.y - p1.y) * (X_MAX - p1.x) / (p2.x - p1.x);
            break;
        case BOTTOM_EDGE:
            intersectPt.y = Y_MIN;
            intersectPt.x = p1.x + (p2.x - p1.x) * (Y_MIN - p1.y) / (p2.y - p1.y);
            break;
        case TOP_EDGE:
            intersectPt.y = Y_MAX;
            intersectPt.x = p1.x + (p2.x - p1.x) * (Y_MAX - p1.y) / (p2.y - p1.y);
            break;
    }
    
    return intersectPt;
}

bool inside(Point p, Edge edge) {
    switch (edge) {
        case LEFT_EDGE:   return p.x >= X_MIN;
        case RIGHT_EDGE:  return p.x <= X_MAX;
        case BOTTOM_EDGE: return p.y >= Y_MIN;
        case TOP_EDGE:    return p.y <= Y_MAX;
    }
    return false;
}

std::vector<Point> clipPolygon(const std::vector<Point>& input, Edge edge) {
    std::vector<Point> output;
    
    for (size_t i = 0; i < input.size(); i++) {
        Point current = input[i];
        Point next = input[(i + 1) % input.size()];
        
        bool currentInside = inside(current, edge);
        bool nextInside = inside(next, edge);
        
        if (currentInside && nextInside) {
            output.push_back(next);
        } else if (currentInside && !nextInside) {
            output.push_back(intersect(current, next, edge));
        } else if (!currentInside && nextInside) {
            output.push_back(intersect(current, next, edge));
            output.push_back(next);
        }
    }
    
    return output;
}

void drawGrid() {
    // Light gray grid
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_LINES);
    
    for (int x = -100; x <= 100; x += 25) {
        glVertex2i(x, -100);
        glVertex2i(x, 100);
    }
    for (int y = -100; y <= 100; y += 25) {
        glVertex2i(-100, y);
        glVertex2i(100, y);
    }
    glEnd();
    
    // Axes
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2i(-100, 0);
    glVertex2i(100, 0);
    glVertex2i(0, -100);
    glVertex2i(0, 100);
    glEnd();
    glLineWidth(1.0f);
}

void drawClipWindow() {
    // Draw clipping window
    glColor3f(0.0f, 0.6f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(X_MIN, Y_MIN);
    glVertex2f(X_MAX, Y_MIN);
    glVertex2f(X_MAX, Y_MAX);
    glVertex2f(X_MIN, Y_MAX);
    glEnd();
    glLineWidth(1.0f);
}

void drawPolygon(const std::vector<Point>& poly, float r, float g, float b) {
    if (poly.empty()) return;
    
    // Draw filled polygon (semi-transparent)
    glColor4f(r, g, b, 0.4f);
    glBegin(GL_POLYGON);
    for (const auto& p : poly) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    
    // Draw polygon outline
    glColor3f(r, g, b);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
    for (const auto& p : poly) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glLineWidth(1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawClipWindow();
    
    // Apply polygon clipping
    std::vector<Point> clipped = polygon;
    
    // Clip against all four edges (in order)
    clipped = clipPolygon(clipped, LEFT_EDGE);
    clipped = clipPolygon(clipped, RIGHT_EDGE);
    clipped = clipPolygon(clipped, BOTTOM_EDGE);
    clipped = clipPolygon(clipped, TOP_EDGE);
    
    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Draw original polygon (blue)
    drawPolygon(polygon, 0.0f, 0.0f, 1.0f);
    
    // Draw clipped polygon (green)
    drawPolygon(clipped, 0.0f, 0.7f, 0.0f);
    
    glDisable(GL_BLEND);
    
    // Display information
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glRasterPos2f(-90, 90);
    std::string title = "SUTHERLAND-HODGEMAN POLYGON CLIPPING";
    for (char c : title) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    
    glRasterPos2f(-90, 80);
    std::string shape = "Original Shape: Pentagon (5 vertices)";
    for (char c : shape) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-90, 70);
    std::string clippedInfo = "Clipped Shape: " + std::to_string(clipped.size()) + " vertices";
    for (char c : clippedInfo) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-90, 60);
    std::string window = "Clipping Window: Square (-50,-50) to (50,50)";
    for (char c : window) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-90, 50);
    std::string algorithm = "Algorithm: Clip against 4 edges in fixed order";
    for (char c : algorithm) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glRasterPos2f(-90, 40);
    std::string legend = "BLUE: Original Polygon | GREEN: Clipped Polygon";
    for (char c : legend) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    // Show clipping process steps
    glRasterPos2f(-90, 25);
    std::string steps = "Clipping Steps: LEFT -> RIGHT -> BOTTOM -> TOP";
    for (char c : steps) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c);
    
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sutherland-Hodgeman Polygon Clipping - Single Case");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
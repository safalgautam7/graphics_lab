#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

// Global variables
int currentAlgorithm = 1;
const int WIDTH = 800;
const int HEIGHT = 600;

// ============= UTILITY FUNCTIONS =============
void putPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

// ============= 1. DDA LINE DRAWING ALGORITHM =============
void drawLineDDA(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        putPixel(x0, y0);
        return;
    }
    
    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;
    
    float x = x0, y = y0;
    
    for(int i = 0; i <= steps; i++) {
        putPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

// ============= 2. BRESENHAM LINE DRAWING ALGORITHM =============
void drawLineBresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    
    bool steep = dy > dx;
    
    if (steep) {
        // Swap x and y for steep lines
        int temp = x0; x0 = y0; y0 = temp;
        temp = x1; x1 = y1; y1 = temp;
        temp = dx; dx = dy; dy = temp;
        temp = sx; sx = sy; sy = temp;
    }
    
    int d = 2 * dy - dx;
    int y = y0;
    
    for (int x = x0; x != x1 + sx; x += sx) {
        if (steep)
            putPixel(y, x);
        else
            putPixel(x, y);
            
        if (d > 0) {
            y += sy;
            d -= 2 * dx;
        }
        d += 2 * dy;
    }
}

// ============= 3. MIDPOINT CIRCLE DRAWING ALGORITHM =============
void plotCirclePoints(int xc, int yc, int x, int y) {
    putPixel(xc + x, yc + y);
    putPixel(xc - x, yc + y);
    putPixel(xc + x, yc - y);
    putPixel(xc - x, yc - y);
    putPixel(xc + y, yc + x);
    putPixel(xc - y, yc + x);
    putPixel(xc + y, yc - x);
    putPixel(xc - y, yc - x);
}

void drawCircleMidpoint(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 1 - r;
    
    plotCirclePoints(xc, yc, x, y);
    
    while (x < y) {
        x++;
        if (d < 0) {
            d = d + 2 * x + 1;
        } else {
            y--;
            d = d + 2 * (x - y) + 1;
        }
        plotCirclePoints(xc, yc, x, y);
    }
}

// ============= 4. LINE GRAPH USING DDA/BRESENHAM =============
void drawLineGraph(bool useDDA) {
    // Sample sine wave data (similar to lab report)
    std::vector<float> dataX;
    std::vector<float> dataY;
    
    int numPoints = 50;
    float baseY = 300;
    float amplitude = 80;
    
    for (int i = 0; i < numPoints; i++) {
        float t = i * 2 * M_PI / numPoints;
        dataX.push_back(50 + i * 15);
        dataY.push_back(baseY + amplitude * sin(t));
    }
    
    // Draw axes
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(30, 50);
    glVertex2f(30, 550);
    glVertex2f(30, 550);
    glVertex2f(770, 550);
    glEnd();
    
    // Labels
    glColor3f(0.0, 0.0, 0.0);
    drawText(10, 30, "Y");
    drawText(760, 565, "X");
    
    // Draw rasterized line graph
    glColor3f(0.0, 0.5, 1.0);
    glPointSize(2.0);
    for (size_t i = 0; i < dataX.size() - 1; i++) {
        if (useDDA) {
            drawLineDDA((int)dataX[i], (int)dataY[i], (int)dataX[i+1], (int)dataY[i+1]);
        } else {
            drawLineBresenham((int)dataX[i], (int)dataY[i], (int)dataX[i+1], (int)dataY[i+1]);
        }
    }
    
    // Draw data points
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < dataX.size(); i++) {
        glVertex2f(dataX[i], dataY[i]);
    }
    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);
    if (useDDA) {
        drawText(270, 30, "Rasterized Line Graph using DDA");
    } else {
        drawText(250, 30, "Rasterized Line Graph using Bresenham");
    }
}

// ============= 5. PIE CHART =============
void drawFilledCircleSector(int xc, int yc, int r, float startAngle, float endAngle, 
                            float red, float green, float blue) {
    // Fill sector
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc, yc);
    
    for (float angle = startAngle; angle <= endAngle; angle += 0.01) {
        float x = xc + r * cos(angle);
        float y = yc + r * sin(angle);
        glVertex2f(x, y);
    }
    glVertex2f(xc + r * cos(endAngle), yc + r * sin(endAngle));
    glEnd();
    
    // Draw outline
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(xc, yc);
    for (float angle = startAngle; angle <= endAngle; angle += 0.01) {
        float x = xc + r * cos(angle);
        float y = yc + r * sin(angle);
        glVertex2f(x, y);
    }
    glVertex2f(xc + r * cos(endAngle), yc + r * sin(endAngle));
    glVertex2f(xc, yc);
    glEnd();
}

void drawPieChart() {
    int centerX = 400, centerY = 300, radius = 150;
    
    // Data from lab report: A=30%, B=15%, C=45%, D=10%
    float data[] = {30, 15, 45, 10};
    const char* labels[] = {"A (30%)", "B (15%)", "C (45%)", "D (10%)"};
    float colors[4][3] = {
        {0.2, 0.6, 1.0},   // Blue
        {1.0, 0.5, 0.0},   // Orange
        {0.3, 0.8, 0.3},   // Green
        {1.0, 0.3, 0.3}    // Red
    };
    
    float startAngle = 0;
    for (int i = 0; i < 4; i++) {
        float endAngle = startAngle + (data[i] / 100.0) * 2 * M_PI;
        drawFilledCircleSector(centerX, centerY, radius, startAngle, endAngle,
                               colors[i][0], colors[i][1], colors[i][2]);
        
        // Draw label
        float midAngle = (startAngle + endAngle) / 2.0;
        float labelX = centerX + (radius + 40) * cos(midAngle);
        float labelY = centerY + (radius + 40) * sin(midAngle);
        glColor3f(0.0, 0.0, 0.0);
        drawText(labelX - 20, labelY, labels[i]);
        
        startAngle = endAngle;
    }
    
    // Title
    glColor3f(0.0, 0.0, 0.0);
    drawText(320, 50, "Example Pie Chart");
}

// ============= DISPLAY FUNCTION =============
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4.0);
    
    switch(currentAlgorithm) {
        case 1: { // DDA Line
            glColor3f(0.0, 0.0, 1.0);
            drawLineDDA(50, 50, 400, 250);
            glColor3f(0.0, 0.0, 0.0);
            drawText(320, 30, "DDA Line from (50,50) to (400,250)");
            break;
        }
        case 2: { // Bresenham - Shallow slope (|m| < 1)
            glColor3f(1.0, 0.0, 0.0);
            drawLineBresenham(50, 100, 500, 250);
            glColor3f(0.0, 0.0, 0.0);
            drawText(250, 30, "Bresenham Line: |m| < 1 (shallow slope)");
            break;
        }
        case 3: { // Bresenham - Steep slope (|m| >= 1)
            glColor3f(1.0, 0.0, 0.0);
            drawLineBresenham(150, 50, 300, 500);
            glColor3f(0.0, 0.0, 0.0);
            drawText(250, 30, "Bresenham Line: |m| >= 1 (steep slope)");
            break;
        }
        case 4: { // Bresenham - Negative direction
            glColor3f(1.0, 0.0, 0.0);
            drawLineBresenham(600, 100, 150, 400);
            glColor3f(0.0, 0.0, 0.0);
            drawText(200, 30, "Bresenham Line with Reverse Direction");
            break;
        }
        case 5: { // Midpoint Circle
            glColor3f(0.0, 0.5, 0.0);
            drawCircleMidpoint(400, 300, 150);
            glColor3f(0.0, 0.0, 0.0);
            drawText(280, 30, "Midpoint Circle (center 400,300 r=150)");
            break;
        }
        case 6: { // Line Graph - DDA
            drawLineGraph(true);
            break;
        }
        case 7: { // Line Graph - Bresenham
            drawLineGraph(false);
            break;
        }
        case 8: { // Pie Chart
            drawPieChart();
            break;
        }
    }
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0); // Origin at top-left
    glPointSize(2.0);
}

void menu(int option) {
    currentAlgorithm = option;
    glutPostRedisplay();
}

void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("1. DDA Line", 1);
    glutAddMenuEntry("2. Bresenham Line (|m| < 1)", 2);
    glutAddMenuEntry("3. Bresenham Line (|m| >= 1)", 3);
    glutAddMenuEntry("4. Bresenham Line (Reverse)", 4);
    glutAddMenuEntry("5. Midpoint Circle", 5);
    glutAddMenuEntry("6. Line Graph (DDA)", 6);
    glutAddMenuEntry("7. Line Graph (Bresenham)", 7);
    glutAddMenuEntry("8. Pie Chart", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Raster Graphics Algorithms - Lab 2");
    
    init();
    createMenu();
    glutDisplayFunc(display);
    
    std::cout << "\n=== Raster Graphics Algorithms ===" << std::endl;
    std::cout << "Right-click to select algorithm:\n" << std::endl;
    std::cout << "1. DDA Line Drawing Algorithm" << std::endl;
    std::cout << "2. Bresenham Line (|m| < 1 - shallow slope)" << std::endl;
    std::cout << "3. Bresenham Line (|m| >= 1 - steep slope)" << std::endl;
    std::cout << "4. Bresenham Line (reverse direction)" << std::endl;
    std::cout << "5. Midpoint Circle Drawing Algorithm" << std::endl;
    std::cout << "6. Rasterized Line Graph using DDA" << std::endl;
    std::cout << "7. Rasterized Line Graph using Bresenham" << std::endl;
    std::cout << "8. Pie Chart" << std::endl;
    std::cout << "\n=================================\n" << std::endl;
    
    glutMainLoop();
    return 0;
}
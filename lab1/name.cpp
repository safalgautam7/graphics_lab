#include <GL/glut.h>

void init() {
    glClearColor(1, 1, 1, 1);   // White background
    glColor3f(0.1, 0.2, 0.8);   // Blue color for polygons
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1400, 0, 800); // 2D coordinate system
}

void drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ----- LETTER S -----
    drawRect(50, 400, 200, 450);   // draws top bar
    drawRect(50, 350, 100, 400);   // draws upper left
    drawRect(50, 300, 200, 350);   // draws middle bar
    drawRect(150, 250, 200, 300);  // draws lower right
    drawRect(50, 200, 200, 250);   // draws bottom bar

    // ----- LETTER A -----
    drawRect(250, 200, 300, 450);  // draws left bar
    drawRect(400, 200, 450, 450);  // draws right bar
    drawRect(250, 400, 450, 450);  // draws top bar
    drawRect(300, 300, 400, 350);  // draws middle bar

    // ----- LETTER F -----
    drawRect(500, 200, 550, 450);  // draws vertical bar
    drawRect(500, 400, 650, 450);  // draws top bar
    drawRect(500, 300, 600, 350);  // draws middle bar

    // ----- LETTER A (again) -----
    drawRect(700, 200, 750, 450);
    drawRect(850, 200, 900, 450);
    drawRect(700, 400, 900, 450);
    drawRect(750, 300, 850, 350);

    // ----- LETTER L -----
    drawRect(950, 200, 1000, 450); // vertical bar
    drawRect(950, 200, 1100, 250); // bottom bar

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("OpenGL - SAFAL Using Polygons");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

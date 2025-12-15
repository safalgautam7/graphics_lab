#include <GL/glut.h>
#include <iostream>

void display() {
    int screenW = glutGet(GLUT_SCREEN_WIDTH);
    int screenH = glutGet(GLUT_SCREEN_HEIGHT);

    std::cout << "Screen Resolution: " << screenW << " x " << screenH << std::endl;

    exit(0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Resolution Check");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

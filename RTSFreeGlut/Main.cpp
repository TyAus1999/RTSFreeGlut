#include <iostream>
#include "GL/glut.h"

void idleFunc() {

	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

void windowReshape(int x, int y) {
	//printf("x: %i, y: %i\n", x, y);
	glViewport(0, 0, x, y);
}

int main(int argv, char **args) {
	glutInit(&argv, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("RTS Test");
	glutIdleFunc(idleFunc);
	glutDisplayFunc(display);
	glutReshapeFunc(windowReshape);
	glutFullScreen();
	glutMainLoop();
	return 0;
}
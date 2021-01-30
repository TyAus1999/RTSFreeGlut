#include <iostream>
#include "GL/glut.h"
#include "unit.h"
#include <vector>
using namespace std;
typedef unsigned long long u64;


vector<unit> units;

void idleFunc() {
	for (int i = 0; i < units.size(); i++) {
		unit* u = &units[i];
		u->rotateAdd(0.5, 0);
		u->rotateAdd(0.5, 1);
	}
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	for (int i = 0; i < units.size(); i++) {
		unit* u = &units[i];
		//u->rotateAdd(1, 1);
		u->draw();
	}
	
	glutSwapBuffers();
}

void windowReshape(int x, int y) {
	//printf("x: %i, y: %i\n", x, y);
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (double)x/(double)y, 0.01, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

int main(int argv, char **args) {
	unit toAdd(0.0,0.0,0.0);
	toAdd.move(0, 0, -3);
	units.push_back(toAdd);
	
	glutInit(&argv, args);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutCreateWindow("RTS Test");
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GLUT_MULTISAMPLE);

	glutIdleFunc(idleFunc);
	glutDisplayFunc(display);
	glutReshapeFunc(windowReshape);
	//glutKeyboardFunc(keyboardFunc);
	//glutFullScreen();
	glutMainLoop();
	printf("Closing\n");
	return 0;
}
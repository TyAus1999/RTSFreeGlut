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
		u->rotateAdd(1, 0);
	}
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		for (int i = 0; i < units.size(); i++) {
			unit* u = &units[i];
			//u->rotateAdd(1, 1);
			u->draw();
		}
	glEnd();
	glutSwapBuffers();
}

void windowReshape(int x, int y) {
	//printf("x: %i, y: %i\n", x, y);
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

int main(int argv, char **args) {
	unit toAdd(-0.5,-0.5,0);
	units.push_back(toAdd);
	
	glutInit(&argv, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);
	glutCreateWindow("RTS Test");
	glEnable(GL_DEPTH_TEST);
	glEnable(GLUT_MULTISAMPLE);
	glMatrixMode(GL_PROJECTION);
	glutIdleFunc(idleFunc);
	glutDisplayFunc(display);
	glutReshapeFunc(windowReshape);
	//glutKeyboardFunc(keyboardFunc);
	glutFullScreen();
	glutMainLoop();
	cout << "Closing\n";
	return 0;
}
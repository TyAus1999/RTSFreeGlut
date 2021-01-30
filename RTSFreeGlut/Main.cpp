#include <iostream>
#include "GL/glut.h"
#include "unit.h"
#include <vector>
#include "Engine.h"
#include <chrono>
using namespace std;
typedef unsigned long long u64;


vector<unit> units;
Camera* currentCamera;
double camVel = -10;
u64 prevTime;

u64 getCurrentTimeMS() {
	u64 out = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return out;
}

void idleFunc() {
	u64 currentTime = getCurrentTimeMS();
	double deltaT=(double)currentTime-(double)prevTime;
	deltaT /= 1000;//Convert to seconds
	for (int i = 0; i < units.size(); i++) {
		unit* u = &units[i];
		//u->rotateAdd(0.5, 0);
		//u->rotateAdd(0.5, 1);
	}
	currentCamera->moveByVel(0,0,camVel,deltaT);
	if (currentCamera->coords[2] < -50 || currentCamera->coords[2] > -5) {
		camVel *= -1;
		currentCamera->moveByVel(0,0,camVel,deltaT);
	}
	prevTime = currentTime;
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	currentCamera->draw();
	//gluLookAt(5.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

	Camera c0(0, 5, -10);
	c0.lookingAt[1] = 0;

	currentCamera = &c0;

	char winName[] = "RTS Test\0";
	Engine e(winName, argv, args);
	e.setSize(500, 500);
	e.setDisplay(display);
	e.setIdle(idleFunc);
	e.setReshape(windowReshape);
	e.start();

	/*
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
	*/
	return 0;
}
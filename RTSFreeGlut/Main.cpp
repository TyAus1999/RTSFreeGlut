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
Engine* currentEngine;
double CameraVelocity=7;
double nCameraVelocity = -1 * CameraVelocity;
u64 prevTime;
int prevMouseX=0;
int prevMouseY=0;

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

	if (currentEngine->rightMouseDown) {
		int* mx = &currentEngine->mouseX;
		int* my = &currentEngine->mouseY;
		int diffX = *mx - prevMouseX;
		int diffY = *my - prevMouseY;

		if (diffX < 0)
			currentCamera->lookingAt[0] += 1;
		else if (diffX > 0)
			currentCamera->lookingAt[0] -= 1;
	}

	if (currentEngine->LeftShift) {
		double toUse = CameraVelocity*5;
		double nToUse = -1 * toUse;
		if (currentEngine->W)
			currentCamera->moveByVel(0, 0, toUse, deltaT);
		else if (currentEngine->S)
			currentCamera->moveByVel(0, 0, nToUse, deltaT);
		if (currentEngine->A)
			currentCamera->moveByVel(toUse, 0, 0, deltaT);
		else if (currentEngine->D)
			currentCamera->moveByVel(nToUse, 0, 0, deltaT);
	}
	else {
		if (currentEngine->W)
			currentCamera->moveByVel(0, 0, CameraVelocity, deltaT);
		else if (currentEngine->S)
			currentCamera->moveByVel(0, 0, nCameraVelocity, deltaT);
		if (currentEngine->A)
			currentCamera->moveByVel(CameraVelocity, 0, 0, deltaT);
		else if (currentEngine->D)
			currentCamera->moveByVel(nCameraVelocity, 0, 0, deltaT);
	}

	prevMouseX = currentEngine->mouseX;
	prevMouseY = currentEngine->mouseY;
	glutPostRedisplay();
}

void display() {
	u64 currentTime = getCurrentTimeMS();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	currentCamera->draw();
	//Draw Selection Box
	if (currentEngine->leftMouseDown) {
		glBegin(GL_QUADS);
			glColor3d(0, 1, 0);

		glEnd();
	}

	//Draw floor
	glBegin(GL_QUADS);
		glColor3d(0.7, 0.7, 0.7);
		glVertex3d(-100, 0, -100);
		glVertex3d(100, 0, -100);
		glVertex3d(100, 0, 100);
		glVertex3d(-100, 0, 100);
	glEnd();

	//==================
	for (int i = 0; i < units.size(); i++) {
		unit* u = &units[i];
		//u->rotateAdd(1, 1);
		u->draw();
	}
	prevTime = currentTime;
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

void keyDown(unsigned char c, int x, int y) {
	switch (c) {
	case 'W':
	case 'w':
		currentEngine->W = true;
		break;
	case 'A':
	case 'a':
		currentEngine->A = true;
		break;
	case 'S':
	case 's':
		currentEngine->S = true;
		break;
	case 'D':
	case 'd':
		currentEngine->D = true;
		break;
	case 'R':
	case 'r':
		currentCamera->resetLooking();
		break;
	}
}
void keyUp(unsigned char c, int x, int y) {
	switch (c) {
	case 'W':
	case 'w':
		currentEngine->W = false;
		break;
	case 'A':
	case 'a':
		currentEngine->A = false;
		break;
	case 'S':
	case 's':
		currentEngine->S = false;
		break;
	case 'D':
	case 'd':
		currentEngine->D = false;
		break;
	}
}
void sKeyUp(int key, int x, int y) {
	switch (key) {
	case 112:
		currentEngine->LeftShift = false;
		break;
	}
}
void sKeyDown(int key, int x, int y) {
	switch (key) {
	case 112:
		currentEngine->LeftShift = true;
		break;
	}
}
void mouseFunc(int button, int state, int x, int y) {
	bool s = (state) ? GLUT_DOWN : GLUT_UP;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		currentEngine->leftMouseDown = s;
		//printf("Left Mouse is %s\n", (s) ? "Up" : "Down");
		if (!s) {
			currentEngine->mouseXOnLeftMouse = x;
			currentEngine->mouseYOnLeftMouse = y;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		currentEngine->rightMouseDown = s;
		printf("Right Mouse is %s: %i\n", (s) ? "Down" : "Up",s);
		if (!s) {
			currentEngine->mouseXOnRightMouse = x;
			currentEngine->mouseYOnRightMouse = y;
		}
		break;
	}
}
void mouseMotion(int x, int y) {
	currentEngine->mouseX = x;
	currentEngine->mouseY = y;
}

int main(int argv, char **args) {
	unit toAdd(0.0,1,0.0);
	unit toAdd2(0, 1, 10);
	units.push_back(toAdd);
	units.push_back(toAdd2);

	Camera c0(0, 5, -10);
	c0.lookingAt[1] = 0;

	currentCamera = &c0;

	char winName[] = "RTS Test\0";
	Engine e(winName, argv, args);
	currentEngine = &e;
	e.setSize(500, 500);
	e.setDisplay(display);
	e.setIdle(idleFunc);
	e.setReshape(windowReshape);
	e.setKeyboardDown(keyDown);
	e.setKeyboardUp(keyUp);
	e.setSpecialDownKB(sKeyDown);
	e.setSpecialUpKB(sKeyUp);
	e.setMouse(mouseFunc);
	e.setMouseMotion(mouseMotion);
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
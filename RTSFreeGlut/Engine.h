#pragma once
#include "GL/freeglut.h"
#include "GL/glut.h"
#include <immintrin.h>

//Want to add multithreading, mutexs is for a task in the future
class Engine {
public:
	bool W, A, S, D;
	bool LeftShift=false;
	int mouseX=0;
	int mouseY=0;
	bool leftMouseDown = false;
	int mouseXOnLeftMouse = 0;
	int mouseYOnLeftMouse = 0;
	bool rightMouseDown = false;
	int mouseXOnRightMouse = 0;
	int mouseYOnRightMouse = 0;
	Engine(char *windowName, int argv, char **args) {
		glutInit(&argv, args);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);
		glutCreateWindow(windowName);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GLUT_MULTISAMPLE);

		glCullFace(GL_FRONT);
		W = false;
		A = false;
		S = false;
		D = false;
		glutReshapeFunc(Engine::Reshape3D);
	}
	void setSize(int w, int h) {
		glutReshapeWindow(w, h);
	}
	void setIdle(void (*idleFunc)(void)) {
		glutIdleFunc(idleFunc);
	}
	void setDisplay(void (*displayFunc)(void)) {
		glutDisplayFunc(displayFunc);
	}
	void setKeyboardDown(void (*kbd)(unsigned char, int, int)) {
		glutKeyboardFunc(kbd);
	}
	void setKeyboardUp(void (*kbu)(unsigned char, int, int)) {
		glutKeyboardUpFunc(kbu);
	}
	void setSpecialDownKB(void (*SKBD)(int, int, int)) {
		glutSpecialFunc(SKBD);
	}
	void setSpecialUpKB(void (*SKBU)(int, int, int)) {
		glutSpecialUpFunc(SKBU);
	}
	void setMouse(void (*mouseFunction)(int, int, int, int)) {
		glutMouseFunc(mouseFunction);
	}
	void setMouseMotion(void(*mouseMotion)(int, int)) {
		glutPassiveMotionFunc(mouseMotion);
	}
	void start() {
		glutMainLoop();
	}
private:
	static void Reshape3D(int w, int h) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, (double)w / (double)h, 0.01, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
};

class Camera {
public:
	double coords[4];
	double up[4];
	Camera(double x, double y, double z) {
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;

		lookingAt[0] = x;
		lookingAt[1] = y;
		lookingAt[2] = z + radius;

		up[0] = 0;
		up[1] = 1;
		up[2] = 0;

		for (char i = 0; i < 4; i++)
			rotations[i] = 0;
	}
	void moveByVel(double x, double y, double z, double deltaT) {
		double toAdd[4];
		toAdd[0] = x;
		toAdd[1] = y;
		toAdd[2] = z;
		toAdd[3] = 0;
		__m256d _velocities = _mm256_load_pd(toAdd);
		__m256d _deltaT = _mm256_broadcast_sd(&deltaT);
		__m256d _addAmount = _mm256_mul_pd(_velocities, _deltaT);
		this->moveToAdd(_addAmount);
	}

	void moveForward(double vel, double deltaT) {

	}

	void resetLooking() {
		lookingAt[0] = coords[0];
		lookingAt[1] = coords[1];
		lookingAt[2] = coords[2] + radius;
		
	}

	void draw() {
		/*glTranslated(coords[0], coords[1], coords[2]);
		glRotated(45, 1, 0, 0);
		glRotated(180, 0, 1, 0);*/

		/*glPushMatrix();
		glRotated(rotations[0], 1, 0, 0);
		glRotated(rotations[1], 0, 1, 0);
		glRotated(rotations[2], 0, 0, 1);*/
		gluLookAt(coords[0], coords[1], coords[2],
			lookingAt[0], lookingAt[1], lookingAt[2],
			up[0], up[1], up[2]);
		//glPopMatrix();
	}

	//Params in degrees
	void setRotation(double x, double y, double z) {
		rotations[0] = x;
		rotations[1] = y;
		rotations[2] = z;
		if (x) {
			double newX = radius * sin(x);
			lookingAt[0] = coords[0] + newX;
		}
		if (y) {
			double newY = radius * cos(y);
			lookingAt[1] = coords[1] + newY;
		}
	}

private:
	double radius = 5;
	double lookingAt[4];
	double rotations[4];
	void moveToAdd(__m256d _toAdd) {
		__m256d _coords, _lookingAt, _resultCoords, _resultLookingAt;
		_coords = _mm256_load_pd(coords);
		_lookingAt = _mm256_load_pd(lookingAt);
		_resultCoords = _mm256_add_pd(_toAdd, _coords);
		_resultLookingAt = _mm256_add_pd(_toAdd, _lookingAt);
		_mm256_store_pd(coords, _resultCoords);
		_mm256_store_pd(lookingAt, _resultLookingAt);
	}
};
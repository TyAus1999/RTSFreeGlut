#pragma once
#include <iostream>
#include <GL/glut.h>
typedef unsigned long long u64;
using namespace std;

struct face {
	double width;
	double height;
	int direction;
};

class unit {
public:
	unit() {
		x = 0;
		y = 0;
		z = 0;
		initColours();
		initRotation();
	}
	unit(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
		initColours();
		initRotation();
	}
	void draw() {
		glPushMatrix();
		glTranslated(x, y, z);
		glRotated(rotation[0], 1.0, 0.0, 0.0);
		glRotated(rotation[1], 0.0, 1.0, 0.0);
		glRotated(rotation[2], 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		
		//Front face
		glColor3d(0.5, 0.5, 0.5);
		glVertex3d(-1, 1, -1);
		glVertex3d(-1, -1, -1);
		glVertex3d(1, -1, -1);
		glVertex3d(1, 1, -1);

		//Backface
		glColor3d(1, 0.5, 0.5);
		glVertex3d(-1, -1, 1);
		glVertex3d(-1, 1, 1);
		glVertex3d(1, 1, 1);
		glVertex3d(1, -1, 1);

		//Right face
		glColor3d(0.5, 1, 0.5);
		glVertex3d(1, 1, -1);
		glVertex3d(1, -1, -1);
		glVertex3d(1, -1, 1);
		glVertex3d(1, 1, 1);

		//Left Face
		glColor3d(0.5, 0.5, 1);
		glVertex3d(-1, 1, -1);
		glVertex3d(-1, 1, 1);
		glVertex3d(-1, -1, 1);
		glVertex3d(-1, -1, -1);

		//Top Face
		glColor3d(1, 1, 0.5);
		glVertex3d(-1, 1, -1);
		glVertex3d(1, 1, -1);
		glVertex3d(1, 1, 1);
		glVertex3d(-1, 1, 1);

		//Bottom Face
		glColor3d(1, 0.5, 1);
		glVertex3d(-1, -1, -1);
		glVertex3d(-1, -1, 1);
		glVertex3d(1, -1, 1);
		glVertex3d(1, -1, -1);

		glEnd();
		glPopMatrix();
	}
	void move(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	//xyz
	//0=x, 1=y, 2=z
	void rotateAdd(double angle, int xyz) {
		if (xyz >= 0 && xyz < 3) {
			rotation[xyz] += angle;
			if (rotation[xyz] > 360)
				rotation[xyz] -= 360;
			else if (rotation[xyz] < 0)
				rotation[xyz] += 360;
		}
		else
			return;
	}

private:
	double x, y, z;
	double rotation[3];
	double colours[3];

	void initRotation() {
		for (int i = 0; i < 3; i++) {
			rotation[i] = 0;
		}
	}
	void initColours() {
		for (int i = 0; i < 3; i++)
			colours[i] = 0.6;
	}
};